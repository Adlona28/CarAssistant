#include "txt_parser_node.h"
#include "ros/ros.h"

TxtParserNode::TxtParserNode(void) {}


void main_loop(void) {
  ROS_INFO("HI");
}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "txt_parser_node");

  ros::NodeHandle n;
  ros::Rate loop_rate(10);

  // Main loop.
  while (ros::ok()) {
    main_loop();
    ros::spinOnce();
    loop_rate.sleep();
  }
}
