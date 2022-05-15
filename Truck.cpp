#include"Truck.h"
#include<iostream>
using namespace std;

Truck::Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S)
{
	ID = id;
	Type = T;
	Truck_Capacity = TC;
	Maintenance_Time = MT;
	J = j;
	Speed = S;
}
TRUCK_TYPE Truck:: GetType() const
{
	return Type;
}
int Truck::GetCapacity() const
{
	return Truck_Capacity;
}
void Truck::set_DInterval(float x) {
	Delivery_Interval = x;
}

float Truck::GetMaintenanceTime() const
{
	return Maintenance_Time;
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
void Truck::load(Cargo* x, int LT)
{
	container.EnQueue(x, LT);
	move_counter = container.Peek()->GetLU_Time();
}
void Truck::count_down()
{
	move_counter--;
}
int Truck::get_move_counter()
{
	return move_counter;
}
void Truck::print()
{
	if (container.QueueEmpty())
		return;

	ui_p->print(to_string(ID));
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
ostream& operator<<(ostream& out, const Truck* t)
{
	out << t->GetID();
	return out;
}