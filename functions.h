#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // this is what makes it windows-only: provides _getch()
#include <ctype.h>

// functions.c
void mainMenu(int* choice);
void printGameRules(void);
void rollDice(int dice[], int diceToRoll[], int* rollNum);
void printDice(int dice[]);
int sumDice(int dice[]);
void indent(int score);
void printScorecard(struct player p);
void getComboChoice(int* comboChoice, int rollNum, int scoresUsed[]);
void getCounts(int dice[], int counts[]);
int ofAKind(int counts[], int numOfAKind, int forbiddenNum);
int findLargestSequence(int counts[]);
int getCombinationPoints(int dice[], int comboChoice);
void getDiceToRoll(int diceToRoll[]);

// game.c
void playGame(void);
void takeTurn(struct player *p, int roundNum);

struct player
{
	int playerNum;
	int dice[5]; // contains values for all 5 dice rolls
	int diceToRoll[5]; // if diceToRoll[index] is 1, we roll the die at index
	int scorecard[14]; // this contains all the points
	int scoresUsed[14];
	int upperSectionSum;
	int bottomSectionSum;
};
