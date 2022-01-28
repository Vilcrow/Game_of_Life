CC = gcc
CFLAGS = -g -Wall
SRCMODULES = carriage.c cell.c colpairs.c msgbox.c preparation.c renderer.c interface.c
OBJMODULES = $(SRCMODULES:.c=.o)

%.o: %.c %.h
			$(CC) $(CFLAGS) -c $< -o $@

gameoflife: main.c const.h $(OBJMODULES)
				$(CC) $(CFLAGS) $^ -o $@ -lncurses

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
		$(CC) -MM $^ > $@

run: gameoflife
				./gameoflife

clean:
		rm -f *.o gameoflife

