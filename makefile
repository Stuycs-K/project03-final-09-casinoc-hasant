.PHONY: clean compile init
compile: wordle.o init.o
	@gcc -o initme init.o wordle.o
wordle.o: wordle.c
	@gcc -c wordle.c
init.o: init.c wordle.h
	@gcc -c init.c $(ARGS)
init: initme
	@./initme
clean:
	rm *.o
	rm initme
	rm *.txt
