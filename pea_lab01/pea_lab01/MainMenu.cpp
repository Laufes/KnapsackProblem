#include "MainMenu.h"
#include <iostream>
using namespace std;

MainMenu::MainMenu()
{
	knapsack = new Knapsack();
}

MainMenu::~MainMenu()
{
	delete knapsack;
}

void MainMenu::DisplayMenu()
{
	char option;
	while (true)
	{
		cout << "\tKnapsack problem: \n1. Display\n2. Create random\n3. Load from file\n4. Dynamic programming\n5. Greedy algorithm\n6. Bruteforce\n"
			<< "7. Branch and Bound\n0. Exit\n";
		cin >> option;
		switch (option)
		{
		case '1':
			cout << knapsack->Display() << endl;
			break;
		case '2':
		{
			int capacity, itemsCount, minSize, maxSize, minValue, maxValue;
			cout << "Knapsack size\n";
			cin >> capacity;
			cout << "Number of items\n";
			cin >> itemsCount;
			cout << "Minimum item size\n";
			cin >> minSize;
			cout << "Maximum item size\n";
			cin >> maxSize;
			cout << "Minimum item value\n";
			cin >> minValue;
			cout << "Maximum item value\n";
			cin >> maxValue;
			knapsack->RandomItems(capacity, itemsCount, minSize, maxSize, minValue, maxValue);
			break;
		}
		case '3':
		{
			string fileName;
			cout << "Filename: " << endl;
			cin >> fileName;
			knapsack->LoadFromFile(fileName);
			break;
		}
		case '4':
		{
			knapsackResult = knapsack->DynamicProgramming();
			cout << knapsackResult->Display() << endl;
			delete knapsackResult;
			knapsackResult = NULL;
			break;
		}
		case '5':
		{
			knapsackResult = knapsack->GreedyAlgorithm();
			cout << knapsackResult->Display() << endl;
			delete knapsackResult;
			knapsackResult = NULL;
			break;
		}
		case '6':
		{
			knapsackResult = knapsack->BruteforceAlgorithm();
			cout << knapsackResult->Display() << endl;
			delete knapsackResult;
			knapsackResult = NULL;
			break;
		}
		case '7':
		{
			knapsackResult = knapsack->BranchAndBound();
			cout << knapsackResult->Display() << endl;
			delete knapsackResult;
			knapsackResult = NULL;
			break;
		}
		case '0':
			return;
		default:
			cout << "unknown commend" << endl;
		}
	}
}
