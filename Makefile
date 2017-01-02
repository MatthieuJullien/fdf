NAME		:=	fdf
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror

LINKSMACOS	:=	-lmlx -framework OpenGL -framework AppKit

SRCDIR		:=	sources
SRCFILES	:=	fdf.c \
				free_env.c \
				get_map.c \
				map_to_2d.c \
				print.c \
				keys_functions.c

SRC			:=	$(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR		:=	objects
OBJ			:=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

LIBFTDIR	:=	libft
LIBFTINCDIR	:=	$(LIBFDIR)/includes
LIBFTFILE	:=	$(LIBFTDIR)/libft.a
LIBFT		:=	-L $(LIBFTDIR) -lft

INCDIR		:=	includes

all: $(NAME)

$(NAME): $(LIBFTFILE) $(OBJ)
	@echo "Compiling" $(NAME)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INCDIR) $(LIBFT) $(LINKSMACOS)

$(LIBFTFILE):
	@echo "Making libft.a"
	@make -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	@echo "Compiling" $@
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(INCDIR) -I $(LIBFTINCDIR)

clean:
	@make -C $(LIBFTDIR) clean
	@echo "Cleaning" $(NAME)
	@/bin/rm -rf $(OBJDIR)


fclean:
	@echo "Deleting objects"
	@/bin/rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) fclean
	@echo "Deleting" $(NAME)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
