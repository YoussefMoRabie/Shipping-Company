#pragma once
#include "Def.h"
#include <iostream>
#include <string>
using namespace std;

class UI
{

public:
	UI();
	SIM_MODE get_sim_mode();
	void print(string);
	int getIntger();
	string getString();
};

