// Copyright (c) 2023 Direct Drive Technology Co., Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
