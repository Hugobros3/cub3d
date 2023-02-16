# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2023/01/30 19:26:43 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

vpath %.c $(shell find ./srcs -type d)

NAME =		libemlx.a
SRCS =  	$(notdir $(shell find ./srcs -type f -name '*.c'))

OBJS_DIR =	objs
OBJS =		$(SRCS:%.c=$(OBJS_DIR)/%.o)

CC =		gcc
CFLAGS :=	-O3 -Wall -Wextra -Werror
RM =		rm -f
ifdef MOREFLAGS
	CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
INCLUDES +=	-I./includes \
			-I./libft/ \
			-I./mlx_linux \
			-I/usr/include \
			-I/usr/include/freetype2 \
			-I/home/reclaire/Downloads/freetype-2.10.0/include
CFLAGS +=	-D LINUX -D CL_TARGET_OPENCL_VERSION=300 -Wno-deprecated-declarations

ifneq (,$(findstring -g,$(MOREFLAGS)))
    CFLAGS += -D DEBUG -rdynamic
endif

endif
ifeq ($(UNAME_S),Darwin)
	HOSTNAME = $(shell hostname)
ifneq (,$(findstring 42mulhouse,$(HOSTNAME)))
INCLUDES +=	-I./includes \
			-I./libft \
			-I./mlx_engine/minilibx \
			-I/Users/$(USER)/.brew/include/freetype2/ \
			-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.1.sdk/System/Library/Frameworks/OpenCL.framework/Headers
CFLAGS +=	-D OSX

ifneq (,$(findstring -g,$(MOREFLAGS)))
    CFLAGS += -D DEBUG
endif

else
INCLUDES +=	-I./includes \
			-I./libft \
			-I/usr/local/Cellar/freetype/2.12.1/include/freetype2 \
			-I./minilibx/ \
			-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/System/Library/Frameworks/OpenCL.framework/Headers
CFLAGS +=	-D OSX

ifneq (,$(findstring -g,$(MOREFLAGS)))
    CFLAGS += -D DEBUG
endif

endif
endif

$(OBJS_DIR):
			mkdir $(OBJS_DIR)

$(OBJS): $(OBJS_DIR)/%.o : %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS_DIR) $(OBJS)
			ar -rcs $(NAME) $(OBJS)
				
all:		$(NAME)

clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		fclean all clean re start print
