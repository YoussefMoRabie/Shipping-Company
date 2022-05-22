#pragma once
#include "Def.h"
#include "Cargo.h"
#include "Truck.h"
#include "UI.h"
#include "Queue.h"
#include "PriQueue.h"
#include "LinkedList.h"
#include <fstream>

class Event;

class Company
{
	UI* ui_p;
	Time Sim_Time;
	ifstream Loaded;
	//------------------------------------------------------

	//Cargos
	PriQueue<Cargo*> W_V_C;		//waiting vip cargos
	Queue<Cargo*> W_S_C;		//waiting special cargos
	LinkedList<Cargo*> W_N_C;	//waiting normal cargos
	Queue<Cargo*> Delivered_cargo;

	//------------------------------------------------------

	//Trucks
	Queue<Truck*> empty_VIP;
	Queue<Truck*> empty_Special;
	Queue<Truck*> empty_Normal;
	Queue<Truck*> Check_up_Normal;
	Queue<Truck*> Check_up_Special;
	Queue<Truck*> Check_up_VIP;
	PriQueue<Truck*> Moving_truck;

	Queue<Event*> Event_List;

	//-------------------------------------------------------

	int MaxWait;
	int AutoPro;
	int Num_of_events;
	int nCap, sCap, vCap;
	//Numbers of Trucks in each list

	int VIP_Trucks_count;
	int Normal_Trucks_count;
	int Special_Trucks_count;
	int Assigned_Trucks_count;
	int InCheck_Trucks_count;
	int Total_Trucks_count;

	//-------------------------------------------------------
	
	//Number of cargos in each list
	int Moving_Cargos_count;
	int Delivered_Cargos_count;
	int Total_Cargos_count;
	int Num_Promoted_cargos;

	//--------------------------------------------------------
	int auto_promoted_count;
	int cancelled;
	
	//--------------------------------------------------------
	Truck* Loading_Normal;
	Truck* Loading_Special;
	Truck* Loading_VIP;

	//--------------------------------------------------------
	// Utility functions
	void check_checkup_list();
	void check_to_available(Truck*&);
	void move_to_available(Truck*);
	void move_to_checkup(Truck*);
	Truck* Pick_VIP_Truck();
	Truck* Pick_Normal_Truck();
	Truck* Pick_Special_Truck();
	bool load_VIP();
	bool load_Normal();
	bool load_Special();
	bool load_MaxW();
	bool Need_Checkup(Truck*);
	int Loading_count();

public:

	Company();
	void Start_Simuulation();
	void Working_Hours();
	void Truck_Controller();
	void Off_Hours();

	// Reading data function
	SIM_MODE get_input_mode() ;
	void execute_mode(SIM_MODE);
	bool readFile(string);
	bool write_output_file(); // need to implementation
	int rest_in_waiting(Cargo* car);
	Time& get_Sim_Time() ;
	Time& get_Nearest_Event_Time();
	Event* get_Nearest_Event();
	void Advance_Sim_Time(int = 1);
	void Auto_Promotion();
	// Simulation Functions
	void assign_cargo();
	void check_completed_cargo();
	void increment_cancelled();
	void Deliver_cargos();

	//Printing Functions
	void Print_Sim_Time();
	void InteractivePrinting();
	void StepByStepPrinting();
	void SilentPrinting();
	void Print(SIM_MODE Mode);

	//---------------------------------------
	void print_W_V_C();
	void print_W_S_C();
	void print_W_N_C();

	//---------------------------------------
	void print_check_up_v_trucks();
	void print_check_up_s_trucks();
	void print_check_up_n_trucks();
	void print_empty_VIP();
	void print_empty_Normal();
	void print_empty_Special();
	//--------------------------------------
	bool Events_empty();
	
	void AddCargo(Cargo*);
	void Waiting_To_Delivered();

	bool Upgrade_Normal_Cargo(int id,int extra_money=0);
	bool Cancel_Normal_Cargo(int id);
	void Move_Trucks();			//checks for truck movement and calls Move_Truck accordingly
	void Move_Truck(Truck*& t);	//actually moves the truck, adding it to the Moving_Truck queue

	bool All_Delivered();		//checks that all waiting and moving lists are empty

	//------------------------------------------------------------
	void Output_Console();


	//Destructor
	~Company(){}


};


