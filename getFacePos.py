import cv2
#import matplotlib library
import matplotlib.pyplot as plt
#importing time library for speed comparisons of both classifiers
import time 


import qi
import argparse
import sys
import time
import Image

# Remember:
# PYTHONPATH=${PYTHONPATH}:${PWD}
# for site and dist packages


def convertToRGB(img):
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def get_NAO_image(session):
    """
    First get an image, then show it on the screen with PIL.
    """
    # Get the service ALVideoDevice.

    video_service = session.service("ALVideoDevice")
    resolution = 2    # VGA
    colorSpace = 11   # RGB

    videoClient = video_service.subscribe("python_client", resolution, colorSpace, 5)

    t0 = time.time()

    # Get a camera image.
    # image[6] contains the image data passed as an array of ASCII chars.
    naoImage = video_service.getImageRemote(videoClient)

    t1 = time.time()

    # Time the image transfer.
    print "acquisition delay ", t1 - t0

    video_service.unsubscribe(videoClient)


    # Now we work with the image returned and save it as a PNG  using ImageDraw
    # package.

    # Get the image size and pixel array.
    imageWidth = naoImage[0]
    imageHeight = naoImage[1]
    array = naoImage[6]
    image_string = str(bytearray(array))

    # Create a PIL Image from our pixel array.
    im = Image.frombytes("RGB", (imageWidth, imageHeight), image_string)

    # Save the image.
    im.save("camImage.png", "PNG")

    #im.show()



def detect_faces(f_cascade, colored_img, scaleFactor = 1.05):
    #just making a copy of image passed, so that passed image is not changed
    img_copy = colored_img.copy()
    #convert the test image to gray image as opencv face detector expects gray images
    gray = cv2.cvtColor(img_copy, cv2.COLOR_BGR2GRAY)
    #let's detect multiscale (some images may be closer to camera than others) images
    faces = f_cascade.detectMultiScale(gray, scaleFactor=scaleFactor, minNeighbors=5);
    #go over list of faces and draw them as rectangles on original colored img
    #for (x, y, w, h) in faces:
    #    cv2.rectangle(img_copy, (x, y), (x+w, y+h), (0, 255, 0), 2)
    return img_copy, faces

def update_image(ip, port):
    #parser = argparse.ArgumentParser()
    #parser.add_argument("--ip", type=str, default="127.0.0.1",
                        #help="Robot IP address. On robot or Local Naoqi: use '127.0.0.1'.")
    #parser.add_argument("--port", type=int, default=9559,
                        #help="Naoqi port number")

    #args = parser.parse_args()
    session = qi.Session()
    try:
        session.connect("tcp://" + ip + ":" + str(port))
    except RuntimeError:
        print ("Can't connect to Naoqi at ip \"" + ip + "\" on port " + str(port) +".\n"
               "Please check your script arguments. Run with -h option for help.")
        sys.exit(1)
    get_NAO_image(session)

def getFacePos(ip = "192.168.0.103", port = 9559):
    
    update_image(ip, port)
    
    face_cascade = cv2.CascadeClassifier('data/lbpcascade_frontalface.xml')
    #load test iamge
    test1 = cv2.imread('camImage.png')

    faces_detected_img, face_data = detect_faces(face_cascade, test1)
    if len(face_data) == 0:
		return (None, None)
    #print the number of faces found
    #print('Faces found: ', len(face_data))
    
    current_area = 0
    output = 0
    for i in face_data:
        if i[2]*i[3]>current_area:
            current_area = i[2]*i[3]
            largest_face = i
    
    height, width = faces_detected_img.shape[:2]
    #print(width, height, largest_face)
    #72.6degDFOV (60.9degHFOV,47.6degVFOV)
    #http://doc.aldebaran.com/2-5/family/robots/video_robot.html
    HFOV = 60.9
    VFOV = 47.6
    x_cent = width/2
    y_cent = height/2
    x_rot = (largest_face[0]-float(x_cent))/float(x_cent)
    y_rot = (largest_face[1]-float(y_cent))/float(y_cent)
    
    h_fudge = 1
    v_fudge = 1
    
    return (x_rot*h_fudge*HFOV/2, y_rot*v_fudge*VFOV/2)
        

    #plt.imshow(convertToRGB(faces_detected_img))
    #plt.show()

#print(getFacePos())
