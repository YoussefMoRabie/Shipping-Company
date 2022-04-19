#include "Ui.h"
#include <iostream>
#include <fstream>
#include<Windows.h> 
using namespace std;
UI::UI(){}

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

void UI::InteractivePrinting() const
{
	cout << "Interactive Mode\n";

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
//
//void UI::Output_Console() const
//{
//	cout << "Current Time (Day:Hour):" << company_ptr->get_Sim_Time().getDay() << ":" << company_ptr->get_Sim_Time().getHour()<<endl;
//	//calculate # of waiting cargos
//	int W_C = company_ptr->get_W_V_C().GetCount()+ company_ptr->get_W_S_C().GetCount()+ company_ptr->get_W_N_C().GetCount();
//	cout << W_C << " Waiting Cargos: [";
//	// First --> print the ID of the Normal Cargos
//	company_ptr->get_W_N_C().print();
//	cout << "] (";
//	// Second --> print the ID of the Special Cargos
//	company_ptr->get_W_S_C().print();
//	cout << ") {";
//	// Third --> print the ID of the VIP Cargos
//	company_ptr->get_W_V_C().print();
//	cout << "}"<<endl;
//	cout << "----------------------------------------------------------------------------"<<endl;
//	cout << company_ptr->get_Loading().GetCount() << "  Loading Trucks: ";
//
//}

void UI::print(string s)
{
	cout << s;
}


