import keyboard as kb

import pyautogui

import easyocr

import cv2 as cv
import numpy as np
import copy

import config

# before go ahead, you have to firstly specify a picture path, 
# like, 'data\deepth\pic\0.jpg'
# open it in ms-paint.
# then in ms-paint, you can ctrl+l to see values the mouse points

pth = config.pth

pth = r'D:\workplace\geoproject\pictureproject\data\deepth\cleanedOutputpic\1.png'


reader = easyocr.Reader(['ch_sim','en'])

img = cv.imread( pth )

print('start by ctrl+l to get pixel values')
while True:
    if kb.is_pressed("ctrl+l"):

        myScreenshot = pyautogui.screenshot()
        myScreenshot.save(r'D:\workplace\geoproject\pictureproject\data\dustbin\abc.png')

        cropped_img = myScreenshot.crop( (100,1050,100+140,1050+30))
        cropped_img.save(r'D:\workplace\geoproject\pictureproject\data\dustbin\xyz.png')
        print('saved image')

        # 创建reader对象
        # 读取图像
        result = reader.readtext(r'D:\workplace\geoproject\pictureproject\data\dustbin\xyz.png')

        xy = result[-1][-2].split(',')
        x = int( xy[0] )
        y = int( xy[-1][0:-2] )
        print(x,y)

        print(img[y,x,:])

        
