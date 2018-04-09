#cmake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息
project(hw)

#查找当前目录下的所有源文件
#并将名称保存到 DIR_SRCS 变量
#aux_source_directory()

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(BASE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/base/include")

set(BASE_SRC_DIR "${PROJECT_SOURCE_DIR}/base/src")

set(BASE_ROLESVR_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/rolesvr/include")

set(BASE_ROLESVR_SRC_DIR "${PROJECT_SOURCE_DIR}/rolesvr/src")

#添加子目录
add_subdirectory("${BASE_SRC_DIR}")

add_subdirectory("${BASE_ROLESVR_SRC_DIR}")