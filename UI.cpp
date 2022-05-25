#include "Ui.h"
#include <iostream>
#include <fstream>
#include<Windows.h> 
using namespace std;
UI::UI(){}
void UI::print(string s)
{
	cout << s;
}
int UI::getIntger()
{
	int input;
	cin >> input;
	return input;
}
string UI::getString()
{
	string str;
	cin >> str;
	return str;
}