cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
find_package(Eigen3 REQUIRED) 
include_directories(${EIGEN3_INCLUDE_DIR})
 set(SOURCES ClassifierSona.cpp Classifier.cpp      main.cpp Circles.cpp Image.h Image.cpp Density.h Density.cpp)
add_executable( DisplayImage ${SOURCES} )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )


