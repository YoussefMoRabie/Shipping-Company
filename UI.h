#pragma once
#include "Def.h"
#include <iostream>
#include <string>
//#include"Company.h"
using namespace std;

class UI
{
//private:
//	Company* company_ptr;
public:
	UI();
	SIM_MODE get_sim_mode();
	void InteractivePrinting() ;
	void StepByStepPrinting() ;
	void SilentPrinting() ;
	void print(string);

	int getIntger()
	{
		int input;
		cin >> input;
		return input;
	}
	string getString()
	{
		string str;
		cin >> str;
		return str;
	}
};

