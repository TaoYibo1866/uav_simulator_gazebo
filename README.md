# 无人机硬件在环仿真
## 编译
```Bash
$ sudo apt-get install ros-kinetic-joint-state-publisher-gui
$ cd ~/catkin_ws/src
$ git clone https://gitee.com/harbin-institute-of-technology-csc/drone_simulator.git
$ cd ~/catkin_ws
$ catkin_make
```
## 运行结果
查看模型
```Bash
$ roslaunch drone_description display.launch
```
![image](https://gitee.com/harbin-institute-of-technology-csc/drone_simulator/raw/master/dji_m100_gimbal_camera_rviz.png)
精准穿越场景
```Bash
$ roslaunch drone_gazebo jing_zhun_chuan_yue.launch
```
![image](https://gitee.com/harbin-institute-of-technology-csc/drone_simulator/raw/master/jing_zhun_chuan_yue.png)
天宫筑塔场景
```Bash
$ roslaunch drone_gazebo tian_gong_zhu_ta.launch
```
大疆OSDK飞行数据回放
```Bash
$ roslaunch drone_simulator tian_gong_zhu_ta_replay.launch
```
![image](https://gitee.com/harbin-institute-of-technology-csc/drone_simulator/raw/master/tian_gong_zhu_ta_replay.png)