#include <ros/ros.h>
#include <string>

#include "ppdr_tf_tools/tf_common.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_copier");
  ros::NodeHandle nh("~");

  std::string source_parent, soucre_child;
  std::string new_parent, new_child;
  int loop_rate;
  nh.param<std::string>("source_parent", source_parent, "map");
  nh.param<std::string>("soucre_child",  soucre_child,  "odom");
  nh.param<std::string>("new_parent",    new_parent,    "odom");
  nh.param<std::string>("new_child",     new_child,     "robot");
  nh.param("rate", loop_rate, 100);

  // Need check if frame names are correct.

  ros::Rate rate(loop_rate);

  ppdr_tf_tools::TFHandler tf_handler;

  while(ros::ok()){
      geometry_msgs::TransformStamped t = tf_handler.get_tf(source_parent, soucre_child);
      tf_handler.send_tf(t, new_parent, new_child);
      rate.sleep();
  }
  return 0;
};