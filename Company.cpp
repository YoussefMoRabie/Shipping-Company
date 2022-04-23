#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include<Windows.h>
#include <string>
using namespace std;

Company::Company(UI* p)
{
	ui_p = p;
}

void Company::move_to_checkup(Truck*)
{
}

bool Company::Events_empty()
{
	return Event_List.QueueEmpty();
}

//searches the normal cargo list with the id, if found it is removed from the normal queue and added to the vip one.
/*bool Company::Find_Normal_Cargo(int id, Cargo*& ptr)
{
	if (Normal_cargo.find_cargo(id, ptr))
		return true;
	return false;
}*/



void Company::AddCargo(Cargo* c)
{
	switch (c->GetType())
	{
	case CARGO_TYPE::NORMAL:
	{
		W_N_C.InsertBegin(c);
		break;
	}
	case CARGO_TYPE::SPECIAL:
	{
		W_S_C.EnQueue(c);
		break;
	}
	case CARGO_TYPE::VIP:
	{
		W_V_C.EnQueue(c);
		break;
	}
	}
}

void Company::readFile(string filename)
{
	Loaded.open(filename);

	if (!Loaded.is_open())
	{
		ui_p->print("Error: Can't open file! Click to continue ...");
		return;
	}
	int N, S, V, nCap, sCap, vCap;
	float nSpeed, sSpeed, vSpeed;
	int Num_of_journeys, nCheck, sCheck, vCheck;

	Loaded >> N >> S >> V >> nSpeed >> sSpeed >> vSpeed >> nCap >> sCap >> vCap;
	Loaded >> Num_of_journeys >> nCheck >> sCheck >> vCheck >> AutoPro >> MaxWait >> Num_of_events;

	for (int i = 0; i < N; i++)
	{
		Truck* T = new Truck(TRUCK_TYPE::NORMAL, nCap, nCheck, Num_of_journeys, nSpeed);
		Normal_truck.EnQueue(T);
	}
	for (int i = 0; i < S; i++)
	{
		Truck* T = new Truck(TRUCK_TYPE::SPECIAL, sCap, sCheck, Num_of_journeys, sSpeed);
		Special_truck.EnQueue(T);
	}
	for (int i = 0; i < V; i++)
	{
		Truck* T = new Truck(TRUCK_TYPE::VIP, vCap, vCheck, Num_of_journeys, vSpeed);
		VIP_truck.EnQueue(T);
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
	Event* Eptr = Event_List.Peek();
	Event_List.DeQueue();
	return Eptr;
}

void Company::Advance_Sim_Time(int value)
{
	Sim_Time.AdvanceTime(value);
}
//
//LinkedQueue<Mission*>& Company::get_w_p_m()
//{
//	// // O: insert return statement here
//}
//
//Queue<Cargo*>& Company::get_w_e_m()
//{
//	// // O: insert return statement here
//}

void Company::Waiting_To_Delivered()
{
	Cargo* c;
	if (!W_V_C.QueueEmpty())
	{
		c = W_V_C.Peek();
		W_V_C.DeQueue();
		if (c)
			Delivered_cargo.EnQueue(c);
	}
	if (!W_S_C.QueueEmpty())
	{
		c = W_S_C.Peek();
		W_S_C.DeQueue();
		if (c)
			Delivered_cargo.EnQueue(c);
	}
	if(!W_N_C.IsEmpty())
	{
		c = W_N_C.getFirst();
		W_N_C.removeFirst();
		if (c)
			Delivered_cargo.EnQueue(c);
	}
}

void Company::Output_Console() 
{
	ui_p->print("Current Time (Day:Hour):" +to_string(Company::get_Sim_Time().getDay())+":"+ to_string(Company::get_Sim_Time().getHour())+"\n");
	//calculate # of waiting cargos
	int W_C = Company:: get_W_V_C().GetCount() + Company::get_W_S_C().GetCount() + Company::get_W_N_C().GetCount();
	ui_p->print( to_string(W_C) + " Waiting Cargos: [");
	// First --> print the ID of the Normal Cargos
	get_W_N_C().print();
	ui_p->print( "] (");
	// Second --> print the ID of the Special Cargos
	get_W_S_C().print();
	ui_p->print(") {");
    // Third --> print the ID of the VIP Cargos
      get_W_V_C().print();
	  ui_p->print("}\n");
	  ui_p->print("----------------------------------------------------------------------------\n");
	  //---------------------------------------------------------------------------------------------------------//
	  ui_p->print(to_string(get_Loading().GetCount()) + "  Loading Trucks: \n");
	  ui_p->print("----------------------------------------------------------------------------\n");
	  //---------------------------------------------------------------------------------------------------------//
	  ui_p->print(to_string(get_Empty().GetCount()) + "  Empty Trucks: \n");
	  ui_p->print("----------------------------------------------------------------------------\n");
	  //---------------------------------------------------------------------------------------------------------//
	  int M_C = Company::get_M_V_C().GetCount() + Company::get_M_S_C().GetCount() + Company::get_M_N_C().GetCount();
	  ui_p->print(to_string(M_C) + " Moving Cargos: "+to_string(get_M_N_C().GetCount())+"[");
	  // First --> print the ID of the Normal Cargos
	  get_M_N_C().print();
	  ui_p->print("] "+ to_string(get_M_S_C().GetCount()) +"(");
	  // Second --> print the ID of the Special Cargos
	  get_M_S_C().print();
	  ui_p->print(") "+to_string(get_M_V_C().GetCount()) + "{");
	  // Third --> print the ID of the VIP Cargos
	  get_M_V_C().print();
	  ui_p->print("}\n");
	  ui_p->print("----------------------------------------------------------------------------\n");

	  //---------------------------------------------------------------------------------------------------------//

	  int C_T = Company::get_check_up_v_trucks().GetCount() + Company::get_check_up_s_trucks().GetCount() + Company::get_check_up_n_trucks().GetCount();
	  ui_p->print(to_string(C_T) + " In-Checkup Trucks: [");
	  // First --> print the ID of the Normal Cargos
	  get_check_up_n_trucks().print();
	  ui_p->print("] (");
	  // Second --> print the ID of the Special Cargos
	  get_check_up_s_trucks().print();
	  ui_p->print(") {");
	  // Third --> print the ID of the VIP Cargos
	  get_check_up_v_trucks().print();
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
	  }
	  ui_p->print("\n//////////////////////////////////////////////////////////////////////////////////////\n");
}

void Company::InteractivePrinting()
{
	ui_p->print("Interactive Mode\n");
	int Five_Counter = 0;
	while (!Events_empty())
	{
		//UI_P->print("Current Time (Day:Hour): ");
		//company.Print_Sim_Time();
		//UI_P->print("\n");
		//company.Print_Waiting_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");
		//company.Print_Moving_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");
		//company.Print_Delivered_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");

		if (get_Sim_Time() == get_Nearest_Event_Time())
		{
			Event* Eptr = get_Nearest_Event();
			Eptr->Execute();
		}

		while (true)
		{
			if (cin.get())
			{
				Output_Console();

				Advance_Sim_Time();
				Five_Counter++;
				if (Five_Counter == 5)
				{
					Five_Counter = 0;
					Waiting_To_Delivered();
				}
				break;
			}

		}
	}
	ui_p->print("All Events are done, Simulation over.");
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
	int Five_Counter = 0;
	while (!Events_empty())
	{

		//UI_P->print("Current Time (Day:Hour): ");
		//company.Print_Sim_Time();
		//UI_P->print("\n");
		//company.Print_Waiting_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");
		//company.Print_Moving_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");
		//company.Print_Delivered_Cargos();
		//UI_P->print("-----------------------------------------------------------------------------------------\n");


		if (get_Sim_Time() == get_Nearest_Event_Time())
		{
			Event* Eptr = get_Nearest_Event();
			Eptr->Execute();
		}

		while (true)
		{
			Sleep(1000);
			
				Output_Console();

				Advance_Sim_Time();
				Five_Counter++;
				if (Five_Counter == 5)
				{
					Five_Counter = 0;
					Waiting_To_Delivered();
				}
				break;
			

		}


		

		

	}
	ui_p->print("All Events are done, Simulation over.");
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
	return 0;
}

PriQueue<Cargo*>& Company::get_W_V_C()
{
	return W_V_C;
}

Queue<Cargo*>& Company::get_W_S_C()
{
	return W_S_C;
}

LinkedList<Cargo*>& Company::get_W_N_C()
{
	return W_N_C;
}

PriQueue<Cargo*>& Company::get_M_V_C()
{
	return M_V_C;
}

PriQueue<Cargo*>& Company::get_M_S_C()
{
	return M_S_C;
}

PriQueue<Cargo*>& Company::get_M_N_C()
{
	return M_N_C;
}

Queue<Truck*>& Company::get_Loading()
{
	return Loading;
}
Queue<Truck*>& Company::get_Empty()
{
	return Empty;
}
Queue<Truck*>& Company::get_check_up_v_trucks()
{
	return Check_up_VIP;
}
Queue<Truck*>& Company::get_check_up_s_trucks()
{
	return Check_up_Special;
}
Queue<Truck*>& Company::get_check_up_n_trucks()
{
	return Check_up_Normal;
}