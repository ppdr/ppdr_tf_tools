#include "ppdr_tf_tools/tf_common.h"

namespace ppdr_tf_tools{

geometry_msgs::TransformStamped TFHandler::get_tf(const std::string parent_frame, const std::string child_frame, const float timeout){
  // Wait until all tfs are available.
  // All interpolation will be considered, however it takes a short time.
  static tf2_ros::Buffer tfBuffer;
  static tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::TransformStamped transformStamped;
  transformStamped.transform.rotation.w = 1.0;

  ros::Time now = ros::Time::now();
  if(!tfBuffer.canTransform(parent_frame, child_frame, now, ros::Duration(timeout))){
    ROS_WARN("Could not lookup transform from %s to %s, in duration %f [sec]", parent_frame.c_str(), child_frame.c_str(), timeout);
    return transformStamped;
  }

  try{
    transformStamped = tfBuffer.lookupTransform(parent_frame, child_frame, now, ros::Duration(0.1));
  }
  catch(tf2::TransformException &ex){
    ROS_WARN("%s", ex.what());
    return transformStamped;
  }

  _tf_stamped = transformStamped;

  return transformStamped;
}

geometry_msgs::TransformStamped TFHandler::get_tf_immediate(std::string parent_frame, std::string child_frame){
  // Get tf immediately.
  // It takes no time, however some part of tf may be old.
  static tf2_ros::Buffer tfBuffer;
  static tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::TransformStamped transformStamped;
  transformStamped.transform.rotation.w = 1.0;

  try{
    transformStamped = tfBuffer.lookupTransform(parent_frame, child_frame, ros::Time(0), ros::Duration(0.1));
  }
  catch(tf2::TransformException &ex){
    ROS_WARN("%s", ex.what());
    return transformStamped;
  }

  _tf_stamped = transformStamped;

  return transformStamped;
}

void TFHandler::send_tf(std::string parent_frame, std::string child_frame){
  static tf2_ros::TransformBroadcaster br;

  geometry_msgs::TransformStamped tf;
  tf.header.stamp = ros::Time::now();
  tf.header.frame_id = parent_frame;
  tf.child_frame_id = child_frame;
  tf.transform = _tf_stamped.transform;
  br.sendTransform(tf);
}

void TFHandler::send_tf(geometry_msgs::TransformStamped tf_stamped, std::string parent_frame, std::string child_frame){
  static tf2_ros::TransformBroadcaster br;

  geometry_msgs::TransformStamped tf;
  tf.header.stamp = ros::Time::now();
  tf.header.frame_id = parent_frame;
  tf.child_frame_id = child_frame;
  tf.transform = tf_stamped.transform;
  br.sendTransform(tf);
}

}