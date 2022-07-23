#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <gmp.h>
using namespace std;
#define NZEROS 100000

int binarySearch(int arr, int x, int low, int high)
	if (low > high) {
		return -1;
	} else {
		mid = (low + high) / 2; 
		if (x == arr[mid]) {
			return mid;
		} else if (x > arr[mid]) {
			return binarySearch(arr, x, mid + 1, high);
		} else {
			return binarySearch(arr, x, low, mid - 1) 
		}
	}
}

void* strrev(char* ee) {
	long l = strlen(ee);
	for (int i = 0; i < int(l / 2); ++i) {
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
	long ncycles = ceil(l/3)*4;
	long j = ncycles;
	while (1) {
		long nlength = j*l;
		char* pp = (char*) calloc(nlength + 1, sizeof(char));
		char* ee = (char*) calloc(nlength + 1, sizeof(char));
		strncpy(pp, pi, nlength);
		strncpy(ee, e, nlength);
		strrev(ee);
		pp[nlength] = '\0';
		ee[nlength] = '\0';
		for (int i = 0; i < nlength; ++i) {
			char nn = num[i % l];
		}
		--j;
	}
	return 0;
}
