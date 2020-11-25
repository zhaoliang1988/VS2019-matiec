# 项目信息
project (iec2c)

add_compile_options(/wd4819)

# 添加 absyntax 子目录
add_subdirectory(absyntax)

# 添加 absyntax_utils 子目录
add_subdirectory(absyntax_utils)

# 添加 stage1_2 子目录
add_subdirectory(stage1_2)

# 添加 stage3 子目录
add_subdirectory(stage3)

# 添加 stage4 子目录
add_subdirectory(stage4)

include_directories(./lib)

include_directories(./lib/C)

# 指定生成目标 
add_executable(iec2c main.cc getopt.c getopt_int.c)

# 添加链接库
target_link_libraries(iec2c stage1_2)

# 添加链接库
target_link_libraries(iec2c stage3)

# 添加链接库
target_link_libraries(iec2c stage4_c)

# 添加链接库
target_link_libraries(iec2c absyntax)

# 添加链接库
target_link_libraries(iec2c absyntax_utils)