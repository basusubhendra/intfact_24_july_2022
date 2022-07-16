#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

vector<char*>* heap1 = 0, *heap2 = 0;

void* factorize(void* arg) {
	int t = *(int*) arg;
	std::string factor = "";
	FILE* f1 = fopen64("./op.txt", "r");
	FILE* f2 = fopen64("./op2.txt", "r");
	FILE* fp = fopen64("./pi.txt", "r");
	FILE* fe = fopen64("./e.txt", "r");
	char posit1 = 0, posit2 = 0;
	char pp = 0, ee = 0;
	int ret1 = fscanf(f1, "%c", &posit1);
	int ret2 = fscanf(f2, "%c", &posit2);
	long numerator_sum = 0;
	long denominator_sum = 0;
	while (1) {
		bool pk_hit = false, ek_hit = false;
		fscanf(fp, "%c", &pp);
		fscanf(fe, "%c", &ee);
		int pk = pp - '0';
		int ek = ee - '0';
		bool is_pk_even = (pk % 2 == 0);
		bool is_pk_odd = (pk % 2 == 1);
		bool is_ek_even = (ek % 2 == 0);
		bool is_ek_odd = (ek % 2 == 1);
		if (t == 0 && is_pk_odd) {
			pk_hit = true;
		}
		if (t == 0 && is_ek_even) {
			ek_hit = true;
		}
		if (t == 1 && is_pk_even) {
			pk_hit = true;
		}
		if (t == 1 && is_pk_odd) {
			ek_hit = true;
		}
		if (pk_hit && ek_hit && ((t == 1 && pp == posit2 && ee == posit1) || (t == 0 && pp == posit1 && ee == posit2))) {
			cout << "numerator_sum\t" << numerator_sum << endl;
			cout << "denominator_sum\t" << denominator_sum << endl;
			system("a=1; read a");
			factor += boost::lexical_cast<std::string>(abs(numerator_sum - denominator_sum));
			if (t == 0) {
				heap1->push_back(strdup((char*) factor.c_str()));
			} else if (t == 1) {
				heap2->push_back(strdup((char*) factor.c_str()));
			}
			numerator_sum = 0;
			denominator_sum = 0;
			ret1 = fscanf(f1, "%c", &posit1);
			ret2 = fscanf(f2, "%c", &posit2);
			if (ret1 == EOF) {
				fseek(f1, 0, SEEK_SET);
			}
			if (ret2 == EOF) {
				fseek(f2, 0, SEEK_SET);
			}
		} else if (pk_hit && ((t == 1 && pp == posit2) || (t == 0 && pp == posit1))) {
			numerator_sum += pk;
			fscanf(f1, "%c", &posit1);
			ret1 = fscanf(f1, "%c", &posit1);
			if (ret1 == EOF) {
				fseek(f1, 0, SEEK_SET);
			}
		} else if (ek_hit && ((t == 1 && ee == posit2) || (t == 0 && ee == posit1))) {
			denominator_sum += ek;
			fscanf(f2, "%c", &posit2);
			ret2 = fscanf(f2, "%c", &posit2);
			if (ret2 == EOF) {
				fseek(f2, 0, SEEK_SET);
			}
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
	heap1 = (vector<char*>*) calloc(1, sizeof(vector<char*>));
        heap2 = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	pthread_t thread_id1, thread_id2;
	pthread_create(&thread_id1, NULL, factorize, &t);
	t = 1 - t;
	pthread_create(&thread_id2, NULL, factorize, &t);
	pthread_join(thread_id1, (void**) &ret1);
	pthread_join(thread_id2, (void**) &ret2);
	return 0;
}
