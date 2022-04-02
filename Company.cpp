#include "Company.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include <string>
using namespace std;

Company::Company(UI* u)
{
	ui_p = u;
}

void Company::move_to_checkup(Truck*)
{
}

bool Company::Events_empty()
{
	return Events.QueueEmpty();
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
		Normal_cargo.EnQueue(c);
		break;
	}
	case CARGO_TYPE::SPECIAL:
	{
		Special_cargo.EnQueue(c);
		break;
	}
	case CARGO_TYPE::VIP:
	{
		VIP_cargo.EnQueue(c);
		break;
	}
	}
}

void Company::readFile(string filename)
{
	Loaded.open(filename);

	if (!Loaded.is_open())
	{
		ui_p->print("Error: Can't open file ! Click to continue ...");
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
		Loaded >> event_type;
		if (event_type == 'R')
		{
			char cargo_type;
			string t;
			int id;
			float dist, LT, cost;
			Loaded >> cargo_type >> t >> id >> dist >> LT >> cost;

			Time T(t);
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
			string t;
			int id;
			Loaded >> t >> id;
			Time T(t);
			Eptr = new CancelEvent(this, T, id);
		}
		else if (event_type == 'P')
		{
			string t;
			int id;
			float extra;
			Loaded >> t >> id >> extra;
			Time T(t);
			Eptr = new PromoteEvent(this, T, id, extra);
		}
		if (Eptr)
		{
			Eptr->Execute();
			delete Eptr;
		}
	}
}