#! /usr/bin/env python

from SimpleCV import Camera
import time
import serial

cam = Camera()
port = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout = 3.0)
# half of the width: 320
x_middle = 320



	
def filter_image(img):
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
	blueDist = img.colorDistance((255.0, 182.0, 1.0))
	# select pixel who's gray degree islarger than set velue.
	## then invert, target area is black finally.
	blueDistBin = blueDist.binarize(50)
	return blueDistBin

def get_position(img):
	'''
	find middle point of the light circle
	return x,y
	'''
	blobs = img.findBlobs()
	if blobs:
		position = tuple(blobs[0].coordinates())
		return position
	else:
		print 'find no blobs'
		
	
def left_or_right((x,y)):
	'''
	compare x with middle of this image,
	if x > middle_X, return right
	if x < middle_X, return left
	'''
	x_target, y_target = (x,y)
	if x_target > x_middle:
		print 'target is in right'
		return 'right'
	elif x_target < x_middle:
		print 'target is in left'
		return 'left'

def call_arduino(command):
		port.println(command)




while True:
	img = cam.getImage()
	img = filter_image(img)
	if(get_position(img)):
		position = get_position(img)
		print position
		left_or_right(position)
	
	time.sleep(0.1)
