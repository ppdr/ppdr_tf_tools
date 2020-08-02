#ifndef PPDR_TF_COMMON
#define PPDR_TF_COMMON
#include <ros/ros.h>
#include <string>

#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>

namespace ppdr_tf_tools{

class TFHandler{
public:
    geometry_msgs::TransformStamped _tf_stamped;

    TFHandler(){};
    geometry_msgs::TransformStamped get_tf(std::string parent_frame, std::string child_frame);
    void send_tf(std::string parent_frame, std::string child_frame);
    void send_tf(geometry_msgs::TransformStamped tf_stamped, std::string parent_frame, std::string child_frame);

};

}
#endif