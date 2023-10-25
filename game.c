#include "functions.h"

// This file contains the majority of the game logic.

void playGame()
{
	struct player p1 = { .playerNum = 1, .dice = {0}, .diceToRoll = {0}, .scorecard = {0}, .scoresUsed = {0}, .upperSectionSum = 0, .bottomSectionSum = 0 };
	struct player p2 = { .playerNum = 2, .dice = {0}, .diceToRoll = {0}, .scorecard = {0}, .scoresUsed = {0}, .upperSectionSum = 0, .bottomSectionSum = 0 };
	
	for (int roundNum = 1; roundNum < 14; roundNum++)
	{
		takeTurn(&p1, roundNum);
		printScorecard(p1);
		printf("Press any key to continue ... ");
		_getch();
		system("cls");

		takeTurn(&p2, roundNum);
		printScorecard(p2);
		printf("Press any key to continue ... ");
		_getch();
		system("cls");
	}

	// Calculate total score and add 35 if upperSectionSum is >= 63 (bool expr evals to 1 if true)
	int p1Score = p1.upperSectionSum + p1.bottomSectionSum + (p1.upperSectionSum >= 63) * 35;
	int p2Score = p2.upperSectionSum + p2.bottomSectionSum + (p2.upperSectionSum >= 63) * 35;
	
	int winnerNum = (p1Score > p2Score) ? 1 : 2;
	system("cls");
	printf("Player 1 score: %d. Player 2 score: %d.\nPlayer %d wins!\n", p1Score, p2Score, winnerNum);
	printf("Press any key to continue ... ");
	_getch();
	system("cls");
}

void takeTurn(struct player *p, int roundNum)
{
	int rollNum = 0, comboChoice = 0, points = 0;
	
	printf("Round %d\nPlayer %d's turn. Press any key to perform initial roll ... ", roundNum, p->playerNum);
	_getch();

	while (rollNum < 3)
	{
		rollDice(p->dice, p->diceToRoll, &rollNum); // Note that this is where rollNum is incremented
		system("cls");
		printDice(p->dice);
		printScorecard(*p);

		/* Combinations have been printed
		 * Ask user what combination they want to store into: if 0, then roll again.
		 * If > 0 && < 14, and not an already used combination, validate, then store */
		getComboChoice(&comboChoice, rollNum, p->scoresUsed);

		if (comboChoice != 0) // player wants to use dice roll for one of the combinations
		{
			if (p->scoresUsed[comboChoice] == 0) // this combination has not been used before
			{
				points = getCombinationPoints(p->dice, comboChoice);
				p->scorecard[comboChoice] = points;
				p->scoresUsed[comboChoice] = 1;
				if (comboChoice < 7)
				{
					p->upperSectionSum += points;
				}
				else
				{
					p->bottomSectionSum += points;
				}
				break;
			}
			else
			{
				printf("This combination has already been used. You lose your turn!\n");
				break;
			}
		}
		else // player chose to not put the dice into a combination and wants to hold some dice
		{
			getDiceToRoll(p->diceToRoll);
			// after this we need to roll again, so we go back to the start of the loop
		}
	}
}
