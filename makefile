.PHONY: clean game compile init
compile: compile1 compile2
compile1: wordle.o game.o
	@gcc -o gameme wordle.o game.o
compile2: init.o
	@gcc -o initme init.o
game.o: game.c wordle.h
	@gcc -c game.c
wordle.o: wordle.c
	@gcc -c wordle.c
init.o: init.c
	@gcc -c init.c
game: gameme
	@./gameme $(ARGS)
init: initme
	@./initme
clean:
	rm *.o
	rm gameme
	rm initme
