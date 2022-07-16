#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <math.h>
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

long factorize(char* tuple, int stage, long l) {
	FILE* fp = fopen64("./pi.txt","r");
	FILE* fe = fopen64("./e.txt","r");
	long hit = 0;
	long pos = 0;
	char pp = 0, ee = 0;
	while (hit < (int(ceil(l/3)*64) - 1)) {
		fscanf(fp, "%c", &pp);
		fscanf(fe, "%c", &ee);
		if (pp == tuple[0] && ee == tuple[1]) {
			++hit;
		}
		++pos;
	}
	fclose(fp);
	fclose(fe);
	return pos;
}

long reverse(long p) {
	long rev = 0;
	while (p > 0) {
		rev = (rev*10) + (p % 10);
		p /= 10;
	}
	return rev;
}

int main(int argc, char* argv[]) {
	FILE* characterization_output = fopen64("./op.txt", "w");
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*>* tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	characterize(num, *tuples);
	long l = strlen(num);
	std::string factor_lt = "";
	std::string factor_gt = "";
	int polarity1 = -1, polarity2 = -1;
	long sz = tuples->size();
	vector<long> posits;
	for (int i = 0; i < sz; ++i) {
		char* tuple = tuples->at(i);
		int u = 0, w = 0;
		int polarity1 = 0, polarity2 = 0;
		long pos = factorize(tuple, i + 1, l);
		fprintf(characterization_output, "%ld", pos + 1);
		posits.push_back(pos + 1);
		cout << tuple << "\t" << pos + 1 << endl;
	}
	fclose(characterization_output);
	FILE* characterization_output2 = fopen64("./op2.txt", "w");
	for (int i = sz - 1; i >= 0; --i) {
		long posit = reverse(posits[i]);
		fprintf(characterization_output2, "%ld", posit);
	}
	fclose(characterization_output2);
	for (int i = 0; i < tuples->size(); ++i) {
		free(tuples->at(i));
	}
	free(tuples);
	return 0;
}
