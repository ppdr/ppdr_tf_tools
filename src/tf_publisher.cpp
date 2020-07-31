#include <ros/ros.h>
#include <string>

#include <tf/transform_broadcaster.h>

#include <tf2/convert.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>

// #include <geometry_msgs/TransformStamped.h>
// #include <Eigen/Dense>

geometry_msgs::TransformStamped sub_tf(std::string parent, std::string child){
  static tf2_ros::Buffer tfBuffer;
  static tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::TransformStamped transformStamped;

  try{
    transformStamped = tfBuffer.lookupTransform(parent, child, ros::Time(0));
    ROS_INFO("ok");
  }
  catch(tf2::TransformException &ex){
    ROS_WARN("%s", ex.what());
    return transformStamped;
  }

  return transformStamped;
}

void pub_tf(geometry_msgs::Transform t, std::string parent, std::string child){
  static tf2_ros::TransformBroadcaster br;

  geometry_msgs::TransformStamped tf;
  tf.header.stamp = ros::Time::now();
  tf.header.frame_id = parent;
  tf.child_frame_id = child;
  tf.transform = t;
  br.sendTransform(tf);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_duplicate");
  ros::NodeHandle nh;

  ros::Rate rate(50);

  while(ros::ok()){
      geometry_msgs::TransformStamped t = sub_tf("odom", "map");
      pub_tf(t.transform, "odom", "map_clone");
      rate.sleep();
  }
  return 0;
};