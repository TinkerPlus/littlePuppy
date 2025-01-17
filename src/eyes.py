#! /usr/bin/env python

from SimpleCV import Camera
import time
import serial
import RPi.GPIO as GPIO

def filter_image(p_img): # p for paremeter
    '''
    filter the image, get the light circle
    return a image only contains light circle
    
    while True:                    
        #cam = Camera()
        img = cam.getImage()   
        blueDist = img.colorDistance((255.0, 182.0, 1.0))
        blueDistBin = blueDist.binarize(50).invert()
        blueDistBin.show()
        
        
        blobs = blueDistBin.findBlobs()
        blobs.show(width=5)
        print blobs.coordinates()
    '''
    # calculate distance between target point and others,
    ## the closer to target color, the more black. 
    blueDist = p_img.colorDistance((255.0, 182.0, 1.0))
    # select pixel who's gray degree islarger than set velue.
    ## then invert, target area is black finally.
    blueDistBin = blueDist.binarize(60)
    #blueDistBin.show()
    return blueDistBin

def get_position(p_img):
    '''
    find middle point of the light circle
    return x,y
    '''
    blobs = p_img.findBlobs()
    if blobs:
        position = tuple(blobs[0].coordinates())
        return position
    else:
        print 'find no blobs'
        return False
        
    
def get_command((p_x,p_y)):
    '''
    compare x with middle of this image,
    if p_x > middle_X, return right
    if p_x < middle_X, return left
    '''
    x_target, y_target = (p_x, p_y)
    cam_width = 640
    left_boarder  = 210
    right_boarder = cam_width - left_boarder
    
    if x_target > right_boarder:
        print 'target is in right'
        return 'L'
    elif x_target < left_boarder:
        print 'target is in left'
        return 'R'
    elif x_target > left_boarder and x_target < right_boarder:
        print 'target is on forward'
        return 'S'
    else:
        return ''

def call_arduino(p_command):
    #ser.write('R')
    ser.write(p_command)


def serial_test():
    '''
    for testing serial
    '''
    for i in range(0,10):
        ser.write("F")
        time.sleep(1)
        ser.write("S")
        time.sleep(1)

def setup_GPIO():
    l_HUMAN_PIN = 12
    GPIO.setmode(GPIO.BOARD)
    #print("GPIO mode: "+str(GPIO:getmode())
    #GPIO.setwarnings(False) # ignore warning that changing mode from input to output
    GPIO.setup(l_HUMAN_PIN, GPIO.IN)
    
    
    
def is_alarm():
    l_HUMAN_PIN = 12
    if GPIO.input(l_HUMAN_PIN) == 1:
        return True
    else:
        return 0
def clean_up_GPIO():
    l_HUMAN_PIN = 12
    GPIO.cleanup(l_HUMAN_PIN)


cam = Camera()
ser = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout = 3.0)
x_middle = 320 # half of the width: 320

is_forward = 0

while not is_forward:
    img = cam.getImage()
    img = filter_image(img)
    #targetCount = 0
    if(get_position(img)):
        
        '''
        position = get_position(img)
        print position
        command = get_command(position)
        print ("Command sent: "+command)
        if (command):
            #ser.write(command)
            call_arduino(command)
        '''
        #ser.write('R'
        ser.write('F')   
        print("target is on  forward") 
        #is_forward = 1
    else:
        ser.write("L")
        print("Turn left to find target")
        #is_forward = 0

#ser.write('R')

    
