// Lab 4
// "I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own."
// Victor Pueyo

#include <iostream>
#include <iomanip> 
#include <string>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

char suit(int);
char picture(int);
void swap(int&, int&);
void swap(char&, char&);
bool IsItFlush(char[][5], int);
bool IsRoyalFlush(int[][5], int);
bool IsStraight(int[][5], int);
bool IsFourofaKind(int[][5], int);
bool IsFullHouse(int[][5], int);
bool IsThreeofaKind(int[][5], int);
bool IsTwoPairs(int[][5], int);
bool OnePair(int[][5], int);
int ScoreofOnePair(int[][5], int, int[]);

int main()
{
    int cards[5][5], Total[5] = { 0 }, ranking[5];
    char suits[5][5], tempsuit, next_game = 0;
    int deck[52]; //picked[52] = {0}
    int i, j, k, number, temp, start, index, minIndex, minValue;
    int maxRank, maximumVal, maximumIndex;
    string hand[5], maximumValueHand;
    srand(time(NULL));
    
    system("COLOR A0");

    // This do while loop is so that the user enters the proper value to play again
    do
    {
        cout << right;
        // It is inside this while loop so we are able to play the next game
        int picked[52] = { 0 };

        // Clears the screen
        system("cls");

        // For loop to go over all the cards of the deck with a do while inside to shuffle the deck. 
        for (i = 0; i < 52; i++)
        {
            do
            {
                number = rand() % 52;
            } while (picked[number] != 0);
            
            deck[i] = number;
            picked[number]++;
        }

        k = 0;

        // In this for loop 5 cards are dealt to each player
        for (i = 0; i < 5; i++)
            for (j = 0; j < 5; j++)
            {
                cards[i][j] = deck[k];
                suits[i][j] = suit(deck[k]);
                k++;
            }

        // The cout inside this for loop displays each players cards and the suit 
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                cout << setw(2) << cards[i][j] << suits[i][j] << ' ';
            }
            cout << endl;
        }
        
        cout << "\n\nAfter: " << endl;
        cout << endl << endl;

        // This for loop changes the card array from 0-51 to 0-12
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                cards[i][j] = cards[i][j] % 13;
            }
            cout << endl;
        }

        // This for loop displays the cards between 0-12
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                cout << setw(3) << cards[i][j] << suits[i][j] << ' ';
            }
            cout << endl;
        }

        cout << endl << endl;

        // Displays the real card, the picture and the suit
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                temp = cards[i][j] % 13;
                if (temp > 9 || temp == 0)
                    cout << setw(3) << picture(temp);
                else
                    cout << setw(3) << temp + 1;
                cout << suits[i][j];
                k++;
            }
            cout << endl;
        }

        // This loop sorts the cards from low to high for each player
        for (j = 0; j < 5; j++)
        {
            for (start = 0; start < 4; start++)
            {
                minIndex = start;
                minValue = cards[j][start];
                tempsuit = suits[j][start];
                for (index = start + 1; index < 5; index++)
                {
                    if (cards[j][index] < minValue)
                    {
                        minValue = cards[j][index];
                        tempsuit = suits[j][index];
                        minIndex = index;
                    }
                }

                swap(cards[j][minIndex], cards[j][start]);
                swap(suits[j][minIndex], suits[j][start]);
            }
        }

        cout << endl << endl;

        // This for loop displays the cards from low to high for each player
        for (i = 0; i < 5; i++)
        {
            cout << "Player " << (i + 1) << ": ";

            for (j = 0; j < 5; j++)
            {
                temp = cards[i][j] % 13;
                if (temp > 9 || temp == 0)
                    cout << setw(3) << picture(temp);
                else
                    cout << setw(3) << temp + 1;
                cout << suits[i][j];
                k++;
            }
            cout << endl << endl;
        }

        for (i = 0; i < 5; i++)  // for all five players
        {
            // check if it is a flush
            if (IsItFlush(suits, i)) // 6,000,000
            {
                // check if it is Royal Flush 10JQKA - A10JQK
                if (IsRoyalFlush(cards, i)) // 10, 000, 000
                {
                    Total[i] = 10000000;
                    hand[i] = "Royal flush";

                    cout << "Player " << (i + 1) << " has a Royal Flush" << endl;
                }
                // Check if it is a straight Flush 5 cards one is higher than previous
                else if (IsStraight(cards, i))
                {
                    Total[i] = 9000000 + cards[i][4] * 10000;
                    hand[i] = "Straight flush";

                    cout << "Player " << (i + 1) << " has a Straight Flush" << endl;
                }
                // It is a flush
                else
                {
                    Total[i] = 6000000;
                    if (cards[i][0] == 0)
                        Total[i] += 130000;
                    else
                        Total[i] += cards[i][0];
                    Total[i] += cards[i][4] * 10000;
                    Total[i] += cards[i][3] * 1000;
                    Total[i] += cards[i][2] * 100;
                    Total[i] += cards[i][1] * 10;

                    hand[i] = "Flush";

                    cout << "Player " << (i + 1) << " has a Flush" << endl;
                }
            }
            //  else if(Check for 4 of a kind) 8,000,000
            else if (IsFourofaKind(cards, i))
            {
                Total[i] = 8000000;
                if (cards[i][0] == cards[i][3] && cards[i][0] == 0)
                    Total[i] += 800000;
                else if (cards[i][0] == 0)
                    Total[i] += cards[i][2] * 10000 + 1000;
                else
                    Total[i] += cards[i][2] * 10000;

                if (cards[i][0] == cards[i][3])
                    Total[i] += cards[i][4] * 10;
                else
                    Total[i] += cards[i][0] * 10;

                hand[i] = "4 of a kind";

                cout << "Player " << (i + 1) << " has 4 of a kind" << endl;
            }
            // else if( check for full house) 7,000,000
            else if (IsFullHouse(cards, i))
            {
                Total[i] = 7000000;
                if (cards[i][0] == cards[i][2])
                {
                    if (cards[i][0] == 0)
                        Total[i] += 800000 + cards[i][4] * 100;
                    else
                        Total[i] += cards[i][2] * 10000 + cards[i][4] * 100;
                }
                else
                {
                    Total[i] += cards[i][2] * 15000 + cards[i][1] * 100;
                }

                hand[i] = "Full house";

                cout << "Player " << (i + 1) << " has a Full House" << endl;
            }
            // else if (check for straight) 5,000,000
            else if (IsStraight(cards, i))
            {
                Total[i] = 5000000 + cards[i][4] * 10000;

                hand[i] = "Straight Hand";

                cout << "Player " << (i + 1) << " has a Straight Hand" << endl;
            }
            // else if (check for 3 of a kind) 4,000,000
            else if (IsThreeofaKind(cards, i))
            {
                Total[i] = 4000000 + cards[i][2] * 10000;
                if (cards[i][0] == cards[i][2])
                {
                    if (cards[i][0] == 0)
                        Total[i] = 500000;
                    Total[i] += cards[i][4] * 100;
                    Total[i] += cards[i][3];
                }
                else if (cards[i][1] == cards[i][3])
                {
                    Total[i] += cards[i][4] * 100;
                    Total[i] += cards[i][0];
                }
                else
                {
                    Total[i] += cards[i][1] * 100;
                    Total[i] += cards[i][0];
                }

                hand[i] = "3 of a kind";

                cout << "Player " << (i + 1) << " has 3 of a kind" << endl;
            }
            // else if (check for 2 pairs) 3,000,000
            else if (IsTwoPairs(cards, i))
            {
                if (cards[i][0] == cards[i][1] && cards[i][2] == cards[i][3])
                {
                    Total[i] = 3000000 + cards[i][3] * 10000 + cards[i][1] * 100 + cards[i][4];
                    if (cards[i][0] == 0)
                        Total[i] += 400000;
                }
                else if (cards[i][0] == cards[i][1] && cards[i][3] == cards[i][4])
                {
                    Total[i] = 3000000 + cards[i][4] * 10000 + cards[i][1] * 100 + cards[i][2];
                    if (cards[i][0] == 0)
                        Total[i] += 400000;
                }
                else
                {
                    Total[i] = 3000000 + cards[i][4] * 10000 + cards[i][2] * 100 + cards[i][0];
                    if (cards[i][0] == 0)
                        Total[i] += 15;
                }

                hand[i] = "2 Pairs";

                cout << "Player " << (i + 1) << " has 2 Pairs" << endl;
            }
            // else if (check for a pair) 2,000,000
            else if (OnePair(cards, i))
            {
                ScoreofOnePair(cards, i, Total);
                hand[i] = "a Pair";

                cout << "Player " << (i + 1) << " has a Pair" << endl;
            }
            // no hand - calculate value + 1,000,000
            else
            {
                Total[i] = 1000000 + cards[i][4] * 10000 + cards[i][3] * 1000 + cards[i][2] * 100 + cards[i][1] * 10 + cards[i][0];
                if (cards[i][0] == 0)
                    Total[i] += 200000;
                hand[i] = "High Card";

                cout << "Player " << (i + 1) << " has a High Card" << endl;
            }

            cout << "Player " << (i + 1) << "'s score is: " << Total[i] << endl << endl;

            ranking[i] = (i + 1);
        }

        // Ranks the players from highest to lowest 
        for (start = 0; start < 4; start++)
        {
            maximumIndex = start;
            maximumVal = Total[start];
            maxRank = ranking[start];
            maximumValueHand = hand[start];
            for (index = start + 1; index < 5; index++)
            {
                if (Total[index] > maximumVal)
                {
                    maximumVal = Total[index];
                    maxRank = ranking[index];
                    maximumValueHand = hand[index];
                    maximumIndex = index;
                }
            }

            swap(Total[maximumIndex], Total[start]);
            swap(ranking[maximumIndex], ranking[start]);
            swap(hand[maximumIndex], hand[start]);
        }

        // Displays the Header of the Result Ranking
        cout << endl << "The Player Ranking:" << endl << "-------------------" << endl;
        cout << left << setw(10) << "Player # " << left << setw(20) << "Hand" << left << setw(7) << "Score" << endl;

        // Displays the ranking
        for (int k = 0; k < 5; k++)
            cout << left << setw(10) << ranking[k] << left << setw(20) << hand[k] << left << setw(7) << Total[k] << endl;

        // This if else statement looks for a tie
        if (Total[0] == Total[1])
            cout << endl << endl << "The winners of this round are: Players " << ranking[0] << " and " << ranking[1] << '.' << endl << endl << endl;
        else
            cout << endl << endl << "The Winner of this round is: Player " << ranking[0] << '.' << endl << endl << endl;

        // Sound when the game is done
        Beep(200, 100);
        Beep(600, 500);

        cout << "Do you want to play again? Yes (Y) No (N) : ";
        cin >> next_game;
        
        // While loop keeps asking until player enters correct value 
        while (next_game != 'Y' && next_game != 'N')
        {
            cout << "Do you want to play again? Yes (Y) No (N) : ";
            cin >> next_game;
        }
        
    } while (next_game == 'Y');

    cout << endl << endl << "Thank you for playing!" << endl << endl;

    system("pause");
    return 0;
}


// This funtion determines the suit of each card
char suit(int card)
{
    return card / 13 + 3;
}


// This function checks if the card is a number or a Ace, Jack, Queen or King.
char picture(int num)
{
    if (num == 0)
        return 'A';
    else if (num == 10)
        return 'J';
    else if (num == 11)
        return 'Q';

    return 'K';
}


// This function swaps the numbers to sort the array
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}


// This function swaps the suits to sort the array
void swap(char& a, char& b)
{
    char temp = a;
    a = b;
    b = temp;
}


// This function looks if a player has a flush, meaning he has same color cards
bool IsItFlush(char suits[][5], int i)
{
    for (int j = 0; j < 4; j++)
    {
        if (suits[i][j] != suits[i][j + 1])
            return false;
    }
    return true;
}


// This function looks if a player has a royal flush, menaing you have 5 cards of the same color, all 5 are they are a 10, Ace, Jack, Queen and King  
bool IsRoyalFlush(int cards[][5], int i)
{
    if (cards[i][0] == 0 && cards[i][4] == 12 && cards[i][3] == 11 && cards[i][2] ==
        10 && cards[i][1] == 9)
        return true;
    
    return false;
}


// This function looks if a player has a straight, meaning like a stair (they are in a row)
bool IsStraight(int cards[][5], int i)
{
    for (int j = 0; j < 4; j++)
    {
        if (cards[i][j] + 1 != cards[i][j + 1])
            return false;
    }
    return true;
}


//This function checks if a player has four of a kind or not. You have four of a kind if you have 4 cards with the same number
bool IsFourofaKind(int cards[][5], int i)
{
    if (cards[i][0] == cards[i][3] || cards[i][1] == cards[i][4])
        return true;
    
    return false;
}


// This function looks if a player has a full house, meaning you have triple (three of a kind) and a pair
bool IsFullHouse(int cards[][5], int i)
{
    if (cards[i][0] == cards[i][2] && cards[i][3] == cards[i][4] || cards[i][0] == cards[i][1] && cards[i][2] == cards[i][4])
        return true;
    
    return false;
}


// This function looks if a player has three of a kind, meaning you have three cards of one rank and two cards of two other ranks
bool IsThreeofaKind(int cards[][5], int i)
{
    if (cards[i][0] == cards[i][2] || cards[i][1] == cards[i][3] || cards[i][2] == cards[i][4])
        return true;
    
    return false;
}


// This function looks if a player has two pairs, meaning you have two pair of two cards that are the same number
bool IsTwoPairs(int cards[][5], int i)
{
    if (cards[i][0] == cards[i][1] && cards[i][2] == cards[i][3] ||
        cards[i][0] == cards[i][1] && cards[i][3] == cards[i][4] ||
        cards[i][1] == cards[i][2] && cards[i][3] == cards[i][4])
        return true;
    
    return false;
}


// This function looks if a player has a one pair, meaning you have two cards which are the same number
bool OnePair(int cards[][5], int i)
{
    if (cards[i][0] == cards[i][1] || cards[i][1] == cards[i][2] ||
        cards[i][2] == cards[i][3] || cards[i][3] == cards[i][4])
        return true;
    return false;
}


// This function the final score you have if you got a pair (added this funtion to have 10 functions, which was a requirement of the lab.)
// This could have been done in the main body as well. 
int ScoreofOnePair(int cards[][5], int i, int Total[])
{
    if (cards[i][0] == cards[i][1])
    {
        Total[i] = 2000000 + cards[i][1] * 10000 + cards[i][4] * 1000 + cards[i][3] * 100 + cards[i][2] * 10;
        if (cards[i][0] == 0)
            Total[i] += 200000;
    }
    else if (cards[i][1] == cards[i][2])
    {
        Total[i] = 2000000 + cards[i][2] * 10000 + cards[i][4] * 1000 + cards[i][3] * 100 + cards[i][0] * 10;
        if (cards[i][0] == 0)
            Total[i] += 1500;
    }
    else if (cards[i][2] == cards[i][3])
    {
        Total[i] = 2000000 + cards[i][3] * 10000 + cards[i][4] * 1000 + cards[i][1] * 100 + cards[i][0] * 10;
        if (cards[i][0] == 0)
            Total[i] += 1500;
    }
    else
    {
        Total[i] = 2000000 + cards[i][4] * 10000 + cards[i][2] * 1000 + cards[i][1] * 100 + cards[i][0] * 10;
        if (cards[i][0] == 0)
            Total[i] += 1500;
    }

    return Total[i];
}

