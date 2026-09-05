import requests

def upload_image_and_label_to_server(image_path, label_path):
    url = 'http://8.152.218.172:5000/pest_images'
    with open(image_path, 'rb') as image_file, open(label_path, 'r', encoding='utf-8') as label_file:
        files = {
            'image': image_file,
            'label': label_file
        }
        response = requests.post(url, files=files)
        print(response.status_code, response.json())

# 示例调用
upload_image_and_label_to_server('detections/20250625_21-51-48.jpg', 'detections/20250625_21-51-48.txt')
