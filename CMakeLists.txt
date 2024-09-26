cmake_minimum_required(VERSION 3.13)
project (cub3d C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# required for MSVC
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

if(UNIX AND NOT APPLE)
    add_compile_definitions(-DLINUX)
elseif (APPLE)
    add_compile_definitions(-DOSX)
endif()

add_compile_definitions(-DCOLOR_WRONG=240,72,5,255)
add_compile_definitions(-DCOLOR_WHITE=255,255,255,255)
add_compile_definitions(-DCOLOR_GOOD1=129,240,65,255)
add_compile_definitions(-DCOLOR_GOOD2=61,163,2,255)
add_compile_definitions(-DCOLOR_EMPTY=255,242,206,255)
add_compile_definitions(-DCOLOR_WALL=128,128,128,255)
add_compile_definitions(-DCOLOR_INFECT1=70,255,157,255)
add_compile_definitions(-DCOLOR_INFECT2=0,163,76,255)
add_compile_definitions(-DCOLOR_OK2=16,31,163,255)

add_compile_definitions(-DCL_TARGET_OPENCL_VERSION=300)

cmake_policy(SET CMP0118 NEW)
add_subdirectory(mlx_engine)

add_executable(cub3d)
target_include_directories(cub3d PUBLIC include)
target_link_libraries(cub3d emlx m)
add_subdirectory(srcs)

