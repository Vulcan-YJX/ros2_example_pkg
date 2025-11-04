from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'mqtt_ros_bridge'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    # packages=find_packages(include=['mqtt_ros_bridge', 'mqtt_ros_bridge.*']),
    package_dir={'': '.'},
    data_files=[
        (os.path.join('share', package_name), ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        # (os.path.join('share', package_name, 'mqtt_ros_bridge'), glob('mqtt_ros_bridge/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='vulcan',
    maintainer_email='jinxu.yu@directdrivetech.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'mqtt_bridge_node = mqtt_ros_bridge.mqtt_bridge:main'
        ],
    },
)
