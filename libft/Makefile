.ONESHELL:

CC = cc
NAME = libft.a

FILES = 	ft_atoi ft_isascii ft_memcmp	\
			ft_putendl_fd ft_strdup ft_strlen \
			ft_strtrim ft_bzero ft_isdigit 	\
			ft_memcpy ft_putnbr_fd 				\
			ft_striteri ft_strmapi ft_substr 	\
			ft_calloc ft_isprint ft_memmove 	\
			ft_putstr_fd ft_strjoin 			\
			ft_strncmp ft_tolower ft_isalnum 	\
			ft_itoa ft_memset ft_split 		\
			ft_strlcat ft_strnstr ft_toupper 	\
			ft_isalpha ft_memchr 				\
			ft_putchar_fd ft_strchr 			\
			ft_strlcpy ft_strrchr print_arg	\
			args_to_str ft_itoa_base 			\
			ft_printf	ft_straddchr 				\
			ft_strcat_malloc get_next_line		\
			get_next_line_utils 	\
			ft_lstadd_back_bonus 	\
			ft_lstclear_bonus 	\
			ft_lstiter_bonus 		\
			ft_lstmap_bonus 		\
			ft_lstsize_bonus 		\
			ft_lstadd_front_bonus \
			ft_lstdelone_bonus 	\
			ft_lstlast_bonus 		\
			ft_lstnew_bonus

CFLAGS = -Wall -Werror -Wextra

DEF			=	"\033[0m"
BG_GREEN	=	"\033[48;2;0;200;0m"
BG_RED		=	"\033[48;2;210;0;0m"
FG_RED		=	"\033[38;2;210;0;0m"
FG_BLUE		=	"\033[38;2;0;70;200m"
FG_GREEN	=	"\033[38;2;0;200;0m"
BG_BLACK	=	"\033[48;2;0;0;0m"

PROG = 0
FILE = 1
TOP = 2
MID = 3
BOT = 4
SUCCESS = 5

progress  :
	@clear
	@tput cup $(PROG) 0
	@echo -n $(DEF)$(FG_BLUE)Compiling $(FG_GREEN)$(NAME)$(DEF)
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
		cc -c $$file.c -o $$file.o 2>> ../compil.log
		if [ "$$?" = "0" ]; then
			echo -n $(BG_GREEN)" "$(DEF)
		else
			echo -n $(BG_RED)" "$(DEF)
		fi
		tput sc
		tput cup $(FILE) 0
		echo -n $(FG_GREEN)$$file$(DEF) "                "
		tput rc
	done;
	@tput cup $(FILE) 0
	@echo -n "                "
	@ar rcs $(NAME) *.o 2>> ../compil.log
	@tput cup $(SUCCESS) 0

progress_clean  :
	@clear
	@tput cup $(PROG) 0
	@echo -n $(DEF)$(FG_RED)Cleaning $(FG_GREEN)$(NAME)$(DEF)
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
		echo -n $(FG_RED)$$file$(DEF) "                "
		tput rc
		sleep .01
	done;
	@tput cup $(FILE) 0
	@echo -n "                "
	@rm -f $(NAME)
	@tput cup $(SUCCESS) 0

all : progress

clean :	progress_clean

fclean : clean
	rm -f $(NAME)

re : fclean all
