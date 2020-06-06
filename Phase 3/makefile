all:
	flex LEX.l
	bison -dy SYN.y
	g++ -Wno-write-strings -std=gnu++11 Label.cpp lex.yy.c y.tab.c
	a
exec: all
	./a.out
