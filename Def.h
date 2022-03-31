#pragma once
#ifndef Def_H
#define Def_H
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
	IN_EXECUTION,
	CHECKUP
};

enum class CARGO_TYPE {
	VIP,
	SPECIAL,
	NORMAL
};

enum class CARGO_STATUS {
	WAITING,
	IN_EXECUTION,
	COMPLETED,
	CANCELLED
};
#endif // !Def_h

