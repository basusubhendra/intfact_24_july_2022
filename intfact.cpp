#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <iostream>
#include <gmp.h>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include "pi.hpp"
#include "e.hpp"
using namespace boost;
using namespace std;

char* quotient(char* num, char* factor) {
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
	bool succ = (mpz_cmp_si(rz, 0) == 0);
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

void* strrev(char* ee) {
	long l = strlen(ee);
	for (int i = 0; i < int(l / 2); ++i) {
		char t = ee[i];
		ee[i] = ee[l - 1 - i];
		ee[l - 1 - i] = t;
	}
	return 0;
}

int reverse(int x) {
	int rev = 0;
	while (x > 0) {
            rev = rev*10 + (x % 10);
	    x /= 10;
	}
	return rev;
}

long _calculate(vector<int> int_params, int sz, vector<long> posits) {
	vector<long> res;
	long prev_posit = posits[0];
	int prev_int_param = int_params[0];
	long sum = 0;
	int hit = 0;
	long buffer = prev_int_param;
        for (int i = 1; i < posits.size(); ++i) {
		if (hit == 1 && posits[i] == (posits[i - 1] + 1)) {
			sum = reverse(sum);
			buffer = int_params[i];
			prev_int_param = int_params[i];
			hit = 0;
		} else if (hit == 0 && posits[i] == (posits[i - 1] + 1)) {
                    sum += (prev_int_param*10 + int_params[i]);
		    prev_int_param = int_params[i];
                    ++hit;
		    buffer = 0;
		} else if (hit == 0) {
			sum += buffer;
			buffer = int_params[i];
			prev_int_param = buffer;
		} else if (hit == 1) {
			sum += buffer;
			buffer = int_params[i];
			prev_int_param = buffer;
		}
	}
	return sum;
}

long _calculate(int ctr, vector<int> int_params, vector<long> posits) {
	long res = pow(2, ctr);
	long sz = int_params.size();
	long residual_size = sz - res;
	long res1 = _calculate(int_params, res, posits);
	vector<int> _int_params;
	vector<long> _posits;
	std::copy(int_params.begin() + res, int_params.end(), back_inserter(_int_params));
	std::copy(posits.begin() + res, posits.end(), back_inserter(_posits));
	long res2 = _calculate(_int_params, residual_size, _posits);
	return res2 - res1;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber Entered was:%s\n", num);
	long l = strlen(num);
	long ncycles = ceil(l/3)*4;
	long j = ncycles;
	std::string _factor_odd = "", _factor_even = "";
	int ctr = 0;
	vector<int> int_params;
	vector<long> posits;
	bool found = false;
	long params = 0;
	while (1) {
		int hit = 0, t = 0;
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
			_nn[0] = nn;
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
						posits.push_back(ctr);
						params += (_payload_k / nk);
						++hit;
						if (hit % 5 == 0) {
							if (params % 10 == 0) {
								long snippet = _calculate(ctr + 1, int_params, posits);
								if (t == 0) {
									_factor_odd += boost::lexical_cast<std::string>(snippet);
								} else if (t == 1) {
									_factor_even += boost::lexical_cast<std::string>(reverse(snippet));
								}
								t = 1 - t;
							}
							found = true;
							break;
						}	
					}
				}
			}
			if (found) {
				found = false;
				break;
			}
		}
		--j;
		++ctr;
		free(pp);
		free(ee);
	}
	std::string factor = _factor_odd + _factor_even;
	char* other_factor = quotient(num, strdup((char*) factor.c_str()));
	cout << endl << num << "\t=\t" << factor << "\tX\t" << other_factor << endl;
        return 0;
}
