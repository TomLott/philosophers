NAME = philo_one

FLAGS = -Wall -Werror -Wextra

SRCS = init.c \
		philo_one.c \
		status.c \
		threads.c \
		utils_1.c \
		utils_2.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		gcc $(FLAGS) -o $(NAME) $(OBJS)

.c.o:
		gcc $(FLAGS) -c $< -o $@