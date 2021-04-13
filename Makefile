CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c util_valid.c util_str.c util_etc.c util_set.c util_solve.c util_keyboard_1.c util_keyboard_2.c util_standard.c
TARGET = BSQ

all : $(TARGET)

$(TARGET) : 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean :
	rm -f util_valid.o util_str.o util_etc.o util_set.o util_solve.o util_keyboard_1.o util_keyboard_2.o util_standard.o

fclean : clean
	rm -f $(TARGET)

re :
	make fclean
	make all
