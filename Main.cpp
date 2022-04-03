#include "Company.h"
#include "Event.h"
#include "UI.h"

int main()
{
	int Five_Counter = 0;

	UI* UI_P = new UI();
	Company company(UI_P);

	string filename;
	filename = UI_P->getString();
	company.readFile(filename);
	cin.get();

	while (!company.Events_empty())
	{
		UI_P->print("Current Time (Day:Hour): ");
		company.Print_Sim_Time();
		UI_P->print("\n");
		company.Print_Waiting_Cargos();
		UI_P->print("-----------------------------------------------------------------------------------------\n");
		company.Print_Moving_Cargos();
		UI_P->print("-----------------------------------------------------------------------------------------\n");
		company.Print_Delivered_Cargos();
		UI_P->print("-----------------------------------------------------------------------------------------\n");

		if (company.get_Sim_Time() == company.get_Nearest_Event_Time())
		{
			Event* Eptr = company.get_Nearest_Event();
			Eptr->Execute();
		}

		while (true)
		{
			if (cin.get())
			{
				company.Advance_Sim_Time();
				Five_Counter++;
				if (Five_Counter == 5)
				{
					Five_Counter = 0;
					company.Waiting_To_Delivered();
				}
				break;
			}
		}
	}
	UI_P->print("All Events are done, Simulation over.");
	return 0;
}