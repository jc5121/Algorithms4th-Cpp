sudo chmod 777 /dev/ttyUSB*

gnome-terminal -x roslaunch rbx1_bringup fake_turtlebot.launch 
sleep 2s
gnome-terminal -x roslaunch razor_imu_9dof sanchi_imu.launch
sleep 2s
gnome-terminal -x roslaunch zed_wrapper zed.launch publish_tf:=false
sleep 5s
gnome-terminal -x roslaunch moonshot test_robot_pose_ekf.launch
sleep 2s
gnome-terminal -x roslaunch rbx1_bringup odom_ekf.launch
sleep 2s
#rtabmap建图模式
gnome-terminal -x roslaunch rtabmap_ros stereo_mapping.launch rtabmap_args:="--delete_db_on_start --Vis/CorFlowMaxLevel 5 --Stereo/MaxDisparity 200" stereo:=true 
#gnome-terminal -x roslaunch rtabmap_ros stereo_mapping.launch rtabmap_args:="--Vis/CorFlowMaxLevel 5 --Stereo/MaxDisparity 200" stereo:=true 
sleep 10s  #rtabmap打开后，手动调节是建图模式，并打开grapview的显示，然后切换到键盘进行建图

#启动键盘
gnome-terminal -x roslaunch moonshot keyboard_teleop.launch
