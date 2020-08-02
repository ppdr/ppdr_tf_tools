cmake_minimum_required(VERSION 2.8.3)
project(ppdr_tf_tools)
add_compile_options(-Wall -Wextra)

#読み込むパッケージ
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  tf2
)

#使用するメッセージファイル
#add_message_files(FILES
#  csm_data.msg
#  csm_status.msg
#  whill_data.msg
#)

#generate_messages(DEPENDENCIES std_msgs)

#インクルード
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ppdr_tf_tools
  CATKIN_DEPENDS roscpp std_msgs tf tf2
  #DEPENDS system_lib
)


#インクルードするファイルの場所
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#C++11の関数を使う用
add_definitions(-std=c++11)

add_library(tf_common src/tf_common.cpp)
target_link_libraries(tf_common
  ${catkin_LIBRARIES}
)

#作成する実行プログラムの名前とソースの場所
add_executable(tf_copier src/tf_copier.cpp)
#add_dependencies(tf_copier tf_common)
target_link_libraries(tf_copier
  tf_common
  ${catkin_LIBRARIES}
)



#カスタムメッセージを利用するパッケージの依存性
#add_dependencies(imu_node ${PROJECT_NAME}_generate_messages_cpp)
#add_dependencies(rotary_encoder_node ${PROJECT_NAME}_generate_messages_cpp)
