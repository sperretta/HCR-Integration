# -*- encoding: UTF-8 -*-

import sys
from naoqi import ALProxy
import time
import almath

class Eyecontrol:	
    def __init__(self,ip):
        try:
            self.proxy = ALProxy("ALLeds", ip, 9559)
        except Exception,e:
            print "Could not create proxy to ALLeds"
            print "Error was ",e
            sys.exit(1)
			
    def ledreset(self):
        self.proxy.reset('FaceLeds')
        return
		
    def ledoff(self):
        self.proxy.off('FaceLeds')
        return
		
    def ledon(self):
        self.proxy.on('FaceLeds')
        return
		
    def ledrotate(self,rgb,timeForRotation,totalDuration):
        self.proxy.rotateEyes(rgb,timeForRotation,totalDuration)
        return
		
    def ledfade(self,intensity,duration):
        self.proxy.fade('FaceLeds', intensity, duration)
        return
		
    def ledcolour(self,colorName, duration):
        self.proxy.fadeRGB('FaceLeds', colorName, duration)
        return
		
	    

if __name__ == "__main__":
    robotIp = "127.0.0.1"

    if len(sys.argv) <= 1:
        print "Usage python eye_led.py IP"
    else:
        robotIp = sys.argv[1]
	
    eye = Eyecontrol(robotIp)
    eye.ledoff()
    time.sleep(2)
    eye.ledon()
    time.sleep(2)
    eye.ledrotate(000255000,0.5,2)
    eye.ledfade(0.5,5)
    eye.ledcolour(000000255,2)
    time.sleep(2)
    eye.ledreset()
	
    #main(robotIp, pitch, roll)
