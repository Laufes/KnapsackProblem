#include <iostream>
#include <fstream>
#include <windows.h>
#include "TimeMeasurement.h"

#define REPEATS 20
using namespace std;

TimeMeasurement::TimeMeasurement()
{
	knapsack = new Knapsack();
}
TimeMeasurement::~TimeMeasurement()
{
	delete knapsack;
}

double PCFreq = 0.0;
__int64 CounterStart = 0;
double timeValue;

void TimeMeasurement::StartCounter() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double TimeMeasurement::GetCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void TimeMeasurement::MeasureBranchAndBound() {

	ofstream timesFile("Results.txt");

	// Dane
	int capacity[3] = { 150, 300, 450 };
	int itemsCount[5] = { 100, 200, 300, 400, 500 };
	int minSize = 1;
	int maxSize = 10;
	int minValue = 10;
	int maxValue = 100;

	for (int k = 0; k < 3; k++)
	{
		cout << "Capacity: " << capacity[k] << endl;
		timesFile << "Capacity: " << capacity[k] << endl;
		for (int j = 0; j < 5; j++)
		{
			timeValue = 0;
			cout << "Number of items: " << itemsCount[j] << endl;
			timesFile << "Number of items: " << itemsCount[j] << endl;
			for (int i = 0; i < REPEATS; i++)
			{

				knapsack->RandomItems(capacity[k], itemsCount[j], minSize, maxSize, minValue, maxValue);
				StartCounter();
				knapsackResult = knapsack->GreedyAlgorithm();
				timeValue += GetCounter();
				delete knapsackResult;
			}
			timeValue /= REPEATS;
			timesFile << timeValue << endl;
	
		}
	}
	timesFile.close();
}