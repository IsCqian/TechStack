cmake_minimum_required(VERSION 3.8)

project(VEC)        

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIR include)

set(SOURCE_DIR src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


file(GLOB INCLUDE_FILES ${INCLUDE_DIR}/*.h)
file(GLOB RESOURCE_FILES ${SOURCE_DIR}/*.cpp)


add_library(myVecLib ${RESOURCE_FILES})

target_include_directories(myVecLib PUBLIC ${INCLUDE_DIR})

add_executable(myVec main.cpp)
    
target_link_libraries(myVec myVecLib)
