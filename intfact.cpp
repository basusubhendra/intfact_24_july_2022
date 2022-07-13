#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

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

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*> tuples;
	characterize(num, tuples);
	for(int i = 0; i < tuples.size(); ++i) {
		printf("\n%s\n", tuples[i]);
	}
	return 0;
}
