NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror

INCLUDE		=	-I includes

SRC_DIR		=	src/

FILES		=	main.c		\
				parsing.c	\
				prm.c		\
				pipeline.c	\
				execute.c	\
				run.c		\
				input.c		\
				redirect.c	\
				heredoc.c

SRC			=	$(addprefix $(SRC_DIR),$(FILES))

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

LIB			=	-lreadline

all		:	lib
	@echo "\033[0;33m\nCOMPILING $(NAME)"
	$(CC) -o $(NAME) $(SRC) $(LIBFT_LIB) $(INCLUDE) $(LIB)
	@echo "\033[1;32m$(NAME) created"

valgrind:	lib
	@echo "\033[0;33m\nCOMPILING $(NAME)"
	$(CC) -g3 -o $(NAME) $(SRC) $(LIBFT_LIB) $(INCLUDE) $(LIB)
	@echo "\033[1;32m$(NAME) created"

lib		:
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32m$(LIBFT_FILE) created"

clean	:
	@echo "\033[0;31mDeleting objects in $(LIBFT_PATH)..."
	@make clean -sC $(LIBFT_PATH)

fclean	:	clean
	@echo "\033[0;31mDeleting executables..."
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "\033[1;32mDone"

re		:	fclean all

.PHONY: all clean fclean re