#include"Truck.h"
#include<iostream>
using namespace std;

Truck::Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S,TRUCK_SHIFT sh)
{
	ID = id;
	Type = T;
	Truck_Capacity = TC;
	Maintenance_Time = MT;
	J = j;
	Speed = S;
	Journeys_Till_Check = j;
	Set_AT(0);
	TDC = 0;
	N = 0;
	shift = sh;
}
TRUCK_TYPE Truck:: GetType() const
{
	return Type;
}
int Truck::GetCapacity() const
{
	return Truck_Capacity;
}
void Truck::setSpeed(float x) {
	Speed = x;
}
void Truck::set_DInterval() {
	float temp = 2* ceil( Delivery_Distance/ GetSpeed()) + GetContainer_count() * container.Peek()->GetLU_Time();

	Delivery_Interval = temp;
}
int Truck:: GetJTC() {
	return Journeys_Till_Check;
}
int Truck::GetContainer_count() {
	return container.GetCount();
}
void Truck::restore_JTC() {
	Journeys_Till_Check = J;
}
TRUCK_SHIFT Truck::getshift() {
	return shift;
}
void Truck::DecrementJTC() {
	Journeys_Till_Check--;
}
float Truck::GetMaintenanceTime() const
{
	
	return Maintenance_Time;
}
void Truck::set_finish_point(const Time& t) {
	finish_point = t;
}
Time Truck::get_finish_point() {
	return finish_point;
}
float Truck:: GetSpeed() const
{
	return Speed;
}
float Truck::GetDeliveryInterval()
{
	return Delivery_Interval;
}
int Truck:: GetID() const
{
	return ID;
}
void Truck::load(Cargo* x, float delivery_time)
{
	if (container.QueueEmpty())
		Delivery_Distance = x->GetDistance();

	else if (x->GetDistance() > Delivery_Distance)
		Delivery_Distance = x->GetDistance();

	container.EnQueue(x, 100/delivery_time);
	if (x->GetLU_Time() > move_counter)
		move_counter = x->GetLU_Time();

}
Cargo* Truck::unload() {
	if (GetContainer_count() > 0) {
		Cargo* c_temp;
		container.DeQueue(c_temp);
		return c_temp;
	}
	return nullptr;
}
void Truck::count_down()
{
	move_counter--;
}
int Truck::get_move_counter()
{
	return move_counter;
}


float Truck::Get_nearest_dis() {
	if (GetContainer_count() > 0)
		return container.Peek()->GetDistance();
	else
		return Delivery_Distance;
}
Time Truck::Get_nearest_stop() {
	return Nearest_stop;
}
void Truck::set_nearest_stop(Time t, float x) {
	float l_t;
	if (GetContainer_count() > 0)
		l_t = ceil(container.Peek()->GetLU_Time() +( Get_nearest_dis() - x) / GetSpeed());
	else
		l_t = ceil(Get_nearest_dis() / GetSpeed());
	Nearest_stop = t + l_t;
}
void Truck::Set_AT(int h)
{
	AT.setTime(h);
}
void Truck::inc_TDC()
{
	TDC++;
}
void Truck::inc_N()
{
	N++;
}
int Truck::Get_TDC()
{
	return TDC;
}
int Truck::Get_N()
{
	return N;
}
Time Truck::Get_AT()
{
	return AT;
}
float Truck::utilization(Time& Sim_Time)
{
	if (N == 0)
		return 0;
	return 100 * (TDC / (N * Truck_Capacity) * (float(AT.Time_In_Hours()) / Sim_Time.Time_In_Hours()));
}

void Truck::print_container()
{
	Cargo* c;
	PriQueue<Cargo*>temp;
	float pri = 0;
	while (!container.QueueEmpty())
	{
		container.DeQueue(c);
		if (c->GetType() == CARGO_TYPE::VIP)
		{
			int time = c->GetPrepTime().Time_In_Hours();
			pri = 10 * c->GetCost() / (c->GetDistance() * time);
		}
		else
			pri = 10 / c->GetPrepTime().Time_In_Hours();
		temp.EnQueue(c, pri);
	}
	temp.print();
	while (!temp.QueueEmpty())
	{
	temp.DeQueue(c);
	pri	= 10 / (c->GetDistance() / Speed);
	container.EnQueue(c, pri);
	}
}

void Truck::print()
{
	ui_p->print(to_string(ID));
	if (container.QueueEmpty())
	{
		return;
	}

	if (container.Peek()->GetType() == CARGO_TYPE::VIP)
	{
		ui_p->print("{");
		container.print();
		ui_p->print("} ");
	}
	else if (container.Peek()->GetType() == CARGO_TYPE::SPECIAL)
	{
		ui_p->print("(");
		container.print();
		ui_p->print(") ");
	}
	else if (container.Peek()->GetType() == CARGO_TYPE::NORMAL)
	{
		ui_p->print("[");
		container.print();
		ui_p->print("] ");
	}
}
void Truck::Set_moving_time(Time& Sim_Time)
{
	moving_time = Sim_Time;
}
Time Truck::get_moving_time()
{
	return moving_time;
}
ostream& operator<<(ostream& out, Truck* t)
{
	t->print();
	return out;
}