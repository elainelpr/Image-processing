# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import cv2
import numpy as np
A = cv2.imread("/Users/apple/Desktop/2.png")
#注意：为了使后面可以逐渐减半，这里的尺寸必须为2的次幂
A = cv2.resize(A,(256,256),interpolation=cv2.INTER_CUBIC) 
B = cv2.imread("/Users/apple/Desktop/3.png")
B = cv2.resize(B,(256,256),interpolation=cv2.INTER_CUBIC)
# generate Gaussian pyramid for A
G = A.copy()
gpA = [G]

for i in range(3):     #将苹果进行高斯金字塔处理，总共六级处理
    G = cv2.pyrDown(G)
    gpA.append(G)
# generate Gaussian pyramid for B
G = B.copy()
gpB = [G]
for i in range(3):  # #将橘子进行高斯金字塔处理，总共六级处理
    G = cv2.pyrDown(G)
    gpB.append(G)
# generate Laplacian Pyramid for A
lpA = [gpA[3]]               
for i in range(3,0,-1):    #将苹果进行拉普拉斯金字塔处理，总共5级处理
    GE = cv2.pyrUp(gpA[i])
    L = cv2.subtract(gpA[i-1],GE)
    lpA.append(L)
# generate Laplacian Pyramid for B
lpB = [gpB[3]]
for i in range(3,0,-1):    #将橘子进行拉普拉斯金字塔处理，总共5级处理,从5到0，不包括0.-1是步长
    GE = cv2.pyrUp(gpB[i])
    L = cv2.subtract(gpB[i-1],GE)
    lpB.append(L)
# Now add left and right halves of images in each level
#numpy.hstack(tup)
#Take a sequence of arrays and stack them horizontally
#to make a single array.
LS = []
for la,lb in zip(lpA,lpB):
    #rows,cols,dpt = la.shape
    rows,cols,dpt = la.shape
    a=la[:,:]
    b=lb[:,:]
    ls = cv2.addWeighted(a,0.5,b,0.5,0)    #将两个图像的矩阵的左半部分和右半部分拼接到一起
    LS.append(ls)
# now reconstruct
ls_ = LS[0]   #这里LS[0]为高斯金字塔的最小图片
for i in range(1,4):                        #第一次循环的图像为高斯金字塔的最小图片，依次通过拉普拉斯金字塔恢复到大图像
    ls_ = cv2.pyrUp(ls_)
    ls_ = cv2.add(ls_, LS[i])                #采用金字塔拼接方法的图像
# image with direct connecting each half
#real = np.hstack((A[:,:cols//2],B[:,cols//2:]))   #直接的拼接
real=cv2.add(A,B)
#cv2.imwrite('Pyramid_blending2.jpg',ls_)
#cv2.imwrite('Direct_blending.jpg',real)
cv2.imshow("LS",ls_)
cv2.imshow("Real",real)
#cv2.imwrite("C:\\Users\\123\\Desktop\\opencv\\add.jpg",ls_)
#cv2.imwrite("C:\\Users\\123\\Desktop\\opencv\\real.jpg",real)
cv2.waitKey()  
cv2.destroyAllWindows()


'''
import cv2
 
img1=cv2.imread("/Users/apple/Desktop/1.png")  #读取图片1
img1 = cv2.resize(img1,(256,256),interpolation=cv2.INTER_CUBIC) 
img2=cv2.imread("/Users/apple/Desktop/2.png")   #读取图片2
img2 = cv2.resize(img2,(256,256),interpolation=cv2.INTER_CUBIC)

 
dst1=cv2.addWeighted(img1,0.5,img2,0.5,0)
cv2.imshow("dst1",dst1)
 
cv2.waitKey(0)
cv2.destroyAllWindows()
'''

