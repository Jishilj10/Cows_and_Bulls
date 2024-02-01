#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <conio.h>

using namespace std;

string generateRandomNumber() 
{
    string digits = "0123456789";
    random_shuffle(digits.begin(), digits.end());
    return digits.substr(0, 4);
}

pair<int, int> getFeedback(const string& secretNumber, const string& guess) 
{
    int bs = 0, cs = 0;
    for (size_t i = 0; i < 4; ++i) 
    {
        if (secretNumber[i] == guess[i]) 
        {
            bs++;
        } else if (count(secretNumber.begin(), secretNumber.end(), guess[i]) > 0) 
        {
            cs++;
        }
    }
    return make_pair(bs, cs);
}

void printGuessTable(const vector<pair<string, pair<int, int>>>& guessTable) 
{
    cout << "Player Guesses Table:" << endl;
    cout << "------------------------------------" << endl;
    cout << "|   Guess   |   Feedback   |" << endl;
    cout << "------------------------------------" << endl;

    for (const auto& entry : guessTable) 
    {
        cout << "|   " << entry.first << "   |   " << entry.second.first << "Bs, " << entry.second.second << "Cs   |" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(); 
    }

    cout << "------------------------------------" << endl;
}

void displayWelcomeMessage() 
{
    cout << "Welcome to the Cows and Bulls Game!" << endl;
    cout << "Try to guess the 4-digit number. Good luck!" << endl;
    cout << "Enter your 4-digit guess with no repetitive digits" << endl;
    cout << "After each guess, the game will provide feedback in terms of Bs (correct digit in the correct position) and Cs (correct digit in the wrong position)." << endl;
    cout << "The game continues until you correctly guess the number with 4Bs." << endl
}

string getPlayerGuess() 
{
    string playerGuess;
    cout << "Enter your 4-digit guess with no repetitive digits: ";
    cin >> playerGuess;
    return playerGuess;
}

void displayFeedback(const pair<int, int>& feedback) 
{
    cout << "Feedback: " << feedback.first << "Bs, " << feedback.second << "Cs" << endl;
}

void displayGameOverMessage(const string& secretNumber, int attempts) 
{
    cout << "Congratulations! You've guessed the correct number " << secretNumber << " in " << attempts << " attempts." << endl;
}


int main() 
{
    srand(static_cast<unsigned>(time(nullptr)));
    string secretNumber = generateRandomNumber();
    int attempts = 0;
    vector<pair<string, pair<int, int>>> guessTable;

    displayWelcomeMessage();

    while (true) 
    {
        system("cls");
        printGuessTable(guessTable);

        // Player's turn
        string playerGuess = getPlayerGuess();
        attempts++;

        auto feedback = getFeedback(secretNumber, playerGuess);
        guessTable.push_back(make_pair(playerGuess, feedback));
        displayFeedback(feedback);

        if (feedback.first == 4) 
        {
            displayGameOverMessage(secretNumber, attempts);
            break;
        }
    }
    return 0;
}
