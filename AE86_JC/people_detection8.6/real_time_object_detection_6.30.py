#!/usr/bin/env python3

# USAGE
# python real_time_object_detection.py 

# import the necessary packages
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import rospy
import numpy as np
import imutils
import time
import cv2
import pygame

distant_flag = False
rect_list = [0, 0, 0, 0]

def play_sounds():  
    if not pygame.mixer.music.get_busy():
        pygame.mixer.music.play()

def depth_image_callback(ros_depth_image):
	global distant_flag

	bridge = CvBridge()
	try:
		img = bridge.imgmsg_to_cv2(ros_depth_image, "32FC1")
	except CvBridgeError:
		print(CvBridgeError)
	frame = img
	frame = imutils.resize(frame, width=400)
	#print(rect_list[0], rect_list[1], rect_list[2], rect_list[3])
	y = (rect_list[0] + rect_list[2]) / 2
	x = (rect_list[1] + rect_list[3]) / 2
	#print(x, y)
	if frame.item(x, y) <= 1:
		print(str(frame.item(x,y)) + " hey!!!!!!!")
		distant_flag = True

def callback(ros_image):
	global rect_list
	global distant_flag

	dur = rospy.Duration.from_sec(0.2).to_sec()
	last_time = rospy.get_param("last_time")
	
	bridge = CvBridge()
	try:
		img = bridge.imgmsg_to_cv2(ros_image, "bgr8")
	except CvBridgeError:
		print(CvBridgeError)
	frame = img
	frame = imutils.resize(frame, width=400)
	if rospy.get_rostime().to_sec() - last_time >= dur:
		# grab the frame dimensions and convert it to a blob
		(h, w) = frame.shape[:2]
		blob = cv2.dnn.blobFromImage(cv2.resize(frame, (300, 300)),
			0.007843, (300, 300), 127.5)

		# pass the blob through the network and obtain the detections and
		# predictions
		net.setInput(blob)
		detections = net.forward()

		# loop over the detections
		for i in np.arange(0, detections.shape[2]):
			# extract the confidence (i.e., probability) associated with
			# the prediction
			confidence = detections[0, 0, i, 2]

			# filter out weak detections by ensuring the `confidence` is
			# greater than the minimum confidence
			if confidence > 0.2:
				# extract the index of the class label from the
				# `detections`, then compute the (x, y)-coordinates of
				# the bounding box for the object
				idx = int(detections[0, 0, i, 1])
				box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
				(startX, startY, endX, endY) = box.astype("int")
				rect_list = (startX, startY, endX, endY)
				# draw the prediction on the frame
				label = "{}: {:.2f}%".format(CLASSES[idx],
					confidence * 100)
				if idx == 15:  # person
					cv2.rectangle(frame, (startX, startY), (endX, endY),
						COLORS[idx], 2)
					# print(rospy.Time.now().to_nsec())
					if distant_flag:  
						play_sounds()
						distant_flag = False
					else:
						print("too far.")
		rospy.set_param('last_time', rospy.Time.now().to_sec())
					
	# show the output frame
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF




if __name__ == '__main__':
	rospy.init_node('detection_listener', anonymous=True)
	#initialize the music play mode 
	pygame.mixer.init() 
	pygame.mixer.music.load("sounds/3.mp3")
	# initialize the list of class labels MobileNet SSD was trained to
	# detect, then generate a set of bounding box colors for each class

	CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
		"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
		"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
		"sofa", "train", "tvmonitor"]

	# CLASSES = ["person"]
	COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))
	# load our serialized model from disk
	print("[INFO] loading model...")
	net = cv2.dnn.readNetFromCaffe("MobileNetSSD_deploy.prototxt.txt", "MobileNetSSD_deploy.caffemodel")
	print("success")
	rospy.set_param('last_time', rospy.Time.now().to_sec())
	rospy.Subscriber("/zed/left/image_raw_color", Image, callback) #, queue_size = 100)
	rospy.Subscriber("/zed/depth/depth_registered", Image, depth_image_callback)
	rospy.spin()
	# do a bit of cleanup
	cv2.destroyAllWindows()
