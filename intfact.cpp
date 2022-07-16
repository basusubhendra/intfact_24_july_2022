#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

struct packet {
	long p1;
	long p2;
};

struct return_packet {
	long p1;
	long p2;
	char* factor;
};

void* factorize(void* arg) {
	struct packet* p = (struct packet*) arg;
	long p1 = p->p1;
	long p2 = p->p2;
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
	struct packet* ptr1 = (struct packet*) calloc(1, sizeof(struct packet));
	struct packet* ptr2 = (struct packet*) calloc(1, sizeof(struct packet));
	long fpos1 = 0, fpos2 = 0, fpos3 = 0, fpos4 = 0;
	ptr1->p1 = fpos1;
	ptr1->p2 = fpos2;
	ptr2->p1 = fpos3;
	ptr2->p2 = fpos4;
	struct return_packet* ret1, *ret2;
	pthread_t thread_id1, thread_id2;
	pthread_create(&thread_id1, NULL, factorize, ptr1);
	pthread_create(&thread_id2, NULL, factorize, ptr2);
	pthread_join(thread_id1, (void**) &ret1);
	pthread_join(thread_id2, (void**) &ret2);
	return 0;
}
