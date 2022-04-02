#include "Company.h"
#include "UI.h"

int main()
{
	UI* UI_P = new UI();
	Company company(UI_P);

	string filename;
	filename = UI_P->getString();
	company.readFile(filename);

	return 0;
}