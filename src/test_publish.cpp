#include <ros/ros.h>
#include <string>
#include <geometry_msgs/PoseStamped.h>

#include "ppdr_tf_tools/tf_common.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_sin_publish");
  ros::NodeHandle nh("~");

  ppdr_tf_tools::TFHandler tf_handler;
  std::string source_parent, soucre_child;
  int loop_rate;
  double t = 0.0;
  double dt = 0.01;
  
  nh.param<std::string>("source_parent", source_parent, "map");
  nh.param<std::string>("soucre_child",  soucre_child,  "odom");
  nh.param("rate", loop_rate, 100);
  nh.param("dt", dt, 0.01);

  ros::Rate rate(loop_rate);


  while(ros::ok()){
      ros::spinOnce();

      geometry_msgs::TransformStamped tfs;

      tfs.transform.translation.x = cos(t);
      tfs.transform.translation.y = sin(t);
      tfs.transform.translation.z = 0.0;
      tf2::Quaternion q;
      q.setRPY(0, 0, t);
      tfs.transform.rotation.x = q.x();
      tfs.transform.rotation.y = q.y();
      tfs.transform.rotation.z = q.z();
      tfs.transform.rotation.w = q.w();

      tf_handler.send_tf(tfs, source_parent, soucre_child);

      t += dt;
      rate.sleep();
  }
  return 0;
};