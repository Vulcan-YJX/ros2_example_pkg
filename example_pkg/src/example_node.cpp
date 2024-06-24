#include "example_pkg/example_node.hpp"

void ExampleNode::topic1_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
  value1_ = msg->data;
}

void ExampleNode::topic2_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
  value2_ = msg->data;
}

void ExampleNode::timer_callback()
{
  auto message = std_msgs::msg::Float64();
  message.data = add_function(value1_,value2_);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
  publisher_->publish(message);
}
