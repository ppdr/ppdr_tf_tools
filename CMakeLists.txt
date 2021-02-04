cmake_minimum_required(VERSION 2.8.3)
project(ppdr_tf_tools)
add_compile_options(-Wall -Wextra)

#読み込むパッケージ
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
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
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs tf tf2 # ros libs
  #DEPENDS system_lib # non-ros libs
)


#インクルードするファイルの場所
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#C++11の関数を使う用
add_definitions(-std=c++11)

add_library(${PROJECT_NAME} src/tf_common.cpp)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

#作成する実行プログラムの名前とソースの場所
add_executable(tf_copy src/tf_copy.cpp)
target_link_libraries(tf_copy
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(tf_fix src/tf_fix.cpp)
target_link_libraries(tf_fix
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(tf_to_pose src/tf_to_pose.cpp)
target_link_libraries(tf_to_pose
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(tf_to_array src/tf_to_array.cpp)
target_link_libraries(tf_to_array
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(test_publish src/test_publish.cpp)
target_link_libraries(test_publish
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

#カスタムメッセージを利用するパッケージの依存性
#add_dependencies(imu_node ${PROJECT_NAME}_generate_messages_cpp)
#add_dependencies(rotary_encoder_node ${PROJECT_NAME}_generate_messages_cpp)
