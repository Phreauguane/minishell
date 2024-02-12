NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror

INCLUDE		=	-I includes

SRC_DIR		=	src/

FILES		=	main.c				\
				parsing.c			\
				parsing2.c			\
				prm.c				\
				pipeline.c			\
				execute.c			\
				run.c				\
				run_builtin.c		\
				input.c				\
				redirect.c			\
				heredoc.c			\
				env.c				\
				cd.c				\
				history.c			\
				echo.c				\
				pwd.c				\
				export.c			\
				git.c				\
				unset.c

SRC			=	$(addprefix $(SRC_DIR),$(FILES))

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

LIB			=	-lreadline

all		:	lib
	@echo "\033[0;33m\nCOMPILING $(NAME)"
	$(CC) -o $(NAME) $(SRC) $(LIBFT_LIB) $(INCLUDE) $(LIB)
	@echo "\033[1;32m$(NAME) created\033[0m"

valgrind:	lib
	@echo "\033[0;33m\nCOMPILING $(NAME)"
	$(CC) -g3 -o $(NAME) $(SRC) $(LIBFT_LIB) $(INCLUDE) $(LIB)
	@echo "\033[1;32m$(NAME) created\033[0m"

lib		:
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32m$(LIBFT_FILE) created\033[0m"

clean	:
	@echo "\033[0;31mDeleting objects in $(LIBFT_PATH)..."
	@make clean -sC $(LIBFT_PATH)

fclean	:	clean
	@echo "\033[0;31mDeleting executables..."
	@rm -f $(NAME)
	@rm	-f .history
	@make fclean -sC $(LIBFT_PATH)
	@echo "\033[1;32mDone\033[0m"

re		:	fclean all

git		:	fclean
	git status
	git add *
	git commit -m "Auto commit from makefile"
	git push

run		:	all
	@clear
	@./$(NAME)

.PHONY: all clean fclean re