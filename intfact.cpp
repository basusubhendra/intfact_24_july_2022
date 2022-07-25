#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <gmp.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
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

long reverse(long x) {
	long rev = 0;
	while (x > 0) {
		rev = rev*10 + (x % 10);
		x /= 10;
	}
	return rev;
}

long compute_distance(char* s1, char* s2, long& location) {
	char* ptr1 = strstr((char*)e, s1);
        char* ptr2 = strstr(ptr1, s2);
	long short_len = ptr2 - ptr1 + 1;
	char* tmp = (char*) calloc(short_len + 1, sizeof(char));
	strncpy(tmp, ptr1, short_len);
	ptr1 = strstr(tmp, s1);
	while (ptr1) {
		ptr1 = strstr(ptr1, s1);
	}
	char* p = ptr1;
	long distance = 0;
	while (p != ptr2) {
		if (*p == '0') {
			distance = 0;
		} 
		++distance;
		++p;
	}
	free(tmp);
	return distance;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	FILE* comparator_pi = fopen64("./pi.txt","r");
	int ctr = l - 1;
	long* hash_map = (long*) calloc(10, sizeof(long));
	std::string factor = "";
	long location = 0;
	long pos = 0, last_pos = 0;
	for (int i = ctr; i > 0; --i) {
		char nn1 = num[i];
		char nn2 = num[i - 1];
		long pos1 = -1, pos2 = -1;
		cout << nn1 << "\t" << nn2 << endl;
		while (1) {
			char pp = 0;
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if ((pp == nn1) && (pp == num[pos % l])) {
					pos1 = reverse(hash_map[pp-'0']);
					last_pos = pos;
				}
				if ((pp == nn2) && (pp == num[pos % l]) && (pos > last_pos)) {
					pos2 = reverse(hash_map[pp-'0']);
					++pos;
					break;
				}
				++pos;
			}
			if (pos1 != pos2) {
				break;
			}
		}
		char* s_pos1 = (char*) calloc(128, sizeof(char));
		char* s_pos2 = (char*) calloc(128, sizeof(char));
		sprintf(s_pos1, "%ld", pos1);
		sprintf(s_pos2, "%ld", pos2);
		cout << s_pos1 << "\t" << s_pos2 << endl;
		long distance = compute_distance(s_pos1, s_pos2, location);
		cout << endl << distance << endl;
		free(s_pos1);
		free(s_pos2);
		factor += boost::lexical_cast<std::string>(distance);
	}
	fclose(comparator_pi);
	bool succ = false;
	char* other_factor = quotient(num, strdup((char*) factor.c_str()), succ);
	if (succ == true) {
		printf("\n%s\t=%s\tX\t%s\n",num, strdup((char*) factor.c_str()), other_factor);
	}
	return 0;
}
