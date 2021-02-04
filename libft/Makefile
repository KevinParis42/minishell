NAME = libft.a

SRC_NAME = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_convert_base.c \
	ft_cutend.c \
	ft_free_str_tab.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putchar_fd.c \
	ft_realloc_char.c \
	ft_realloc_char_tab.c \
	ft_pop_char_tab.c \
	ft_realloc_int.c \
	ft_split.c \
	ft_str_tab_len.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c \
	ft_strcmp.c \
	ft_cutend.c \
	ft_display_error.c \
	is_av_spaces.c

SRC_PATH = ./
OBJ_PATH = ./

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))


CFLAGS = -Werror -Wall -Wextra

##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m

all: $(OBJ_PATH) $(NAME)
	printf "\33[2K\r$(_GREEN)created: $(NAME)$(_END)"

$(OBJ_PATH):
	mkdir $@
	mkdir $@/ft_printf

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	printf "\33[2K\r$(_CYAN)compiling: $<$(_END)"
	gcc $(CFLAGS) -o $@ -c $< 

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -rf *.o
	printf "\33[2K\r$(_RED)deleted: libft$(_END)\n"

nameclean:
	/bin/rm -f $(NAME)
	printf "\33[2K\r$(_RED)deleted: $(NAME)$(_END)\n"

fclean: clean
	/bin/rm -f $(NAME)
	printf "\33[2K\r$(_RED)deleted: $(NAME)$(_END)\n"

re: fclean all

.PHONY: all clean fclean nameclean

.SILENT: