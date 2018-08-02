# CMakeList.txt : 顶级 CMake 项目文件，执行全局配置
# 和此处的包含子项目。
#
cmake_minimum_required (VERSION 3.8)


add_executable(main main.cpp util.h)

#add_library(util util.h)

#target_link_libraries(main util)