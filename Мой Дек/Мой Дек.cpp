
#include "pch.h"
#include <iostream>
#include "Deque.h"
using namespace std;
static int i;
void foo()
{
	static int x = 0;
	
	
	cout << x << endl;
	i++;
	x++;
}
int main()
{
	/*Deque<const char*> D2;
	D2.push_back("Alex came to the cabinet.");
	D2.push_front("Alex said: ");
	D2.push_front("Where is my chair?");
	cout << D2 << endl;

	cout << D2.sort() << endl;*/
	i = 0;
	foo();
	foo();
	foo();
	foo();
	return 0;
}
