#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

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
#ifdef _DEBUG
		cout << pp << "\t" << ee << "\n" << posit1 << "\t" << posit2 << endl;
		system("a=1;read a");
#endif
		int pk = pp - '0';
		int ek = ee - '0';
		bool is_pk_even = (pk != 0 && pk % 2 == 0);
		bool is_pk_odd = (pk != 0 && pk % 2 == 1);
		bool is_ek_even = (ek != 0 && ek % 2 == 0);
		bool is_ek_odd = (ek != 0 && ek % 2 == 1);
		if (t == 0 && is_ek_odd) {
			pk_hit = true;
		}
		if (t == 0 && is_pk_even) {
			ek_hit = true;
		}
		if (t == 1 && is_pk_odd) {
			ek_hit = true;
		}
		if (t == 1 && is_ek_even) {
			pk_hit = true;
		}
		if (pk_hit && ek_hit && ((t == 1 && pp == posit2 && ee == posit1) || (t == 0 && pp == posit1 && ee == posit2))) {
		        pid_t x = syscall(__NR_gettid);
			cout << endl << x << "\t" << pp << "\t" << ee << endl;
			return 0;
			ret1 = fscanf(f1, "%c", &posit1);
			ret2 = fscanf(f2, "%c", &posit2);
			if (ret1 == EOF) {
				fseek(f1, 0, SEEK_SET);
			}
			if (ret2 == EOF) {
				fseek(f2, 0, SEEK_SET);
			}
		} else if (pk_hit && ((t == 1 && pp == posit2) || (t == 0 && pp == posit1))) {
#ifdef _DEBUG
			cout << "\npk_hit\n";
#endif
			//numerator_sum += pk;
			if (t == 1) {
				ret2 = fscanf(f2, "%c", &posit2);
			} else if (t == 0) {
				ret1 = fscanf(f1, "%c", &posit1);
			}
			if (ret1 == EOF) {
				fseek(f1, 0, SEEK_SET);
			}
			if (ret2 == EOF) {
				fseek(f2, 0, SEEK_SET);
			}
		} else if (ek_hit && ((t == 0 && ee == posit2) || (t == 1 && ee == posit1))) {
#ifdef _DEBUG
			cout << "\nek_hit\n";
#endif
			//denominator_sum += ek;
			if (t == 0) {
				ret2 = fscanf(f2, "%c", &posit2);
			} else if (t == 1) {
				ret1 = fscanf(f1, "%c", &posit1);
			}
			if (ret1 == EOF) {
				fseek(f1, 0, SEEK_SET);
			}
			if (ret2 == EOF) {
				fseek(f2, 0, SEEK_SET);
			}
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(fp);
	fclose(fe);
	return 0;
}

int main() {
	int t = 0;
	heap1 = (vector<char*>*) calloc(1, sizeof(vector<char*>));
        heap2 = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	pthread_t thread_id1, thread_id2;
	pthread_create(&thread_id1, NULL, factorize, &t);
	int t2 = 1 - t;
	pthread_create(&thread_id2, NULL, factorize, &t2);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	return 0;
}
