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

#ifndef EXAMPLE_PKG__EXAMPLE_NODE_HPP_
#define EXAMPLE_PKG__EXAMPLE_NODE_HPP_

#include <chrono>
#include <memory>

#include "example_pkg/user_function.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

class ExampleNode : public rclcpp::Node
{
public:
  explicit ExampleNode(const rclcpp::NodeOptions & options);

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

#endif  // EXAMPLE_PKG__EXAMPLE_NODE_HPP_
