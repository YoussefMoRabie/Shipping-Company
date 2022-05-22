#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include <Windows.h>
#include <string>
#include <cmath>
using namespace std;

Company::Company()
{
	Loading_Normal = nullptr;
	Loading_Special = nullptr;
	Loading_VIP = nullptr;
	Num_Promoted_cargos = 0;
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
		load_VIP();
	}
	if (!Loading_Normal)
	{
		load_Normal();
	}
	load_MaxW();
}
void Company::Off_Hours()
{

}

bool Company::load_VIP()
{
	Truck* t_temp = Pick_VIP_Truck();
	Cargo* c_temp;
	if (t_temp) 
	{
		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_V_C.DeQueue(c_temp);
			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			t_temp->load(c_temp, delivery_time);
		}
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
	if (t_temp) {
		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_S_C.DeQueue(c_temp);
			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			t_temp->load(c_temp, delivery_time);
		}
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
	if (t_temp)
	{

		for (int i = 0; i < t_temp->GetCapacity(); i++)
		{
			W_N_C.removeFirst(c_temp);
			float delivery_time = c_temp->GetDistance() / t_temp->GetSpeed();
			t_temp->load(c_temp, delivery_time);
		}
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


void Company::Truck_Controller() {
	Move_Trucks();
	Truck* t_temp;
	if (!Moving_truck.QueueEmpty())
		if (Sim_Time >= Moving_truck.Peek()->get_finish_point() && Moving_truck.Peek()->GetContainer_count() == 0) {
			Moving_truck.DeQueue(t_temp);
			t_temp->DecrementJTC();
			if (Need_Checkup(t_temp)) {
				move_to_checkup(t_temp);
			}
			else move_to_available(t_temp);
		}

	if (!Check_up_VIP.QueueEmpty())
		if (Sim_Time == Check_up_VIP.Peek()->get_finish_point())
		{
			Check_up_VIP.DeQueue(t_temp);
			check_to_available(t_temp);
		}

	if (!Check_up_Special.QueueEmpty())
		if (Sim_Time == Check_up_Special.Peek()->get_finish_point())
		{
			Check_up_Special.DeQueue(t_temp);
			check_to_available(t_temp);
		}

	if (!Check_up_Normal.QueueEmpty())
		if (Sim_Time == Check_up_Normal.Peek()->get_finish_point())
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
	if (W_V_C.GetCount() >= nCap && !Loading_Normal)
	{
		if (!empty_Normal.QueueEmpty()) {
			empty_Normal.DeQueue(t_temp);
			return t_temp;
		}
	}
	if (W_V_C.GetCount() >= sCap && !Loading_Special)
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
	if (W_N_C.GetCount() >= vCap && !Loading_VIP)
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
	if (!Moving_truck.Peek())
		return;

	if (Moving_truck.Peek() && Moving_truck.Peek()->GetContainer_count() == 0)
		return;

	if (get_Sim_Time() >= Moving_truck.Peek()->Get_nearest_stop()) 
	{
		Truck* temp;
		PriQueue<Truck*> truck_temp;
		Cargo* c_temp = Moving_truck.Peek()->unload();
		Delivered_cargo.EnQueue(c_temp);
		float x = Moving_truck.Peek()->Get_nearest_dis();
		if (Moving_truck.Peek()->GetContainer_count() != 0)
			Moving_truck.Peek()->set_nearest_stop(get_Sim_Time() + (x - c_temp->GetDistance()) / Moving_truck.Peek()->GetSpeed());
		while (Moving_truck.GetCount()>1) {
			Moving_truck.DeQueue(temp);
		
			truck_temp.EnQueue(temp, temp->Get_nearest_stop() - get_Sim_Time());
		}
		while (truck_temp.GetCount() > 1) {
			truck_temp.DeQueue(temp);
			Moving_truck.EnQueue(temp);
		}
	}
}
void Company::Move_Truck(Truck*& t)
{
	float dis_temp;
	t->set_DInterval();
	int finish_time = ceil(t->GetDeliveryInterval());
	t->set_finish_point(get_Sim_Time() + finish_time);
	dis_temp = t->Get_nearest_dis();
	float time_temp= ceil(dis_temp / t->GetSpeed());
	t->set_nearest_stop(get_Sim_Time() + time_temp);
	Moving_truck.EnQueue(t,time_temp);
	t = nullptr;
}
bool Company::Need_Checkup(Truck* t) {
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
		int time = (c->GetPrepTime().getDay() * 24) + c->GetPrepTime().getHour();
		float priority = 10 * c->GetCost() / (c->GetDistance() * time);
		W_V_C.EnQueue(c, priority);
		break;
	}
	}
}
void Company::Auto_Promotion()
{
	if (W_N_C.IsEmpty())
		return;
	
	while (rest_in_waiting(W_N_C.getFirst()) >= AutoPro * 24)
	{
		Upgrade_Normal_Cargo(W_N_C.getFirst()->GetID());
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
		temp.EnQueue(c);
	
	}
	while (!temp.QueueEmpty())
	{
		temp.DeQueue(c);
		Delivered_cargo.EnQueue(c);
	}
	ui_p->print("\n\n###########################################################################################\n\n");
}
void Company::Print(SIM_MODE Mode)
{
	if (Mode == SIM_MODE::INTERACTIVE)
		ui_p->print("Interactive Mode\n");
	else if (Mode == SIM_MODE::STEP_BY_STEP)
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
		if ( Mode == SIM_MODE::STEP_BY_STEP||cin.get()&& Mode == SIM_MODE::INTERACTIVE)
		{
			if(Mode == SIM_MODE::STEP_BY_STEP)
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
	}
	if (Mode == SIM_MODE::STEP_BY_STEP)
		Sleep(1000);
	else
		cin.get();
	Output_Console();
	ui_p->print("Everything is done, Simulation over.");
}
void Company::InteractivePrinting()
{
	Print(SIM_MODE::INTERACTIVE);
}

void Company::SilentPrinting()
{
	ui_p->print("Silent Mode\n");
	ui_p->print("Simulation Starts...\n");
	ui_p->print("Simulation ends, Output file created\n");
}
void Company::StepByStepPrinting()
{
	Print(SIM_MODE::STEP_BY_STEP);
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