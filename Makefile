NAME			= minishell

SRCS_FILE		= srcs/main.c \
		srcs/parsing/lexer.c \
		srcs/parsing/parser.c \
		srcs/parsing/weak_string.c \
		srcs/parsing/create_tuple.c \
		srcs/builtin/export_builtin.c \
		srcs/builtin/env_builtin.c \
		srcs/builtin/unset_builtin.c \
		srcs/builtin/echo_builtin.c \
		srcs/builtin/pwd_builtin.c \
		srcs/builtin/exit_builtin.c \
		srcs/builtin/cd_builtin.c \
		srcs/utils/edit_env.c \
		srcs/utils/get_env_paths.c \
		srcs/utils/find_command_path.c \
		srcs/utils/get_user_line.c \
		srcs/utils/exec_command.c \
		srcs/utils/print_mini_env.c \
		srcs/utils/exist_path.c \
		srcs/utils/builtin_utils.c \
		srcs/utils/is_delimiter.c \
		srcs/utils/returns.c \
		srcs/utils/check_file.c \
		srcs/utils/redirections.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS_FILE:.c=.o))

SRCS_DIR		= ./
OBJS_DIR		= ./
INCLUDES_DIR	= ./includes/
LIBFT_DIR		= ./libft/

LIBFT			= $(LIBFT_DIR)libft.a
HEADER			= $(INCLUDES_DIR)minishell.h
CFLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=address,undefined -Wpadded
CC				= clang

INCLUDES	= $(addprefix -I, $(INCLUDES_DIR) $(LIBFT_DIR))

# COLORS
_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

.PHONY: all launch clean fclean re
.SILENT:

all: launch

launch:
	echo MINISHELL PROJECT
	$(MAKE) $(LIBFT)
	echo -n $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	$(MAKE) $(NAME)
	echo $(_GREEN)"\nDone."$(_END)

$(OBJS_DIR):
	mkdir $@

$(LIBFT): FORCE
	$(MAKE) -sC $(LIBFT_DIR)
	echo

FORCE:

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf $<

clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(RM) -r srcs/builtin/*.o
	$(RM) -r srcs/parsing/*.o
	$(RM) -r srcs/utils/*.o
	$(RM) -r srcs/*.o
	$(RM) -r *.o

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)
	echo $(_RED)"deleted: minishell"$(_END)

re:
	$(MAKE) -s fclean
	$(MAKE) -s