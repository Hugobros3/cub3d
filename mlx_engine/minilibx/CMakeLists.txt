enable_language(OBJC)

add_library(mlx)
target_sources(mlx PRIVATE mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c)

#TODO: cocoa and whatever
