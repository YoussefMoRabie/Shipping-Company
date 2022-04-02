#include "Ui.h"
#include <iostream>
#include <fstream>
#include<Windows.h>  //for the delay
using namespace std;
UI::UI()//Company* ptr)
{
	//company_ptr = ptr;
}

SIM_MODE UI::get_sim_mode()
{
	cout << "Hello my friend.\n";
	cout << "We are happy to help you\n";
	cout << "Please select The mode you want to enter" << endl <<
		"1- Interactive Mode\n2- Step-By-Step Mode\n3- Silent Mode\n enter: ";
	int x;
	cin >> x;
	while (x > 3 || x < 1)
	{
		cout << "Please enter a valid number: ";
		cin >> x;
	}

	if (x == 1)
		return SIM_MODE::INTERACTIVE;
	else if (x == 2)
		return  SIM_MODE::STEP_BY_STEP;
	else
		return SIM_MODE::SILENT;
}

/*void UI::InteractivePrinting() const
{
}

void UI::StepByStepPrinting() const
{
}

void UI::SilentPrinting() const
{
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}

void UI::Output_Console() const
{
}*/

void UI::print(string s)
{
	cout << s << endl;
}


