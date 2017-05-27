#include "Knapsack.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <math.h>
#define Math

// Constructors
// -------------------------------------------------------------------
Knapsack::Knapsack()
{
	elemSize = new int[1];
	elemValue = new int[1];
	elemSize[0] = 0;
	elemValue[0] = 0;
	itemsCount = 1;
}
Knapsack::Knapsack(int capacity)
{
	this->capacity = capacity;
	elemSize = new int[1];
	elemValue = new int[1];
	elemSize[0] = 0;
	elemValue[0] = 0;
	itemsCount = 1;
}
Knapsack::~Knapsack()
{
	delete []elemSize;
	delete []elemValue;
}
// Algorithms
// -------------------------------------------------------------------
KnapsackResult* Knapsack::DynamicProgramming()
{
	int maxValue;
	// result
	KnapsackResult* knapsackResult = new KnapsackResult();
	// for backtracking
	int curCapacity;
	// creating matrix
	int** result;
	result = new int*[itemsCount + 1];
	for (int i = 0; i <= itemsCount; i++)
	{
		result[i] = new int[capacity + 1];
	}
	for (int i = 0; i <= capacity; i++)
	{
		result[0][i] = 0;
	}
	// Dynamic Algorithm
	for (int j = 1; j <= itemsCount; j++)
	{
		for (int i = 0; i <= capacity; i++)
		{		
			result[j][i] = result[j - 1][i];

			if (i >= 1 && result[j][i - 1] > result[j][i])
			{
				result[j][i] = result[j][i - 1];
			}
			if (i >= elemSize[j - 1] && result[j-1][i - elemSize[j - 1]] + elemValue[j - 1] > result[j][i])
			{
				result[j][i] = result[j - 1][i - elemSize[j - 1]] + elemValue[j - 1];
			}
		}
	}

	//Displaying
	/*for (int j = 0; j <= itemsCount; j++)
	{
	for (int i = 0; i <= capacity; i++)
	{
	cout << setw(4) << result[j][i];
	}
	cout << endl;
	}*/

	maxValue = result[itemsCount][capacity];
	knapsackResult->SetValue(maxValue);
	//Backtracking
	curCapacity = capacity;
	for (int i = itemsCount; i > 0; i--)
	{
		if (result[i][curCapacity] != result[i - 1][curCapacity])
		{
			knapsackResult->Add(i - 1);
			curCapacity -= elemSize[i - 1];
		}
	}
	// removing dynamic matrix
	for (int i = 0; i <= itemsCount; i++)
	{
		delete[] result[i];
	}
	delete[] result;

	return knapsackResult;
}
KnapsackResult* Knapsack::DynamicProgrammingProfit()
{
	int maxValue;
	KnapsackResult* knapsackResult = new KnapsackResult();
	int curCapacity;
	int pMax = 0;
	int tabLenght;

	for (int i = 0; i < itemsCount; i++)
	{
		if (elemValue[i] > pMax)
		{
			pMax = elemValue[i]; 
		}
	}
	tabLenght = itemsCount * pMax;


	int** result;
	result = new int*[itemsCount + 1];
	for (int i = 0; i <= itemsCount; i++)
	{
		result[i] = new int[tabLenght + 1];
	}
	for (int i = 0; i <= capacity; i++)
	{
		result[0][i] = -1;
	}
	for (int j = 0; j <= itemsCount; j++)
	{
		for (int i = 0; i <= tabLenght; i++)
		{

			result[j][i] = INT_MAX;
			if(i == 0)
				result[j][i] = 0;
		}
	}
	cout << tabLenght << endl; 
	int y = 0; 
	do
	{
		y = y + 1;
		for (int k = 1; k <= itemsCount; k++)
		{
			if (y - elemValue[k-1] < 0 || result[k - 1][y - elemValue[k-1]] == INT_MAX)
			{
				result[k][y] = result[k - 1][y];
			}
			else
			{
				if (result[k - 1][y] >= result[k - 1][y - elemValue[k-1]] + elemSize[k-1])
				{
					result[k][y] = result[k - 1][y - elemValue[k-1]] + elemSize[k-1];
				}
				else
				{
					result[k][y] = result[k - 1][y];
				}
			}

			if (result[itemsCount][y] <= capacity)
			{
				maxValue = y;
				cout << maxValue << " " << result[itemsCount][y] << endl;
			}
		}
	} while (y < tabLenght);

	knapsackResult->SetValue(maxValue);

	// removing dynamic matrix
	for (int i = 0; i <= itemsCount; i++)
	{
		delete[] result[i];
	}
	delete[] result;

	return knapsackResult;
}
KnapsackResult* Knapsack::ApproximationAlgorithm(float epsilon)
{
	int maxValue;
	KnapsackResult* knapsackResult = new KnapsackResult();
	int curCapacity;

	int** result;
	result = new int*[itemsCount + 1];
	for (int i = 0; i <= itemsCount; i++)
	{
		result[i] = new int[capacity + 1];
	}
	for (int i = 0; i <= capacity; i++)
	{
		result[0][i] = 0;
	}
	// Dynamic algorithm
	for (int j = 1; j <= itemsCount; j++)
	{
		for (int i = 0; i <= capacity; i++)
		{

			result[j][i] = result[j - 1][i];

			if (i >= 1 && result[j][i - 1] > result[j][i])
			{
				result[j][i] = result[j][i - 1];
			}

			if (i >= elemSize[j - 1] && result[j - 1][i - elemSize[j - 1]] + elemValue[j - 1] > result[j][i])
			{
				result[j][i] = result[j - 1][i - elemSize[j - 1]] + elemValue[j - 1];
			}
		}
	}



	maxValue = result[itemsCount][capacity];
	knapsackResult->SetValue(maxValue);
	//Backtracking
	curCapacity = capacity;
	for (int i = itemsCount; i > 0; i--)
	{
		if (result[i][curCapacity] != result[i - 1][curCapacity])
		{
			knapsackResult->Add(i - 1);
			curCapacity -= elemSize[i - 1];
		}
	}
	// Removing matrix
	for (int i = 0; i <= itemsCount; i++)
	{
		delete[] result[i];
	}
	delete[] result;

	return knapsackResult;
}
KnapsackResult* Knapsack::GreedyAlgorithm()
{

	int maxValue = 0;
	int curSize = 0;

	PriorityQueue *Queue = new PriorityQueue();
	ElemQueue *pointer;

	float value;
	float size;

	KnapsackResult * knapsackResult = new KnapsackResult();
	for (int i = 0; i < itemsCount; i++)
	{
		value = elemValue[i];
		size = elemSize[i];
		Queue->Add(i, value / size);
	}

	pointer = Queue->GetFirst();
	while (pointer != NULL)
	{
		if (curSize + elemSize[pointer->item] <= capacity)
		{
			curSize += elemSize[pointer->item];
			maxValue += elemValue[pointer->item];
			knapsackResult->Add(pointer->item);
		}
		pointer = pointer->next;
	}
	knapsackResult->SetValue(maxValue);

	delete Queue;
	return knapsackResult;
}
KnapsackResult* Knapsack::BruteforceAlgorithm()
{

	long long int i, j, k;

	int maxValue = 0;

	int curSize = 0;
	int curValue = 0;

	bool* inKnapsack = new bool[itemsCount];
	bool* bestOption = new bool[itemsCount];
	for (i = 0; i < itemsCount; i++)
	{
		inKnapsack[i] = false;
		bestOption[i] = false;
	}	
	KnapsackResult * knapsackResult = new KnapsackResult();

	for (i = 1; i < pow(2, itemsCount); i++)
	{
		j = 0;
		curSize = 0;
		curValue = 0;
		while (inKnapsack[j] != false && j < itemsCount)
		{
			inKnapsack[j] = false;
			j++;
		}
		inKnapsack[j] = true; 
		for (k = 0; k < itemsCount; k++)
		{
			if (inKnapsack[k] == true)
			{
				curValue += elemValue[k];
				curSize += elemSize[k];
			}
		}
		if (curValue > maxValue && curSize <= capacity)
		{
			maxValue = curValue;
			for (k = 0;k < itemsCount; k++)
			{
				bestOption[k] = inKnapsack[k];
			}
		}
	}
	for (k = itemsCount -1; k >= 0; k--)
	{
		if (bestOption[k] == true)
			knapsackResult->Add(k);
	}
	knapsackResult->SetValue(maxValue);

	delete[] inKnapsack;
	delete[] bestOption;
	return knapsackResult;
	
}
KnapsackResult* Knapsack::BranchAndBound()
{

	PriorityQueue *Queue = new PriorityQueue();
	ElemQueue *pointer;

	BranchAndBoundQueue *BBQ = new BranchAndBoundQueue();
	BBElemQueue *BBpointer;

	

	KnapsackResult * knapsackResult = new KnapsackResult();
	float upperBound;
	float UB;
	float bestValue = 0;
	bool *bestItems = new bool[itemsCount];

	bool *items = new bool[itemsCount];
	int treeLevel = 0;

	float weight = 0; 
	float size = 0;

	float value = 0;
	float profit = 0; 

	// Preparing
	//----------------------------------------------
	for (int i = 0; i < itemsCount; i++)
	{
		bestItems[i] = false;
		items[i] = false;

		profit = elemValue[i];
		size = elemSize[i];
		Queue->Add(i, profit / size);
	}
	//Algorithm
	//----------------------------------------------
	upperBound = SetUpperBound(Queue, weight, value, treeLevel);

	//Add first element
	BBQ->Add(treeLevel, upperBound, value, weight, items, itemsCount);

	//----------------------------------------------
	while (BBQ->GetFirst() != NULL)
	{
		BBpointer = BBQ->GetFirst();

		profit = BBpointer->value;
		size = BBpointer->weight;
		upperBound = BBpointer->upperBound;
		treeLevel = BBpointer->treeLevel;
		for (int i = 0; i < itemsCount; i++)
			items[i] = BBpointer->items[i];

		BBQ->Remove();

		pointer = Queue->GetFirst();
		for (int i = 0; i < treeLevel; i++)
		{
			pointer = pointer->next;
		}

		if (upperBound > bestValue)
		{
			weight = size + elemSize[pointer->item];
			
			if (weight <= capacity)
			{
				value = profit + elemValue[pointer->item];
			
				if (value > bestValue)
				{
					bestValue = value;
					items[pointer->item] = true;

					for (int i = 0; i < itemsCount; i++)
						bestItems[i] = items[i]; 
				}
				UB = SetUpperBound(Queue, weight, value, treeLevel + 1);
				if(UB > bestValue)
				{
					items[pointer->item] = true;
					BBQ->Add(treeLevel + 1, UB, value, weight, items, itemsCount);
				}
			}
			weight = size;
			if (weight <= capacity)
			{
				value = profit;

				if (value > bestValue)
				{
					bestValue = value;
					items[pointer->item] = false;

					for (int i = 0; i < itemsCount; i++)
						bestItems[i] = items[i];
				}
				UB = SetUpperBound(Queue, weight, value, treeLevel + 1);
				if (UB > bestValue)
				{
					items[pointer->item] = false;
					BBQ->Add(treeLevel + 1, UB, value, weight, items, itemsCount);
				}
			}
		}
	}
	knapsackResult->SetValue(bestValue);

	for (int i = itemsCount - 1; i >= 0; i--)
		if (bestItems[i] == true)
			knapsackResult->Add(i);

	delete Queue;
	delete BBQ;
	delete[] bestItems;
	delete[] items;
	return knapsackResult;

}

float Knapsack::SetUpperBound(PriorityQueue* Queue, int wght, int profit, int treeLevel)
{
	float uB = profit;
	float weight = wght;
	ElemQueue * pointer;

	pointer = Queue->GetFirst();
	for (int i = 0; i < treeLevel; i++)
	{
		pointer = pointer->next;
	}	

	while (pointer != NULL)
	{
		if (weight + elemSize[pointer->item] < capacity)
		{
			weight += elemSize[pointer->item];
			uB += elemValue[pointer->item];
		}
		else
		{
			uB += ((capacity - weight) / elemSize[pointer->item]) * elemValue[pointer->item];
			break;
		}
		pointer = pointer->next;
	}
	return uB;

}
// Functions
// -------------------------------------------------------------------
string Knapsack::Display()
{
	string result;
	stringstream stream;

	stream << "Knapsack capacity: " << capacity << endl;
	stream << "Number of items: " << itemsCount << endl;
	stream << setw(8) << "index" << setw(8) << "size" << setw(8) << "value" << endl;
	for (int i = 0; i < itemsCount; i++)
	{
		stream << setw(8) << i << setw(8) << elemSize[i] << setw(8) << elemValue[i] << endl;
	}	
	result = stream.str();
	stream.str(string());
	stream.clear();
	return result;
}
void Knapsack::LoadFromFile(string fileName)
{
	ifstream file;
	file.open(fileName, ios::in);
	if (!file.is_open())
	{
		cout << "Error. File doesn't exist!\n";
		return;
	}
	delete[]elemSize;
	delete[]elemValue;

	file >> capacity;
	file >> itemsCount;
	elemSize = new int[itemsCount];
	elemValue = new int[itemsCount];

	for (int i = 0; i < itemsCount; i++)
	{
		file >> elemSize[i];
		file >> elemValue[i];
	}
	file.close();
}
void Knapsack::RandomItems(int capacity, int itemsCount, int minSize, int maxSize, int minValue, int maxValue)
{
	srand(time(NULL));
	if (maxSize * itemsCount < capacity * 1.25)
	{
		cout << "Not created! Total items size must be nothing less than 1.25 greater than capacity of knapsack!" << endl;
		return;
	}
	
	delete[]elemSize;
	delete[]elemValue;

	this->capacity = capacity;
	this->itemsCount = itemsCount;
	elemSize = new int[itemsCount];
	elemValue = new int[itemsCount];
	int totalSize = 0;
	int randSize;
	

	for (int i = 0; i < itemsCount; i++)
	{
		elemSize[i] = rand() % (maxSize - minSize) + minSize;
		elemValue[i] = rand() % (maxValue - minValue) + minValue;
		totalSize += elemSize[i];
	}

	if (totalSize > 1.25 * capacity)
		return;
	else
	{
		
		while (totalSize > 1.25 * capacity)
		{
			totalSize = 0;
			for (int i = 0; i < itemsCount; i++)
			{
				randSize = rand() % (maxSize - minSize) + minSize;
				if (randSize > 	elemSize[i])
					elemSize[i] = randSize;
				totalSize += elemSize[i];
			}
		}
	}

}
