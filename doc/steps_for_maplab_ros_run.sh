roscore


# step1
cd ~/DEV/Projs/maplab/maplab_ws
source ~/DEV/Projs/maplab/maplab_ws/devel/setup.bash
rosrun rovioli run_rovioli_live_weng save_folder_200522

# step2
rosbag play ~/DEV/Projs/dataset/mh_dataset/V2_03_difficult.bag

# step3
# start maplab_console
# run it in clion or
cd ~/DEV/Projs/maplab/maplab_ws
source ~/DEV/Projs/maplab/maplab_ws/devel/setup.bash
rosrun maplab_console maplab_console 
# load map in ‘maplab<>:/$ ’
load --map_folder /home/weng/DEV/Projs/maplab/maplab_ws/save_folder_200522

# step4
rosrun rviz rviz 

# step5
# in ‘maplab<>:/$ ’
visualize


# step6
# config

