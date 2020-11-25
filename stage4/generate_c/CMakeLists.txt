#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (stage4)

#include_directories(../)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
#aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
#add_library (stage4 ${DIR_LIB_SRCS})

# 生成链接库
add_library (stage4_c generate_c_st.cc generate_c.cc generate_c_base.cc generate_c_configbody.cc generate_c_typedecl.cc generate_c_vardecl.cc generate_location_list.cc generate_var_list.cc stage4.cc)