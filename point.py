# -*- encoding: UTF-8 -*-

import sys
from naoqi import ALProxy
import time
import almath

def main(robotIP):
    PORT = 9559

    try:
        motionProxy = ALProxy("ALMotion", robotIP, PORT)
    except Exception,e:
        print "Could not create proxy to ALMotion"
        print "Error was: ",e
        sys.exit(1)

    motionProxy.setStiffnesses("Head", 1.0)
	
    names            = "HeadPitch"
    angles           = 10.0*almath.TO_RAD
    fractionMaxSpeed = 0.05
    motionProxy.setAngles(names,angles,fractionMaxSpeed)
	
    time.sleep(1.5)	

    # Simple command for the HeadYaw joint at 10% max speed
    names            = "HeadYaw"
    angles           = 30.0*almath.TO_RAD
    fractionMaxSpeed = 0.08
    motionProxy.setAngles(names,angles,fractionMaxSpeed)

    time.sleep(1.5)
	
    angles           = -30.0*almath.TO_RAD
    fractionMaxSpeed = 0.08
    motionProxy.setAngles(names,angles,fractionMaxSpeed)

    time.sleep(3.0)	
	
    angles           = 0
    fractionMaxSpeed = 0.08
    motionProxy.setAngles(names,angles,fractionMaxSpeed)

    time.sleep(1.5)	
	
    names            = "HeadPitch"
    angles           = 0
    fractionMaxSpeed = 0.05
    motionProxy.setAngles(names,angles,fractionMaxSpeed)
	
    time.sleep(1.5)
	
    motionProxy.setStiffnesses("Head", 0.0)

if __name__ == "__main__":
    robotIp = "Meeseeks.local"

    if len(sys.argv) <= 1:
        print "Usage python almotion_controllingjoints.py robotIP (optional default: 127.0.0.1)"
    else:
        robotIp = sys.argv[1]

    main(robotIp)
