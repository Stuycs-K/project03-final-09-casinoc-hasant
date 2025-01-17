.PHONY: clean compile init
compile initme: wordle.o init.o
	@gcc -o initme -g wordle.o init.o
wordle.o: wordle.c wordle.h
	@gcc -c wordle.c -g
init.o: init.c
	@gcc -c init.c -g
init: initme
	@./initme $(ARGS)
clean:
	rm *.o
	rm initme
