#pragma once
#include "Def.h"
#include "Cargo.h"
#include "Truck.h"
#include "UI.h"
#include "Queue.h"
#include <fstream>

class Event;

class Company
{
	UI* ui_p;
	ifstream Loaded;
	//------------------------------------------------------

	//Cargos
	Queue<Cargo*> VIP_cargo;
	Queue<Cargo*> Special_cargo;
	Queue<Cargo*> Normal_cargo;
	Queue<Cargo*> InExecution_cargo;
	Queue<Cargo*> Completed_cargo;

	//------------------------------------------------------

	//Trucks
	Queue<Truck*> VIP_truck;
	Queue<Truck*> Special_truck;
	Queue<Truck*> Normal_truck;
	Queue<Truck*> Check_up_truck;
	Queue<Truck*> InExecution_truck;

	//-------------------------------------------------------

	
	
	//-------------------------------------------------------

	Queue<Event*> Events;

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
	bool read_input_file();
	int get_current_day();
	int get_current_hour();
	bool write_output_file();


	// Simulation Functions
	void assign_cargo();
	void check_completed_cargo();
	void increment_cancelled();


	Queue<Cargo*>& get_vip_c();
	Queue<Cargo*>& get_sp_c();
	Queue<Cargo*>& get_norm_c();
	Queue<Cargo*>& get_in_execution_cargos();
	Queue<Cargo*>& get_completed_cargos();
	//---------------------------------------
	Queue<Truck*>& get_check_up_trucks();
	Queue<Truck*>& get_available_trucks_vip_();
	Queue<Truck*>& get_available_trucks_normal_();
	Queue<Truck*>& get_available_trucks_polar_();
	//--------------------------------------
	bool Events_empty();
	void readFile(string);
	void AddCargo(Cargo*);
	bool Find_Normal_Cargo(int id, Cargo*&);


	bool check_special_t_c();
	void increment_cancelled_c();
	void increment_formulated_c();


	//Destructor
	~Company(){}

};


