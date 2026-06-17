cmake_minimum_required(VERSION 3.25)

project(AC_Internal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-m32")

set(EXE_Name AC_DLL_INJECTOR)
set(DLL_Name AC_DLL)

include(${CMAKE_CURRENT_LIST_DIR}/TD_GetModuleBaseAddress/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/TD_GetPidFromProcName/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Loader/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/DLL/CMakeLists.txt)


add_library(${TD_GetModuleBaseAddress_name} STATIC ${TD_GetModuleBaseAddress_files})
add_library(${TD_GetPidFromProcName_name} STATIC ${TD_GetPidFromProcName_files})
add_library(${DLL_Name} SHARED ${Dll_files})


message(Loader Files: ${Loader_files})
message(Dll Files: ${Loader_files})

add_executable(${EXE_Name}
    ${Loader_files}
)

target_link_libraries(${EXE_Name} 
${TD_GetPidFromProcName_name}
${TD_GetModuleBaseAddress_name}
)

target_include_directories(${EXE_Name} PUBLIC 
${TD_GetPidFromProcName_path}
${CMAKE_CURRENT_LIST_DIR}/TD_Logging
)

target_include_directories(${DLL_Name} PUBLIC 
${TD_GetModuleBaseAddress_path}
${CMAKE_CURRENT_LIST_DIR}/TD_Logging
)