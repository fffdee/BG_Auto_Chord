cmake_minimum_required(VERSION 3.10)

project(chord)

# 指定C语言编译器
set(CMAKE_C_COMPILER gcc)

# 设置源文件
set(SRC_FILES
    ./src/main.c
    ./src/bg_auto_chord.c
)

# 设置头文件目录
include_directories(include)

# 生成可执行文件
add_executable(chord ${SRC_FILES})

# 链接所需的库（如果有的话）
target_link_libraries(chord ev)
