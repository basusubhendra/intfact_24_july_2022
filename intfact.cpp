#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <gmp.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "pi.hpp"
#include "e.hpp"
using namespace std;
using namespace boost;

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

void* strrev(char* ss) {
	long l = strlen(ss);
	for (int i = 0; i < (l / 2); ++i) {
		char t = ss[i];
		ss[i] = ss[l - 1 - i];
		ss[l - 1 - i] = t;
	}
	return 0;
}

int _length(long x) {
	long cnt = 0;
	while (x > 0) {
		x /= 10;
		if (x > 0) {
			++cnt;
		}
	}
	return cnt;
}

bool _compare(char* p, long init_posit) {
	char* s = p;
	while (init_posit > 0) {
		int sk = *s - '0';
		if (sk == init_posit % 10) {
			init_posit /= 10;
			--s;
		} else {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	long ctr = l - 1;
	FILE* fp = fopen64("./pi.txt", "r");
	long* hash_map = (long*) calloc(10, sizeof(long));
	vector<long> posits;
	char pp = 0;
	long pos = 0;
	std::string factor = "";
	while (ctr >= 0) {
		char nn = num[ctr];
		char _nn = num[pos % l];
		fscanf(fp, "%c", &pp);
		hash_map[pp-'0']++;
		if (pp == nn && pp == _nn) {
			posits.push_back(hash_map[pp-'0']);
			--ctr;
		}
		++pos;
	}
	for (int i = 0; i < posits.size(); ++i) {
		cout << posits[i] << "\t, ";
	}
	cout << endl;
	char _dd[128];
	char* last_ptr1 = (char*)pi;
	for (int i = 0; i < posits.size(); ++i) {
		sprintf(_dd, "%ld", posits[i]);
		char* ptr = strstr(last_ptr1, _dd);
		last_ptr1 = ptr;
	}
	long increment1 = last_ptr1 - pi + 1;
	increment1 += strlen(_dd);
	--increment1;
	char* ee = (char*) calloc(increment1 + 1, sizeof(char));
	ee[increment1] = '\0';
	strncpy(ee, e, increment1);
	strrev(ee);
	char* pp3 = (char*) calloc(increment1 + 1, sizeof(char));
	pp3[increment1] = '\0';
	strncpy(pp3, pi, increment1);
	cout << pp3 << endl;
	cout << ee << endl;
	long i = 0;
	long init_posit = posits[i];
	char _pp[128];
	sprintf(_pp, "%ld", init_posit);
	char* last_ptr = strstr((char*)pi ,_pp);
	long increment = last_ptr - pi + 1;
	cout << ee[increment] << endl;
	for (int i = 1; i < posits.size(); ++i) {
		long pk = posits[i];
		if (pk == init_posit) {
			factor += boost::lexical_cast<std::string>(0);
			init_posit = pk;
			continue;
		}
		init_posit = pk;
		sprintf(_pp, "%ld", pk);
		char* ptr = strstr(last_ptr , _pp);
		increment += ptr - last_ptr;
		cout << ee[increment] << endl;
		exit(3);
		char* p = ptr;
		--p;
		long cnt = 0;
		while (1) {
			if (_compare(p, init_posit) == true) {
				cnt += _length(init_posit);
				break;
			}
			if (p == last_ptr) {
				break;
			}
			++cnt;
			--p;
		}	
		cout << endl << cnt << endl;
		system("a=1; read a");
		factor += boost::lexical_cast<std::string>(cnt);
		last_ptr = ptr;
	}
	bool succ = false;
	char* other_factor = quotient(num, strdup((char*) factor.c_str()), succ);
	if (succ) {
		cout << endl << num << "\t=\t" << factor << "\tX\t" << other_factor << endl;
	}
	return 0;
}
