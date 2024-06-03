CC = gcc
SRCS = main.c register.c
EXEC = exec

all: $(EXEC)

$(EXEC):
	$(CC) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC)