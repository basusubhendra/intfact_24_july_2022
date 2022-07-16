#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

void* factorize(void* arg) {
	struct return_packet* ret = (struct return_packet*) calloc(1, sizeof(struct return_packet));
	FILE* f1 = fopen64("./op.txt", "r");
	FILE* f2 = fopen64("./op2.txt", "r");
	fseek(f1, p1, SEEK_SET);
	fseek(f2, p2, SEEK_SET);
	char posit1 = 0, posit2 = 0;
	while (1) {
		fscanf(f1, "%c", &pp);
		fscanf(f2, "%c", &ee);
		if (pp == 
	}
	fclose(f1);
	fclose(f2);
	return ret;
}

int main() {
	char* ret1, *ret2;
	pthread_t thread_id1, thread_id2;
	pthread_create(&thread_id1, NULL, factorize, NULL);
	pthread_create(&thread_id2, NULL, factorize, NULL);
	pthread_join(thread_id1, (void**) &ret1);
	pthread_join(thread_id2, (void**) &ret2);
	return 0;
}
