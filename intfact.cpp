#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <gmp.h>
#include <boost/lexical_cast.hpp>
using namespace boost;
using namespace std;

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
	int hit = 0, t = 0;
	std::string _factor_odd = "", _factor_even = "";
	int ctr = 0;
	vector<int> int_params;
	while (1) {in 6703d4f] code
		 1 file changed, 42 insertions(+), 1 deletion(-)
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
			char _pp = pp[i];
			char _ee = ee[i];
			char _payload[3];
			_payload[0] = _pp;
			_payload[1] = _ee;
			_payload[2] = '\0';
			char _nn[3];
			_nn[0] = nn[0];
			_nn[2] = '\0';
			for (char k = '0'; k < '9'; ++k) {
				_nn[1] = k;
				int nk = atoi(_nn);
				int _payload_k = atoi(_payload);
				if (_payload_k == 0) _payload_k = 100;
				if (nk > 0) {
					int _payload_k_rem = _payload_k % nk;
					if (_payload_k_rem == 0) {
						int_params.push_back(k - '0');
						params += _payload_k / nk;
						++hit;
						if (hit % 5 == 0) {
							if (params % 10 == 0) {
								long snippet = _calculate(ctr, int_params);
								if (t == 0) {
									_factor_odd += boost::lexical_cast<std::string>(snippet);
								} else if (t == 1) {
									_factor_even += boost::lexical_cast<std::string>(snippet);
								}
								t = 1 - t;
							}
						}	
					}
				}
			}
		}
		--j;
		++ctr;
	}
	return 0;
}
