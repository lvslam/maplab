export ROS_VERSION=noetic  
export CATKIN_WS=~/DEV/Projs/maplab/maplab_ws 
cd $CATKIN_WS
catkin config --merge-devel  
catkin config --extend /opt/ros/$ROS_VERSION 
catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release 
# cd $CATKIN_WS

catkin build maplab 