sudo chmod 777 /dev/ttyUSB*

gnome-terminal -x roslaunch rbx1_bringup fake_turtlebot.launch 
sleep 2s
gnome-terminal -x roslaunch moonshot keyboard_teleop.launch
