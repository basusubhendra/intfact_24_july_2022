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

void* factorize(char* tuple, int& factor1, int& factor2, int& polarity) {
	FILE* fp = fopen64("./pi.txt","r");
	FILE* fe = fopen64("./e.txt","r");
	fclose(fp);
	fclose(fe);
	return 0;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*>* tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	characterize(num, *tuples);
	std::string factor_lt = "";
	std::string factor_gt = "";
	int polarity = -1;
	for (int i = 0; i < tuples->size(); ++i) {
		char* tuple = tuples->at(i);
		int factor1 = 0, factor2 = 0;
		factorize(tuple, factor1, factor2, polarity);
		factor_lt += boost::lexical_cast<std::string>((polarity==0)? factor1:factor2);
		factor_gt += boost::lexical_cast<std::string>((polarity==0)? factor2:factor1);
		polarity = 1 - polarity;
	}
	for (int i = 0; i < tuples->size(); ++i) {
		free(tuples->at(i));
	}
	free(tuples);
	return 0;
}
