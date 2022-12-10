#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import cv2
import numpy as np
#import pandas as pd
 
img1 = cv2.imread('//Users//apple//Desktop//paper//img//2.png')
img2 = cv2.imread('//Users//apple//Desktop//paper//img//3.png') 
img2 = cv2.resize(img2,(344,252),interpolation=cv2.INTER_CUBIC) 


image = np.concatenate((img1, img2),axis=1) 



list1=[326.0]
ptStart1 = (183, 55)
ptEnd1 = (522, 56)
point_color1 = (0, 255, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart1, ptEnd1, point_color1, thickness, lineType)

ptStart2 = (177, 22)
ptEnd2 = (505, 38)
point_color2 = (255, 0, 0) # BGR
cv2.line(image, ptStart2, ptEnd2, point_color2, thickness, lineType)

ptStart3 = (150, 89)
ptEnd3 = (486, 91)
point_color3 = (0, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart3, ptEnd3, point_color3, thickness, lineType)

ptStart4 = (280, 60)
ptEnd4 = (632, 75)
point_color4= (14, 212, 124) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart4, ptEnd4, point_color4, thickness, lineType)

ptStart5 = (220, 70)
ptEnd5 = (507, 68)
point_color5 = (159, 134, 167) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart5, ptEnd5, point_color5, thickness, lineType)

ptStart6 = (243, 120)
ptEnd6 = (578, 117)
point_color6 = (0, 255, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart6, ptEnd6, point_color6, thickness, lineType)

ptStart7 = (187, 52)
ptEnd7 = (488, 54)
point_color7 = (90, 100, 190) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart7, ptEnd7, point_color7, thickness, lineType)

ptStart8 = (170, 52)
ptEnd8 = (490, 51)
point_color8 = (255, 0, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart8, ptEnd8, point_color8, thickness, lineType)

ptStart9 = (303, 120)
ptEnd9 = (615, 43)
point_color9 = (255, 0, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart9, ptEnd9, point_color9, thickness, lineType)

ptStart10 = (301, 172)
ptEnd10 = (622, 71)
point_color10 = (255, 255, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart10, ptEnd10, point_color10, thickness, lineType)

ptStart11 = (249, 204)
ptEnd11 = (503, 8)
point_color11 = (255, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart11, ptEnd11, point_color11, thickness, lineType)




cv2.imshow("//Users//apple//Desktop//img2.jpg",image)

cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.waitKey(1)
