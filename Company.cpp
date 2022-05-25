





#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include <Windows.h>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

Company::Company()
{
	Loading_Normal = nullptr;
	Loading_Special = nullptr;
	Loading_VIP = nullptr;
	Num_Promoted_cargos = 0;
	VIP_Cargos_count=0;
	Normal_Cargos_count=0;
	Special_Cargos_count=0;
	VIP_Trucks_count=0;
	Normal_Trucks_count=0;
	Special_Trucks_count=0;
	Total_Trucks_count = 0;
	Total_Cargos_count=0;
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
	Auto_Promotion();
	Truck_Controller();
	Deliver_cargos();

	if(!Loading_VIP)
	{
		load_VIP();
	}
	if (!Loading_Special)
	{

		load_Special();
	}
	if (!Loading_Normal)
	{
		load_Normal();
	}
	load_MaxW();
}
void Company::Off_Hours()
{
	Truck_Controller();
	Deliver_cargos();
}

bool Company::load_VIP()
{
	Truck* t_temp = Pick_VIP_Truck();
	Cargo* c_temp;
	float T_L_T=0;
	float M_L_T = 0;
	float DT=0;
	if (t_temp) 
	{
		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_V_C.DeQueue(c_temp);			
			if (c_temp)
			{
				c_temp->Set_Truck_ID(t_temp->GetID());
				if (c_temp->GetLU_Time() > M_L_T)
					M_L_T = c_temp->GetLU_Time();
				T_L_T += c_temp->GetLU_Time();
				t_temp->inc_TDC();
			}

			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			if (delivery_time > DT)
				DT = delivery_time;
			t_temp->load(c_temp, delivery_time);
		}
		T_L_T += M_L_T;
		t_temp->Set_AT(ceil(T_L_T+DT + t_temp->Get_AT().Time_In_Hours()));
		Loading_VIP = t_temp;
		return true;
	}
	else
		return false;
}

bool Company::load_Special()
{
	Truck* t_temp = Pick_Special_Truck();
	Cargo* c_temp;
	float T_L_T = 0;
	float M_L_T = 0;
	float DT = 0;
	if (t_temp) {
		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_S_C.DeQueue(c_temp);
			if (c_temp)
			{
				c_temp->Set_Truck_ID(t_temp->GetID());
				if (c_temp->GetLU_Time() > M_L_T)
					M_L_T = c_temp->GetLU_Time();
				T_L_T += c_temp->GetLU_Time();
			}

			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			if (delivery_time > DT)
				DT = delivery_time;
			t_temp->load(c_temp, delivery_time);
			t_temp->inc_TDC();

		}
		T_L_T += M_L_T;
		t_temp->Set_AT(ceil(T_L_T + DT + t_temp->Get_AT().Time_In_Hours()));
		Loading_Special = t_temp;
		return true;
	}

	else
		return false;
}

bool Company::load_Normal()
{
	Truck* t_temp = Pick_Normal_Truck();
	Cargo* c_temp;
	float T_L_T = 0;
	float M_L_T = 0;
	float DT = 0;
	if (t_temp)
	{

		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_N_C.removeFirst(c_temp);
			if (c_temp)
			{
				c_temp->Set_Truck_ID(t_temp->GetID());
				if (c_temp->GetLU_Time() > M_L_T)
					M_L_T = c_temp->GetLU_Time();
				T_L_T += c_temp->GetLU_Time();
			}

			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			if (delivery_time > DT)
				DT = delivery_time;
			t_temp->load(c_temp, delivery_time);
			t_temp->inc_TDC();

		}
		T_L_T += M_L_T;
		t_temp->Set_AT(ceil(T_L_T + DT + t_temp->Get_AT().Time_In_Hours()));
		Loading_Normal = t_temp;
		return true;

	}
	else
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
					t_temp->inc_TDC();
					Loading_Special = t_temp;
					if (c_temp)
					{
						c_temp->Set_Truck_ID(t_temp->GetID());
						t_temp->Set_AT(ceil(c_temp->GetLU_Time()*2+ (c_temp->GetDistance()/t_temp->GetSpeed())+t_temp->Get_AT().Time_In_Hours()));

					}
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
					t_temp->inc_TDC();
					Loading_Normal = t_temp;
					if (c_temp)
					{
						c_temp->Set_Truck_ID(t_temp->GetID());
						t_temp->Set_AT(ceil(c_temp->GetLU_Time() * 2 + (c_temp->GetDistance() / t_temp->GetSpeed()) + t_temp->Get_AT().Time_In_Hours()));
					}
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
					t_temp->inc_TDC();
					Loading_VIP = t_temp;
					if (c_temp)
					{
						c_temp->Set_Truck_ID(t_temp->GetID());
						t_temp->Set_AT(ceil(c_temp->GetLU_Time() * 2 + (c_temp->GetDistance() / t_temp->GetSpeed()) + t_temp->Get_AT().Time_In_Hours()));
					}
					return true;
				}
			}
		}
	}
	return false;
}


void Company::Truck_Controller() //controll the transition of trucks between lists
{
	if((in_working(Sim_Time)))
		Move_Trucks();
	Truck* t_temp;
		while (!Moving_truck.QueueEmpty() && Sim_Time >= Moving_truck.Peek()->Get_nearest_stop()&& Moving_truck.Peek()->GetContainer_count() == 0) //if the truck finished the journey
		{
			
			Moving_truck.DeQueue(t_temp);//remove it from the moving
			
				t_temp->DecrementJTC(); //decrement the journeys untill its maintainence
				t_temp->inc_N(); //increment total journeys 
				if (Need_Checkup(t_temp)) //checks if it needs maintainence
				{
					move_to_checkup(t_temp);
				}
				else move_to_available(t_temp);
		
		}

	
		while (!Check_up_VIP.QueueEmpty()&& Sim_Time == Check_up_VIP.Peek()->get_finish_point())// checks if it finished checkup
		{
			Check_up_VIP.DeQueue(t_temp);
			check_to_available(t_temp);
		}

		while (!Check_up_Special.QueueEmpty()&&Sim_Time == Check_up_Special.Peek()->get_finish_point())// checks if it finished checkup
		{
			Check_up_Special.DeQueue(t_temp);
			check_to_available(t_temp);
		}

		while (!Check_up_Normal.QueueEmpty()&&Sim_Time == Check_up_Normal.Peek()->get_finish_point())// checks if it finished checkup
		{
			Check_up_Normal.DeQueue(t_temp);
			check_to_available(t_temp);
		}

}

//Picks an available truck for a vip cargo
Truck* Company::Pick_VIP_Truck() {
	Truck* t_temp;

	if (W_V_C.GetCount() >= vCap && !Loading_VIP)
	{
		if (!empty_VIP.QueueEmpty()) {
			empty_VIP.DeQueue(t_temp);
			return t_temp;
		}
	}
	
	if (empty_VIP.QueueEmpty()&& W_V_C.GetCount() >= nCap && !Loading_VIP)
	{
		if (!empty_Normal.QueueEmpty()) {
			empty_Normal.DeQueue(t_temp);
			return t_temp;
		}
	}
	if (empty_VIP.QueueEmpty()&& empty_Normal.QueueEmpty() && W_V_C.GetCount() >= sCap && !Loading_VIP)
	{
		if (!empty_Special.QueueEmpty()) {
			empty_Special.DeQueue(t_temp);
			return t_temp;
		}
	}
	return nullptr;
}
//Picks an available truck for a normal cargo
Truck* Company::Pick_Normal_Truck() {
	Truck* t_temp;

	if (W_N_C.GetCount() >= nCap && !Loading_Normal)
	{
		if (!empty_Normal.QueueEmpty()) {
			empty_Normal.DeQueue(t_temp);
			return t_temp;
		}
	}
	if (empty_Normal.QueueEmpty()&& W_N_C.GetCount() >= vCap && !Loading_Normal)
	{
		if (!empty_VIP.QueueEmpty()) {
			empty_VIP.DeQueue(t_temp);
			return t_temp;
		}
	}
	return nullptr;

}
//Picks an available truck for a special cargo
Truck* Company::Pick_Special_Truck() {
	Truck* t_temp;

	if (W_S_C.GetCount() >= sCap && !Loading_Special)
	{
		if (!empty_Special.QueueEmpty()) {
			empty_Special.DeQueue(t_temp);
			return t_temp;
		}
	}
	return nullptr;
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
void Company::Deliver_cargos() {
	Truck* temp;
	PriQueue<Truck*> truck_temp;
	Cargo* c_temp;

	while (Moving_truck.Peek() && Moving_truck.Peek()->GetContainer_count() != 0)//if there is moving truck and not empty
	{
		
		Moving_truck.DeQueue(temp);
		if (Sim_Time >= temp->Get_nearest_stop())//checks if it has arrvived for its destination
		{
			 c_temp = temp->unload(); //unload cargo from conatiner
			Delivered_cargo.EnQueue(c_temp); //moves it to delivered
			temp->set_nearest_stop(get_Sim_Time(), c_temp->GetDistance()); // set the nest destination
			c_temp->Set_DT(get_Sim_Time());
			c_temp->Set_WT(temp->get_moving_time() - c_temp->Get_Preparation_Time());



		}
		if (Moving_truck.Peek() &&Moving_truck.Peek()->GetContainer_count() == 0)
			Truck_Controller();
		truck_temp.EnQueue(temp, -(temp->Get_nearest_stop() - Sim_Time)); // enqueue the truck based on its new destination among the moving trucks
	}
	while (!truck_temp.QueueEmpty()) //updates the moving list
	{
		truck_temp.DeQueue(temp);
		Moving_truck.EnQueue(temp,  -(temp->Get_nearest_stop() - Sim_Time));
	}

}
void Company::Move_Truck(Truck*& t)
{
	float dis_temp;
	t->set_DInterval(); //set the delivery distance
	
	dis_temp = t->Get_nearest_dis(); 
	float time_temp= dis_temp / t->GetSpeed();
	t->Set_moving_time(Sim_Time);
	t->set_nearest_stop(get_Sim_Time(),0 ); //set the first destination
	Moving_truck.EnQueue(t,-(t->Get_nearest_stop() - Sim_Time)); 
	t = nullptr;
}
bool Company::Need_Checkup(Truck* t) //checks every journey if the truck needs maintainence
{
	if (t->GetJTC() == 0)
		return true;
	return false;
}

void Company::move_to_checkup(Truck* t)
{ 
	
	t->set_finish_point(get_Sim_Time() + t->GetMaintenanceTime());
	if (t->GetType() == TRUCK_TYPE::VIP) {
		Check_up_VIP.EnQueue(t);
	}
	else {
		if (t->GetType() == TRUCK_TYPE::NORMAL)
			Check_up_Normal.EnQueue(t);
		else {
			if (t->GetType() == TRUCK_TYPE::SPECIAL)
				Check_up_Special.EnQueue(t);
		}
	}

}
void Company::check_to_available(Truck*& t) {
	t->restore_JTC();
	if (t->GetType() == TRUCK_TYPE::VIP) {
		empty_VIP.EnQueue(t);
	}
	else {
		if (t->GetType() == TRUCK_TYPE::NORMAL)
			empty_Normal.EnQueue(t);
		else {
			if (t->GetType() == TRUCK_TYPE::SPECIAL)
				empty_Special.EnQueue(t);
		}
	}
}
void Company::move_to_available(Truck* t) {

	
	if (t->GetType() == TRUCK_TYPE::VIP) {
		empty_VIP.EnQueue(t);
	}
	else {
		if (t->GetType() == TRUCK_TYPE::NORMAL)
			empty_Normal.EnQueue(t);
		else {
			if (t->GetType() == TRUCK_TYPE::SPECIAL)
				empty_Special.EnQueue(t);
		}
	}
}

bool Company::Events_empty()
{
	return Event_List.QueueEmpty();
}

//searches the normal cargo list with the id, if found it is removed from the normal list and added to the vip one.
bool Company::Upgrade_Normal_Cargo(int id, int extra_money)
{
	Cargo* ptr = new Cargo(id);
	Cargo* temp;
	if (W_N_C.Find_Remove(ptr, temp))
	{
		temp->PromoteToVip(extra_money);
		AddCargo(temp);
		delete ptr;
		return true;
	}
	delete ptr;
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
		int time = c->GetPrepTime().Time_In_Hours();
		float priority = 10 * c->GetCost() / (c->GetDistance() * time);
		W_V_C.EnQueue(c, priority);
		break;
	}
	}
}
void Company::Auto_Promotion()
{	
	while (!W_N_C.IsEmpty() && rest_in_waiting(W_N_C.getFirst()) >= AutoPro * 24)
	{
		Upgrade_Normal_Cargo(W_N_C.getFirst()->GetID());
		Num_Promoted_cargos++;
	}
}
int Company::rest_in_waiting(Cargo * car)
{
	return get_Sim_Time() - car->GetPrepTime();
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
		Normal_Trucks_count++;
	}
	for (int i = 0; i < S; i++)
	{
		Truck* T = new Truck(truck_id, TRUCK_TYPE::SPECIAL, sCap, sCheck, Num_of_journeys, sSpeed);
		empty_Special.EnQueue(T);
		truck_id++;
		Special_Trucks_count++;

	}
	for (int i = 0; i < V; i++)
	{
		Truck* T = new Truck(truck_id, TRUCK_TYPE::VIP, vCap, vCheck, Num_of_journeys, vSpeed);
		empty_VIP.EnQueue(T);
		truck_id++;
		VIP_Trucks_count++;
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
			if(in_working(T))
			switch (cargo_type)
			{
			case 'N':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::NORMAL, T, id, dist, LT, cost);
				Normal_Cargos_count ++;
				break;
			}
			case 'S':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::SPECIAL, T, id, dist, LT, cost);
				Special_Cargos_count++;
				break;
			}
			case 'V':
			{
				Eptr = new PreparationEvent(this, CARGO_TYPE::VIP, T, id, dist, LT, cost);
				VIP_Cargos_count++;
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
	if (Event_List.Peek())
	return Event_List.Peek()->getTime();
	else
	{
		Time t(0, 0);
		return t;
	}
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

//
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

//simulation ends when every cargo is delivered
bool Company::All_Delivered()
{
	if (W_N_C.IsEmpty() && W_S_C.QueueEmpty() && W_V_C.QueueEmpty() && !Loading_Normal && !Loading_Special && !Loading_VIP && Moving_truck.QueueEmpty())
		return true;
	else
		return false;
}

void Company::Output_Console()
{
	ui_p->print("Current Time (Day:Hour):" + to_string(Company::get_Sim_Time().getDay()) + ":" + to_string(Company::get_Sim_Time().getHour()) + "\n");
	//calculate # of waiting cargos
	int loading_count=0;
	if (Loading_Normal)
		loading_count += Loading_Normal->GetContainer_count();
	if (Loading_Special)
		loading_count += Loading_Special->GetContainer_count();
	if (Loading_VIP)
		loading_count += Loading_VIP->GetContainer_count();
	int W_C = W_V_C.GetCount() + W_S_C.GetCount() + W_N_C.GetCount() + loading_count;
	ui_p->print(to_string(W_C) + " Waiting Cargos: [");
	// First --> print the ID of the Normal Cargos
	if (Loading_Normal)
	{
		Loading_Normal->print_container();
		if(!W_N_C.IsEmpty())
			ui_p->print(",");
	}
	W_N_C.print();
	ui_p->print("] (");
	// Second --> print the ID of the Special Cargos
	if (Loading_Special)
	{
		Loading_Special->print_container();
		if (!W_S_C.QueueEmpty())
			ui_p->print(",");
	}
	W_S_C.print();
	ui_p->print(") {");
	// Third --> print the ID of the VIP Cargos
	if (Loading_VIP)
	{
		Loading_VIP->print_container();
		if (!W_V_C.QueueEmpty())
			ui_p->print(",");
	}
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
	int M_C = Moving_truck.GetCount();
	ui_p->print(to_string(M_C) + " Moving Cargos: ");
	Moving_truck.print();
	ui_p->print("\n----------------------------------------------------------------------------\n");

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
	Cargo* c;
	ui_p->print(to_string(Delivered_cargo.GetCount()) + " Delivered Cargos:");
	while (!Delivered_cargo.QueueEmpty())
	{
		Delivered_cargo.DeQueue(c);
		if (c->GetType() == CARGO_TYPE::NORMAL)
			ui_p->print("[" + to_string(c->GetID()) + "]");
		else if (c->GetType() == CARGO_TYPE::VIP)
			ui_p->print("{" + to_string(c->GetID()) + "}");
		else
			ui_p->print("(" + to_string(c->GetID()) + ")");
		ui_p->print(" ");
		temp.EnQueue(c);
	}
	while (!temp.QueueEmpty())
	{
		temp.DeQueue(c);
		Delivered_cargo.EnQueue(c);
	}
	ui_p->print("\n\n###########################################################################################\n\n");
}
void Company::Sim_Manager(SIM_MODE Mode)
{
	if (Mode == SIM_MODE::INTERACTIVE)
		ui_p->print("Interactive Mode\n");
	else if (Mode == SIM_MODE::STEP_BY_STEP)
		ui_p->print("StepByStep Mode\n");
	else if (Mode == SIM_MODE::SILENT)
	{
		ui_p->print("Silent Mode\n");
		ui_p->print("Simulation Starts...\n");

	}

	while (!Events_empty() || !All_Delivered())
	{
		if (!Events_empty())
		{
			while ( get_Sim_Time() == get_Nearest_Event_Time() )
			{
				Event* Eptr = get_Nearest_Event();
				Eptr->Execute();
			}
		}
		if (Mode == SIM_MODE::SILENT || Mode == SIM_MODE::STEP_BY_STEP||cin.get()&& Mode == SIM_MODE::INTERACTIVE)
		{
			if(Mode == SIM_MODE::STEP_BY_STEP)
				Sleep(1000);
			if (in_working(Sim_Time))
			{
				Working_Hours();
			}
			else
			{
				Off_Hours();
			}
			if (Mode != SIM_MODE::SILENT)
				Output_Console();
			Advance_Sim_Time();
		}
	}
	if (Mode == SIM_MODE::STEP_BY_STEP)
		Sleep(1000);
	else if(Mode == SIM_MODE::INTERACTIVE)
		cin.get();
	if(Mode!= SIM_MODE::SILENT)
	Output_Console();
	write_output_file();
	ui_p->print("Simulation ends, Output file created\n");
}
bool Company::in_working(Time T)
{
	return 5 <= T.getHour() && T.getHour() <= 23;
}
void Company::InteractivePrinting()
{
	Sim_Manager(SIM_MODE::INTERACTIVE);
}

void Company::SilentPrinting()
{
	Sim_Manager(SIM_MODE::SILENT);
}
void Company::StepByStepPrinting()
{
	Sim_Manager(SIM_MODE::STEP_BY_STEP);
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
	int Delivered = Delivered_cargo.GetCount();
	string Text = "";
	ofstream outFile("output.txt");
	if (!(outFile.is_open()))return false;
	if (!Delivered)
		Text = "THERE ARE NO COMPLETED MISSIONS !!!!\n";
	else
		Statistics_File(Delivered, Text);
	outFile << Text;
	outFile.close();
	if (outFile.is_open())return false;
	return true;
}
void Company::Statistics_File(int Delivered, string & text)
{
	stringstream str;
	Cargo* car;
	Truck * truck;
	float T_A_T=0;
	int T_W=0;
	float utilization = 0;
	Total_Cargos_count = Normal_Cargos_count + Special_Cargos_count + VIP_Cargos_count;
	 Total_Trucks_count= VIP_Trucks_count + Normal_Trucks_count + Special_Trucks_count;;
	str << "CDT\tID\tPT\tWT\tTID\n";
	for (int i = 0; i < Delivered; i++)
	{
		Delivered_cargo.DeQueue(car);
		str <<car->Get_DT().Time_to_print() << "\t" << car->GetID() << "\t"<<car->Get_Preparation_Time().Time_to_print()<<"\t"<< car->Get_WT().Time_to_print() << "\t" << car->Get_Truck_ID() << "\n";
		T_W += car->Get_WT().Time_In_Hours();
	}
	while (!empty_VIP.QueueEmpty())
	{
		empty_VIP.DeQueue(truck);
		utilization += truck->utilization(get_Sim_Time());
		T_A_T += truck->Get_AT().Time_In_Hours();
	}	
	while (!empty_Special.QueueEmpty())
	{
		empty_Special.DeQueue(truck);
		utilization += truck->utilization(get_Sim_Time());
		T_A_T += truck->Get_AT().Time_In_Hours();
	}	
	while (!empty_Normal.QueueEmpty())
	{
		empty_Normal.DeQueue(truck);
		utilization += truck->utilization(get_Sim_Time());
		T_A_T += truck->Get_AT().Time_In_Hours();
	}
	Time Avg_Wait(T_W / Delivered);
	Time Avg_Active_Time(T_A_T / Total_Trucks_count);
	str << "-------------------------------------------------------------\n";
	str << "Cargos: " << to_string(Total_Cargos_count) << " [N: " << to_string(Normal_Cargos_count) << ", S: " << to_string(Special_Cargos_count) << ", V: " << to_string(VIP_Cargos_count) << "]\n";
	str << "Cargo Avg Wait = " << Avg_Wait.Time_to_print() << "\n";
	str << "Auto-promoted Cargos:" << to_string((auto_promoted_count/ Total_Cargos_count)*100)<<"%\n";
	str << "Trucks: " << to_string(Total_Trucks_count) << " [N: " << to_string(Normal_Trucks_count) << ", S: " << to_string(Special_Trucks_count) << ", V: " << to_string(VIP_Trucks_count) << "]\n";
	str << "Avg Active time = " << to_string( (float(Avg_Active_Time.Time_In_Hours())/ get_Sim_Time().Time_In_Hours())*100) << "%\n";
	str << "Avg utilization = "<<to_string(utilization/ Total_Trucks_count)<<"%\n";

	text = str.str();
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