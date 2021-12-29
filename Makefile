NAME1 	= client
NAME2 	= server

LIBFT	= ./libft/libft.a
LFT_DIR = ./libft

SRCS1	= client.c \
	  utils.c
SRCS2	= server.c \
	  utils.c

CC	= gcc
CFLAGS 	= -Wall -Wextra -Werror
RM	= rm -rf

OBJSFD 	= temp

OBJS1	= $(addprefix $(OBJSFD)/,$(SRCS1:.c=.o))

OBJS2	= $(addprefix $(OBJSFD)/,$(SRCS2:.c=.o))

HDR	= -I./
LFT_HDR = -I$(LFT_DIR)
LFT_BIN = -L$(LFT_DIR) -lft

all: $(LIBFT) ./libft/libft.a $(NAME1) $(NAME2)

FORCE:	;
	
LIBFT	= ./libft/libft.a

$(LIBFT): FORCE
	make -C ./libft

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: %.c Makefile | $(OBJSFD)
	gcc -g $(CFLAGS) $(HDR) $(LFT_HDR) -c $< -o $@

$(NAME1): $(OBJS1) ./minitalk.h
	gcc -g $(OBJS1) $(LFT_BIN) -o $@

$(NAME2): $(OBJS2) ./minitalk.h
	gcc -g $(OBJS2) $(LFT_BIN) -o $@

clean:
	$(RM) $(OBJSFD)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)
	make -C ./libft fclean

re: 	fclean all