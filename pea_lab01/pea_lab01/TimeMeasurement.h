#pragma once
#include "Knapsack.h"
class TimeMeasurement
{
private:
	Knapsack *knapsack;
	KnapsackResult *knapsackResult;
public:
	TimeMeasurement();
	~TimeMeasurement();

	void StartCounter();
	double GetCounter();
	void MeasureBranchAndBound();
};