# real-mav
Realsense-ros를 통해 얻는 `/camera/odom/sample`데이터를 px4의 `/mavros/vision_pose/pose` 토픽으로 바꿔서 publish해주는 패키지입니다.

## Installation
``` bash
$ cd ~/catkin_ws/src
$ git clone https://github.com/start0821/real-mav.git
$ cd ..
$ catkin_make
```

## run the node
```bash
$ rosrun real-mav subscribe_realsense_publish_mavros
```
