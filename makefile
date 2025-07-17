all:
	gcc -o main main.c instruction-set.c debug-modules.c utils.c

crun:
	make all
	make run
run:
	./main

clean:
	rm -rf main teste.forg *.obj *.bin