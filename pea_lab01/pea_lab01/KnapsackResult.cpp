#include "KnapsackResult.h"
#include <sstream>

using namespace std;

KnapsackResult::KnapsackResult()
{
	value = 0;
	first = NULL;
}
KnapsackResult::KnapsackResult(int value)
{
	this->value = value;
	first = NULL;
}

KnapsackResult::~KnapsackResult()
{
	Item * pointer;
	pointer = first;
	while (first)
	{
		pointer = first->next;
		delete first;
		first = pointer;
	}
	first = NULL;
}
void KnapsackResult::Add(int indeks)
{
	Item *temp = new Item();
	temp->next = NULL;
	temp->indeks = indeks;
	temp->next = first;
	first = temp;
}

Item *KnapsackResult::GetFirst()
{
	return first;
}

string KnapsackResult::Display()
{
	Item *pointer;
	string res = "";
	stringstream stream;
	pointer = first;
	while (pointer != NULL)
	{
		stream << pointer->indeks << " ";
		pointer = pointer->next;
	}
	stream << endl << "Suma wartosci wynosi: " << value << endl;
	res = stream.str();
	stream.str(string());
	stream.clear();
	return res;
}
void KnapsackResult::SetValue(int value)
{
	this->value = value;
}
