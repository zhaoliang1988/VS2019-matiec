# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (libabsyntax_utils)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

include_directories(../)

# 生成链接库
add_library (absyntax_utils ${DIR_LIB_SRCS})
