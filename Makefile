all: nektech_shell

nektech_shell: input_parser.o cmd_execution.o
	gcc input_parser.o cmd_execution.o -o nektech_shell

cmd_execution.o: cmd_execution.c
	gcc -c -g cmd_execution.c

input_parser.o: input_parser.c
	gcc -c -g input_parser.c

clean:
	rm -rf *.o nektech_shell
install:
	cp ./nektech_shell /bin
