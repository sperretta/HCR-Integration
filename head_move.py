# -*- encoding: UTF-8 -*-

import sys
from naoqi import ALProxy
import time
import almath

class Headmovement:	
    def __init__(self,ip):
        try:
            self.motionProxy = ALProxy("ALMotion", ip, 9559)
        except Exception,e:
            print "Could not create proxy to ALMotion"
            print "Error was: ",e
            sys.exit(1)

    def movehead(self, pitch, yaw):

        self.motionProxy.setStiffnesses("Head", 1.0)
        
        self.motionProxy.setAngles("HeadPitch",int(pitch)*almath.TO_RAD,0.1)
        self.motionProxy.setAngles("HeadYaw",int(yaw)*almath.TO_RAD,0.1)
        time.sleep(2)

        self.motionProxy.setStiffnesses("Head", 0.0)
        return
		
    def head_nod(self):
	
        self.motionProxy.setStiffnesses("Head", 1.0)
	
        self.motionProxy.setAngles("HeadYaw",0,0.15)
        self.motionProxy.setAngles("HeadPitch",20.0*almath.TO_RAD,0.1)
        time.sleep(0.5)
        self.motionProxy.setAngles("HeadPitch",-20.0*almath.TO_RAD,0.1)
        time.sleep(1.0)
        self.motionProxy.setAngles("HeadPitch",20.0*almath.TO_RAD,0.1)
        time.sleep(1.0)
        self.motionProxy.setAngles("HeadPitch",-20.0*almath.TO_RAD,0.1)
        time.sleep(1.0)	
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(1.0)
	
        self.motionProxy.setStiffnesses("Head", 0.0)
        return
	
    def head_shake(self):
	    
        self.motionProxy.setStiffnesses("Head", 1.0)
	
        self.motionProxy.setAngles("HeadPitch",10.0*almath.TO_RAD,0.05)
        time.sleep(0.2)
        self.motionProxy.setAngles("HeadYaw",-20.0*almath.TO_RAD,0.2)
        time.sleep(0.4)
        self.motionProxy.setAngles("HeadYaw",20.0*almath.TO_RAD,0.2)
        time.sleep(0.4)
        self.motionProxy.setAngles("HeadYaw",-20.0*almath.TO_RAD,0.2)
        time.sleep(0.4)	
        self.motionProxy.setAngles("HeadYaw",0,0.15)
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(0.8)
		
        self.motionProxy.setStiffnesses("Head", 0.0)
        return
	
    def head_sweep(self):
	
        self.motionProxy.setStiffnesses("Head", 1.0)

        self.motionProxy.setAngles("HeadYaw",30.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",10.0*almath.TO_RAD,0.05)
        time.sleep(1.5)
        self.motionProxy.setAngles("HeadYaw",-30.0*almath.TO_RAD,0.08)
        time.sleep(2.5)	
        self.motionProxy.setAngles("HeadYaw",0,0.08)
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(1.5)
	
        self.motionProxy.setStiffnesses("Head", 0.0)
        return
	
    def head_sweep_1(self):
	    
        self.motionProxy.setStiffnesses("Head", 1.0)
	
        self.motionProxy.setAngles("HeadYaw",30.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",10.0*almath.TO_RAD,0.03)
        time.sleep(2.0)
        self.motionProxy.setAngles("HeadYaw",10.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",15.0*almath.TO_RAD,0.03)
        time.sleep(1.0)
        self.motionProxy.setAngles("HeadYaw",-30.0*almath.TO_RAD,0.08)
        time.sleep(2.5)	
        self.motionProxy.setAngles("HeadYaw",0,0.08)
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(1.5)
		
        self.motionProxy.setStiffnesses("Head", 0.0)
        return
	
    def head_sweep_2(self):
	
        self.motionProxy.setStiffnesses("Head", 1.0)
	
        self.motionProxy.setAngles("HeadYaw",30.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",-10.0*almath.TO_RAD,0.03)
        time.sleep(1.5)
        self.motionProxy.setAngles("HeadYaw",-10.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",-5.0*almath.TO_RAD,0.03)
        time.sleep(2.0)
        self.motionProxy.setAngles("HeadYaw",-20.0*almath.TO_RAD,0.08)
        time.sleep(1.5)	
        self.motionProxy.setAngles("HeadYaw",0,0.08)
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(1.5)
		
        self.motionProxy.setStiffnesses("Head", 0.0)
        return
	
    def head_sweep_3(self):	
	
        self.motionProxy.setStiffnesses("Head", 1.0)
	
        self.motionProxy.setAngles("HeadYaw",-10.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",5.0*almath.TO_RAD,0.03)
        time.sleep(1.5)
        self.motionProxy.setAngles("HeadYaw",-15.0*almath.TO_RAD,0.08)
        self.motionProxy.setAngles("HeadPitch",-5.0*almath.TO_RAD,0.03)
        time.sleep(2.0)
        self.motionProxy.setAngles("HeadYaw",10.0*almath.TO_RAD,0.08)
        time.sleep(1.5)	
        self.motionProxy.setAngles("HeadYaw",0,0.08)
        self.motionProxy.setAngles("HeadPitch",0,0.05)
        time.sleep(1.5)
		
        self.motionProxy.setStiffnesses("Head", 0.0)
        return

if __name__ == "__main__":
    robotIp = "127.0.0.1"

    if len(sys.argv) <= 1:
        print "Usage python head_move.py ip optional: pitch yaw"
    else:
        robotIp = sys.argv[1]
	
    if len(sys.argv) <= 3:
	    robotIp = sys.argv[1]
    else:
	    pitch = sys.argv[2]
	    yaw = sys.argv[3]
	
    move = Headmovement(robotIp)
    move.movehead(pitch,yaw)
    #move.head_sweep()

    #main(robotIp, pitch, yaw)
