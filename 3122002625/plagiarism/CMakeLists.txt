cmake_minimum_required(VERSION 3.10)

# 项目信息
project(PlagiarismChecker VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 主程序
add_executable(plagiarism
    src/main.cpp
)

# 构建可执行文件输出目录
set_target_properties(plagiarism PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 生成静态库 similarity
add_library(similarity STATIC
src/Similarity.cpp
)

# 构建库文件输出目录
set_target_properties(similarity PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

# 链接库
target_link_libraries(plagiarism PRIVATE similarity)

# 安装规则
install(TARGETS plagiarism similarity
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(FILES Similarity.h DESTINATION include)

# 打印构建信息（调试方便）
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
