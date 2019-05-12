cmake_minimum_required(VERSION 3.12)
project(Chapter4_Stack_Queue)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        Chapter4_Stack_Queue
        main.cpp
        Stack.cc Stack.h
        Application/implementation.cc Application/implementation.h
        Application/Queen.cc Application/Queen.h
        Application/Cell.cc Application/Cell.h
        Queue.h
        )


#查找当前目录下的所有源文件，并将名称保存到DIR_SRCS变量
#aux_source_directory(. DIR_SRCS)

#添加子目录
#add_subdirectory(Application)

#制定生成目标
#add_executable(Chapter4_Stack_Queue ${DIR_SECS})

#添加链接库
#target_link_libraries(Chapter4_Stack_Queue Implementation)
