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
