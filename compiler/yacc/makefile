all:run

run:
	bison -y -d -v B033040006.y
	flex B033040006.l
	gcc lex.yy.c y.tab.c -ly -lfl
