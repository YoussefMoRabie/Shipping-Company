/**
 * @file Company.h
 * @brief Manager of all operations that occur in the program
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
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

	//Original Lists

	PriQueue<Truck*> empty_VIP; //avail. VIP trucks
	PriQueue<Truck*> empty_Special; //avail. Special trucks
	PriQueue<Truck*> empty_Normal;  //avail. Normal trucks
	Queue<Truck*> Check_up_Normal;  //Normla trucks in check up
	Queue<Truck*> Check_up_Special;  //Special trucks in Check up
	Queue<Truck*> Check_up_VIP;  //VIP trucks in check up
	PriQueue<Truck*> Moving_truck;
	Queue<Event*> Event_List;

	//------------------------------------------------------
	//Bonus Lists
	PriQueue<Truck*> empty_VIP_night; //avail. VIP night shift trucks
	PriQueue<Truck*> empty_Special_night; //avail. Special night shift trucks
	PriQueue<Truck*> empty_Normal_night;  //avail. Normal night shift trucks
	Queue<Truck*> urgent_Check_up_Normal;  //Normla trucks in unusual check up
	Queue<Truck*> urgent_Check_up_Special;  //Special trucks in unusual Check up
	Queue<Truck*> urgent_Check_up_VIP;  //VIP trucks in unusual check up


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
	
	
/**
 * @brief Number of cargos in each list
 * 
 */
	int VIP_Cargos_count;
	int Normal_Cargos_count;
	int Special_Cargos_count;
	int Moving_Cargos_count;
	int Delivered_Cargos_count;
	int Total_Cargos_count;

	//--------------------------------------------------------
	float auto_promoted_count;
	int total_count_normal;
	int cancelled;
	
	//--------------------------------------------------------
	Truck* Loading_Normal;
	Truck* Loading_Special;
	Truck* Loading_VIP;

	//--------------------------------------------------------
	/**
	 * @brief Utility functions
	 * 
	 */
	void check_checkup_list();
	void check_to_available(Truck*&); //moves a truck from checkup to available
	void move_to_available(Truck*); //moves a truck from moving to available
	void move_to_checkup(Truck*); //moves a truck from moving to checkup
	void  to_urgentCheckup(Truck*);
	Truck* out_of_urgentCheckup(TRUCK_TYPE t);
	Truck* Pick_VIP_Truck(); //picks the appropriate truck from loading VIP cargos
	Truck* Pick_Normal_Truck(); //picks the appropriate truck from loading Normal cargos
	Truck* Pick_Special_Truck();//picks the appropriate truck from loading Special cargos
	bool load_VIP();
	bool need_urgent_checkup(Truck*);
	bool load_Normal();
	bool load_Special();
	bool load_MaxW();
	bool Need_Checkup(Truck*); //checks on a returning truck if it needs maintainence
	bool in_working(Time T);
	void Loading_count(int&, int&);

public:
/**
 * @brief Construct a new Company object
 * 
 */
	Company();
	void Start_Simuulation();
	void Working_Hours();
	void Truck_Controller(); //controls the transition of trucks between different lists
	void Off_Hours();

	// Reading data function
	void execute_mode(SIM_MODE);
	void readFile();
	/**
	 * @brief prepairs the output file at the end of the simulation
	 * 
	 * @return true || false
	 */
	bool write_output_file();
	/**
	 * @brief Statistics are collected at the end and sent to me to put in the output file
	 * @param int Delivered 
	 * @param string text 
	 */
	void Statistics_File(int Delivered,string & text);
	/**
	 * @brief time of rest in waiting
	 * 
	 * @param Cargo* car 
	 * @return int 
	 */
	int rest_in_waiting(Cargo* car);
	Time& get_Sim_Time() ;
	Time& get_Nearest_Event_Time();
	Event* get_Nearest_Event();
	void Advance_Sim_Time(int = 1);
	/**
	 * @brief Promote cargos that exceeds a certain waiting time
	 * 
	 */
	void Auto_Promotion();
	// Simulation Functions
	void assign_cargo();
	void check_completed_cargo();
	void increment_cancelled();
	void Deliver_cargos(); //deliver cargos when reached its destination

	//Printing Functions
	void Print_Sim_Time();
	void InteractivePrinting();
	void StepByStepPrinting();
	void SilentPrinting();
	/**
	 * @brief Simulation Manager take simulation mode and to the stable operation
	 * 
	 * @param SIM_MODE Mode 
	 */
	void Sim_Manager(SIM_MODE Mode);

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
	SIM_MODE get_sim_mode();
	/**
	 * @brief function print data on console
	 * 
	 */
	void Output_Console();
	/**
	 * Bonus Func.
	 */
	bool Delivery_failure();
	//Destructor
	/**
	 * @brief Destroy the Company object
	 * 
	 */
	~Company(){}


};


