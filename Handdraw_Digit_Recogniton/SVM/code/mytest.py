import cv2
import numpy as np
import joblib

def photo_process(img):
    # 先变成统一大小
    resized_img = cv2.resize(img,(20,20),interpolation=cv2.INTER_CUBIC)
    gray_img = cv2.cvtColor(resized_img,cv2.COLOR_BGR2GRAY)
    #gray_img = 255-gray_img
    normalized_img = np.round(gray_img / 255)
    cv2.imshow("origin",normalized_img)
    #cv2.waitKey(0)
    img_arr = normalized_img.reshape(1, -1)
    return img_arr

# 加载模型
model = joblib.load('../model/poly_ovo.model')

# 读取并预处理新的手写数字样本
image_path = '../data/Mnist-image/mytest/7_2.png'

img = cv2.imread(image_path)


img_arr = photo_process(img)

# 使用模型进行预测
prediction = model.predict(img_arr)

# 打印预测结果
print("预测结果为:", prediction)
