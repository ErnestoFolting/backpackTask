#pragma once
#include "item.h"
#include <vector>
#include <iostream>


using namespace std;
struct solution
{
	vector<bool> sol;
	double allValue;
	double allWeight;
	double koef;
	solution(vector<bool>vec, vector<item> items) {
		sol = vec;
		allValue = 0;
		allWeight = 0;
		for (int i = 0; i < 100; i++) {
			if (vec[i] == 1) {
				allValue += items[i].value;
				allWeight += items[i].weight;
			}
		}
		if (allWeight != 0) {
			koef = allValue / allWeight;
		}
		else {
			koef = 0;
		}
	}
};

