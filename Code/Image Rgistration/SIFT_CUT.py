#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import cv2
import random
import numpy as np
import matplotlib.pyplot as plt

img1=cv2.imread('//Users//apple//Desktop//paper//1.1.bmp',0)
img2=cv2.imread('//Users//apple//Desktop//paper//1.0.bmp',0)
sift = cv2.xfeatures2d.SIFT_create()
kp1, des1 = sift.detectAndCompute(img1,None)
kp2, des2 = sift.detectAndCompute(img2,None)

# create BFMatcher object
bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
# Match descriptors.
good = bf.match(des1,des2)
# Sort them in the order of their distance.
#good = sorted(good, key = lambda x:x.distance)
if len(good)>10:
    src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
    dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2) 
    M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
    matchesMask = mask.ravel().tolist()

    h,w = img1.shape
    pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
    dst = cv2.perspectiveTransform(pts,M)

    img2 = cv2.polylines(img2,[np.int32(dst)],True,255,3, cv2.LINE_AA) 
    good = sorted(good, key = lambda x:x.distance) 
    
    # Draw first 10 matches.  
    img3 = cv2.drawMatches(img1,kp1,img2,kp2,good[60:70],None,flags=2)

list_kp1 = []
list_kp2 = []
list1=[320.0]
# For each match...
for mat in good:

    # Get the matching keypoints for each of the images
    img1_idx = mat.queryIdx
    img2_idx = mat.trainIdx

    # x - columns
    # y - rows
    # Get the coordinates
    (x1, y1) = kp1[img1_idx].pt
    (x2, y2) = kp2[img2_idx].pt

    # Append to each list
    list_kp1.append((x1, y1))
    list_kp2.append((x2, y2))

list_kp3=[]
for m in range(len(list_kp2)):
    j = []
    list_kp3.append(j)
    for n in range(2):
            list_kp4=list_kp2[m][0]+list1[0] 
            j.append(list_kp4)
    list_kp3[m][1]=list_kp2[m][1]

#calculate the distance between two points
dis1=((((list_kp3[38][0] - list_kp1[38][0])**2) + ((list_kp3[38][1]-list_kp1[38][1])**2) )**0.5)
dis2=((((list_kp3[15][0] - list_kp1[15][0])**2) + ((list_kp3[15][1]-list_kp1[15][1])**2) )**0.5)
dis3=((((list_kp3[14][0] - list_kp1[14][0])**2) + ((list_kp3[14][1]-list_kp1[14][1])**2) )**0.5)
dis4=((((list_kp3[11][0] - list_kp1[11][0])**2) + ((list_kp3[11][1]-list_kp1[11][1])**2) )**0.5)
dis5=((((list_kp3[8][0] - list_kp1[8][0])**2) + ((list_kp3[8][1]-list_kp1[8][1])**2) )**0.5)
print(dis1,dis2,dis3,dis4,dis5)
dis_=[]
dis_f=[] 
kp1_f=[]
kp2_f=[]
kp3_f=[]


for i in range(len(list_kp3)):
    dis=((((list_kp3[i][0] - list_kp1[i][0])**2) + ((list_kp3[i][1]-list_kp1[i][1])**2) )**0.5)
    dis_.append(dis)
    if dis_[i]<324 and dis_[i]>318: 
        dis_f.append(dis_[i])
        kp1_f.append(list_kp1[i])
        kp3_f.append(list_kp3[i])


for m in range(len(kp3_f)):
       x = [] 
       kp2_f.append(x)
       for n in range(2):
           x.append(kp3_f)
       kp2_f[m][0]=kp3_f[m][0]-list1[0]
       kp2_f[m][1]=kp3_f[m][1]
dix_=[]
diy_=[]
dix_f=[]
diy_f=[]
for i in range(len(kp1_f)):
    dix=kp2_f[i][0]-kp1_f[i][0]
    diy=kp2_f[i][1]-kp1_f[i][1]
    dix_.append(dix)
    diy_.append(diy)
    if diy_[i]>-5 and diy_[i]<3 and dix_[i]>-2 and dix_[i]<5:
        dix_f.append(dix_[i])
        diy_f.append(diy_[i])
x_bias=(dix_f[0]+dix_f[1]+dix_f[2]+dix_f[3]+dix_f[4])/5
print(x_bias)
y_bias=(diy_f[0]+diy_f[1]+diy_f[2]+diy_f[3]+diy_f[4])/5
print(y_bias)
img1_=cv2.imread('//Users//apple//Desktop//paper//1.1.bmp',1)
img2_=cv2.imread('//Users//apple//Desktop//paper//1.0.bmp',1)
cropped1=img1_[1:240,0:319]
cropped2=img2_[0:239,1:320]
cv2.imshow('sift_keypoints.jpg',cropped1)
cv2.imshow('photo',cropped2) 
cv2.imwrite("//Users//apple//Desktop//img1.jpg",cropped1)
cv2.imwrite("//Users//apple//Desktop//img2.jpg",cropped2)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.waitKey(1)
