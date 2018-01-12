//potentially handy includes - google the C++ documentation for details
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
 
 
 
using namespace std;
 
// FOR ALL THE FUNCTION DECLARATIONS BELOW, YOU MAY USE VECTORS INSTEAD OF LISTS BUT BEAR IN MIND THE DIFFERENCE IN EFFICIENCY MAY REQUIRE YOU TO ALTER THE IMPLEMENTATION A BIT
 
/*
This function reads a file and stores each line in a list of strings, you should use <fstream> to achieve this
@param  l: the list of strings
@param  s: the filename*/
void readFile(list<string>& l, string Elements1) {
    std::ifstream ifs(Elements1);
    string v;
    while (getline(ifs, v)) {
        l.push_back(v);
    }
}
 
string toLowerCase(string moo) {
    string mooLower;
    for (int o = 0; o < moo.length(); o++) {
        mooLower += tolower(moo[o]);
 
    }
    return mooLower;
}
 
bool equalsIgnoreCase(string l, string s) {
    return toLowerCase(l) == toLowerCase(s);
}
 
/*
This function returns true if a specified string is contained in a list
@param  l: the list of strings
@param  s: the string to be checked
@return true if s is a member of l, false otherwise
*/
//function that cycles through the list and ignores the case
 
bool isin(list<string> l, string s) {
    for (auto i : l) {
        if (equalsIgnoreCase(i, s)) {
            cout << "Your word has been accepted" << endl;
            return true;
        }
 
    }
    cout << "Your word does not match the criteria" << endl;
    cout << "A life has been deducted from you" << endl;
    cout << "Please try again" << endl;
 
    return false;
}
//Life check
 
void lives(int P1, int P2) {
    if (P1 == 0) {
        cout << "Player 2 Wins" << endl;
 
    }
    if (P2 == 0) {
        cout << "Player 1 Wins" << endl;
    }
}
 
/*
This function returns true if the last letter of one string matches the first letter of another
@param  first:  the string whose first character is to be checked
@param  last:   the string whose last character to be checked
@return true if first and last characters are equal, regardless of case
*/
 
//Checks to see if the two answers are matching
 
bool match(string answer, string lastAnswer) {
    //    stops error at the start of the game where lastAnswer was empty
    if (lastAnswer.empty()) {
        return true;
    }
    //    specifies the location of the characters I want to focus on
    char f = answer[0];
    char end = lastAnswer[lastAnswer.length() - 1];
    //    converts them to lowercase
    if (tolower(f) == tolower(end)) {
        cout << "Next move" << endl;
        return true;
    }
    else {
        cout << "Your word does not fulfill the objective" << endl;
 
        return false;
    }
}
//Checks the answer given
 
bool answer(list<string> playerWords, string &lastAnswer) {
    string answer = "";
    getline(cin, answer);
    //    Checks to see if the word is found in the external file
    if (!isin(playerWords, answer)) {
        return false;
    }
    //    Checks to see if there is a match between the first and last letters
    if (!match(answer, lastAnswer)) {
        return false;
    }
    //    last Answer takes the value of answer
    lastAnswer = answer;
 
    return true;
}
//Life deduction
 
bool lives(bool success, int &playerLives) {
    if (!success) {
        playerLives--;
    }
 
    return playerLives > 0;
}
 
//insert program here....
 
int main() {
    list<string> playerWords;
    readFile(playerWords, "Elements.txt");
    int player1Lives = 3;
    int player2Lives = 3;
 
    cout << "Welcome to the Periodic table game" << endl;
    cout << "Players will each take turns typing in names of the elements" << endl;
    cout << "on the periodic table" << endl;
    cout << "You will need to match the first letter of your word to the last" << endl;
    cout << "letter played by the other player" << endl;
    cout << "Good luck" << endl;
 
 
 
 
 
    cout << "Round START" << endl;
 
    bool running = true;
    bool player1Turn = true;
 
    string lastAnswer;
 
    while (running) {
        if (player1Turn) {
            while (true) {
                cout << "Player One's lives left" << " " << player1Lives << endl;
                cout << "player One please enter your word" << endl;
                bool success = answer(playerWords, lastAnswer);
                bool playerAlive = lives(success, player1Lives);
 
                if (!playerAlive) {
                    cout << "Player 2 Wins" << endl;
                    running = false;
                    break;
                }
 
                if (success) {
                    break;
                }
            }
        }
        else {
            while (true) {
                cout << "Player Two's lives left" << " " << player2Lives << endl;
                cout << "player Two please enter your word" << endl;
                bool success = answer(playerWords, lastAnswer);
                bool playerAlive = lives(success, player2Lives);
 
                if (!playerAlive) {
                    cout << "Player 1 Wins" << endl;
                    running = false;
                    break;
                }
 
                if (success) {
                    break;
                }
            }
        }
 
        player1Turn = !player1Turn;
    }
 
    system("pause");
}