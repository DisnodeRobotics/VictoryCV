cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
find_package( OpenCV REQUIRED )

file(GLOB SOURCES src/*.cpp)
add_executable( VictoryCV ${SOURCES} )
target_link_libraries( VictoryCV ${OpenCV_LIBS} )
