#include <stdlib.h>
#include <time.h>
#include "GameMenu.h"
#include "Profile.h"

Profile* Profile::instance = nullptr;

int main()
{
	srand(time(NULL));

	GameMenu gm;
	gm.ShowMenu();
}
