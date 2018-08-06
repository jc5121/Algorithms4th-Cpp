
gnome-terminal -x roscore
sleep 2s
gnome-terminal -x rosrun rtabmap_ros rtabmap _database_path:=~/.ros/rtabmap.db
sleep 15s
gnome-terminal -x rosrun map_server map_saver map:=proj_map
sleep 5s
gnome-terminal -x rosservice call /publish_map 1 1 0
