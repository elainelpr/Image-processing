#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#Brute-Force matcher is simple. It takes the descriptor of one feature in first set 
#and is matched with all other features in second set using some distance calculation. 
#And the closest one is returned.
import cv2
import random
import numpy as np
import matplotlib.pyplot as plt

img1 = cv2.imread('//Users//apple//Desktop//paper//1.1.jpg',0)
img2 = cv2.imread('//Users//apple//Desktop//paper//1.0.bmp',0) 
sift = cv2.xfeatures2d.SIFT_create()
kp1, des1 = sift.detectAndCompute(img1,None)
kp2, des2 = sift.detectAndCompute(img2,None)

# create BFMatcher object
bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)
# Match descriptors.
good = bf.match(des1,des2)
# Sort them in the order of their distance.
good = sorted(good, key = lambda x:x.distance)

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
img3 = cv2.drawMatches(img1,kp1,img2,kp2,good[61:80],None,flags=2)

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
print(dis1,dis2,dis3,dis4)
print((dis1+dis2+dis3+dis4+dis5)/5)
dis_=[]
dis_f=[] 
kp1_f=[]
kp2_f=[]
kp3_f=[]


for i in range(len(list_kp3)):
    dis=((((list_kp3[i][0] - list_kp1[i][0])**2) + ((list_kp3[i][1]-list_kp1[i][1])**2) )**0.5)
    dis_.append(dis)
    if dis_[i]<325 and dis_[i]>315: 
        dis_f.append(dis_[i])
        kp1_f.append(list_kp1[i])
        kp3_f.append(list_kp3[i])





cv2.imshow('sift_keypoints.jpg',img3) 
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.waitKey(1)

