#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <gmp.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
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

long _locate(char* ss, long loc, FILE* _c_pi) {
	char pp = 0;
	char* _ss = ss;
	fseek(_c_pi, loc, SEEK_SET);
	while (1) {
		while (1) {
			fscanf(_c_pi, "%c", &pp);
			if (pp == *ss) {
		                ++ss;
				break;
			}
		}
		while (*ss != '\0') {
			fscanf(_c_pi, "%c", &pp);
			if (pp == *ss) {
				++ss;
			} else {
				break;
			}
		}
		if (*ss == '\0') {
			break;
		} else {
			ss = _ss;
		}
	}
	return ftello(_c_pi);
}

long _compute_distance(long loc1, long loc2, FILE* _c_pi) {
	fseek(_c_pi, loc1, SEEK_SET);
	char pp = 0;
	long distance = 0;
	while (ftello(_c_pi) != loc2) {
		fscanf(_c_pi, "%c", &pp);
		if (pp == '0') {
			distance = 0;
		}
		++distance;
	}
	return distance;
}

long compute_distance(char* s_pos1, char* s_pos2, long& loc1, long& loc2) {
	FILE* calculator_pi = fopen64("./e.txt","r");
	fseek(calculator_pi, loc2, SEEK_SET);
	loc1 = _locate(s_pos1, loc2, calculator_pi);
	loc2 = _locate(s_pos2, loc1, calculator_pi);
	long distance = _compute_distance(loc1, loc2, calculator_pi);
	fclose(calculator_pi);
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
	long loc1 = 0, loc2 = 0;
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
				cout << pp << "\t\t" << num[pos % l] << "\t\t" << nn1 << "\t\t" << nn2 << endl;
				system("a=1;read a");
				hash_map[pp-'0']++;
				if ((pp == nn1) && (pp == num[pos % l])) {
					pos1 = reverse(hash_map[pp-'0']);
					last_pos = pos;
					cout << endl << "N1 set" << endl;
				}
				if ((pp == nn2) && (pp == num[pos % l]) && (pos > last_pos)) {
					pos2 = reverse(hash_map[pp-'0']);
					cout << endl << "N2 set" << endl;
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
		long distance = compute_distance(s_pos1, s_pos2, loc1, loc2);
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
