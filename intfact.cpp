#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <pthread.h>
using namespace std;

void* characterize(char* num, vector<char*>& tuples, vector<char*>& reverse_tuples) {
	long l = strlen(num);
	for (long i = l - 1; i >= 0; --i) {
		char* tuple = (char*) calloc(3, sizeof(char));
		tuple[0] = num[l - 1 - i];
		tuple[1] = num[i];
		tuple[2] = '\0';
		tuples.push_back(tuple);
		char* reverse_tuple = (char*) calloc(3, sizeof(char));
		reverse_tuple[0] = num[i];
		reverse_tuple[1] = num[l - 1 - i];
		reverse_tuple[2] = '\0';
		reverse_tuples.push_back(reverse_tuple);
	}
	return 0;
}

void* factorize(void* arg) {
	vector<char*>* tuples = (vector<char*>*) arg;
	FILE* fp = fopen64("./pi.txt", "r");
	FILE* fe = fopen64("./e.txt", "r");
	fclose(fp);
	fclose(fe);
	return 0;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*>* tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	vector<char*>* reverse_tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	characterize(num, *tuples, *reverse_tuples);
	pthread_t thread_id1, thread_id2;
	char* factor1 = 0, *factor2 = 0;
	pthread_create(&thread_id1, NULL, factorize, tuples);
	pthread_create(&thread_id2, NULL, factorize, reverse_tuples);
	pthread_join(thread_id1, (void**) &factor1);
	pthread_join(thread_id2, (void**) &factor2);
	free(tuples);
	free(reverse_tuples);
	return 0;
}
