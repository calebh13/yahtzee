#include "functions.h"

// Note: this program only runs on Windows.

int main(void)
{
	srand((unsigned int)time(NULL));

	int choice = 0;
	do 
	{
		mainMenu(&choice);
		system("cls");
		switch (choice)
		{
		case 1:
			printGameRules();
			break;
		case 2:
			playGame();
			break;
		default:
			break;
		}
	} while (choice != 3);

	printf("Thanks for playing!");

	return 0;
}
