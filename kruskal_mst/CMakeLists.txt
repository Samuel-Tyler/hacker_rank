cmake_minimum_required(VERSION 2.8)
project(hacker_rank)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wno-long-long -Wno-gnu -Wno-nested-anon-types -pedantic")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -flto -fno-omit-frame-pointer -fsanitize=address")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
endif()

include_directories(../utils)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(
    ${PROJECT_NAME}
    )
