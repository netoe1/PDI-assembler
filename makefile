all:
	gcc -o assembler assembler.c instruction-set.c debug-modules.c utils.c coder.c
dev:

	gcc -o testing testing.c instruction-set.c utils.c debug-modules.c
crun:
	make all
	make run
run:
	./main

clean:
	rm -rf main testing assembler *.obj *.bin