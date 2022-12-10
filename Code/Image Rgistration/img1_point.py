#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import cv2
import numpy as np
#import pandas as pd
 
img1 = cv2.imread('//Users//apple//Desktop//paper//1.1.jpg')
img2 = cv2.imread('//Users//apple//Desktop//paper//1.0.bmp') 
#====using numpy array and concatenate======

image = np.concatenate((img1, img2),axis=1) 


#=============
ptStart1 = (246, 98)
ptEnd1 = (565, 94)
point_color1 = (0, 255, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart1, ptEnd1, point_color1, thickness, lineType)

ptStart2 = (120, 105)
ptEnd2 = (439, 105)
point_color2 = (255, 0, 0) # BGR
cv2.line(image, ptStart2, ptEnd2, point_color2, thickness, lineType)

ptStart3 = (120, 95)
ptEnd3 = (439, 97)
point_color3 = (0, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart3, ptEnd3, point_color3, thickness, lineType)

ptStart4 = (112, 109)
ptEnd4 = (434, 110)
point_color4= (14, 212, 124) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart4, ptEnd4, point_color4, thickness, lineType)

ptStart5 = (301, 70)
ptEnd5 = (624, 68)
point_color5 = (159, 134, 167) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart5, ptEnd5, point_color5, thickness, lineType)

ptStart6 = (301, 211)
ptEnd6 = (628, 211)
point_color6 = (0, 255, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart6, ptEnd6, point_color6, thickness, lineType)

ptStart7 = (271, 159)
ptEnd7 = (613, 151)
point_color7 = (90, 100, 190) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart7, ptEnd7, point_color7, thickness, lineType)

ptStart8 = (35, 190)
ptEnd8 = (355, 190)
point_color8 = (255, 0, 0) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart8, ptEnd8, point_color8, thickness, lineType)

ptStart9 = (50, 200)
ptEnd9 = (372, 200)
point_color9 = (255, 230, 87) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart9, ptEnd9, point_color9, thickness, lineType)

ptStart10 = (10, 240)
ptEnd10 = (332, 242)
point_color10 = (0, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart10, ptEnd10, point_color10, thickness, lineType)

ptStart11 = (33,153)
ptEnd11 = (355, 163)
point_color11 = (255, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart11, ptEnd11, point_color11, thickness, lineType)

ptStart12 = (222, 156)
ptEnd12 = (526, 71)
point_color12 = (0, 255, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart12, ptEnd12, point_color12, thickness, lineType)

ptStart13 = (64, 57)
ptEnd13 = (331, 228)
point_color13 = (0, 0, 255) # BGR
thickness = 1 
lineType = 4
cv2.line(image, ptStart13, ptEnd13, point_color13, thickness, lineType)



cv2.imshow('image', image)
cv2.imwrite("//Users//apple//Desktop//img1.jpg",image)
cv2.waitKey(0) 
cv2.destroyAllWindows()
cv2.waitKey(1)
