#pragma once
#include "item.h"
#include <vector>
#include <iostream>
#include "solution.h"


using namespace std;

struct backpack
{
	vector<item>items;
	vector<solution> population;
	void generateItems() {
		for (int i = 0; i < 100; i++) {
			int crValue = (rand() % 29) + 2;
			int crWeight = (rand() % 25) + 1;
			items.push_back(item(crValue, crWeight));
		}
	}
	void startPopulation() {
		for (int i = 0; i < 100; i++) {
			vector<bool> tempBool(100, 0);
			tempBool[i] = 1;
			population.push_back(solution(tempBool,items));
		}
	}
	int record() {
		int record = 0;
		for (int i = 0; i < 100; i++) {
			if (population[i].allValue > record){
				record = population[i].allValue;
			}
		}
		return record;
	}
	solution cross(solution S1, solution S2) {
		vector<bool> vec(100, 0);
		for (int i = 0; i < 100; i++) {
			if (i >= 0 && i < 25) {
				vec[i] = S1.sol[i];
			}
			else if (i >= 25 && i < 50) {
				vec[i] = S2.sol[i];
			}
			else if (i >= 50 && i < 75) {
				vec[i] = S1.sol[i];
			}
			else if (i >= 75 && i < 100) {
				vec[i] = S2.sol[i];
			}
		}
		solution res(vec, items);
		return res;
	}
	void debug(vector<bool> vec) {
		cout << "Vector: " << endl;
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << ' ';
		}
		cout << endl;
	}
	void mutation(solution& afterCross) {
		int chance = rand() % 100;
		if (chance < 100) {
			int posToChange = rand() % 100;
			if (afterCross.sol[posToChange] == 0) {
				afterCross.sol[posToChange] = 1;
			}
			else {
				afterCross.sol[posToChange] = 0;
			}
		}
	}
	void localUpgrade(solution& afterCross) {
		int min = 31;
		int index = 0;
		for (int i = 0; i < 100; i++) {
			if (items[i].weight < min && afterCross.sol[i] != 1) {
				min = items[i].weight;
				index = i;
			}
		}
		afterCross.sol[index] = 1;
	}
	backpack() {
		generateItems();
		startPopulation();
		for (int iterations = 0; iterations < 1; iterations++) {
			int pos1 = rand() % 100;
			int pos2 = 0;
			for (int i = 0; i < 100; i++) {
				if (population[i].allValue == record()) {
					pos2 = i;
					break;
				}
			}
			solution S1 = population[pos1];
			solution S2 = population[pos2];
			solution afterCross = cross(S1, S2);
			debug(S1.sol);
			debug(S2.sol);
			debug(afterCross.sol);
			mutation(afterCross);
			debug(afterCross.sol);
			localUpgrade(afterCross);
			debug(afterCross.sol);
		}
	}
};

