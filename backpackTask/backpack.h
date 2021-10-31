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
	backpack() {
		generateItems();
		startPopulation();
		for (int i = 0; i < population[0].sol.size(); i++) {
			cout << population[0].sol[i] << ' ';
		}
		cout << "item" << items[0].value << ' ' << items[0].weight << endl;
		cout << endl;
		cout << population[0].allValue << endl;
		cout << population[0].allWeight << endl;
		cout << population[0].koef << endl;
	}
};

