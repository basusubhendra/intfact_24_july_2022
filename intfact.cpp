#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include "zeros.hpp"
#include "e.hpp"
using namespace std;
#define NZEROS 2001052

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

void* strrev(char* ee) {
	long l = strlen(ee);
	for (int i = 0; i < int(l / 2.0); ++i) {
		char t = ee[i];
		ee[i] = ee[l - 1 - i];
		ee[l - 1 - i] = t;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	FILE* comparator_pi = fopen64("./pi.txt","r");
	int ctr = l - 1;
	long* hash_map = (long*) calloc(10, sizeof(long));
	std::string factor = "";
	long pos = 0;
	for (int i = ctr; i > 0; --i) {
		char nn1 = num[i];
		char nn2 = num[i - 1];
		long pos1 = -1, pos2 = -1;
		long idx = 0;
		bool found = true;
		while (1) {
			char pp = 0;
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if ((pp == nn1) && (pp == num[pos % l])) {
					pos1 = hash_map[pp-'0'];
					pos++;
					break;
				}
				pos++;
			}
			while (1) {
				fscanf(comparator_pi, "%c", &pp);
				hash_map[pp-'0']++;
				if (pp == num[pos % l] && (pp != nn2)) {
					pos1 = -1;
					++pos;
					++i;
					found = false;
					break;
				} else if ((pp == nn2) && (pp == num[pos % l])) {
					pos2 = hash_map[pp-'0'];
					++pos;
					break;
				}
				++pos;
			}
			if (found) {
				idx = binarySearch(zeros, (pos1*10 + pos2), 0, NZEROS);
				if (idx != -1) {
					break;
				}
			} else {
				break;
			}
		}
	}
	long f_pos = ftello(comparator_pi);
	printf("\nOutput of Analysis = %ld\n", f_pos);
        char* ee = (char*) calloc(f_pos + 1, sizeof(char));
	strncpy(ee, e, f_pos);
	strrev(ee);
	printf("\n%s\n", ee);
	fclose(comparator_pi);
	return 0;
}
