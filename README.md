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