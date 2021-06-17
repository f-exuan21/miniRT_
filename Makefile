CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGL -framework AppKit
RM = rm -rf

SRCS_DIR = srcs
SRCS = ${wildcard ${SRCS_DIR}/*.c}

OBJS_DIR = objs
OBJS = ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}

GNL_DIR = gnl
GNL = ${wildcard ${GNL_DIR}/*.c}
GNL_OBJ = ${GNL:${GNL_DIR}/%.c=${GNL_DIR}/%.o}

LIBFT_DIR = lib/libft
LIBFT = libft.a

MLX_DIR = lib/libmlx
MLX = libmlx.dylib
MLX_H = mlx.h

NAME = miniRT

all: ${NAME}

${GNL_DIR}/%.o: ${GNL_DIR}/%.c
	${CC} ${CFLAGS} -c $< -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	mkdir -p ${OBJS_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make add -C ${LIBFT_DIR}
	cp ${LIBFT_DIR}/${LIBFT} ./lib/${LIBFT}

${MLX}:
	make -C ${MLX_DIR}
	cp ${MLX_DIR}/${MLX} ./${MLX}
	cp ${MLX_DIR}/${MLX} ./lib/${MLX}
	cp ${MLX_DIR}/${MLX_H} ./includes/${MLX_H}

${NAME}: ${LIBFT} ${GNL_OBJ} ${OBJS} ${MLX}
	${CC} -L./lib -lft -lmlx ${CFLAGS} ${FRAMEWORK} ${OBJS} ${GNL_OBJ} -o ${NAME}

clean:
	${RM} ${OBJS}
	${RM} ${OBJS_DIR}
	${RM} ${GNL_OBJ}
	${RM} ${MLX} lib/${LIBFT} lib/${MLX}
	make clean -C ${LIBFT_DIR}
	make clean -C ${MLX_DIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re
