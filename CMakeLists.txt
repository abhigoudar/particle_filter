cmake_minimum_required (VERSION 2.6)
project ("Monte-Carlo Localizatoin")
find_package(OpenCV REQUIRED)
find_package(Armadillo REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
add_executable(mclocalize src/mclocalize.cpp)
target_link_libraries(mclocalize ${OpenCV_LIBS} ${ARMADILLO_LIBRARIES})


