.ONESHELL:

NAME		=	minishell

CC			=	cc -Wall -Wextra -Werror

INCLUDE		=	-I includes

SRC_DIR		=	src/

OBJ_DIR		=	obj/

FILES		=	main				\
				parsing				\
				parsing2			\
				prm					\
				pipeline			\
				execute				\
				run					\
				run_builtin			\
				input				\
				redirect			\
				heredoc				\
				env					\
				cd					\
				history				\
				echo				\
				pwd					\
				export				\
				git					\
				unset				\
				wcard				\
				wcard2				\
				wcard3				\
				wcard4

NO_OF_FILES := $(words $(FILES))

COUNT		=	1

SRC			=	$(addprefix $(SRC_DIR),$(FILES))

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

LIB			=	-lreadline

DEF			=	"\033[0m"
BG_GREEN	=	"\033[48;2;0;200;0m"
BG_RED		=	"\033[48;2;210;0;0m"
FG_RED		=	"\033[38;2;210;0;0m"
FG_BLUE		=	"\033[38;2;0;70;200m"
FG_GREEN	=	"\033[38;2;0;200;0m"
BG_BLACK	=	"\033[48;2;0;0;0m"

PROG = 5
FILE = 6
TOP = 7
MID = 8
BOT = 9
SUCCESS = 10

progress  : lib
	@mkdir -p $(OBJ_DIR)
	@tput cup $(PROG) 0
	@echo -n $(DEF)$(FG_BLUE)Compiling $(FG_GREEN)$(NAME)$(DEF) "                                                             "
	@tput cup $(TOP) 0
	@echo -n "▁▁▁▁▁▁▁▁▁▁"
	@for file in $(FILES); do \
		echo -n "▁";\
	done;
	@tput cup $(MID) 0
	@echo -n $(BG_BLACK)"Progress ▕"
	@for file in $(FILES); do \
		echo -n $(BG_BLACK)" "$(DEF);\
	done;
	@tput cup $(BOT) 0
	@echo -n "▔▔▔▔▔▔▔▔▔▔"
	@for file in $(FILES); do \
		echo -n "▔";\
	done;
	@tput cup $(MID) 10
	@for file in $(FILES); do
		cc $(INCLUDE) $(LIB) -c $(SRC_DIR)$$file.c -o $(OBJ_DIR)$$file.o 2>> compil.log
		if [ "$$?" = "0" ]; then
			echo -n $(BG_GREEN)" "$(DEF)
		else
			echo -n $(BG_RED)" "$(DEF)
		fi
		tput sc
		tput cup $(FILE) 0
		echo -n $(FG_GREEN)$$file$(DEF) "                                                    "
		tput rc
		sleep .01
	done;
	@tput cup $(FILE) 0
	@echo -n "                                                    "
	@$(CC) $(OBJ_DIR)/*.o -o $(NAME) $(LIBFT_LIB) $(INCLUDE) $(LIB) 2>> compil.log
	@tput cup $(SUCCESS) 0
	@echo -n $(FG_RED)
	@cat compil.log
	@echo -n $(DEF)
	@echo $(HEADER)
	@rm -f compil.log


progress_clean  :
	@tput cup $(PROG) 0
	@echo -n $(DEF)$(FG_RED)Cleaning $(FG_GREEN)$(NAME)$(DEF) "                                                            "
	@tput cup $(TOP) 0
	@echo -n "▁▁▁▁▁▁▁▁▁▁"
	@for file in $(FILES); do \
		echo -n "▁";\
	done;
	@tput cup $(MID) 0
	@echo -n $(BG_BLACK)"Progress ▕"
	@for file in $(FILES); do \
		echo -n $(BG_BLACK)" "$(DEF);\
	done;
	@tput cup $(BOT) 0
	@echo -n "▔▔▔▔▔▔▔▔▔▔"
	@for file in $(FILES); do \
		echo -n "▔";\
	done;
	@tput cup $(MID) 10
	@for file in $(FILES); do
		rm -f $$file.o
		echo -n $(BG_RED)" "$(DEF)
		tput sc
		tput cup $(FILE) 0
		echo -n $(FG_RED)$$file$(DEF) "                                                    "
		tput rc
		sleep .02
	done;
	@tput cup $(FILE) 0
	@echo -n "                                                    "
	@rm -rf $(OBJ_DIR)
	@tput cup $(SUCCESS) 0

all			:	lib progress

lib			:
	@make -C $(LIBFT_PATH)

clean_lib	:
	@make clean -sC $(LIBFT_PATH)

clean		:	clean_lib progress_clean

fclean		:	clean
	@rm -f $(NAME)
	@rm	-f .history

re			:	fclean all

git			:	fclean
	git status
	git add *
	git commit -m "Auto commit from makefile"
	git push

run			:	all
	@clear
	@./$(NAME)

valgrind	:	valgrind_c
	@valgrind --suppressions=./valgrind.supp ./$(NAME)

.PHONY: all clean fclean re