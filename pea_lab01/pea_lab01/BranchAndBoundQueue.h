#pragma once
#include <string>
using namespace std;
// BranchAndBoundQueue Element
struct BBElemQueue
{
	BBElemQueue * next;
	float upperBound;
	int treeLevel;
	int value;
	int weight;
	bool *items;
};
// Class containing information obout tree vertices
class BranchAndBoundQueue
{
private:
	int length;
	BBElemQueue * first;
public:
	BranchAndBoundQueue();
	~BranchAndBoundQueue();
	// Add new element and set order depending on upperBound
	void Add(int treeLevel, float upperBound, int value, int weight, bool * items, int itemsCount);
	void Remove();
	BBElemQueue * GetFirst();
	string Display();
};