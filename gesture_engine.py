# -*- encoding: UTF-8 -*-

import sys
from naoqi import ALProxy
import time
import almath

import getFacePos
import random

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

def moverarm_JR(motionProxy, pitch, roll):

    motionProxy.setStiffnesses("RArm", 1.0)
    motionProxy.setStiffnesses("Head", 1.0)
    
    motionProxy.setAngles("RShoulderPitch",int(pitch)*almath.TO_RAD,0.2)	
    motionProxy.setAngles("RElbowRoll",10*almath.TO_RAD,0.2)
    motionProxy.setAngles("RShoulderRoll",int(roll)*almath.TO_RAD,0.2)
    motionProxy.setAngles("HeadPitch",int(pitch)*almath.TO_RAD,0.1)
    motionProxy.setAngles("HeadYaw",int(roll)*almath.TO_RAD,0.1)
    motionProxy.openHand('RHand')
    
    
def movelarm_JR(motionProxy, pitch, roll):

    motionProxy.setStiffnesses("LArm", 1.0)
    motionProxy.setStiffnesses("Head", 1.0)
    
    motionProxy.setAngles("LShoulderPitch",int(pitch)*almath.TO_RAD,0.2)	
    motionProxy.setAngles("LElbowRoll",10*almath.TO_RAD,0.2)
    motionProxy.setAngles("LShoulderRoll",int(roll)*almath.TO_RAD,0.2)
    motionProxy.setAngles("HeadPitch",int(pitch)*almath.TO_RAD,0.1)
    motionProxy.setAngles("HeadYaw",int(roll)*almath.TO_RAD,0.1)
    motionProxy.openHand('LHand')
	
    
def point_fn(robotIp = "192.168.0.100", roll = 0, pitch = 0, RightArm = True):
    try:
        motionProxy = ALProxy("ALMotion", robotIp, 9559)
        postureProxy = ALProxy("ALRobotPosture", robotIp, 9559)
        
        
        if (RightArm):
            moverarm_JR(motionProxy, roll, pitch)
        else:
            movelarm_JR(motionProxy, roll, pitch)
        return True
    
    except Exception,e:
        print "Could not create proxy to ALMotion"
        print "Error was: ",e
        return False
    
def point_rest(robotIp = "192.168.0.100"):
    try:
        motionProxy = ALProxy("ALMotion", robotIp, 9559)
        postureProxy = ALProxy("ALRobotPosture", robotIp, 9559)
        
        
        postureProxy.goToPosture("Crouch", 0.5)
        motionProxy.setStiffnesses("LHipPitch", 0)
        motionProxy.setStiffnesses("RHipPitch", 0)
        motionProxy.setStiffnesses("LHipRoll", 0)
        motionProxy.setStiffnesses("RHipRoll", 0)
        
        return True
    
    except Exception,e:
        print "Could not create proxy to ALMotion"
        print "Error was: ",e
        return False

def point_main(robotIp = "192.168.0.100", roll = 0, pitch = 0, Override = False):
    if Override:
        return point_fn(robotIp, roll, pitch)
        
    if pitch>0:
        return point_fn(robotIp, roll, pitch, False)
    else:
        return point_fn(robotIp, roll, pitch, True)

def wave_hello(robotIp = "192.168.0.100"):
    try:
        motionProxy = ALProxy("ALMotion", robotIp, 9559)
        postureProxy = ALProxy("ALRobotPosture", robotIp, 9559)
        
        
        if (RightArm):
            moverarm_JR(motionProxy, roll, pitch)
        else:
            movelarm_JR(motionProxy, roll, pitch)
        return True
    
    except Exception,e:
        print "Could not create proxy to ALMotion"
        print "Error was: ",e
        return False


def point_wrap(robotIp = "192.168.0.100", loc = 0):
    if loc == 0:
        return point_main(robotIp, 20, -15)
    elif loc == 1:
        return point_main(robotIp, 20, 15)
    elif loc == 2:
        return point_main(robotIp, 15, 5, True)
    elif loc == 3:
        return point_rest(robotIp)
    else:
        print "Invalid Movement Command"
        return False
#print point_main("192.168.0.100", 30, 30)



def move_head(robotIp="192.168.0.100", pitch=0, yaw=0):
    move = Headmovement(robotIp)
    move.movehead(pitch,yaw)
    
def move_head_random(robotIp="192.168.0.100", dist = 30):
    move = Headmovement(robotIp)
    move.movehead(random.uniform(-dist, dist),random.uniform(-dist, dist))
    
def sweep_head(robotIp="192.168.0.100"):
    move = Headmovement(robotIp)
    idx = random.randint(0,3)
    if (idx == 0):
        move.head_sweep()
    elif (idx == 1):
        move.head_sweep_1()
    elif (idx == 2):
        move.head_sweep_2()
    elif (idx == 3):
        move.head_sweep_3()

    
def look_at_face(robotIp="192.168.0.100"):
    move = Headmovement(robotIp)
    move.movehead(0,0)
    facepos = getFacePos.getFacePos(robotIp)
    print facepos
    try:
        move.movehead(facepos[1]/2,-facepos[0]/2)
    except TypeError:
        print "Couldn't see anyone!"
        move.movehead(random.uniform(-50, 50),random.uniform(-50, 50))
    
        
#move_head("192.168.0.100", -30, 30)
#print(getFacePos.getFacePos("192.168.0.100"))
#sweep_head("192.168.0.100")
#point_wrap("192.168.0.100", "Z")
#look_at_face("192.168.0.100")
