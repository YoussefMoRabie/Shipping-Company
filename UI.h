#pragma once
#ifndef UI_H
#define UI_H
#include "Def.h"
#include "Company.h"

class Company;

class UI
{
private:
	Company* company_ptr;
public:
	UI(Company* ptr);
	SIM_MODE get_sim_mode();
	void InteractivePrinting() const;
	void StepByStepPrinting() const;
	void SilentPrinting() const;
	void Output_Console()const;

};
#endif // UI_H

