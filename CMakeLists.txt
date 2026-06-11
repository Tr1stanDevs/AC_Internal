cmake_minimum_required(VERSION 3.22)
project(AC_Internal LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/TD_GetPidFromProcName/CMakeLists.txt)

add_executable(${PROJECT_NAME} 
    main.cpp
)

add_library(${TD_GetPidFromProcName_name} STATIC 
${TD_GetPidFromProcName_files}
)


target_link_libraries(${PROJECT_NAME} 
${TD_GetPidFromProcName_name}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${TD_GetPidFromProcName_path}
)