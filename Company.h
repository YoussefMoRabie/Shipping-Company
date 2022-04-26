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
	PriQueue<Cargo*> W_V_C;
	Queue<Cargo*> W_S_C; 
	LinkedList<Cargo*> W_N_C; 
	PriQueue<Cargo*> M_S_C;	
	PriQueue<Cargo*> M_V_C;	
	PriQueue<Cargo*> M_N_C;	
	Queue<Cargo*> Delivered_cargo;

	//------------------------------------------------------

	//Trucks
	Queue<Truck*> VIP_truck;
	Queue<Truck*> Special_truck;
	Queue<Truck*> Normal_truck;
	Queue<Truck*> Check_up_Normal;
	Queue<Truck*> Check_up_Special;
	Queue<Truck*> Check_up_VIP;
	Queue<Truck*> Loading;
	Queue<Truck*> Empty;
	Queue<Truck*> Moving_truck;

	Queue<Event*> Event_List;

	//-------------------------------------------------------

	int MaxWait;
	int AutoPro;
	int Num_of_events;

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

	// Utility functions
	void check_auto_promotion();
	void check_checkup_list();
	void move_to_available(Truck*);
	void move_to_available(int);
	void move_to_checkup(Truck*);

public:

	Company();
	void Start_Simuulation();

	// Reading data function
	SIM_MODE get_input_mode() ;
	void execute_mode(SIM_MODE);
	bool readFile(string);
	bool write_output_file(); // need to implementation

	Time& get_Sim_Time() ;
	Time& get_Nearest_Event_Time();
	Event* get_Nearest_Event();
	void Advance_Sim_Time(int = 1);

	// Simulation Functions
	void assign_cargo();
	void check_completed_cargo();
	void increment_cancelled();

	//Printing Functions

	void Print_Sim_Time();
	void InteractivePrinting();
	void StepByStepPrinting();
	void SilentPrinting();


	//---------------------------------------
	void print_W_V_C();
	void print_W_S_C();
	void print_W_N_C();
	void print_M_V_C();
	void print_M_S_C();
	void print_M_N_C();

	//---------------------------------------
	void print_check_up_v_trucks();
	void print_check_up_s_trucks();
	void print_check_up_n_trucks();
	void print_Loading();
	void print_Empty();
	void print_available_trucks_vip_();
	void print_available_trucks_normal_();
	void print_available_trucks_special_();
	//--------------------------------------
	bool Events_empty();
	
	void AddCargo(Cargo*);
	void Waiting_To_Delivered();

	bool Upgrade_Normal_Cargo(int id,int extra_money);
	bool Cancel_Normal_Cargo(int id);

	bool All_Delivered();		//checks that all waiting and moving lists are empty

	//------------------------------------------------------------
	void Output_Console();


	//Destructor
	~Company(){}


};


