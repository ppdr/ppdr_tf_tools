#include <ros/ros.h>
#include <string>
#include <std_msgs/Float64MultiArray.h>
#include <tf/tf.h>

#include "ppdr_tf_tools/tf_common.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_to_array");
  ros::NodeHandle nh("~");

  ppdr_tf_tools::TFHandler tf_handler;
  std::string source_parent, soucre_child;
  int loop_rate;
  std::vector<std::string> data_label;
  // data_label.push_back("x");
  // data_label.push_back("y");
  
  nh.param<std::string>("source_parent", source_parent, "map");
  nh.param<std::string>("soucre_child",  soucre_child,  "odom");
  nh.param("rate", loop_rate, 100);
  nh.getParam("labels", data_label);

  ros::Publisher array_pub = nh.advertise<std_msgs::Float64MultiArray>("output", 1);

  ros::Rate rate(loop_rate);

  while(ros::ok()){
      ros::spinOnce();

      geometry_msgs::TransformStamped tfs = tf_handler.get_tf(source_parent, soucre_child);
      std_msgs::Float64MultiArray output;

      for(const auto& l : data_label){
        std_msgs::MultiArrayDimension d;
        d.label = l;
        output.layout.dim.push_back(d);
      }

      //Should be use tf2 type instead of geometry_msgs::TransformStamped.
      double roll, pitch, yaw;
      tf::Quaternion q(tfs.transform.rotation.x, tfs.transform.rotation.y, tfs.transform.rotation.z, tfs.transform.rotation.w);
      tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
      
      // TODO: need refactoring here.
      for(const auto& label : data_label){
        if (label == "x") {
          output.data.push_back(tfs.transform.translation.x);
        } else if (label == "y") {
          output.data.push_back(tfs.transform.translation.y);
        } else if (label == "z") {
          output.data.push_back(tfs.transform.translation.z);
        } else if (label == "roll") {
          output.data.push_back(roll);
        } else if (label == "pitch") {
          output.data.push_back(pitch);
        } else if (label == "yaw") {
          output.data.push_back(yaw);
        } else if (label == "t") {
          output.data.push_back(tfs.header.stamp.toSec());
        }
      }

      array_pub.publish(output);

      rate.sleep();
  }
  return 0;
};