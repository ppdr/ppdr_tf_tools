#ifndef PPDR_TF_FIX
#define PPDR_TF_FIX
#include <ros/ros.h>
#include <string>

#include "tf_common.h"

std::string source_parent, source_child;
std::string new_parent, new_child;
int loop_rate;

ppdr_tf_tools::TFHandler tf_handler;
bool is_started = false;
#endif