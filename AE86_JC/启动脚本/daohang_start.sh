sudo chmod 777 /dev/ttyUSB*
sudo chmod 777 /dev/ltme01

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
#rtabmap定位模式
gnome-terminal -x roslaunch rtabmap_ros stereo_mapping.launch rtabmap_args:="--Vis/CorFlowMaxLevel 5 --Stereo/MaxDisparity 200" stereo:=true localization:=true
sleep 10s
#启动雷达
gnome-terminal -x roslaunch ltme01_driver ltme01.launch
#gnome-terminal -x roslaunch turtlebot_navigation rplidar_laser.launch
sleep 2s
#加载地图
gnome-terminal -x roslaunch rbx1_nav fake_amcl.launch map:=map_629_bangwan.yaml
sleep 5s
#启动rviz
gnome-terminal -x rosrun rviz rviz -d `rospack find rbx1_nav`/amcl.rviz

