cmake_minimum_required(VERSION 3.14)
project(polyvox_test)

set(CMAKE_CXX_STANDARD 11)

set(ENABLE_EXAMPLES OFF)
set(ENABLE_TESTS OFF)
set(BUILD_DOCS OFF)
add_subdirectory(thirdparty/polyvox)

#find_package(OpenCOLLADA REQUIRED)

add_executable(polyvox_test main.cpp)
target_include_directories(polyvox_test
        PUBLIC ${PolyVoxHeaders_SOURCE_DIR}
#        PUBLIC ${OPENCOLLADA_INCLUDE_DIRS}
)
#target_link_libraries(polyvox_test
#        ${OPENCOLLADA_LIBRARIES}
#)
