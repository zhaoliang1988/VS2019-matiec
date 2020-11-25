#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
include_directories(../absyntax)
include_directories(../absyntax_utils)
# 项目信息
project (stage4)

# 添加 stage4 子目录
add_subdirectory(generate_c)
