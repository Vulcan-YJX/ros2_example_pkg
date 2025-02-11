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
