#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

int main() {
	FILE* f1 = fopen64("./op.txt","r");
	FILE* f2 = fopen64("./op2.txt","r");
	fclose(f1);
	fclose(f2);
	return 0;
}
