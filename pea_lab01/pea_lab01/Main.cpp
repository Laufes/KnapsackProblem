#include <iostream>
#include "Knapsack.h"
#include "MainMenu.h"
#include <iomanip>

using namespace std;

int main()
{

	// class MainMenu
	MainMenu * menu = new MainMenu();
	menu->DisplayMenu();
	delete menu;


	/*
	TimeMeasurement * czasy = new TimeMeasurement();
	czasy->MeasureBranchAndBound();
	delete czasy;
	system("pause");
	*/

	return 0;
}
