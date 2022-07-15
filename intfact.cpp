#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

void* characterize(char* num, vector<char*>& tuples) {
	long l = strlen(num);
	for (long i = l - 1; i >= 0; --i) {
		char* tuple = (char*) calloc(3, sizeof(char));
		tuple[0] = num[l - 1 - i];
		tuple[1] = num[i];
		tuple[2] = '\0';
		tuples.push_back(tuple);
	}
	return 0;
}

void* factorize(char* tuple, int stage, int& factor1, int& factor2, int& polarity) {
	FILE* fp = fopen64("./pi.txt","r");
	FILE* fe = fopen64("./e.txt","r");
	int t = 0;
	char pp = 0, ee = 0, last_pp = 0, last_ee = 0;
	int hit = 1;
	while (1) {
		fscanf(fp, "%c", &pp);
		fscanf(fe, "%c", &ee);
		if (polarity == t && stage == hit && pp == tuple[0] && ee == tuple[1]) {
			//calculate
			int pk = pp - '0';
			int ek = ee - '0';
			char _pp = 0, _ee = 0;
			fscanf(fp, "%c", &_pp);
			fscanf(fe, "%c", &_ee);
			int _pk = _pp - '0';
			int _ek = _ee - '0';
			int _last_pk = last_pp - '0';
			int _last_ek = last_ee - '0';
			if (pk > ek) {
				if (_ek < _last_ek) {
					_ek += 10;
				}
				if (_last_pk < _pk) {
					_last_pk += 10;
				}
				factor2 = _ek - _last_ek;
				factor1 = _last_pk - _pk;
				if (_ek == 0 || _last_ek == 0) {
					cout << "\nfactor2 indeterminate at this stage\n";
					cout <<  "\t" << "\nFactor1\t" << factor1 << "\t" << endl;
				} else if (_pk == 0 || _last_pk == 0) {
					cout << "\nfactor1 indeterminate at this stage\n";
					cout << "\nFactor2\t" << factor2 << "\t" << endl;
				} else {
					cout << factor1 << "\t" << factor2 << "\t" << endl;
				}
			} else if (pk < ek) {
				if (_last_ek < _ek) {
					_last_ek += 10;
				}
				if (_pk < _last_pk) {
					_pk += 10;
				}
				factor2 = _last_ek - _ek;
				factor1 = _pk - _last_pk;
				if (_ek == 0 || _last_ek == 0) {
					cout << "\nfactor2 indeterminate at this stage\n";
					cout <<  "\nFactor1\t" << factor1 << "\t" << endl;
				} else if (_pk == 0 || _last_pk == 0) {
					cout << "\nfactor1 indeterminate at this stage\n";
					cout << "\nFactor2\t"<< factor2 << "\t" << endl;
				} else {
					cout << factor1 << "\t" << factor2 << "\t" << endl;
				}
			} else if (pk == ek) {
				if (_last_ek < _ek) {
					_last_ek += 10;
				}
				if (_last_pk < _pk) {
					_last_pk += 10;
				}
				factor2 = _last_ek - _ek;
				factor1 = _last_pk - _pk;
				if (_ek == 0 || _last_ek == 0) {
					cout << "\nfactor2 indeterminate at this stage\n";
					cout <<  "\nFactor1\t" << factor1 << "\t" << endl;
				} else if (_pk == 0 || _last_pk == 0) {
					cout << "\nfactor1 indeterminate at this stage\n";
					cout << "\nFactor2\t"<< factor2 << "\t" << endl;
				} else {
					cout << factor1 << "\t" << factor2 << "\t" << endl;
				}
			}
			++hit;
			return 0;
		} else if (polarity == t && stage > hit && pp == tuple[0] && ee == tuple[1]) {
			//calculate
			++hit;
			return 0;
		} else if (polarity != t && stage == hit && pp == tuple[0] && ee == tuple[1]) {
			//mark down
			++hit;
		}
		t = 1 - t;
		last_pp = pp;
		last_ee = ee;
	}
	fclose(fp);
	fclose(fe);
	return 0;
}

int main(int argc, char* argv[]) {
	char* num = strdup(argv[1]);
	printf("\nNumber entered was %s\n", num);
	vector<char*>* tuples = (vector<char*>*) calloc(1, sizeof(vector<char*>));
	characterize(num, *tuples);
	std::string factor_lt = "";
	std::string factor_gt = "";
	int polarity = 1;
	for (int i = 0; i < tuples->size(); ++i) {
		char* tuple = tuples->at(i);
		int factor1 = 0, factor2 = 0;
		factorize(tuple, i + 1, factor1, factor2, polarity);
		exit(2);
		factor_lt += boost::lexical_cast<std::string>((polarity==0)? factor1:factor2);
		factor_gt += boost::lexical_cast<std::string>((polarity==0)? factor2:factor1);
		polarity = 1 - polarity;
	}
	for (int i = 0; i < tuples->size(); ++i) {
		free(tuples->at(i));
	}
	free(tuples);
	return 0;
}
