#pragma once
#include "item.h"
#include <vector>
#include <iostream>


using namespace std;

struct backpack
{
	vector<item>items;
	vector<vector<bool>> population;
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
			population.push_back(tempBool);
		}
	}
	backpack() {
		generateItems();
		startPopulation();
	}
};

