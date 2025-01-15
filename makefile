.PHONY: clean compile init
compile initme: wordle.o init.o
	@gcc -o initme wordle.o init.o
wordle.o: wordle.c wordle.h
	@gcc -c wordle.c
init.o: init.c
	@gcc -c init.c
init: initme
	@./initme $(ARGS)
clean:
	rm *.o
	rm initme
	rm *.txt
