#ifndef EXAMPLE_PKG_NODE_HPP
#define EXAMPLE_PKG_NODE_HPP

#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "example_pkg/user_function.hpp"

class ExampleNode : public rclcpp::Node
{
public:
  ExampleNode(const rclcpp::NodeOptions & options) : Node("example_node",options)
  {
    this->get_parameter("value1", value1_);
    this->get_parameter("value2", value2_);
    RCLCPP_INFO(this->get_logger(), "value1 : '%f'", value1_);
    
    subscription1_ = this->create_subscription<std_msgs::msg::Float64>(
      "topic1", 10, std::bind(&ExampleNode::topic1_callback, this, std::placeholders::_1));
    subscription2_ = this->create_subscription<std_msgs::msg::Float64>(
      "topic2", 10, std::bind(&ExampleNode::topic2_callback, this, std::placeholders::_1));
    publisher_ = this->create_publisher<std_msgs::msg::Float64>("sum", 10);
    timer_ = this->create_wall_timer(
      std::chrono::seconds(1), std::bind(&ExampleNode::timer_callback, this));
  }

private:

  /// \brief  Publish result data once per second.
  void timer_callback();

  /// \brief  Numble A receive callback.
  void topic1_callback(const std_msgs::msg::Float64::SharedPtr msg);

  /// \brief  Numble B receive callback.
  void topic2_callback(const std_msgs::msg::Float64::SharedPtr msg);

  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription1_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription2_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  double value1_;
  double value2_;
};


#endif  // EXAMPLE_PKG_NODE_HPP
