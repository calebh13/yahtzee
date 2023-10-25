#include "functions.h"

// This file is for non-text based, dice operation functions.

// Precondition: dice[] and diceToNotRoll[] must both have a length of 5
// dice[] contains values 1 thru 6, and diceToRoll[] has all values 0 (to not roll) or roll (1) for all (indices 1-5, 0 is not used)
void rollDice(int dice[], int diceToRoll[], int* rollNum)
{
    for (int i = 0; i < 5; ++i)
    {
        if (diceToRoll[i] || *rollNum == 0) // if we should roll this specific die
        {
            dice[i] = rand() % 6 + 1;
        }
    }
    *rollNum = *rollNum + 1;
}

int sumDice(int dice[])
{
    return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
}

// dice has length 5, and counts has length 7 - stores counts of dice rolls from 1 to 6, and counts[0] is not used
void getCounts(int dice[], int counts[])
{
    for (int i = 0; i < 5; ++i)
    {
        ++counts[dice[i]];
    }
}

// numOfAKind is at least 2 and at most 5 for example, if numOfAKind = 3, we search to see if 3 dice equal the same number
// Returns the number of which there are (numOfAKind) of. Otherwise returns 0.
// forbiddenNum just prevents it from returning a specific number (e.g. you're looking for the pair for a full house, and don't want the 3 of a kind).
int ofAKind(int counts[], int numOfAKind, int forbiddenNum)
{ 
    for (int i = 1; i <= 6; ++i)
    {
        if (i != forbiddenNum && counts[i] >= numOfAKind)
        {
            return i;
        }
    }
    return 0;
}

int findLargestSequence(int counts[])
{
    int maxSequence = 0, curSequence = 0;
    for (int i = 1; i <= 6; ++i)
    {
        if (counts[i] >= 1)
        {
            curSequence++;
        }
        else if (curSequence > maxSequence)
        {
            maxSequence = curSequence;
            curSequence = 0;
        }
    }
    // Return whichever is greater:
    return (curSequence > maxSequence) ? curSequence : maxSequence; 
}

/* Returns the number of points if dice satisfy the chosen combination, 0 otherwise.
 * Dice[] is values of all 5 dice, and comboChoice is an int from 1 to 13 (input is validated in getComboChoice function).
 * Combinations #1-6 are Sum of #'s (pts: sum all dice with face #).
 * 7: Three-of-a-kind (pts: sum all dice). 8: Four-of-a-kind (pts: sum all dice). 9: Full house (a pair + 3 of a kind) (pts: 25).
 * 10: Small straight (sequence of 4 dice) (pts: 30). 11: Large straight (sequence of 5 dice) (pts: 40).
 * 12: Yahtzee (all the same face) (pts: 50). 13: Chance (any combo) (pts: sum all dice). */
int getCombinationPoints(int dice[], int comboChoice) // Need to refactor
{
    int counts[7] = { 0 };
    getCounts(dice, counts); // fills counts[] with the number of dice with face [index of counts]

    int points = 0, forbiddenNum = 0; // no numbers are forbidden from ofAKind test initially

    if (comboChoice >= 1 && comboChoice <= 6)
    {
        points = counts[comboChoice] * comboChoice; // Sums all the dice of face comboChoice
    }
    else
    {
        switch (comboChoice)
        {
        case 7: // Three of a kind
            if (ofAKind(counts, 3, forbiddenNum))
            {
                points = sumDice(dice);
            }
            break;
        case 8: // Four of a kind
            if (ofAKind(counts, 4, forbiddenNum))
            {
                points = sumDice(dice);
            }
            break;
        case 9: // Full house (pair + 3 of a kind)
            forbiddenNum = ofAKind(counts, 3, forbiddenNum); 
            // Confirm that there is a 3 of a kind, and then check for a pair that doesn't use the number of which there are 3 of
            if(forbiddenNum != 0 && ofAKind(counts, 2, forbiddenNum) != 0) 
            {
                points = 25;
            }
            break;
        case 10: // Small straight (sequence of 4)
            if (findLargestSequence(counts) >= 4)
            {
                points = 30;
            }
            break;
        case 11: // Large straight (sequence of 5)
            if (findLargestSequence(counts) == 5)
            {
                points = 40;
            }
            break;
        case 12: // Yahtzee (all dice are the same)
            if (counts[dice[0]] == 5)
            {
                points = 50;
            }
            break;
        case 13: // Chance (sum all dice)
            points = sumDice(dice);
            break;
        }
    }

    return points;
}
