/**
 * @file Def.h
 * @brief Some Definitions and enums 
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022 * 
 */
#pragma once

enum class SIM_MODE
{
	INTERACTIVE,
	STEP_BY_STEP,
	SILENT
};


enum class TRUCK_TYPE {
	VIP,
	SPECIAL,
	NORMAL
};

enum class TRUCK_STATUS {
	WAITING,
	LOADING,
	MOVING,
	GOING_BACK,
	CHECKUP
};

enum class CARGO_TYPE {
	VIP,
	SPECIAL,
	NORMAL
};

enum class CARGO_STATUS {
	READY,
	LOADED,
	MOVING,
	COMPLETED,
	CANCELLED
};

