cmake_minimum_required(VERSION 3.5.2)
project(myProgram)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        code.cpp
        command.hpp
        enum.hpp
        excecution.hpp
        readin.hpp
        storage.hpp
        transcode.hpp
        ultility.hpp
        )
