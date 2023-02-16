# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2023/01/31 17:23:22 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

vpath %.c $(shell find ./srcs -type d)

NAME =			cub3d
RM =			rm -f
CC =			gcc

SRCS =			$(notdir $(shell find ./srcs -type f -name '*.c'))
OBJS_DIR =		objs
OBJS =			${SRCS:%.c=$(OBJS_DIR)/%.o}

LIBS_DIR =		./libs

CFLAGS :=		-O3 -Wall -Wextra -Werror

#LIBS += -L./ -lefence

ifdef MOREFLAGS
	CFLAGS :=	$(CFLAGS) $(MOREFLAGS)
endif

CFLAGS += -D COLOR_WRONG="240,72,5,255"
CFLAGS += -D COLOR_WHITE="255,255,255,255"
CFLAGS += -D COLOR_GOOD1="129,240,65,255"
CFLAGS += -D COLOR_GOOD2="61,163,2,255"
CFLAGS += -D COLOR_EMPTY="255,242,206,255"
CFLAGS += -D COLOR_WALL="128,128,128,255"
CFLAGS += -D COLOR_INFECT1="70,255,157,255"
CFLAGS += -D COLOR_INFECT2="0,163,76,255"
CFLAGS += -D COLOR_OK2="16,31,163,255"

UNAME_S :=		$(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX +=		./mlx_engine/mlx_linux

	INCLUDES +=	-I./include \
				-I./mlx_engine/mlx_linux \
				-I./mlx_engine/includes \
				-I./mlx_engine/libft \
				-I/usr/include \
				-I/usr/include/freetype2 \
				-I/home/reclaire/Downloads/freetype-2.10.0/include

	LIBS +=		-L./mlx_engine \
				-L./mlx_engine/mlx_linux \
				-L./mlx_engine/libft/ \
				-L/usr/lib \
				-L$(LIBS_DIR) \
				-lemlx \
				-lmlx \
				-lft \
				-lXext \
				-lX11 \
				-lm \
				-lfreetype \
				-lOpenCL


    CFLAGS += -D LINUX -D CL_TARGET_OPENCL_VERSION=300

	ifneq (,$(findstring -g,$(MOREFLAGS)))
    	CFLAGS	+=	-D DEBUG -rdynamic
		LIBS	+=	-ldl
	endif
endif
ifeq ($(UNAME_S),Darwin)
	HOSTNAME = $(shell hostname)
ifneq (,$(findstring 42mulhouse,$(HOSTNAME)))
	MLX +=		./mlx_engine/minilibx

	INCLUDES += -I./include \
				-I./mlx_engine/minilibx \
				-I./mlx_engine/includes \
				-I./mlx_engine/libft \
				-I/Users/$(USER)/.brew/include/freetype2/ \
				-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.1.sdk/System/Library/Frameworks/OpenCL.framework/Headers
    
	LIBS +=		-L/Users/$(USER)/.brew/lib -L/usr/local/lib \
				-L./mlx_engine/minilibx \
				-L/usr/lib \
				-L$(LIBS_DIR) \
				-lemlx \
				./mlx_engine/minilibx/libmlx.a \
				-lft \
				-lm \
				-lfreetype \
				-framework OpenCL \
				-framework OpenGL \
				-framework Cocoa

	CFLAGS += -D OSX -D GL_SILENCE_DEPRECATION

	ifneq (,$(findstring -g,$(MOREFLAGS)))
   		CFLAGS	+=	-D DEBUG
		LIBS	+=	-ldl
	endif
else
	MLX +=		./mlx_engine/minilibx

	INCLUDES += -I./include \
				-I./mlx_engine/minilibx/ \
				-I./mlx_engine/includes \
				-I./mlx_engine/libft \
				-I/usr/local/Cellar/freetype/2.12.1/include/freetype2 \
				-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/System/Library/Frameworks/OpenCL.framework/Headers
    
	LIBS +=		-L/usr/local/lib \
				-L/usr/lib \
				-L$(LIBS_DIR) \
				-L/usr/local/Cellar/freetype/2.12.1/lib \
				-lemlx \
				-lmlx \
				-lft \
				-lm \
				-lfreetype \
				-framework OpenCL \
				-framework OpenGL \
				-framework Cocoa

	CFLAGS += -D OSX -D GL_SILENCE_DEPRECATION

	ifneq (,$(findstring -g,$(MOREFLAGS)))
    	CFLAGS	+=	-D DEBUG
		LIBS	+=	-ldl
	endif
endif
endif

check_fclean:
	@echo -n "Are you sure? [y/N] " && read ans && [ $${ans:-N} = y ]

$(OBJS_DIR):
			mkdir $(OBJS_DIR)

$(OBJS):	$(OBJS_DIR)/%.o : %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -static

libmlx:
			$(MAKE) -C $(MLX)
			cp $(MLX)/libmlx.a ./libs

libemlx:
			$(MAKE) -C ./mlx_engine
			cp ./mlx_engine/libemlx.a ./libs

libft:
			$(MAKE) -C ./mlx_engine/libft
			cp ./mlx_engine/libft/libft.a ./libs

$(LIBS):
			mkdir -p ./libs

$(NAME):	$(LIBS) libmlx libemlx libft $(OBJS_DIR) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
				
all:		$(NAME)

clean:		check_fclean
			$(MAKE) clean -C ./mlx_engine
			$(MAKE) clean -C ./mlx_engine/libft
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			$(MAKE) fclean -C ./mlx_engine
			$(MAKE) fclean -C ./mlx_engine/libft
			$(MAKE) clean -C ./mlx_engine/minilibx
			$(RM) libft.a
			$(RM) libemlx.a
			$(RM) libmlx.a
			$(RM) $(NAME)

re:			fclean all

.PHONY:		fclean all clean re check_fclean