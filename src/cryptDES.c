#include "simpDES.c"


int main(int argc, char **argv){
	int i, size;
	char k1, k2, c, more, less;

	memset(plainText,'\0',TEXTLEN);
	size = getArgs(argc, argv);
	if(size <= 0)
		return 1;

	key = p10(key);
	key = ls_1(key);
	k1  = p8(key);
	key = ls_2(key);
	k2  = p8(key);

	for(i=0;i<size;i++){
		// 1st diagram
		c = plainText[i];
		c = ip(c);
		more = (c >> 4) & 0x0f;
		less = c & 0x0f;
		c = expansion(less);
		c = fk(k1, c);
		more = c = more ^ c;

		// 2nd diagram
		c = expansion(c);
		c = fk(k2, c);
		c = (c ^ less) << 4;
		c = c | more;
		c = ip_1(c);
		printf("%c",c);
	}
	return 0;
}
