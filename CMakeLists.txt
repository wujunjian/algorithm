# CMakeList.txt : 顶级 CMake 项目文件，执行全局配置
# 和此处的包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project (mystack)

add_executable (mystack mystack_2.cpp)
add_executable (c11map c11map.cpp)
add_executable (stack2list stack2list.cpp)
add_executable (tt t.cpp)


add_executable(InvertedIndex InvertedIndex.cpp)

