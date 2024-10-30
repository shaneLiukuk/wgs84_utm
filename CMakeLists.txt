cmake_minimum_required(VERSION 3.10)
project(test)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

# 查找 Eigen 库
find_package(Eigen3 REQUIRED)

file(GLOB SRC
 "${PROJECT_SOURCE_DIR}/src/*.cc"
 "${PROJECT_SOURCE_DIR}/*.cc"
)
# 添加可执行文件
add_executable(${PROJECT_NAME} ${SRC})
# 链接库
target_link_libraries(${PROJECT_NAME} proj)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)