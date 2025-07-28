all:
	gcc -o main main.c instruction-set.c debug-modules.c utils.c
test:

	gcc -o testing testing.c instruction-set.c utils.c debug-modules.c
crun:
	make all
	make run
run:
	./main

clean:
	rm -rf main testing *.obj *.bin