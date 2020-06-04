all:
	flex LEX.l
	bison -dy SYN.y
	g++ -Wno-write-strings -std=gnu++11 lex.yy.c y.tab.c
exec: all
	./a.out
