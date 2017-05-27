#pragma once
#include "Knapsack.h"
class MainMenu
{
private:
	Knapsack *knapsack;
	KnapsackResult *knapsackResult;
public:
	MainMenu();
	~MainMenu();

	//---------------------------------------------------
	void DisplayMenu();
};

