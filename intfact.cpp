#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <gmp.h>
#include <boost/lexical_cast.hpp>
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

FILE* _locate(char* ss, FILE* loc) {
	char pp = 0;
	char* _ss = ss;
	while (1) {
		while (1) {
			fscanf(loc, "%c", &pp);
			if (pp == *ss) {
		                ++ss;
				break;
			}
		}
		while (*ss != '\0') {
			fscanf(loc, "%c", &pp);
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
	return loc;
}

long compute_distance(FILE* loc1, FILE* loc2) {
	FILE* loc = loc1;
	char pp = 0;
	long distance = 0;
	while (loc != loc2) {
		fscanf(loc, "%c", &pp);
		if (pp == '0') {
			distance = 0;
		}
		++distance;
	}
	return distance;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	FILE* comparator_pi = fopen64("./pi.txt","r");
	FILE* calculator_pi = fopen64("./_pi.txt","r");
	FILE* loc1 = calculator_pi, *loc2 = calculator_pi;
	int ctr = l - 1;
	int* hash_map = (int*) calloc(10, sizeof(int));
	std::string factor = "";
	for (int i = ctr; i > 0; --i) {
		char nn1 = num[i];
		char nn2 = num[i - 1];
		long pos1 = -1, pos2 = -1;
		while (1) {
			char pp = 0;
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if (pp == nn1) {
					pos1 = reverse(hash_map[pp-'0']);
					break;
				}
			}
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if (pp == nn2) {
					pos2 = reverse(hash_map[pp-'0']);
					break;
				}
			}
			if (pos1 != pos2) {
				break;
			}
		}
		char s_pos1[128];
		char s_pos2[128];
		sprintf(s_pos1, "%ld", pos1);
		sprintf(s_pos2, "%ld", pos2);
		FILE* loc1 = _locate(s_pos1, loc2);
		FILE* loc2 = _locate(s_pos2, loc1);
		long distance = compute_distance(loc1, loc2);
		factor += boost::lexical_cast<std::string>(distance);
		fclose(loc1);
		fclose(loc2);
	}
	fclose(comparator_pi);
	fclose(calculator_pi);
	bool succ = false;
	char* other_factor = quotient(num, strdup((char*) factor.c_str()), succ);
	if (succ == true) {
		printf("\n%s\t=%s\tX\t%s\n",num, strdup((char*) factor.c_str()), other_factor);
	}
	return 0;
}
