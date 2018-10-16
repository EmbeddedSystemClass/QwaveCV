cmake_minimum_required (VERSION 2.8)
project (qwavecv)
find_package(OpenCV REQUIRED)
include_directories("/usr/local/include")
file(GLOB SOURCES "./*.cpp")
add_library(qwavecv SHARED ${SOURCES})
target_link_libraries (	qwavecv ${OpenCV_LIBS} "/usr/local/natinst/lib/libqwaveopencv.so")
INSTALL(TARGETS qwavecv DESTINATION "/usr/local/natinst/lib")

