#include <ros/ros.h>
#include <string>
#include <std_srvs/Trigger.h>

#include "ppdr_tf_tools/tf_fix.h"

bool fix_tf(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res){
  tf_handler.get_tf("map", "odom");
  is_started = true;
  res.success = true;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "tf_fix");
  ros::NodeHandle nh("~");

  
  nh.param<std::string>("source_parent", source_parent, "map");
  nh.param<std::string>("soucre_child",  soucre_child,  "odom");
  nh.param<std::string>("new_parent",    new_parent,    "odom");
  nh.param<std::string>("new_child",     new_child,     "robot");
  nh.param("rate", loop_rate, 100);

  ros::ServiceServer service = nh.advertiseService("fix", fix_tf);

  // Need check if frame names are correct.

  ros::Rate rate(loop_rate);

  while(ros::ok()){
      ros::spinOnce();
      
      if(is_started){
        tf_handler.send_tf(new_parent, new_child);
      }
      rate.sleep();
  }
  return 0;
};