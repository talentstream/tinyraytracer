cmake_minimum_required(VERSION 3.10)
project(tinyraytracer)
set(CMAKE_CXX_STANDARD 11)

# 递归获取所有源文件
function(get_sources dir result)
    file(GLOB_RECURSE files ${dir}/*.cpp ${dir}/*.hpp)
    set(${result} ${files} PARENT_SCOPE)
endfunction()

# 设置源文件目录
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

# 获取所有源文件
get_sources(${SOURCE_DIR} SOURCES)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 指定输出文件路径
set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/image.ppm")

# 添加自定义命令，执行可执行文件并将输出重定向到image.ppm文件
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${PROJECT_NAME} > ${OUTPUT_FILE}
    COMMENT "Redirecting output to ${OUTPUT_FILE}"
)
