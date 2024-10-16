//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// SlackT_pgm4.cpp
//
// Program: A program to display bar graphs for different input files.
// Process: File is read in based upon user input. An output scaled to the
// width of the console is displayed for every input until 9999 is read from
// the input file. Color is provided if a value is negative or outside of the
// maximum range for the graph to display.
// Results: A colored bar graph with a labeled x and y axis. 
//
// Class: CS 2010
// Section: 1005
// Term: Fall 2024
// Author: Teak Slack
//
// Reflection: This program wasn't too bad! The only functions I wrote were
// to implement OS-specific functionality for the console width (I like to
// program on WSL). The main functionality of the program is contained all
// within the main function. While the program isn't easily scalable, that
// isn't the purpose of this program.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>

#ifdef _WIN32
#include <windows.h>
#elif __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using std::cout, std::cin, std::ifstream, std::abs, std::setw, std::left, std::right, std::setfill, std::string;

#ifdef TEAK_LOCAL
string path = "/mnt/c/users/teaki/OneDrive/Documents/Dev/CS2010/res/";
#else
string path = "";
#endif

// using ansi escape codes for cross-platform compatibility
const string BG_BLUE = "\033[44m";
const string BG_RED = "\033[41m";
const string RESET = "\033[0m";

#ifdef _WIN32
// using winapi to fetch console info
// using hungarian notation to align with winapi
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// enable ansi color codes on windows
void setupConsole()
{
    DWORD consoleMode;
    if(!GetConsoleMode(hConsole, &consoleMode)) exit(EXIT_FAILURE);
    if(!SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) exit(EXIT_FAILURE);
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(!GetConsoleScreenBufferInfo(hConsole, &csbi)) exit(EXIT_FAILURE);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
#elif __unix__
int getConsoleWidth()
{
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) exit(EXIT_FAILURE);
    return w.ws_col;
}

void setupConsole() {}
#endif

const int MAX_SELECTION = 4;

// FIXME: if console size is changed during runtime, output will not scale
const int CONSOLE_WIDTH = getConsoleWidth();
const int MAX_RANGE = 112;

int main()
{
    setupConsole();

    int fileSelection = 0;
    string fileNames[] = {"mixed.txt", "valid.txt", "three.txt", "missing.txt"};

    // loop until valid option is input
    while (fileSelection < 1 || fileSelection > MAX_SELECTION)
    {
        cout << "Select file to process:\n";
        for(int i = 1; i <= MAX_SELECTION; i++) cout << i << ". " << fileNames[i - 1] << "\n";
        cout << "\n";

        cout << "Choice: ";
        cin >> fileSelection;
    }

    // handle invalid input
    if (fileSelection == 4)
    {
        cout << "ERROR: File not found!\n";
        exit(EXIT_FAILURE);
    }

    // create ifstream & open respective file
    ifstream fileData;

    cout << "Bar graph for data contained in " << fileNames[fileSelection - 1] << " file.";

    string fileName;

    switch (fileSelection)
    {
        case 1:
            fileName = "mixed.txt";
            break;
        case 2:
            fileName = "valid.txt";
            break;
        case 3:
            fileName = "three.txt";
            break;
    }

    fileData.open(path + fileName);

    // if file is unable to be opened, quit program
    if(!fileData.is_open())
    {
        cout << "ERROR: Couldn't open file!\n";
        exit(EXIT_FAILURE);
    }

    int invalidCount = 0;
    int idx = 1;
    int nextVal;
    fileData >> nextVal;

    int min1 = nextVal, min2 = nextVal, min3 = nextVal;
    int max1 = nextVal, max2 = nextVal, max3 = nextVal;

    // watch for sentinel value or file read error
    while(nextVal != 9999 && !fileData.fail())
    {
        // check for min/max values
        if(nextVal < min1) min3 = min2, min2 = min1, min1 = nextVal;
        else if(nextVal < min2) min3 = min2, min2 = nextVal;
        else if(nextVal < min3) min3 = nextVal;

        if(nextVal > max1) max3 = max2, max2 = max1, max1 = nextVal;
        else if(nextVal > max2) max3 = min2, max2 = nextVal;
        else if(nextVal > max3) max3 = nextVal;
        
        // check if next value is negative
        if(nextVal < 0)
        {
            cout << BG_BLUE;
            nextVal = abs(nextVal);
            invalidCount++;
        }

        // clamp out of range value to max
        if(nextVal > MAX_RANGE)
        {
            cout << BG_RED;
            nextVal = MAX_RANGE;
            invalidCount++;
        }

        // calculate bar length and print
        int barWidth = ((nextVal * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;

        cout << setfill(' ') << setw(2) << right;
        cout << idx << " |" << setw(barWidth + 1) << setfill('X') << RESET << "\n";

        idx++;
        fileData >> nextVal;
    }

    cout << string(getConsoleWidth(), '-') << "\n";

    // print y axis, scaled to console width
    string yScale = "    1";
    for(int i = 10; i < MAX_RANGE; i += 10)
    {
        int barWidth = ((i * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;
        yScale.append(string(barWidth - yScale.size(), ' ') + std::to_string(i));
    }

    cout << yScale << "\n\n";

    cout << "SMALLEST\n" << "========\n\n";
    cout << "The smallest value: " << min1 << "\nThe 2nd smallest value: " << min2 << "\nThe 3rd smallest value: " << min3 << "\n\n";
    cout << "LARGEST\n" << "=======\n\n" << "The largest value: " << max1 << "\nThe 2nd largest value: " << max2 << "\nThe 3rd largest value: " << max3 << "\n\n";
    cout << "INVALID\n" << "=======\n\n" << "There are " << invalidCount << " invalid values in this data.\n";

    fileData.close();
    return EXIT_SUCCESS;
}