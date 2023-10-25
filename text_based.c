#include "functions.h"

// This file is for text-based or user input functions.

void mainMenu(int* choice)
{
    printf("Choose an option.\n1. Print game rules\n2. Start a game of Yahtzee\n3. Exit\n\nYour choice: ");
    scanf("%d", choice);
    printf("\n");
}

void printGameRules()
{
    printf("====================RULES OF YAHTZEE====================\nSource: https://www.yahtzeeonline.org/yahtzee-rules.php.\n\n");
    printf("The object of the game is to roll certain combinations of numbers, in 13 rounds with the help of five dice.\nEach player in his turn rolls the dice, trying to get a good combination of numbers.\nThere are different combinations which fall under thirteen categories, very similar to the Poker \"hands\", along with some extra categories.They all give different scores.");
    printf("\n\nThere are 13 rounds in a game of Yahtzee. In each turn, a player can roll his dice up to 3 times in order to get the desired combination. On the first two rolls, the player has to roll all five of the dice at once. On the third roll, the player can roll any number of dice he wants to, including none or all of them, trying to get a good combination.");
    printf("\n\nThe player can choose whether he wants to roll once, twice or three times in each turn. After the three rolls in a turn, the player must put his scores down in the scorecard, under any one of the thirteen categories. The score that the player finally gets for that turn depends on the category/box that he chooses and the combination that he got by rolling the dice.");
    printf("\nBut once a box is chosen on the score card, it can't be chosen again. So the player has to choose the box very wisely in every turn.\nThere are many situations it which it is better to put a score of zero in a \"bad\" box, instead of a low score in one of the \"good\" boxes. Otherwise, the good box may be blocked for future turns and the player will not be able to take full advantage of it.");
    printf("\n\nThere are two sections in a Yahtzee scorecard: the upper section and the lower section. In the upper section, there are six boxes that represent the six face values of a die.\nFor these six boxes, the player must enter only the sum of the dice with the corresponding face value. If the player scores a total of 63 or more in the upper section, he gets a bonus of 35 points at the end of the game.");
    printf("\n\nThe lower section of a scorecard is very important. Here, there are various combinations that a player can score for, which are very similar to Poker \"hands\", with score values in parentheses:");
    printf("\n\n3 of a kind: If the dice include 3 or more of the same number. (Sum of all five dice)");
    printf("\n4 of a kind: If the dice include 4 or more of the same number. (Sum of all five dice)");
    printf("\nFull House: If the dice show 3 of one number and 2 of another. (25 pts)");
    printf("\nSmall Straight: If the dice show a sequence of 4 continuous numbers. (30 pts)");
    printf("\nLarge Straight: If the dice show a sequence of 5 continuous numbers. (40 pts)");
    printf("\nChance: The player can score in this box with any combination. (Sum of all five dice)");
    printf("\nYahtzee: If the dice show 5 of the same number. (50 pts)");
    printf("\n\nRegarding the Yahtzee bonus - the same rule doesn't apply when a player rolls a Yahtzee and his Yahtzee box is already filled with a zero. In either case, the \"joker rules\" must be used. That is, if possible the player must fill the upper section box corresponding to the number rolled. But if that box is full, he must fill in any empty box in the lower section.");
    printf("\n\nIf the entire lower section is full he must enter a zero in any one of the open boxes in the upper section. He also must enter a 0 if he selects an invalid section for his combination of dice.\n\n");
}

void printDice(int dice[])
{
    for (int i = 0; i < 4; ++i)
    {
        printf("%d, ", dice[i]);
    }
    printf("%d.\n", dice[4]);
}

// Just used for formatting purposes to make numbers make a nice vertical line
void indent(int score)
{
    if (score < 10)
    {
        printf(" \t");
    }
    else
    {
        printf("\t");
    }
}

void printScorecard(struct player p) // no properties of p are modified which is why this function does not need to take in pointer to player
{
    // Sum of 1's can never be >= 10 so no need to worry about spacing
    printf("\n1. Sum of 1's (%d)\t7. Three of a kind (%d)\n", p.scorecard[1], p.scorecard[7]);

    printf("2. Sum of 2's (%d)", p.scorecard[2]);
    indent(p.scorecard[1]);
    printf("8. Four of a kind (%d)\n", p.scorecard[8]);

    printf("3. Sum of 3's (%d)", p.scorecard[3]);
    indent(p.scorecard[2]);
    printf("9. Full house (%d)\n", p.scorecard[9]);

    printf("4. Sum of 4's (%d)", p.scorecard[4]);
    indent(p.scorecard[3]);
    printf("10. Small straight (%d)\n", p.scorecard[10]);

    printf("5. Sum of 5's (%d)", p.scorecard[5]);
    indent(p.scorecard[4]);
    printf("11. Large straight (%d)\n", p.scorecard[11]);

    printf("6. Sum of 6's (%d)", p.scorecard[6]);
    indent(p.scorecard[5]);
    printf("12. Yahtzee (%d)\n", p.scorecard[12]);

    printf("13. Chance (%d)\n\n", p.scorecard[13]);
}

void getComboChoice(int* comboChoice, int rollNum, int scoresUsed[])
{
    int minChoice = 0;
    *comboChoice = -1;
    printf("Enter a combination to store your dice in. ");
    if (rollNum == 3)
    {
        printf("You must enter a combination because this is your 3rd roll.\n");
        minChoice = 1;
    }
    else
    {
        printf("Or enter 0 to reroll dice of your choice.\n");
    }
    printf("Note that if you select a combination and your dice don't match it, your points for that combination will be set to zero and you lose that roll!\n\n");
    printf("Your choice: ");
    scanf("%d", comboChoice);
    while ((*comboChoice < minChoice || *comboChoice > 13) || (scoresUsed[*comboChoice] == 1)) // If outside range or already used combo, ask again
    {
        printf("Error - please enter an integer between %d and 13, excluding already used combinations: ", minChoice);
        scanf("%d", comboChoice);
    }
}


void getDiceToRoll(int diceToRoll[]) // TODO: input validation (make sure 6 isn't valid)
{
    for (int i = 0; i < 5; i++)
    {
        // Any dice the user does not enter should not be re-rolled. Therefore we need to zero out this array first
        diceToRoll[i] = 0;
    }

    printf("Enter a list of dice to re-roll with NO space between: e.g. \"145\" rerolls dice 1, 4, and 5 (order doesn't matter): ");
    int temp = 0;
    char input[6] = { '\0' }; // potential for buffer overflow, but I don't really care for yahtzee purposes
    scanf("%s", input);

    for (int i = 0; i < 5; i++)
    {
        if (isalnum(input[i]) && input[i] - '0' != 0)
        {
            // input[i] - '0' converts char to int
            diceToRoll[input[i] - '0' - 1] = 1;
        }
        else // reached the end of our string or it's invalid
        {
            break;
        }
    }
}
