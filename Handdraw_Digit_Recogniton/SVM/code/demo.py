import cv2

img = cv2.imread("/home/qian/Desktop/hw/SVM/data/Mnist-image/train/0/0_1.png")

print(img.shape)


img2 = cv2.imread("../data/Mnist-image/mytest/2.png")

print(img2.shape)

resize_img2 = cv2.resize(img2,(20,20))

print(resize_img2.shape)