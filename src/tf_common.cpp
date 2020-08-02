#include "ppdr_tf_tools/tf_common.h"

namespace ppdr_tf_tools{

geometry_msgs::TransformStamped TFHandler::get_tf(std::string parent_frame, std::string child_frame){
  static tf2_ros::Buffer tfBuffer;
  static tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::TransformStamped transformStamped;
  transformStamped.transform.rotation.w = 1.0;

  try{
    transformStamped = tfBuffer.lookupTransform(parent_frame, child_frame, ros::Time(0), ros::Duration(5.0));
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