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
    global ConfigMarker  
    
    Config = ConfigParser.ConfigParser()
    Config.read("mask_config.ini")

    ConfigMarker = ConfigParser.ConfigParser()
    ConfigMarker.read("marker_config.ini")
    
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
    
    if (int(ConfigSectionMap("general")['debug']) == 1):
        # Show keypoints
        im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        view_img(im_with_keypoints)


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

    
def ConfigSectionMapMarker(section):
    dict1 = {}
    options = ConfigMarker.options(section)
    for option in options:
        try:
            dict1[option] = ConfigMarker.get(section, option)
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
    red_blobs = []
    #Uncomment here for recalibration
    for i in blob_data[1]:
        print  "Blue found of size", i.size, "Loc: ", i.pt
        blue_blobs.append(i.pt)
    for i in blob_data[0]:
        print  "Red found of size", i.size, "Loc: ", i.pt
        red_blobs.append(i.pt)
    
    # We now have all required data
    # https://stackoverflow.com/questions/33283088/transform-irregular-quadrilateral-to-rectangle-in-python-matplotlib
    
    # These could be manually configured at the start of a run for better peformance
    bottom_left =  [float(ConfigSectionMapMarker("marker_calibration")['bl_x']), float(ConfigSectionMapMarker("marker_calibration")['bl_y'])] 
    top_left =     [float(ConfigSectionMapMarker("marker_calibration")['tl_x']), float(ConfigSectionMapMarker("marker_calibration")['tl_y'])]
    top_right =    [float(ConfigSectionMapMarker("marker_calibration")['tr_x']), float(ConfigSectionMapMarker("marker_calibration")['tr_y'])]
    bottom_right = [float(ConfigSectionMapMarker("marker_calibration")['br_x']), float(ConfigSectionMapMarker("marker_calibration")['br_y'])]
    
    x_range = 0
    y_range = 0
    
    px_minmax = [0, 8] ## This will need calibrating...
    py_minmax = [0, 4]
    
    t = ProjectiveTransform() #set up transform
    

    #print("QR Codes not in use for calibration - using given values.")
    #print([bottom_left, top_left, top_right, bottom_right])
    #bottom_left = bl
    #top_left = tl
    #top_right = tr
    #bottom_right = br
        
    
    dst = np.asarray([[px_minmax[0], py_minmax[0]], [px_minmax[0], py_minmax[1]], [px_minmax[1], py_minmax[1]], [px_minmax[1], py_minmax[0]]]) ## What we want to transform to
    src = np.asarray([[bottom_left[0], bottom_left[1]], [top_left[0], top_left[1]], [top_right[0], top_right[1]], [bottom_right[0], bottom_right[1]]])
    if not t.estimate(src, dst): raise Exception("estimate failed") # If things break here I'm not sure what to do

    # We now use nearest neighbour "Snap to grid"
    blue_blobs_t = []
    for i in blue_blobs:
        z = t(np.asarray([np.asarray(i)]))
        z = np.round(z)
        blue_blobs_t.append([int(z[0][0]), int(z[0][1])])
        
    red_blobs_t = []
    for i in red_blobs:
        z = t(np.asarray([np.asarray(i)]))
        z = np.round(z)
        red_blobs_t.append([int(z[0][0]), int(z[0][1])])
    #print(blue_blobs, red_blobs)
    #print(blue_blobs_t, red_blobs_t)
    
    # Set outputs to correct value 0=none, 1=blue, 2=red
    output= [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    #print("LEN:", len(output))
    # Map values
    for i in blue_blobs_t:
       output[36+i[0]-9*i[1]] = 1
    
    for i in red_blobs_t:
       output[36+i[0]-9*i[1]] = 2

    return output

#data = readBoard("/dev/video0")

#data_out =  ",".join(str(i) for i in data)
#print type(data_out)
#print data_out
