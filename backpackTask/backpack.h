#pragma once
#include "item.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "solution.h"


using namespace std;

struct backpack
{
	vector<item>items;
	vector<solution> population;
	void generateItems() {
		ofstream outFile("items.txt");
		for (int i = 0; i < 100; i++) {
			int crValue = (rand() % 29) + 2;
			int crWeight = (rand() % 25) + 1;
			outFile << i << " Value: " << crValue << " Weight: " << crWeight << endl;
			items.push_back(item(crValue, crWeight));
		}
		outFile.close();
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
		cout << "The best current solution is to take items with numbers: " << endl;
		debug(population[index].sol);
		cout << "The weight of the best: " <<  population[index].allWeight << endl;
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
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] == 1) {
				cout << i << " ";
			}
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
		for (int iterations = 0; iterations <= 1000; iterations++) {
			int pos1 = rand() % 100;
			int pos2 = 0;
			int maxValue = 0;
			for (int i = 0; i < 100; i++) {
				if (population[i].allValue > maxValue) {
					pos2 = i;
					maxValue = population[i].allValue;
				}
			}
			solution S1 = population[pos1];
			solution S2 = population[pos2];
			solution afterCross = cross(S1, S2);
			mutation(afterCross);
			localUpgrade(afterCross);
			if (!(iterations % 20)) {
				cout << "The number of iteration: " << iterations << endl;
				cout << "Record of value: " << record() << endl << endl;
			}
			if (afterCross.allWeight <= 250) {
				add(afterCross);
			}
		}
	}
};

