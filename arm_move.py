# -*- encoding: UTF-8 -*-

import sys
from naoqi import ALProxy
import time
import almath

class Armmovement:	
    def __init__(self,ip):
        try:
            self.motionProxy = ALProxy("ALMotion", ip, 9559)
            self.postureProxy = ALProxy("ALRobotPosture", ip, 9559)
        except Exception,e:
            print "Could not create proxy to ALMotion"
            print "Error was: ",e
            sys.exit(1)

    def movelarm(self, pitch, roll):

        self.motionProxy.setStiffnesses("LArm", 1.0)
        self.motionProxy.setStiffnesses("Head", 1.0)

        self.motionProxy.setAngles("LShoulderPitch",int(pitch)*almath.TO_RAD,0.2)	
        self.motionProxy.setAngles("LElbowRoll",10*almath.TO_RAD,0.2)
        self.motionProxy.setAngles("LShoulderRoll",int(roll)*almath.TO_RAD,0.2)
        self.motionProxy.setAngles("HeadPitch",int(pitch)*almath.TO_RAD,0.1)
        self.motionProxy.setAngles("HeadYaw",int(roll)*almath.TO_RAD,0.1)
        self.motionProxy.openHand('LHand')
        time.sleep(2)
        self.motionProxy.closeHand('LHand')
        self.postureProxy.goToPosture("Crouch", 0.5)
		
        self.motionProxy.setStiffnesses("LArm", 0.0)
        self.motionProxy.setStiffnesses("Head", 0.0)
        
        return
		
    def moverarm(self, pitch, roll):

        self.motionProxy.setStiffnesses("RArm", 1.0)
        self.motionProxy.setStiffnesses("Head", 1.0)
        
        self.motionProxy.setAngles("RShoulderPitch",int(pitch)*almath.TO_RAD,0.2)	
        self.motionProxy.setAngles("RElbowRoll",10*almath.TO_RAD,0.2)
        self.motionProxy.setAngles("RShoulderRoll",int(roll)*almath.TO_RAD,0.2)
        self.motionProxy.setAngles("HeadPitch",int(pitch)*almath.TO_RAD,0.1)
        self.motionProxy.setAngles("HeadYaw",int(roll)*almath.TO_RAD,0.1)
        self.motionProxy.openHand('RHand')
        time.sleep(2)
        self.motionProxy.closeHand('RHand')
        self.postureProxy.goToPosture("Crouch", 0.5)
		
        self.motionProxy.setStiffnesses("RArm", 0.0)
        self.motionProxy.setStiffnesses("Head", 0.0)
        
        return	

    def arm_1(self):

        self.motionProxy.setStiffnesses("RArm", 1.0)
        self.motionProxy.setStiffnesses("LArm", 1.0)
      
        self.motionProxy.setAngles("RShoulderRoll",-5*almath.TO_RAD,0.05)	
        time.sleep(0.5)
        self.motionProxy.setAngles("LShoulderRoll",5*almath.TO_RAD,0.05)	
        time.sleep(0.5)
		
        self.postureProxy.goToPosture("Crouch", 0.5)
		
        self.motionProxy.setStiffnesses("RArm", 0.0)
        self.motionProxy.setStiffnesses("LArm", 0.0)
        
        return	

    def clasp(self):

        self.motionProxy.setStiffnesses("RArm", 1.0)
        self.motionProxy.setStiffnesses("LArm", 1.0)
      	
        self.motionProxy.openHand('LHand')
        self.motionProxy.openHand('RHand')
        time.sleep(1)	
        self.motionProxy.closeHand('LHand')
        self.motionProxy.closeHand('RHand')
        time.sleep(2)
		
        self.postureProxy.goToPosture("Crouch", 0.5)
		
        self.motionProxy.setStiffnesses("RArm", 0.0)
        self.motionProxy.setStiffnesses("LArm", 0.0)
        
        return			

if __name__ == "__main__":
    robotIp = "127.0.0.1"

    if len(sys.argv) <= 1:
        print "Usage python Larm_move.py IP LShoulderPitch LshoulderRoll"
    else:
        robotIp = sys.argv[1]
		
    if len(sys.argv) <= 3:
	    robotIp = sys.argv[1]
    else:
	    pitch = sys.argv[2]
	    roll = sys.argv[3]
	    inv = -int(roll)

		
	
    move = Armmovement(robotIp)
    move.clasp()
    #move.arm_1()
    move.movelarm(pitch, roll)
    move.moverarm(pitch, inv)
	
    #main(robotIp, pitch, roll)
