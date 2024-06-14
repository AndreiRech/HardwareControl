CC = gcc
MAIN = main.c
EXEC = exec
LIB_NAME = libregister.a
LIB_MAIN = register.c
LIB_OBJ = $(LIB_MAIN:.c=.o)
CFLAGS = -I.

all: $(EXEC)

$(EXEC): $(MAIN) $(LIB_NAME)
	$(CC) $(MAIN) -o $(EXEC) -L. -lregister

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $(LIB_NAME) $(LIB_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(LIB_NAME) $(LIB_OBJ)