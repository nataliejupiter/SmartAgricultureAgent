from flask import Flask, request, jsonify
import os
import pymysql

app = Flask(__name__)

UPLOAD_FOLDER = 'pest_images'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# 上传图片接口
@app.route('/pest_images', methods=['POST'])
# 上传图片接口
def upload_image_and_label():
    # 上传图片接口
    image_file = request.files.get('image')
    if not image_file:
        return jsonify({'status': 'fail', 'reason': 'No file received'}), 400

    # 上传标签文件接口
    label_file = request.files.get("label")
    if not label_file:
        return jsonify({'status': 'fail', 'reason': 'No file received'}), 400


    # 保存图片到服务器
    image_filename = image_file.filename
    image_save_path = os.path.join(UPLOAD_FOLDER, image_filename)
    image_file.save(image_save_path)

    # 保存标签到服务器
    label_filename = label_file.filename
    label_save_path = os.path.join(UPLOAD_FOLDER, label_filename)
    label_file.save(label_save_path)

    """
    # 存入数据库路径
    conn = pymysql.connect(
        host='8.152.218.172',
        user='lily',
        password='lilylily',
        database='smartagr'
    )
    cursor = conn.cursor()
    image_relative_path = f"/{UPLOAD_FOLDER}/{image_filename}"
    # 数据库中只存图片的相对路径
    cursor.execute("INSERT INTO ImageBinFile VALUES (NUll, %s, %s, now())", (image_filename, image_relative_path))
    conn.commit()
    conn.close()
    """

    return jsonify({'status': 'success'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
