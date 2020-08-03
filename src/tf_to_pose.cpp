#include <ros/ros.h>
#include <string>
#include <geometry_msgs/PoseStamped.h>

#include "ppdr_tf_tools/tf_common.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_to_pose");
  ros::NodeHandle nh("~");

  ppdr_tf_tools::TFHandler tf_handler;
  std::string source_parent, soucre_child;
  int loop_rate;
  
  nh.param<std::string>("source_parent", source_parent, "map");
  nh.param<std::string>("soucre_child",  soucre_child,  "odom");
  nh.param("rate", loop_rate, 100);

  ros::Publisher pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose_stamped", 1);

  ros::Rate rate(loop_rate);

  while(ros::ok()){
      ros::spinOnce();

      geometry_msgs::TransformStamped tfs = tf_handler.get_tf(source_parent, soucre_child);
      geometry_msgs::PoseStamped ps;

      ps.header.frame_id = source_parent;
      ps.header.stamp = tfs.header.stamp;
      ps.pose.position.x = tfs.transform.translation.x;
      ps.pose.position.y = tfs.transform.translation.y;
      ps.pose.position.z = tfs.transform.translation.z;
      ps.pose.orientation = tfs.transform.rotation;
      pose_pub.publish(ps);

      rate.sleep();
  }
  return 0;
};