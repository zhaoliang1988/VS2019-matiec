#CMake 最低版本号要求
# 项目信息
project (stage1_2)

#不显示所有警告信息
add_definitions(-w)

find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser iec_bison.yy ${CMAKE_CURRENT_SOURCE_DIR}/iec_bison.cc
			DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/iec_bison.hh)
FLEX_TARGET(MyScanner iec_flex.ll  ${CMAKE_CURRENT_SOURCE_DIR}/iec_flex.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(stage1_2 stage1_2.cc standard_function_names.c create_enumtype_conversion_functions.cc ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})