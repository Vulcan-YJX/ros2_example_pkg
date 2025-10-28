<p align="center"><strong>example_pkg</strong></p>
<p align="center"><a href="https://github.com/${YOUR_GIT_REPOSITORY}/blob/main/LICENSE"><img alt="License" src="https://img.shields.io/badge/License-Apache%202.0-orange"/></a>
<img alt="language" src="https://img.shields.io/badge/language-c++-red"/>
<img alt="platform" src="https://img.shields.io/badge/platform-linux-l"/>
</p>
<p align="center">
    语言：<a href="./docs/docs_en/README_EN.md"><strong>English</strong></a> / <strong>中文</strong>
</p>
​	这是一个 `Ros2` 的附带 `mqtt` 的功能节点。一些数据可以使用 `mqtt` 的进行传输，尤其是远程控制指令。

## Basic Information

| Installation method | Supported platform[s]      |
| ------------------- | -------------------------- |
| Source              | Jetpack 5.1.2 , ros-humble |

------

## Subscribed

| ROS Topic |       Interface        | Frame ID | Description |
| :-------: | :--------------------: | :------: | :---------: |
| `topic1`  | std_msgs::msg::Float64 |  frameA  |  接收数据A  |
| `topic2`  | std_msgs::msg::Float64 |  frameB  |  接收数据B  |

## Published

| ROS Topic |       Interface        | Frame ID |    Description    |
| :-------: | :--------------------: | :------: | :---------------: |
|    sum    | std_msgs::msg::Float64 |  frameC  | 求和结果 1 Hz发布 |

## Service

| Service Topic |     Call Interface     |    Return Interface    |       Description        |
| :-----------: | :--------------------: | :--------------------: | :----------------------: |
| service name  | std_msgs::msg::Float64 | std_msgs::msg::Float64 |    一个service的案例     |
|               | std_msgs::msg::Float64 |                        | Service 的第二个输入描述 |



## Build Package

```bash
# install mqtt broker.
sudo apt install mosquitto-dev

#change ws port.
echo -e "allow_anonymous true\nlistener 1883\nprotocol websockets" | sudo tee /etc/mosquitto/conf.d/example.conf > /dev/null

sudo systemctl restart mosquitto

colcon build
source install/setup.bash
ros2 launch example_pkg example.launch.py
```
