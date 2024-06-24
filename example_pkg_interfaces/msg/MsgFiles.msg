# Service files description
std_msgs/Header header

# Pure visual odometry return code:
# 0 - Unknown state
# 1 - Success
# 2 - Failed
uint8 vo_state

# The total time it takes to process the input frames to output messages in seconds.
float64 node_callback_execution_time