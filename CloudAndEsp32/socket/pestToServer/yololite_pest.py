import cv2
import numpy as np
import onnxruntime as ort
import time
import os
from datetime import datetime
from imagesPostClient import upload_image_and_label_to_server
import pymysql
import threading
import queue

def plot_one_box(x, img, color=None, label=None, line_thickness=None):
    """
    description: Plots one bounding box on image img,
                 this function comes from YoLov5 project.
    param: 
        x:      a box likes [x1,y1,x2,y2]
        img:    a opencv image object
        color:  color to draw rectangle, such as (0,255,0)
        label:  str
        line_thickness: int
        line_thickness: int
    return:
        no return
    """
    tl = (
        line_thickness or round(0.002 * (img.shape[0] + img.shape[1]) / 2) + 1
    )  # line/font thickness
    color = color or [random.randint(0, 255) for _ in range(3)]
    x=x.squeeze()
    c1, c2 = (int(x[0]), int(x[1])), (int(x[2]), int(x[3]))
    cv2.rectangle(img, c1, c2, color, thickness=tl, lineType=cv2.LINE_AA)
    if label:
        tf = max(tl - 1, 1)  # font thickness
        t_size = cv2.getTextSize(label, 0, fontScale=tl / 3, thickness=tf)[0]
        c2 = c1[0] + t_size[0], c1[1] - t_size[1] - 3
        cv2.rectangle(img, c1, c2, color, -1, cv2.LINE_AA)  # filled
        cv2.putText(
            img,
            label,
            (c1[0], c1[1] - 2),
            0,
            tl / 3,
            [225, 255, 255],
            thickness=tf,
            lineType=cv2.LINE_AA,
        )

def _make_grid( nx, ny):
        xv, yv = np.meshgrid(np.arange(ny), np.arange(nx))
        return np.stack((xv, yv), 2).reshape((-1, 2)).astype(np.float32)

def cal_outputs(outs,nl,na,model_w,model_h,anchor_grid,stride):
    
    row_ind = 0
    grid = [np.zeros(1)] * nl
    for i in range(nl):
        h, w = int(model_w/ stride[i]), int(model_h / stride[i])
        length = int(na * h * w)
        if grid[i].shape[2:4] != (h, w):
            grid[i] = _make_grid(w, h)

        outs[row_ind:row_ind + length, 0:2] = (outs[row_ind:row_ind + length, 0:2] * 2. - 0.5 + np.tile(
            grid[i], (na, 1))) * int(stride[i])
        outs[row_ind:row_ind + length, 2:4] = (outs[row_ind:row_ind + length, 2:4] * 2) ** 2 * np.repeat(
            anchor_grid[i], h * w, axis=0)
        row_ind += length
    return outs



def post_process_opencv(outputs,model_h,model_w,img_h,img_w,thred_nms,thred_cond):
    conf = outputs[:,4].tolist()
    c_x = outputs[:,0]/model_w*img_w
    c_y = outputs[:,1]/model_h*img_h
    w  = outputs[:,2]/model_w*img_w
    h  = outputs[:,3]/model_h*img_h
    p_cls = outputs[:,5:]
    if len(p_cls.shape)==1:
        p_cls = np.expand_dims(p_cls,1)
    cls_id = np.argmax(p_cls,axis=1)

    p_x1 = np.expand_dims(c_x-w/2,-1)
    p_y1 = np.expand_dims(c_y-h/2,-1)
    p_x2 = np.expand_dims(c_x+w/2,-1)
    p_y2 = np.expand_dims(c_y+h/2,-1)
    areas = np.concatenate((p_x1,p_y1,p_x2,p_y2),axis=-1)
    
    areas = areas.tolist()
    ids = cv2.dnn.NMSBoxes(areas,conf,thred_cond,thred_nms)
    if len(ids)>0:
        return  np.array(areas)[ids],np.array(conf)[ids],cls_id[ids]
    else:
        return [],[],[]
def infer_img(img0,net,model_h,model_w,nl,na,stride,anchor_grid,thred_nms=0.4,thred_cond=0.75):
    # 图像预处理
    img = cv2.resize(img0, [model_w,model_h], interpolation=cv2.INTER_AREA)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = img.astype(np.float32) / 255.0
    blob = np.expand_dims(np.transpose(img, (2, 0, 1)), axis=0)

    # 模型推理
    outs = net.run(None, {net.get_inputs()[0].name: blob})[0].squeeze(axis=0)

    # 输出坐标矫正
    outs = cal_outputs(outs,nl,na,model_w,model_h,anchor_grid,stride)

    # 检测框计算
    img_h,img_w,_ = np.shape(img0)
    boxes,confs,ids = post_process_opencv(outs,model_h,model_w,img_h,img_w,thred_nms,thred_cond)

    return  boxes,confs,ids

# 后台任务处理线程,做了将图片和标签上云和上传数据库的任务
def save_upload_worker():
    while True:
        task = task_queue.get()
        if task is None:
            break
        img, label_str, id_val = task
        try:
            now = datetime.now().strftime("%Y%m%d_%H-%M-%S")
            save_dir = "detections"
            os.makedirs(save_dir, exist_ok=True)
            img_path = os.path.join(save_dir, f"{now}.jpg")
            label_path = os.path.join(save_dir, f"{now}.txt")

            cv2.imwrite(img_path, img)
            with open(label_path, "w", encoding="utf-8") as f:
                f.write(label_str)

            upload_image_and_label_to_server(img_path, label_path)

            cursor = conn.cursor()
            image_relative_path = f"/pest_images/{img_path}"
            cursor.execute("INSERT INTO ImageBinFile VALUES (NULL, %s, %s, now())",
                           (dic_labels[id_val], image_relative_path))
            conn.commit()
        except Exception as e:
            print("异步任务处理出错：", e)
        finally:
            task_queue.task_done()


if __name__ == "__main__":
    last_save_time = 0 # 上次截图时间
    detected_start_time = None # 当前检测到的开始时间

    # 数据库信息
    conn = pymysql.connect(
        host='8.152.218.172',
        user='lily',
        password='lilylily',
        database='smartagr'
    )

    # 模型加载
    model_pb_path = "best_pest_03150.onnx"
    so = ort.SessionOptions()
    net = ort.InferenceSession(model_pb_path, so)
    
    # 标签字典
    dic_labels= {0:'rice_gall_midge',
            1:'grub',
            2:'mole_cricke'}
    
    # 模型参数
    model_h = 320
    model_w = 320
    nl = 3
    na = 3
    stride=[8.,16.,32.]
    anchors = [[10, 13, 16, 30, 33, 23], [30, 61, 62, 45, 59, 119], [116, 90, 156, 198, 373, 326]]
    anchor_grid = np.asarray(anchors, dtype=np.float32).reshape(nl, -1, 2)

    task_queue = queue.Queue()
    threading.Thread(target=save_upload_worker, daemon=True).start()

    video = 0
    cap = cv2.VideoCapture(video)
    flag_det = True
    while True:
        success, img0 = cap.read()
        if success:
            if flag_det:
                t1 = time.time()
                """
                det_boxes是所有检测框的坐标，scores是每个框的置信度，ids是每个框对应的类别ID，都是np.ndarray类型
                det_boxes是一个二维数组，边界框左边[x1，y1，x2，y2]
                scores是一个一维数组，对应每个检测框的置信度
                ids是类别的整数编号，代表模型判定这个目标属于哪一类
                thred_cond是置信度阈值
                thred_nms是非极大值抑制阈值，用于控制重叠框之间的去重程度
                """
                det_boxes,scores,ids = infer_img(img0,net,model_h,model_w,nl,na,stride,anchor_grid,thred_nms=0.4,thred_cond=0.75)
                t2 = time.time()

                current_time = time.time()

                if len(det_boxes) > 0:  # 检测到病虫害
                    for box, score, id in zip(det_boxes, scores, ids):
                        label = '%s:%.2f' % (dic_labels[id.item()], score)
                        plot_one_box(box.astype(np.int16), img0, color=(255, 0, 0), label=label, line_thickness=None)  # 画框

                    if detected_start_time is None:
                        detected_start_time = current_time # 第一次检测到，记录时间
                    # 如果持续检测超过一秒，并且距离上次保存时间也超过一秒
                    elif (current_time - detected_start_time >= 1) and (current_time - last_save_time >= 1):
                        label_str = f"检测到的害虫是：{dic_labels[id.item()]}\n置信度是：{score}\n时间是：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"
                        task_queue.put((img0.copy(), label_str, id.item()))
                        last_save_time = current_time
                        """
                        # 截图保存并上云,以下没有做多线程处理
                        now = datetime.now().strftime("%Y%m%d_%H-%M-%S")
                        save_dir = "detections"
                        os.makedirs(save_dir, exist_ok = True)
                        img_name = os.path.join(save_dir, f"{now}.jpg")
                        cv2.imwrite(img_name, img0) # 把内存中的图像数据写成一张实际的图片文件

                        label_name = os.path.join(save_dir, f"{now}.txt")
                        with open(label_name, "w", encoding="utf-8") as f:
                            f.write(f"检测到的害虫是：{dic_labels[id.item()]}\n置信度是：{score}\n时间是：{now}")

                        upload_image_and_label_to_server(img_name, label_name) #上传图片和标签到服务器

                        last_save_time = current_time

                        # 存入数据库
                        cursor = conn.cursor()
                        image_relative_path = f"/pest_images/{img_name}"
                        # 数据库中只存图片的相对路径
                        cursor.execute("INSERT INTO ImageBinFile VALUES (NUll, %s, %s, now())",
                                       (dic_labels[id.item()], image_relative_path))
                        conn.commit()
                        # conn.close()
                        """

                else:
                    detected_start_time = None # 如果这一帧没检测到，重置检测时间，重要！
                    
                str_FPS = "FPS: %.2f"%(1./(t2-t1))
                
                cv2.putText(img0,str_FPS,(50,50),cv2.FONT_HERSHEY_COMPLEX,1,(0,255,0),3)

            cv2.imshow("video",img0)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break

        elif key & 0xFF == ord('s'):#press s to start
            flag_det = not flag_det
            print(flag_det)

    cap.release()
    task_queue.put(None)
    task_queue.join()
    conn.close()
