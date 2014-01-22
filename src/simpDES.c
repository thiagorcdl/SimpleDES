#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTLEN (1<<30)

char plainText[TEXTLEN];
short int key;
char *cipherText;
int s0[4][4] = { 1,0,3,2
		,3,2,1,0
		,0,2,1,3
		,3,1,3,2 };
int s1[4][4] = { 0,1,2,3
		,2,0,1,3
		,3,0,1,0
		,2,1,0,3 };

/* Permut8 of key */
char p8(short int key){
	char n_key = 0;

	n_key |= (char) (key << 3) & 0x0080;
	n_key |= (char) (key >> 1) & 0x0040;
	n_key |= (char) (key << 2) & 0x0020;
	n_key |= (char) (key >> 2) & 0x0010;
	n_key |= (char) (key << 1) & 0x0008;
	n_key |= (char) (key >> 3) & 0x0004;
	n_key |= (char) (key << 1) & 0x0002;
	n_key |= (char) (key >> 1) & 0x0001; 
	return n_key;
}

/* Permut10 of key */
short int p10(short int key){
	short int n_key = 0;

	n_key |= (key << 2) & 0x0200;
	n_key |= (key << 3) & 0x0100;
	n_key |= (key >> 1) & 0x0080;
	n_key |= (key << 3) & 0x0040;
	n_key |= (key >> 1) & 0x0020;
	n_key |= (key << 4) & 0x0010;
	n_key |= (key >> 6) & 0x0008;
	n_key |= (key << 1) & 0x0004;
	n_key |= (key >> 1) & 0x0002;
	n_key |= (key >> 4) & 0x0001; 
	return n_key;
}

/* Initial permutation */
char ip(char charmander){
	char c = 0;

	c |= (charmander << 1) & 0x80;
	c |= (charmander << 4) & 0x40;
	c |= (charmander     ) & 0x20;
	c |= (charmander >> 3) & 0x10;
	c |= (charmander >> 1) & 0x08;
	c |= (charmander << 2) & 0x04;
	c |= (charmander >> 2) & 0x02;
	c |= (charmander >> 1) & 0x01;
	return c;
}

/* (Initial permutation)^(-1) */
char ip_1(char charmeleon){
	char c = 0;

	c |= (charmeleon << 3) & 0x80;
	c |= (charmeleon >> 1) & 0x40;
	c |= (charmeleon     ) & 0x20;
	c |= (charmeleon << 1) & 0x10;
	c |= (charmeleon << 2) & 0x08;
	c |= (charmeleon >> 4) & 0x04;
	c |= (charmeleon << 1) & 0x02;
	c |= (charmeleon >> 2) & 0x01;
	return c;
}

/* Expansion/Permutation */
char expansion(char charizard){
	char c = 0;

	c |= (charizard << 7) & 0x80;
	c |= (charizard << 3) & 0x40;
	c |= (charizard << 3) & 0x20;
	c |= (charizard << 3) & 0x10;
	c |= (charizard << 1) & 0x08;
	c |= (charizard << 1) & 0x04;
	c |= (charizard << 1) & 0x02;
	c |= (charizard >> 3) & 0x01;
	return c;
}

short int ls_1(short int seila){
	short int c = 0;

	c = (seila << 1) & 0x0200;
	c|= (seila << 1) & 0x0100;
	c|= (seila << 1) & 0x0080;
	c|= (seila << 1) & 0x0040;
	c|= (seila >> 4) & 0x0020;
	c|= (seila << 1) & 0x0010;
	c|= (seila << 1) & 0x0008;
	c|= (seila << 1) & 0x0004;
	c|= (seila << 1) & 0x0002;
	c|= (seila >> 4) & 0x0001;
	return c;
}

short int ls_2(short int seila){
	short int c = 0;

	c = (seila << 2) & 0x0200;
	c|= (seila << 2) & 0x0100;
	c|= (seila << 2) & 0x0080;
	c|= (seila >> 3) & 0x0040;
	c|= (seila >> 3) & 0x0020;
	c|= (seila << 2) & 0x0010;
	c|= (seila << 2) & 0x0008;
	c|= (seila << 2) & 0x0004;
	c|= (seila >> 3) & 0x0002;
	c|= (seila >> 3) & 0x0001;
	return c;
}

char fk(char kp8, char exp){
	char c, d;
	char a, b, lin, col;

	c = kp8 ^ exp;

	lin  = (c >> 4) & 0x01;
	lin |= (c >> 6) & 0x02;
	col  = (c >> 5) & 0x01;
	col |= (c >> 5) & 0x02;
	a    = s0[lin][col];

	lin  = c & 0x01;
	lin |= (c >> 2) & 0x02;
	col  = (c >> 1) & 0x01;
	col |= (c >> 1) & 0x02;
	b    = s1[lin][col];

	d  =  c = 0;
	d  = (a << 2) | b;
	c  = (d << 1) & 0x08;
	c |= (d << 2) & 0x04;
	c |= (d     ) & 0x02;
	c |= (d >> 3) & 0x01;

	return c;
}

/* Get arguments */
int getArgs(int argc, char **argv){
	int size=0;
	if(argc != 2)
		return 0;
	else {
		//fgets(plainText, TEXTLEN, stdin); // get 8-bit text
		size = read(0, plainText, TEXTLEN);
		sscanf(argv[1], "%hx", &key); // get 10-bit key
		key = key & 0x03ff;
		return size;
	}
}

