FCC = gcc
LDC_s = gcc
LDC_s_FLAGS = -std=c11
LDC_p = gcc
LDC_p_FLAGS = -std=c11
PROG_p = main.cx
OBJS_p = main.o
FLAGS = -std=c11
PROG_s = main_s.cx
RM = /bin/rm
OBJS_s = main_s.o



all: $(PROG_s) $(PROG_p)

$(PROG_s): $(OBJS_s)
	$(LDC_s) $(LDC_FLAGS_s) $(OBJS_s) -o $(PROG_s)

$(PROG_p): $(OBJS_p)
	$(LDC_p) $(LDC_FLAGS_p) $(OBJS_p) -o $(PROG_p)


%.o: %.c
	$(FCC) $(FLAGS) -c $<

clean:
	$(RM) -rf *.o $(PROG_s) $(PROG_p) *.mo *.png *.grid *.speed
