.PHONY: clean control compile write
compile: compile1 compile2
compile1: wordle.o control.o
	@gcc -o controlme wordle.o control.o
compile2: write.o
	@gcc -o writeme write.o
control.o: control.c wordle.h
	@gcc -c control.c
write.o: write.c
	@gcc -c write.c
wordle.o: wordle.c
	@gcc -c wordle.c
control: controlme
	@./controlme $(ARGS)
write: writeme
	@./writeme
clean:
	rm *.o
	rm controlme
	rm writeme
