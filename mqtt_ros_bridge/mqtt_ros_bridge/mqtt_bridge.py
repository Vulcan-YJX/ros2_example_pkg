import rclpy
from rclpy.node import Node
import paho.mqtt.client as mqtt
import json
import time
import threading

class MQTTBridge(Node):
    def __init__(self):
        super().__init__('mqtt_bridge_node')
        self.declare_parameter('broker_ip', "127.0.0.1")
        self.declare_parameter('broker_port', 1883)
        self.declare_parameter('passwd', "")
        self.declare_parameter('reconnect_delay', 15)
        
        self.CLIENT_ID = "namespace"
        self.MQTT_BROKER = self.get_parameter('broker_ip').get_parameter_value().string_value
        self.PORT = self.get_parameter('broker_port').value
        self.passwd =  self.get_parameter('passwd').get_parameter_value().string_value
        self.reconnect_delay = self.get_parameter('reconnect_delay').value
        
        self.mqtt_client = mqtt.Client(client_id=self.CLIENT_ID, transport="websockets")
        self.mqtt_client.username_pw_set(self.CLIENT_ID, self.passwd)
        self.mqtt_connected = False
        self.mqtt_client.on_connect = self.on_mqtt_connect
        self.mqtt_client.on_disconnect = self.on_mqtt_disconnect
        self.mqtt_client.on_message = self.on_mqtt_message

        self.mqtt_topic = [("topic1",0),("topic2",1)]
        self.declare_parameter('forward_speed', [0.0])
        self.declare_parameter('turn_speed', [0.0])
        forward_speed = self.get_parameter('forward_speed').get_parameter_value().double_array_value
        turn_speed = self.get_parameter('turn_speed').get_parameter_value().double_array_value
        self.get_logger().info(f"forward_speed: {list(forward_speed)}")
        self.get_logger().info(f"turn_speed: {list(turn_speed)}")
        timer_period = 3  # seconds
        self.online_timer = self.create_timer(timer_period, self.online_checker)
        
    def destroy_node(self):
        super().destroy_node()
        
    def on_mqtt_connect(self, client, userdata, flags, rc):
        if rc == 0:
            self.mqtt_connected = True
            self.mqtt_client.subscribe(self.mqtt_topic)
            self.get_logger().info(f"mqtt connect broker")
        else:
            self.get_logger().info(f"Failed to connect, return code {rc}")

    def on_mqtt_disconnect(self, client, userdata, rc):
        self.mqtt_connected = False
        self.get_logger().warning("Disconnected from MQTT broker")

    def on_mqtt_message(self, client, userdata, msg):
            print(msg.topic)
            print(msg.payload)
            
    def mqtt_connect(self):
        while not self.mqtt_connected:
            try:
                self.get_logger().info("Attempting to connect to mqtt broker...")
                self.mqtt_client.connect(self.MQTT_BROKER, self.PORT, keepalive=60)
                self.mqtt_client.loop_start()
                break
            except Exception as e:
                self.get_logger().info(f"Connection failed: {e}")
                self.get_logger().info(f"Retrying in {self.reconnect_delay} seconds...")
                time.sleep(self.reconnect_delay)

    def disconnect(self):
        if self.mqtt_connected:
            self.mqtt_client.loop_stop()
            self.mqtt_client.disconnect()
            self.get_logger().info("Disconnected from Remote MQTT broker")

    def online_checker(self):
        if not self.mqtt_connected:
            self.mqtt_connect()

def main(args=None):
    rclpy.init(args=args)
    node = MQTTBridge()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
