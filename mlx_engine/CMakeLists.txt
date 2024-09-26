if (APPLE)
    add_subdirectory(minilibx)
else ()
    add_subdirectory(mlx_linux)
endif ()

add_subdirectory(libft)

add_library(emlx)
target_include_directories(emlx PUBLIC includes)
add_subdirectory(srcs)

target_link_libraries(emlx PUBLIC ft mlx)
find_package(Freetype REQUIRED)
target_link_libraries(emlx PUBLIC Freetype::Freetype)
find_package(OpenCL REQUIRED)
target_link_libraries(emlx PUBLIC OpenCL::OpenCL)
