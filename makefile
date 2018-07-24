FCC = gcc
LDC = gcc
LDC_FLAGS = -std=c11
FLAGS = -std=c11
PROG = main.cx
RM = /bin/rm
OBJS = main.o

all: $(PROG)

$(PROG): $(OBJS)
	$(LDC) $(LDC_FLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(FCC) $(FLAGS) -c $<

clean:
	$(RM) -rf *.o $(PROG) *.mo *.png *.grid *.speed
