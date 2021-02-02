CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rc
INC = -I. -I./gnl

NAME = libft.a

LIBFT_COMMON_DIR = ./common/
LIBFT_COMMON = \
		ft_max \
		ft_min \
		ft_abs \
		ft_itoa

LIBFT_CTYPE_DIR = ./ctype/
LIBFT_CTYPE = \
		ft_isspace

LIBFT_LIST_DIR = ./list/
LIBFT_LIST = \
		ft_lstadd_back \
		ft_lstclear \
		ft_lstlast \
		ft_lstnew \
		ft_lstsize \
		ft_lstdelone

LIBFT_MEMORY_DIR = ./memory/
LIBFT_MEMORY = \
		ft_bzero \
		ft_calloc \
		ft_memcpy \
		ft_memmove \
		ft_memset

LIBFT_STRING_DIR = ./string/
LIBFT_STRING = \
		ft_split \
		ft_strchr \
		ft_strlcpy \
		ft_strlen \
		ft_strlens \
		ft_strncmp \
		ft_strtrim \
		ft_strdup \
		ft_strlcat

GNL_DIR = ./gnl/
GNL = 	get_next_line

SRC = $(addprefix $(LIBFT_COMMON_DIR), $(addsuffix .c, $(LIBFT_COMMON))) \
		$(addprefix $(LIBFT_CTYPE_DIR), $(addsuffix .c, $(LIBFT_CTYPE))) \
		$(addprefix $(LIBFT_LIST_DIR), $(addsuffix .c, $(LIBFT_LIST))) \
		$(addprefix $(LIBFT_MEMORY_DIR), $(addsuffix .c, $(LIBFT_MEMORY))) \
		$(addprefix $(LIBFT_STRING_DIR), $(addsuffix .c, $(LIBFT_STRING))) \
		$(addprefix $(GNL_DIR), $(addsuffix .c, $(GNL)))
OBJ = $(SRC:.c=.o)

all : $(NAME)

clean :
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	rm -rf $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	rm -rf $@
	$(AR) $(ARFLAGS) $@ $(OBJ)

re : fclean all

norme :
	norminette $(SRC) libft.h $(GNL_DIR)get_next_line.h

.PHONY: all clean fclean re norme
