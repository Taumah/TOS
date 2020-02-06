gcc:
	gcc -std=c11 -pthread -Werror -Wall -Wextra src/*.c -o bin/superpixmanip -g