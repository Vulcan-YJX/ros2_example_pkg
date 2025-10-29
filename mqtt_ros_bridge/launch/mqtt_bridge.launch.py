import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('mqtt_ros_bridge'),
        'config',
        'param.yaml'
    )

    return LaunchDescription([
        Node(
            package='mqtt_ros_bridge',
            executable='mqtt_bridge_node',
            name='mqtt_bridge_node',
            output='screen',
            parameters=[config]
        )
    ])


