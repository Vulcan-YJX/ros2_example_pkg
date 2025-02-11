// Copyright (c) 2023 UserName
// Email: user_mail@mail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "example_pkg/example_node.hpp"

ExampleNode::ExampleNode(const rclcpp::NodeOptions & options) : Node("example_node", options)
{
  this->get_parameter("value1", value1_);
  this->get_parameter("value2", value2_);
  RCLCPP_INFO(this->get_logger(), "value1 : '%f'", value1_);

  subscription1_ = this->create_subscription<std_msgs::msg::Float64>(
    "topic1", 10, std::bind(&ExampleNode::topic1_callback, this, std::placeholders::_1));
  subscription2_ = this->create_subscription<std_msgs::msg::Float64>(
    "topic2", 10, std::bind(&ExampleNode::topic2_callback, this, std::placeholders::_1));
  publisher_ = this->create_publisher<std_msgs::msg::Float64>("sum", 10);
  timer_ =
    this->create_wall_timer(std::chrono::seconds(1), std::bind(&ExampleNode::timer_callback, this));
}

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
  message.data = add_function(value1_, value2_);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
  publisher_->publish(message);
}
