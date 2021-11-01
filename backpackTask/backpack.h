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
			population.push_back(solution(tempBool, items));
		}
	}
	int record() {
		int record = 0;
		int index = 0;
		for (int i = 0; i < 100; i++) {
			if (population[i].allValue > record) {
				record = population[i].allValue;
				index = i;
			}
		}
		cout << "weight: " <<  population[index].allWeight << endl;
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
		if (chance < 5) {
			int posToChange = rand() % 100;
			if (afterCross.sol[posToChange] == 0) {
				afterCross.sol[posToChange] = 1;
			}
			else {
				afterCross.sol[posToChange] = 0;
			}
		}
	}
	void add(solution afterCross) {
		int worstIndex = 0;
		double minValue = INT_MAX;
		for (int i = 0; i < 100; i++) {
			if (population[i].allValue < minValue) {
				minValue = population[i].allValue;
				worstIndex = i;
			}
		}
		population.push_back(afterCross);
		vector<solution> tempPopulation;
		for (int i = 0; i < population.size(); i++) {
			if (i != worstIndex) {
				tempPopulation.push_back(population[i]);
			}
		}
		population = tempPopulation;
	}
	void localUpgrade(solution& afterCross) {
		double min = 31;
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
		for (int iterations = 0; iterations < 1000; iterations++) {
			int pos1 = rand() % 100;
			cout << "pos:**************************************" << pos1 << endl;
			int pos2 = 0;
			int maxValue = 0;
			for (int i = 0; i < 100; i++) {
				if (population[i].allValue > maxValue) {
					pos2 = i;
					maxValue = population[i].allValue;
				}
			}
			cout << "pos2:???????????????????????"<< pos2 << endl;
			solution S1 = population[pos1];
			solution S2 = population[pos2];
			solution afterCross = cross(S1, S2);
			mutation(afterCross);
			localUpgrade(afterCross);
			if (afterCross.allWeight <= 250) {
				add(afterCross);
				cout << "i------" << iterations << endl;
				cout << population.size();
				debug(afterCross.sol);
				cout << "RECORD:    " << record();
			}
		}
	}
};

