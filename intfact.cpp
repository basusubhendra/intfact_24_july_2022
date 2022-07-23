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

int main() {
	return 0;
}
