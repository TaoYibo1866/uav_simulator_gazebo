# uav_simulator
## build
```Bash
$ sudo apt-get install ros-melodic-joint-state-publisher-gui
$ cd ~/catkin_ws/src
$ git clone https://github.com/TaoYibo1866/uav_simulator_gazebo.git
$ cd ~/catkin_ws
$ catkin_make
```
## run
```Bash
$ roslaunch uav_description display.launch
```
![image](dji_m100_gimbal_camera_rviz.png)
```Bash
$ roslaunch uav_gazebo jing_zhun_chuan_yue.launch
```
![image](jing_zhun_chuan_yue.png)
```Bash
$ roslaunch uav_gazebo tian_gong_zhu_ta.launch
```
```Bash
$ roslaunch uav_simulator tian_gong_zhu_ta_replay.launch
```
![image](tian_gong_zhu_ta_replay.png)