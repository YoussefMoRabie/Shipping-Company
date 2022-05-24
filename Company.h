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
	Queue<Truck*> empty_VIP; //availabe VIP Trucks
	Queue<Truck*> empty_Special; //availabe Special Trucks
	Queue<Truck*> empty_Normal; //availabe Normal Trucks
	Queue<Truck*> Check_up_Normal; //Normal Trucks in checkup
	Queue<Truck*> Check_up_Special;//Special Trucks in checkup
	Queue<Truck*> Check_up_VIP;//availabe VIP Trucks in checkup
	PriQueue<Truck*> Moving_truck;//Moving Trucks

	Queue<Event*> Event_List;

	//-------------------------------------------------------

	int MaxWait; //maximum waiting time for cargo
	int AutoPro; //time needed to promote a normal cargo to vip
	int Num_of_events;
	int nCap, sCap, vCap; //Capcity for each type of truck
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
	int Moving_Cargos_count;
	int Delivered_Cargos_count;
	int Total_Cargos_count;
	int Num_Promoted_cargos;

	//--------------------------------------------------------
	float auto_promoted_count;
	int cancelled;
	
	//--------------------------------------------------------
	Truck* Loading_Normal;
	Truck* Loading_Special;
	Truck* Loading_VIP;

	//--------------------------------------------------------
	// Utility functions
	void check_checkup_list();
	void check_to_available(Truck*&); //it Moves trucks from checkup to availabe list 
	
	void move_to_available(Truck*);//it moves trucks from moving to availabe list
	
	void move_to_checkup(Truck*);//it moves trucks from moving to checkup list
	
	Truck* Pick_VIP_Truck();//it picks the appropriate truck for a VIP cargos
	
	Truck* Pick_Normal_Truck();//it picks the appropriate truck for a Normal cargos
	
	Truck* Pick_Special_Truck();//it picks the appropriate truck for a Special cargos
	
	bool load_VIP();//it load VIP trucks with cargos
	
	bool load_Normal();//it load Normal trucks with cargos

	bool load_Special();//it load Special trucks with cargos
	
	bool load_MaxW();//it loads cargos with maxw into truck
	
	bool Need_Checkup(Truck*);//it checks if a returnning truck needs checkup or not
	bool in_working(Time T);
	int Loading_count();

public:

	Company();
	void Start_Simuulation();
	void Working_Hours();
	
	void Truck_Controller();//it control the transition of trucks between different lists
	void Off_Hours();

	// Reading data function
	SIM_MODE get_input_mode() ;
	void execute_mode(SIM_MODE);
	bool readFile(string);
	bool write_output_file(); // need to implementation
	void Statistics_File(int Delivered,string & text);
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
	
	void Deliver_cargos();//it deliver cargos when they reach their destination and move them into delivered cargos

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


