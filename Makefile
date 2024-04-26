CFLAGS = -Wall -02

PROG = register
FONTES = register.c
OBJETOS = & (FONTES: .c=.o)

$(PROG): $(OBJETOS)
	gcc $(CFLAGS) &(OBJETOS) -o $@

clean:
	-@ rm -f $(OBJETOS) $(PROG)