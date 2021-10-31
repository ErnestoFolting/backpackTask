#pragma once
struct item
{
	double value;
	double weight;
	double koef;
	item(int val, int wei) {
		value = val;
		weight = wei;
		koef = val / wei;
	}
};

