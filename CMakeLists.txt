cmake_minimum_required(VERSION 3.20)
project(AC_Internal LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


include(${CMAKE_CURRENT_SOURCE_DIR}/TD_GetPidFromProcName/CMakeLists.txt)

#message(${TD_GetPidFromProcName_sources})
add_executable(${PROJECT_NAME} AC_Internal.cpp)
target_link_libraries(${PROJECT_NAME} TD_GetPidFromProcName)

