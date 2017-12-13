#!/usr/bin/env python
import cv2
import numpy as np
import ConfigParser
import json
import zbar
import Image

from skimage.transform import ProjectiveTransform

import capture_picture

def find_markers(img):
    
    global Config 
    
    Config = ConfigParser.ConfigParser()
    Config.read("mask_config.ini")
    
    red_col = [ConfigSectionMap("red")['red'], ConfigSectionMap("red")['green'], ConfigSectionMap("red")['blue']] 
    
    blue_col = [ConfigSectionMap("blue")['red'], ConfigSectionMap("blue")['green'], ConfigSectionMap("blue")['blue']]
    
    red_blobs = find_blob(img, red_col[0], red_col[1], red_col[2], True) ##Red blobs
    blue_blobs = find_blob(img, blue_col[0], blue_col[1], blue_col[2], True) ##Blue V1
    
    #for i in blue_blobs:
    #    print  "Blue found of size", i.size, "Loc: ", i.pt
    #for i in red_blobs:
    #    print  "Red found of size", i.size, "Loc: ", i.pt
    
    return red_blobs, blue_blobs
 
def find_blob(img, red, green, blue, INVERT = True):
    color = np.uint8([[[blue, green, red]]])
    hsv_color = cv2.cvtColor(color, cv2.COLOR_BGR2HSV)
    
    hue = hsv_color[0][0][0]
    #print "Hue is: ", hue
    
    delta = int(ConfigSectionMap("general")['delta']) #From config file?
    
    hue_max = hue + delta
    hue_min = hue - delta
    
    if hue_max >255:
        hue_max = 255
    elif hue_min< 0:
        hue_min = 0

    lower_range = np.array([hue_min, 100, int(ConfigSectionMap("general")['mask_depth_lower'])], dtype=np.uint8)
    upper_range = np.array([hue_max, 255, int(ConfigSectionMap("general")['mask_depth_upper'])], dtype=np.uint8)
    
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    
    mask = cv2.inRange(hsv, lower_range, upper_range)
    
    cv2.imwrite('mask.jpg',mask)
    
    if INVERT:
        im = cv2.bitwise_not(mask)
    else:
        im = mask
    
    k_depth = int(ConfigSectionMap("general")['kd_m'])
    
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(k_depth,k_depth))
    im = cv2.morphologyEx(im,cv2.MORPH_OPEN,kernel)
    
    k_depth_g = int(ConfigSectionMap("general")['kd_g'])

    kernel = np.ones((k_depth_g,k_depth_g),np.float32)/k_depth_g*k_depth_g #Can be messed around with to smooth further

    im = cv2.filter2D(im, -1, kernel)

    params = cv2.SimpleBlobDetector_Params()
    
    
    # Change thresholds
    #params.minThreshold = 10;
    #params.maxThreshold = 200;
    
    # Filter by Area.
    params.filterByArea = True
    params.minArea = int(ConfigSectionMap("general")['min_size_blob'])
    params.maxArea = int(ConfigSectionMap("general")['max_size_blob'])
    
    # Filter by Circularity
    params.filterByCircularity = True
    params.minCircularity = float(ConfigSectionMap("general")['circularity'])
    params.maxCircularity = 1
    
    # Filter by Convexity
    params.filterByConvexity = False
    params.minConvexity = float(ConfigSectionMap("general")['convexity'])
    
    # Filter by Inertia
    params.filterByInertia = False
    params.minInertiaRatio = float(ConfigSectionMap("general")['inerita_ratio']) 

    # Set up the detector with default parameters.
    detector = cv2.SimpleBlobDetector_create(params)
 
    # Detect blobs.
    keypoints = detector.detect(im)
 
    # Draw detected blobs as red circles.
    #cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS ensures the size of the circle corresponds to the size of blob
    
    #if (int(ConfigSectionMap("general")['debug']) == 1):
    #    # Show keypoints
    #    im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    #    view_img(im_with_keypoints)


    return keypoints

def key_2_str(keypoints):
    k = []
    for i in keypoints:
        k.append(i.pt)
    return str(k)


def view_img(img):
    cv2.imshow('image',img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
def ConfigSectionMap(section):
    dict1 = {}
    options = Config.options(section)
    for option in options:
        try:
            dict1[option] = Config.get(section, option)
            if dict1[option] == -1:
                DebugPrint("skip: %s" % option)
        except:
            print("exception on %s!" % option)
            dict1[option] = None
    return dict1



def readBoard(cam_loc = "/dev/video0"):
    #Get image
    
    #cam = cv2.VideoCapture(cam_loc)   # 0 -> index of camera
    #s, img = cam.read()
    #if s:    # frame captured without any errors
        ##cv2.namedWindow("cam-test")
        ##cv2.imshow("cam-test",img)
        ##cv2.waitKey(0)
        ##cv2.destroyWindow("cam-test")
        #cv2.imwrite("exboard_web.jpg",img) #save image
    #else:
        #print("Couldn't connect to camera - using most recent image")
    
    #img = Image.open("exboard_web.jpg")
    #img = img.rotate(90, expand=True)
    #img.save("exboard_web.jpg")
    ## We now have a image to work with
    img_filename = 'exboard_web.jpg'

    capture_picture.get_img(cam_loc, img_filename)
    
    
    img = cv2.imread(img_filename, 1)
    
    ## Search for blobs
    blob_data = find_markers(img)
    
    ## Search for QR codes
    #qr_data = read_qr(img_filename)

    ### Get board position from QR data
    #board_loc = {} #ul, ur, ll, lr
    #for symbol in qr_data:
        ##print(symbol.location)
        #location_x, location_y = 0, 0
        
        #for i in symbol.location:
            #location_x += i[0]
            #location_y += i[1]
        #location_x = location_x/4
        #location_y = location_y/4
        ##print("QR Found: ",location_x, location_y, symbol.data)
        #board_loc[symbol.data] = [location_x, location_y]
    
    blue_blobs = []

    #Uncomment here for recalibration
    for i in blob_data[1]:
        print  "Blue found of size", i.size, "Loc: ", i.pt
        blue_blobs.append(i.pt)
    
    
    
    return blue_blobs

print "#################################"
print "         M0ZJO Inc.              "
print "#################################"
print " 'A calibration process so easy"
print " a robot could do it!'"

device = "/dev/video0"

print "\nPlease ensure that the camera is located at %s"%(device)
print "If not please change the device name"

print "\n\nPlease put a BLUE token on the bottom left of the board and press enter when complete"
raw_input("Press enter")

bl = readBoard(device)

print "\n\nPlease put a BLUE token on the top left of the board and press enter when complete"
raw_input("Press enter")

tl = readBoard(device)

print "\n\nPlease put a BLUE token on the top right of the board and press enter when complete"
raw_input("Press enter")

tr = readBoard(device)

print "\n\nPlease put a BLUE token on the bottom right of the board and press enter when complete"
raw_input("Press enter")

br = readBoard(device)

output = """
[marker_calibration]
bl_x: %f
bl_y: %f
tl_x: %f
tl_y: %f
tr_x: %f
tr_y: %f
br_x: %f
br_y: %f
"""
print "############## Data Output #################"
print "The following data will be inserted into the [marker_calibration] section of marker_config.ini\n\n"
out = output%(bl[0][0], bl[0][1], tl[0][0], tl[0][1], tr[0][0], tr[0][1], br[0][0], br[0][1])
print out, "\n \n \n"
print "Writing to file"

file_out = open("marker_config.ini", "w")
file_out.write(out)
file_out.close()

print "Written to file" 
