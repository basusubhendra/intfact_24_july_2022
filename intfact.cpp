#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

void* factorize(void* arg) {
	int t = *(int*) arg;
	std::string factor = "";
	FILE* f1 = fopen64("./op.txt", "r");
	FILE* f2 = fopen64("./op2.txt", "r");
	FILE* fp = fopen64("./pi.txt", "r");
	FILE* fe = fopen64("./e.txt", "r");
	char posit1 = 0, posit2 = 0;
	char pp = 0, ee = 0;
	fscanf(f1, "%c", &posit1);
	fscanf(f2, "%c", &posit2);
	long numerator_sum = 0;
	long denominator_sum = 0;
	while (1) {
		fscanf(fp, "%c", &pp);
		fscanf(fe, "%c", &ee);
		if ((t == 1 && pp == posit2 && ee == posit1) || (t == 0 && pp == posit1 && ee == posit2)) {
			cout << "numerator_sum\t" << numerator_sum << endl;
			cout << "denominator_sum\t" << denominator_sum << endl;
			factor += boost::lexical_cast<std::string>(abs(numerator_sum - denominator_sum));
			numerator_sum = 0;
			denominator_sum = 0;
			fscanf(f1, "%c", &posit1);
			fscanf(f2, "%c", &posit2);
		} else if ((t == 1 && pp == posit2) || (t == 0 && pp == posit1)) {
			numerator_sum += (pp - '0');
			fscanf(f1, "%c", &posit1);
		} else if ((t == 1 && ee == posit2) || (t == 0 && pp == posit1)) {
			denominator_sum += (ee - '0');
			fscanf(f2, "%c", &posit2);
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(fp);
	fclose(fe);
	return strdup((char*) factor.c_str());
}

int main() {
	char* ret1, *ret2;
	int t = 0;
	pthread_t thread_id1, thread_id2;
	pthread_create(&thread_id1, NULL, factorize, &t);
	t = 1 - t;
	pthread_create(&thread_id2, NULL, factorize, &t);
	pthread_join(thread_id1, (void**) &ret1);
	pthread_join(thread_id2, (void**) &ret2);
	return 0;
}
