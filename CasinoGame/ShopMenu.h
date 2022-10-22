#pragma once
#include "Menu.h"

class ShopMenu : public Menu {
private:

	Shop sm;

public:

	ShopMenu();

	void ShowMenu();
	void Info();

};