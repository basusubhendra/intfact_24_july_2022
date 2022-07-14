#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

void* characterize(char* num, vector<char*>& tuples) {
	long l = strlen(num);
	for (long i = l - 1; i >= 0; --i) {
		char* tuple = (char*) calloc(3, sizeof(char));
		tuple[0] = num[l - 1 - i];
		tuple[1] = num[i];
		tuple[2] = '\0';
		tuples.push_back(tuple);
	}
	return 0;
}

void* factorize(void* arg) {
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*>* tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	characterize(num, *tuples);
	for (int i = 0; i < tuples->size(); ++i) {
		free(tuples->at(i));
	}
	free(tuples);
	return 0;
}
