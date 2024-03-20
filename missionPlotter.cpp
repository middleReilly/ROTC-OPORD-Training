// Created by Reilly White
// Last Updated Mar 20 2024

// User will be able to receive coordinates based off a given map as well as
// a FRAGO in order to plan their mission. The program will run while the user
// plans in order to give them time updates (the program will announce when 18
// minutes have passed).

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>
#include <unistd.h>
#include <thread>

using namespace std;

void intro();
void help();
void frago();
void route();
string genFragoStr(string bigX, string bigY);
string genRouteStr(string bigX, string bigY);
void printMission(time_t start, time_t done, time_t finish, string newCoords, string what);

int main()
{

    intro();

    string option = "", coords = "";
    cout << "What would you like to do?\n"
         << "> ";
    cin >> option;

    int stupidCount = 0;
    while (option != "quit") {
        if (option == "help"){
            help();
        } else if (option == "frago") {
            frago();
        } else if (option == "route") {
            route();
        } else {
            if (stupidCount == 0) {
                cout << "You're not using it right. Input a valid option.\n"
                 << "> ";
                cin >> option;
                stupidCount++;
                continue;
            } else if (stupidCount == 1) {
                cout << "F%@ker, just input a right option.\n"
                     << "> ";
                cin >> option;
                stupidCount++;
                continue;
            } else if (stupidCount > 1) {
                cout << "Peace out, nimrod.\n\n";
                return 0;
            }
        }

        cout << "What would you like to do?\n"
             << "> ";
        cin >> option;
    }

    cout << "\nThanks for using Mission Trainer.\n\n";

    return 0;

}

/*
intro
prints the introduction to the program. gives user the gist
*/
void intro()
{
    cout << "\n\e[7m Welcome to Mission Trainer \e[0m by Reilly White\n\n";

    cout << "    \e[4mWhat you need:\e[0m\n"
         << "\t- Map containing the Ft. Knox Land Nav Training Site\n"
         << "\t- Pencil, Protractor, TMK, and other materials needed to plan OPORDs\n"
         << "\t- Desperation to win at all costs\n\n";

    cout << "    \e[4mOptions:\e[0m\n"
         << "\t> help                = shows purpose and usage of program\n"
         << "\t> frago [CURR COORDS] = gives FRAGO to mission\n"
         << "\t> route [CURR COORDS] = gives endpoint based on given coords\n"
         << "\t> quit                = quits the program, wimp\n\n\n";
}

/*
help
gives help, duh
*/
void help()
{
    cout << "\n\e[7mHello there! This is the help center.\e[0m\n\n";

    cout << "\e[4mUsage:\e[0m\n"
         << "help                - Brings you to this page.\n\n"
         << "frago [CURR COORDS] - You must input coordinates that you could feasibly\n" 
         << "                      be on within the Ft Knox Land Nav site.\n"
         << "                      (For me, this is the square contained within the coordinates\n" 
         << "                      9206, 9200, 9806, 9800). The program will spit out a\n"
         << "                      basic mission in which you have 18 minutes to make\n"
         << "                      an OPORD. This will not tell you how good or bad your\n"
         << "                      brief is, but it gets you reps using actual coords and TMK.\n\n"
         << "route [CURR COORDS] - You provide feasible coordinates, and the program\n"
         << "                      spits out coordinates that can be anywhere within\n"
         << "                      the land nav site (literally, anywhere). Gets you\n"
         << "                      practice with plotting points and basic route planning.\n\n"
         << "quit                - Exits the program.\n\n\n\n"
         << "THIS IS A WORK IN PROGRESS!! Not everything will be polished, so\n"
         << "please let me know what the bugs are and how I can improve this <3.\n\n"
         << "Last Updated: 20 MAR 2024\n\n\n";
}

/*
frago
takes in a starting coordinate. gives user a frago to their mission
*/
void frago()
{
    using namespace std::chrono;

    duration<int,std::ratio<60> > eighteenMin (18);
    duration<int,std::ratio<60*60> > threeHours (3);
    system_clock::time_point now = system_clock::now();
    system_clock::time_point opordFin = now + eighteenMin;
    system_clock::time_point later = now + threeHours;

    time_t start = system_clock::to_time_t(now);
    time_t done = system_clock::to_time_t(opordFin);
    time_t finish = system_clock::to_time_t(later);

    std::string bigX, littleX, bigY, littleY;
    std::cout << endl << "Enter your coordinates. "
         << "Must be formatted like 00 00 00 00!\n"
         << "> ";
    std::cin >> bigX >> littleX >> bigY >> littleY;

    std::string initCoords = bigX + littleX + bigY + littleY;
    std::string newCoords = genFragoStr(bigX, bigY);

    string arr[5] = {"ambush", "raid", "attack", "movement to contact", "defense"};

    srand((unsigned) time(NULL));
	int random = rand() % 5;

    string what = arr[random];

    if (random == 4) {
        newCoords = initCoords;
    }

    printMission(start, done, finish, newCoords, what);
}

string genFragoStr(string bigX, string bigY)
{
    srand((unsigned) time(NULL));
	int random = rand();

    if (random % 2 == 0) {
        bigX = to_string(stoi(bigX) - 1);
        bigY = to_string(stoi(bigY) + 1);
    } else {
        bigX = to_string(stoi(bigX) + 1);
        bigY = to_string(stoi(bigY) - 1);
    }

    string littleX = to_string(rand() % 100);
    string littleY = to_string(((stoi(littleX) * 7) / 3) % 100);

    //adds a '0' if initially a single digit
    if (bigX.size() < 2) {
        bigX.insert(bigX.begin(), '0');
    }
    if (bigY.size() < 2) {
        bigY.insert(bigY.begin(), '0');
    }
    if (littleX.size() < 2) {
        littleX.insert(littleX.begin(), '0');
    }
    if (littleY.size() < 2) {
        littleY.insert(littleY.begin(), '0');
    }

    string newCoords = bigX + littleX + bigY + littleY;

    return newCoords;
}

void printMission(time_t start, time_t done, time_t finish, string newCoords, string what)
{
    string why;
    if (what == "ambush") {
        why = "disrupt the enemy and prevent field of maneuver";
    } else if (what == "raid") {
        why = "destroy enemy caches";
    } else if (what == "attack") {
        why = "neutralize the enemy and seize key terrain";
    } else if (what == "movement to contact") {
        why = "destroy the enemy";
    } else if (what == "defense") {
        why = "block the enemy and retain key terrain";
    }

    cout << "\n\n\n\n\n";
    cout << "\e[4mMission:\e[0m\n\n"
         << "The time is now " << ctime(&start) 
         << "1st PLT, A Co will conduct a " << what << " on OBJ Ginger in vicinity of "
         << newCoords << " in order to " << why << " no later than " 
         << ctime(&finish) << endl;

    cout << "You should complete your OPORD within the next 18 minutes, AKA " << ctime(&done) 
         << "Keep this program running so that it can give you time updates.\n\n\n\n\n";

    cout << "Your time starts now\n\n\n";

    sleep(5); //480

    cout << "\e[4mYou have 10 minutes remaining\e[0m\n\n\n";

    sleep(3); //480

    cout << "\e[1mYou have 5 minutes remaining\e[0m\n\n\n";

    sleep(2); //240
     
    cout << "\e[5mYou have 1 minute remaining\e[0m\n\n\n";

    sleep(1); //60

    cout << "-------    ---+---    |\\  /\\  /|   +----\n"
         << "   |          |       | \\/  \\/ |   |    \n"
         << "   |          |       |        |   +--  \n"
         << "   |          |       |        |   |    \n"
         << "   |       ---+---    |        |   +----\n\n\n"
         << "         |       |    /------\\ \n"
         << "         |       |    |      | \n"
         << "         |       |    |______/ \n"
         << "         |       |    |        \n"
         << "         \\_______/    |        \n\n\n"
         << "\a\a\a\a\a";
}

void route()
{
    string bigX, littleX, bigY, littleY;

    cout << "Enter your coordinates\n"
         << "Must be formatted like 00 00 00 00!\n"
         << "> ";
    cin >> bigX >> littleX >> bigY >> littleY;

    string initCoords = bigX + littleX + bigY + littleY;
    string newCoords = genRouteStr(bigX, bigY);
    
    cout << endl << "You must find a path between " << initCoords << " and "
         << newCoords << ". Good luck!\n\n";
}

string genRouteStr(string bigX, string bigY)
{
    srand((unsigned) time(NULL));

    //randomly generates new coords within boundaries
    bigX = to_string(92 + (rand() % 6));
    string littleX = to_string(rand() % 100);
    bigY = to_string(rand() % 6);
    string littleY = to_string(((rand() + 5 * 7) / 3) % 100);

    //adds a '0' if initially a single digit
    if (bigX.size() < 2) {
        bigX.insert(bigX.begin(), '0');
    }
    if (bigY.size() < 2) {
        bigY.insert(bigY.begin(), '0');
    }
    if (littleX.size() < 2) {
        littleX.insert(littleX.begin(), '0');
    }
    if (littleY.size() < 2) {
        littleY.insert(littleY.begin(), '0');
    }

    string newCoords = bigX + littleX + bigY + littleY;

    return newCoords;
}