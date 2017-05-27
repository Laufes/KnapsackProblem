#pragma once
#include <string>
#include "PriorityQueue.h"
#include "KnapsackResult.h"
#include "BranchAndBoundQueue.h"
using namespace std;

class Knapsack
{
private:
	int capacity;
	int itemsCount;
	int *elemSize;
	int *elemValue;

	float SetUpperBound(PriorityQueue* Queue, int weight, int profit, int treeLevel);
public:	
	//Constructors
	Knapsack();
	Knapsack(int capacity);
	~Knapsack();

	//Algorithms
	KnapsackResult* DynamicProgramming();
	KnapsackResult* GreedyAlgorithm();
	KnapsackResult* BruteforceAlgorithm();
	KnapsackResult* BranchAndBound();
	KnapsackResult* DynamicProgrammingProfit();
	KnapsackResult* ApproximationAlgorithm(float epsilon);

	//Functions
	string Display();
	void LoadFromFile(string fileName);
	void RandomItems(int capacity, int itemsCount, int minSize, int maxSize, int minValue, int maxValue);
};

