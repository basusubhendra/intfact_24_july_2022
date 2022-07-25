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
#define NZEROS 2001052

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

int binarySearch(int arr[], int x, int low, int high) {
	if (low > high) {
		return -1;
	} else {
		int mid = (low + high) / 2; 
		if (x == arr[mid]) {
			return mid;
		} else if (x > arr[mid]) {
			return binarySearch(arr, x, mid + 1, high);
		} else {                        
			return binarySearch(arr, x, low, mid - 1);
		}
	}
}

long compute_distance(char* s1, char* s2, char*& location) {
	char* ptr1 = strstr(location, s1);
	char* ptr2 = strstr(ptr1 + 1, s2);
	location = ptr2 + 1;
	long distance = ptr2 - ptr1 - 1;
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
	char* location = (char*) e;
	long pos = 0, last_pos = 0;
	for (int i = ctr; i > 0; --i) {
		char nn1 = num[i];
		char nn2 = num[i - 1];
		long pos1 = -1, pos2 = -1;
//#ifdef _DEBUG
		cout << nn1 << "\t" << nn2 << endl;
//#endif
		while (1) {
			char pp = 0;
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if ((pp == nn1) && (pp == num[pos % l])) {
					pos1 = reverse(hash_map[pp-'0']);
					pos++;
					break;
				}
				pos++;
			}
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if ((pp == nn1) && (pp == num[pos % l]) && (nn1 != nn2)) {
					pos1 = reverse(hash_map[pp-'0']);
				}
				if ((pp == nn2) && (pp == num[pos % l])) {
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
//#ifdef _DEBUG
		cout << s_pos1 << "\t" << s_pos2 << endl;
//#endif
		long distance = compute_distance(s_pos1, s_pos2, location);
#ifdef _DEBUG
		cout << endl << distance << endl;
#endif
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
