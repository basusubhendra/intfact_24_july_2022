#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <gmp.h>
#include <vector>
#include "pi.hpp"
#include "e.hpp"
using namespace std;

char* quotient(char* num, char* factor, bool& succ) {
	mpz_t nz;
	mpz_init(nz);
	mpz_set_str(nz, num, 10);
	mpz_t fz;
	mpz_init(fz);
	mpz_set_str(fz, factor, 10);
	if (mpz_cmp_si(fz, 0) == 0 || mpz_cmp_ui(fz, 1) == 0) {
		return 0;
	}
	mpz_t qz;
	mpz_init(qz);
	mpz_div(qz, nz, fz);
	mpz_t rz;
	mpz_init(rz);
	mpz_mod(rz, nz, fz);
	succ = (mpz_cmp_si(rz, 0) == 0);
	mpz_clear(nz);
	mpz_clear(fz);
	mpz_clear(rz);
	if (succ) {
		char* quot = strdup(mpz_get_str(0, 10, qz));
		mpz_clear(qz);
		return quot;
	} else {
		mpz_clear(qz);
		return 0;
	}
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	long ctr = l - 1;
	FILE* fp = fopen64("./pi.txt", "r");
	FILE* fe = fopen64("./e.txt", "r");
	long* hash_map = (long*) calloc(10, sizeof(long));
	vector<long> posits;
	char pp = 0;
	while (ctr >= 0) {
		char nn = num[ctr];
		fscanf(fp, "%c", &pp);
		hash_map[pp-'0']++;
		if (pp == nn) {
			posits.push_back(hash_map[pp-'0']);
			--ctr;
		}
	}
	std::string factor = "";
	char* last_ptr = (char*) pi;
	for (int i = 0; i < posits.size(); ++i) {
		int pk = posits[i];
		char pp[128];
		sprintf(pp, "%d", pk);
		char* ptr = strstr(last_ptr , pp);
                last_ptr = ptr;
	}
	return 0;
}
