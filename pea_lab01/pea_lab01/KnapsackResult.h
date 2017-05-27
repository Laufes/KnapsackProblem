#pragma once
#include <string>
using namespace std;

struct Item
{
	Item * next;
	int indeks;
};
class KnapsackResult
{
private:
	int value;
	Item * first;
public:
	KnapsackResult();
	KnapsackResult(int indeks);
	~KnapsackResult();

	void Add(int indeks);
	Item * GetFirst();
	string Display();
	void SetValue(int value);

};

