#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include<Windows.h>
#include <string>
using namespace std;

Company::Company()
{
	Loading_Normal = nullptr;
	Loading_Special = nullptr;
	Loading_VIP = nullptr;
}

void Company::Start_Simuulation()
{
	string filename;
	filename = ui_p->getString();
	if (readFile(filename + ".txt")) {


		cin.get();
		execute_mode(get_input_mode());
	}
}

void Company::Working_Hours()
{
	Move_Trucks();

	while (load_VIP())
	{
	}
	while (load_Special())
	{
	}
	while (load_Normal())
	{
	}
	while (load_MaxW())
	{
	}
}

void Company::Off_Hours()
{

}

bool Company::load_VIP()
{
	Truck* t_temp;
	Cargo* c_temp;
	if (W_V_C.GetCount() >= vCap && !Loading_VIP)
	{
		if (empty_VIP.DeQueue(t_temp))
		{
			for (int i = 0; i < vCap; i++)
			{
				W_V_C.DeQueue(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_VIP = t_temp;
			return true;
		}
	}
	if (W_V_C.GetCount() >= nCap && !Loading_Normal)
	{
		if (empty_Normal.DeQueue(t_temp))
		{
			for (int i = 0; i < nCap; i++)
			{
				W_V_C.DeQueue(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_Normal = t_temp;
			return true;
		}
	}
	if (W_V_C.GetCount() >= sCap && !Loading_Special)
	{
		if (empty_Special.DeQueue(t_temp))
		{
			for (int i = 0; i < sCap; i++)
			{
				W_V_C.DeQueue(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_Special = t_temp;
			return true;
		}
	}
	return false;
}

bool Company::load_Special()
{
	Truck* t_temp;
	Cargo* c_temp;
	if (W_S_C.GetCount() >= sCap && !Loading_Special)
	{
		if (empty_Special.DeQueue(t_temp))
		{
			for (int i = 0; i < sCap; i++)
			{
				W_S_C.DeQueue(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_Special = t_temp;
			return true;
		}
	}
	return false;
}

bool Company::load_Normal()
{
	Truck* t_temp;
	Cargo* c_temp;
	if (W_N_C.GetCount() >= nCap && !Loading_Normal)
	{
		if (empty_Normal.DeQueue(t_temp))
		{
			for (int i = 0; i < nCap; i++)
			{
				W_N_C.removeFirst(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_Normal = t_temp;
			return true;
		}
	}
	if (W_N_C.GetCount() >= vCap && !Loading_VIP)
	{
		if (empty_VIP.DeQueue(t_temp))
		{
			for (int i = 0; i < vCap; i++)
			{
				W_N_C.removeFirst(c_temp);
				float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
				t_temp->load(c_temp, delivery_time);
			}
			Loading_VIP = t_temp;
			return true;
		}
	}
	return false;
}

bool Company::load_MaxW()
{
	Truck* t_temp;
	Cargo* c_temp;
	int wait_time;
	
	//a special cargo has exceeded maxW
	if (!W_S_C.QueueEmpty())
	{
		wait_time = Sim_Time - W_S_C.Peek()->GetPrepTime();
		if (wait_time >= MaxWait)
		{
			if (!Loading_Special)
			{
				if (empty_Special.DeQueue(t_temp))
				{
					W_S_C.DeQueue(c_temp);
					float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
					t_temp->load(c_temp, delivery_time);
					Loading_Special = t_temp;
					return true;
				}
			}
		}
	}
	//a normal cargo has exceeded maxW
	if (!W_N_C.IsEmpty())
	{
		wait_time = Sim_Time - W_N_C.getFirst()->GetPrepTime();
		if (wait_time >= MaxWait)
		{
			if (!Loading_Normal)
			{
				if (empty_Normal.DeQueue(t_temp))
				{
					W_N_C.removeFirst(c_temp);
					float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
					t_temp->load(c_temp, delivery_time);
					Loading_Normal = t_temp;
					return true;
				}
			}
			if (!Loading_VIP)
			{
				if (empty_VIP.DeQueue(t_temp))
				{
					W_N_C.removeFirst(c_temp);
					float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
					t_temp->load(c_temp, delivery_time);
					Loading_VIP = t_temp;
					return true;
				}
			}
		}
	}
	return false;
}

void Company::Move_Trucks()
{
	if (Loading_VIP)
	{
		Loading_VIP->count_down();
		if (Loading_VIP->get_move_counter() == 0)
		{
			Move_Truck(Loading_VIP);
		}
	}
	if (Loading_Special)
	{
		Loading_Special->count_down();
		if (Loading_Special->get_move_counter() == 0)
		{
			Move_Truck(Loading_Special);
		}
	}
	if (Loading_Normal)
	{
		Loading_Normal->count_down();
		if (Loading_Normal->get_move_counter() == 0)
		{
			Move_Truck(Loading_Normal);
		}
	}
}

void Company::Move_Truck(Truck*& t)
{
	int finish_time = 0; //TO BE CALCULATED
	Moving_truck.EnQueue(t,finish_time);
	t = nullptr;
}

void Company::move_to_checkup(Truck* t)
{

}

bool Company::Events_empty()
{
	return Event_List.QueueEmpty();
}

//searches the normal cargo list with the id, if found it is removed from the normal list and added to the vip one.
bool Company::Upgrade_Normal_Cargo(int id, int extra_money)
{
	Cargo* ptr = new Cargo(id);
	if (W_N_C.Find_Remove(ptr, ptr))
	{
		ptr->PromoteToVip(extra_money);
		AddCargo(ptr);
		return true;
	}
	return false;
}

//searches the normal cargo list with the id, if found it is removed from the normal list.
bool Company::Cancel_Normal_Cargo(int id)
{
	Cargo* ptr = new Cargo(id);
	if (W_N_C.Find_Remove(ptr, ptr))
		return true;
	return false;
}


void Company::AddCargo(Cargo* c)
{
	switch (c->GetType())
	{
	case CARGO_TYPE::NORMAL:
	{
		W_N_C.InsertEnd(c);
		break;
	}
	case CARGO_TYPE::SPECIAL:
	{
		W_S_C.EnQueue(c);
		break;
	}
	case CARGO_TYPE::VIP:
	{
		int time = (c->GetPrepTime().getDay() * 24) + c->GetPrepTime().getHour();
		float priority = 10 * c->GetCost() / (c->GetDistance() * time);
		W_V_C.EnQueue(c, priority);
		break;
	}
	}
}

bool Company::readFile(string filename)
{
	Loaded.open(filename);

	if (!Loaded.is_open())
	{
		ui_p->print("Error: Can't open file! Click to continue ...");
		return false;
	}
	int truck_id = 1;
	int N, S, V;
	float nSpeed, sSpeed, vSpeed;
	int Num_of_journeys, nCheck, sCheck, vCheck;

	Loaded >> N >> S >> V >> nSpeed >> sSpeed >> vSpeed >> nCap >> sCap >> vCap;
	Loaded >> Num_of_journeys >> nCheck >> sCheck >> vCheck >> AutoPro >> MaxWait >> Num_of_events;

	for (int i = 0; i < N; i++)
	{
		Truck* T = new Truck(truck_id, TRUCK_TYPE::NORMAL, nCap, nCheck, Num_of_journeys, nSpeed);
		empty_Normal.EnQueue(T);
		truck_id++;
	}
	for (int i = 0; i < S; i++)
	{
		Truck* T = new Truck(truck_id, TRUCK_TYPE::SPECIAL, sCap, sCheck, Num_of_journeys, sSpeed);
		empty_Special.EnQueue(T);
		truck_id++;
	}
	for (int i = 0; i < V; i++)
	{
		Truck* T = new Truck(truck_id, TRUCK_TYPE::VIP, vCap, vCheck, Num_of_journeys, vSpeed);
		empty_VIP.EnQueue(T);
		truck_id++;
	}

	Event* Eptr = nullptr;
	char event_type;
	for (int i = 0; i < Num_of_events; i++)
	{
		string t;
		int id;
		Time T;

		Loaded >> event_type;
		if (event_type == 'R')
		{
			char cargo_type;
			float dist, LT, cost;
			Loaded >> cargo_type >> t >> id >> dist >> LT >> cost;

			T.setTime(t);
			switch (cargo_type)
			{
			case 'N':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::NORMAL, T, id, dist, LT, cost);
				break;
			}
			case 'S':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::SPECIAL, T, id, dist, LT, cost);
				break;
			}
			case 'V':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::VIP, T, id, dist, LT, cost);
				break;
			}
			}
		}
		else if (event_type == 'X')
		{
			Loaded >> t >> id;
			T.setTime(t);
			Eptr = new CancelEvent(this, T, id);
		}
		else if (event_type == 'P')
		{
			float extra;
			Loaded >> t >> id >> extra;
			T.setTime(t);
			Eptr = new PromoteEvent(this, T, id, extra);
		}
		if (Eptr)
		{
			Event_List.EnQueue(Eptr);
			Eptr = nullptr;
		}
	}
	Loaded.close();
}

//Printing Functions

void Company::Print_Sim_Time()
{
	Sim_Time.printTime();
}
//--------------------------------------------------------

Time& Company::get_Sim_Time()
{
	return Sim_Time;
}

Time& Company::get_Nearest_Event_Time()
{
	return Event_List.Peek()->getTime();
}

Event* Company::get_Nearest_Event()
{
	Event* Eptr;
	Event_List.DeQueue(Eptr);
	return Eptr;
}

void Company::Advance_Sim_Time(int value)
{
	Sim_Time.AdvanceTime(value);
}

void Company::Waiting_To_Delivered()
{
	Cargo* c;
	if (!W_V_C.QueueEmpty())
	{
		c = NULL;
		if (W_V_C.DeQueue(c))
			Delivered_cargo.EnQueue(c);
	}
	if (!W_S_C.QueueEmpty())
	{
		c = NULL;
		if (W_S_C.DeQueue(c))
			Delivered_cargo.EnQueue(c);
	}
	if (!W_N_C.IsEmpty())
	{
		if (W_N_C.removeFirst(c))
			Delivered_cargo.EnQueue(c);
	}
}

int Company::Loading_count()
{
	int count = 0;
	if (Loading_Normal)
		count++;
	if (Loading_Special)
		count++;
	if (Loading_VIP)
		count++;
	return count;
}

bool Company::All_Delivered()
{
	//Add Moving Lists in phase 2
	if (W_N_C.IsEmpty() && W_S_C.QueueEmpty() && W_V_C.QueueEmpty())
		return true;
	else
		return false;
}

void Company::Output_Console()
{
	ui_p->print("Current Time (Day:Hour):" + to_string(Company::get_Sim_Time().getDay()) + ":" + to_string(Company::get_Sim_Time().getHour()) + "\n");
	//calculate # of waiting cargos
	int W_C = W_V_C.GetCount() + W_S_C.GetCount() + W_N_C.GetCount();
	ui_p->print(to_string(W_C) + " Waiting Cargos: [");
	// First --> print the ID of the Normal Cargos
	W_N_C.print();
	ui_p->print("] (");
	// Second --> print the ID of the Special Cargos
	W_S_C.print();
	ui_p->print(") {");
	// Third --> print the ID of the VIP Cargos
	W_V_C.print();
	ui_p->print("}\n");
	ui_p->print("----------------------------------------------------------------------------\n");
	//---------------------------------------------------------------------------------------------------------//
	ui_p->print(to_string(Loading_count()) + " Loading Trucks: ");
	if(Loading_Normal)
		Loading_Normal->print();
	if(Loading_Special)
		Loading_Special->print();
	if(Loading_VIP)
		Loading_VIP->print();
	ui_p->print("\n----------------------------------------------------------------------------\n");
	//---------------------------------------------------------------------------------------------------------//
	int E_C = empty_Normal.GetCount() + empty_Special.GetCount() + empty_VIP.GetCount();
	ui_p->print(to_string(E_C) + " Empty Trucks: [");
	// First --> print the ID of the Normal trucks
	empty_Normal.print();
	ui_p->print("] (");
	// Second --> print the ID of the Special trucks
	empty_Special.print();
	ui_p->print(") {");
	// Third --> print the ID of the VIP trucks
	empty_VIP.print();
	ui_p->print("}\n");
	ui_p->print("----------------------------------------------------------------------------\n");
	//---------------------------------------------------------------------------------------------------------//
/*	int M_C = Moving_truck.GetCount();
	ui_p->print(to_string(M_C) + " Moving Cargos: " + to_string(M_N_C.GetCount()) + "[");
	// First --> print the ID of the Normal Cargos
	M_N_C.print();
	ui_p->print("] " + to_string(M_S_C.GetCount()) + "(");
	// Second --> print the ID of the Special Cargos
	M_S_C.print();
	ui_p->print(") " + to_string(M_V_C.GetCount()) + "{");
	// Third --> print the ID of the VIP Cargos
	M_V_C.print();
	ui_p->print("}\n");
	ui_p->print("----------------------------------------------------------------------------\n");

	//---------------------------------------------------------------------------------------------------------//

	int C_T = Check_up_VIP.GetCount() + Check_up_Special.GetCount() + Check_up_Normal.GetCount();
	ui_p->print(to_string(C_T) + " In-Checkup Trucks: [");
	// First --> print the ID of the Normal trucks
	Check_up_Normal.print();
	ui_p->print("] (");
	// Second --> print the ID of the Special trucks
	Check_up_Special.print();
	ui_p->print(") {");
	// Third --> print the ID of the VIP trucks
	Check_up_VIP.print();
	ui_p->print("}\n");
	ui_p->print("----------------------------------------------------------------------------\n");
	//---------------------------------------------------------------------------------------------------------//
	Queue<Cargo*> temp;
	ui_p->print(to_string(Delivered_cargo.GetCount()) + " Delivered Cargos:");
	while (Delivered_cargo.GetFront())
	{
		if (Delivered_cargo.Peek()->GetType() == CARGO_TYPE::NORMAL)
			ui_p->print("[" + to_string(Delivered_cargo.Peek()->GetID()) + "]");

		else if (Delivered_cargo.Peek()->GetType() == CARGO_TYPE::VIP)
			ui_p->print("{" + to_string(Delivered_cargo.Peek()->GetID()) + "}");
		else
			ui_p->print("(" + to_string(Delivered_cargo.Peek()->GetID()) + ")");
		temp.EnQueue(Delivered_cargo.Peek());
		Delivered_cargo.DeQueue();
	}
	while (temp.GetFront())
	{
		Delivered_cargo.EnQueue(temp.Peek());
		temp.DeQueue();
	}*/
	ui_p->print("\n\n###########################################################################################\n\n");
}

void Company::InteractivePrinting()
{
	ui_p->print("Interactive Mode\n");

	while (!Events_empty() || !All_Delivered())
	{

		if (!Events_empty())
		{
			if (get_Sim_Time() == get_Nearest_Event_Time())
			{
				Event* Eptr = get_Nearest_Event();
				Eptr->Execute();
			}
		}
		if (cin.get())
		{
			Output_Console();

			Advance_Sim_Time();
			if (5 <= Sim_Time.getHour() <= 23)
			{
				Working_Hours();
			}
			else
			{
				Off_Hours();
			}
		}
	}

	cin.get();
	Output_Console();
	ui_p->print("Everything is done, Simulation over.");
}

void Company::SilentPrinting()
{
	ui_p->print("Silent Mode\n");
	ui_p->print("Simulation Starts...\n");
	ui_p->print("Simulation ends, Output file created\n");
}
void Company::StepByStepPrinting()
{
	ui_p->print("StepByStep Mode\n");
	while (!Events_empty() || !All_Delivered())
	{

		if (!Events_empty())
		{
			if (get_Sim_Time() == get_Nearest_Event_Time())
			{
				Event* Eptr = get_Nearest_Event();
				Eptr->Execute();
			}
		}
		Sleep(1000);
		Output_Console();
		Advance_Sim_Time();
		if (5 <= Sim_Time.getHour() <= 23)
		{
			Working_Hours();
		}
		else
		{
			Off_Hours();
		}
	}
	Sleep(1000);
	Output_Console();
	ui_p->print("Everything is done, Simulation over.");
}

SIM_MODE Company::get_input_mode()
{
	return ui_p->get_sim_mode();
}

void Company::execute_mode(SIM_MODE Mode)
{
	if (Mode == SIM_MODE::INTERACTIVE)
		InteractivePrinting();
	else if (Mode == SIM_MODE::SILENT)
		SilentPrinting();
	else
		StepByStepPrinting();
}

bool Company::write_output_file()
{
	//to be implemented in phase 2
	return 0;
}

void Company::print_W_V_C()
{
	W_V_C.print();
}

void Company::print_W_S_C()
{
	W_S_C.print();
}

void Company::print_W_N_C()
{
	W_N_C.print();
}
void Company::print_empty_Normal()
{
	empty_Normal.print();
}
void Company::print_empty_Special()
{
	empty_Special.print();
}
void Company::print_empty_VIP()
{
	empty_VIP.print();
}
void Company::print_check_up_v_trucks()
{
	Check_up_VIP.print();
}
void Company::print_check_up_s_trucks()
{
	Check_up_Special.print();
}
void Company::print_check_up_n_trucks()
{
	Check_up_Normal.print();
}