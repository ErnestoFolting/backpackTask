#pragma once
struct item
{
	double value;
	double weight;
	double koef;
	item(double val, double wei) {
		value = val;
		weight = wei;
		koef = val / wei;
	}
};

