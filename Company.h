#pragma once
#include "Def.h"
#include "Cargo.h"
#include "Truck.h"
#include "UI.h"
#include "Queue.h"
#include "PriQueue.h"
#include <fstream>

class Event;

class Company
{
	UI* ui_p;
	Time Sim_Time;
	ifstream Loaded;
	//------------------------------------------------------

	//Cargos
	PriQueue<Cargo*> VIP_cargo; //pri
	Queue<Cargo*> Special_cargo; 
	Queue<Cargo*> Normal_cargo; //list
	PriQueue<Cargo*> Waiting_cargo;
	PriQueue<Cargo*> W_V_C; //pri
	Queue<Cargo*> W_S_C; //pri
	Queue<Cargo*> W_N_C; //pri
	PriQueue<Cargo*> Moving_cargo;	//pri
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
	Queue<Truck*> Moving_truck; //bag

	//-------------------------------------------------------

	
	
	//-------------------------------------------------------

	PriQueue<Event*> Event_List; //pri

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
	int VIP_Cargos_count;
	int Normal_Cargos_count;
	int Special_Cargos_count;
	int InExec_Cargos_count;
	int Comp_Cargos_count;
	int Total_Cargos_count;
	int NO_Promoted_cargos;

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

	Company(UI* p);

	// Reading data function
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);
	void readFile(string);
	bool write_output_file(); // need to implementation

	Time& get_Sim_Time();
	Time& get_Nearest_Event_Time();
	Event* get_Nearest_Event();
	void Advance_Sim_Time(int = 1);

	// Simulation Functions
	void assign_cargo();
	void check_completed_cargo();
	void increment_cancelled();

	//Printing Functions
	void Print_Waiting_Cargos();
	void Print_Moving_Cargos();
	void Print_Delivered_Cargos();
	void Print_Sim_Time();


	//--------------------------------------
	Queue<Cargo*>& get_vip_c();
	Queue<Cargo*>& get_sp_c();
	Queue<Cargo*>& get_norm_c();
	Queue<Cargo*>& get_in_execution_cargos();
	Queue<Cargo*>& get_completed_cargos();
	PriQueue<Cargo*>& get_W_V_C();
	Queue<Cargo*>& get_W_S_C();
	Queue<Cargo*>& get_W_N_C();
	//---------------------------------------
	PriQueue<Truck*>& get_check_up_trucks();
	Queue<Truck*>& get_Loading();
	Queue<Truck*>& get_available_trucks_vip_();
	Queue<Truck*>& get_available_trucks_normal_();
	Queue<Truck*>& get_available_trucks_special_();
	//--------------------------------------
	bool Events_empty();
	
	void AddCargo(Cargo*);
	void Waiting_To_Delivered();

	bool Find_Normal_Cargo(int id, Cargo*&);


	bool check_special_t_c();
	void increment_cancelled_c();
	void increment_formulated_c();


	//Destructor
	~Company(){}

};


