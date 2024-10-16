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
#include <windows.h>

using std::cout, std::cin, std::ifstream, std::abs, std::setw, std::left, std::right, std::setfill, std::string;

// ANSI escape codes for cross-platform background color
const string BG_BLUE = "\033[44m", BG_RED = "\033[41m", RESET = "\033[0m";

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Get console width in Windows
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(!GetConsoleScreenBufferInfo(hConsole, &csbi)) exit(EXIT_FAILURE);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

const int MAX_SELECTION = 4;
const int CONSOLE_WIDTH = getConsoleWidth();
const int MAX_RANGE = 112;

int main()
{
    int fileSelection = 0;
    string fileNames[] = {"mixed.txt", "valid.txt", "three.txt", "missing.txt"};

    // Loop until valid file selection
    while (fileSelection < 1 || fileSelection > MAX_SELECTION)
    {
        cout << "Select file to process:\n";
        for(int i = 1; i <= MAX_SELECTION; i++) cout << i << ". " << fileNames[i - 1] << "\n";
        cout << "\n";

        cout << "Choice: ";
        cin >> fileSelection;
    }

    cout << "Bar graph for data contained in " << fileNames[fileSelection - 1] << " file.\n\n";

    // Open selected file
    ifstream fileData;

    switch (fileSelection)
    {
        case 1:
            fileData.open(fileNames[fileSelection - 1]);
            break;
        case 2:
            fileData.open(fileNames[fileSelection - 1]);
            break;
        case 3:
            fileData.open(fileNames[fileSelection - 1]);
            break;
        case 4:
            fileData.open(fileNames[fileSelection - 1]);
            break;            
    }


    // If file is unable to be opened, quit program
    if(!fileData.is_open())
    {
        cout << "ERROR: Couldn't open file!\n";
        exit(EXIT_FAILURE);
    }

    int invalidCount = 0, idx = 1, nextVal;
    fileData >> nextVal;

    int min1 = nextVal, min2 = nextVal, min3 = nextVal;
    int max1 = nextVal, max2 = nextVal, max3 = nextVal;

    // Process values from file until sentinel value (9999) or error 
    while(nextVal != 9999 && !fileData.fail())
    {
        // Update min/max values
        if(nextVal < min1) min3 = min2, min2 = min1, min1 = nextVal;
        else if(nextVal < min2) min3 = min2, min2 = nextVal;
        else if(nextVal < min3) min3 = nextVal;

        if(nextVal > max1) max3 = max2, max2 = max1, max1 = nextVal;
        else if(nextVal > max2) max3 = min2, max2 = nextVal;
        else if(nextVal > max3) max3 = nextVal;
        
        // Highlight and clamp invalid values
        if(nextVal < 0)
        {
            nextVal = abs(nextVal);
            invalidCount++;
            cout << BG_BLUE;
        }
        
        if(nextVal > MAX_RANGE)
        {
            nextVal = MAX_RANGE;
            invalidCount++;
            cout << BG_RED;
        }

        // Calculate bar width and print bar with 'X'
        int barWidth = ((nextVal * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;

        cout << setfill(' ') << setw(2) << right;
        cout << idx << " |" << setw(barWidth + 1) << setfill('X') << RESET << "\n";

        idx++;
        fileData >> nextVal;
    }

    cout << string(getConsoleWidth(), '-') << "\n";

    // Print y-axis scale line for graph
    string yScale = "    1";
    for(int i = 10; i < MAX_RANGE; i += 10)
    {
        int barWidth = ((i * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;
        yScale.append(string(barWidth - yScale.size(), ' ') + std::to_string(i));
    }

    cout << yScale << "\n\n";

    // Output min, max, and count of invalid values
    cout << "SMALLEST\n" << "========\n\n";
    cout << "The smallest value: " << min1 << "\nThe 2nd smallest value: " << min2 << "\nThe 3rd smallest value: " << min3 << "\n\n";
    cout << "LARGEST\n" << "=======\n\n" << "The largest value: " << max1 << "\nThe 2nd largest value: " << max2 << "\nThe 3rd largest value: " << max3 << "\n\n";
    cout << "INVALID\n" << "=======\n\n" << "There are " << invalidCount << " invalid values in this data.\n";

    // Close file and return
    fileData.close();
    return EXIT_SUCCESS;
}