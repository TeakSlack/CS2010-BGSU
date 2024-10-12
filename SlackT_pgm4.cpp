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

#ifdef _WIN32
// using winapi to fetch console info
// using hungarian notation to align with winapi
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        cout << "ERROR: Cannot fetch console screen buffer info.\n";
        exit(EXIT_FAILURE);
    }

    int width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return width;
}

#elif __unix__
int getConsoleWidth()
{
    struct winsize w;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        cout << "ERROR: Cannot get console size.\n";
        exit(EXIT_FAILURE);
    }

    assert(w.ws_col != -1);
    return w.ws_col;
}
#endif

#ifdef _DEBUG
const int MAX_SELECTION = 5;
#else
const int MAX_SELECTION = 4;
#endif

// FIXME: if console size is changed during runtime, output will not scale
const int CONSOLE_WIDTH = getConsoleWidth();
const int MAX_RANGE = 115;

int main()
{
    int fileSelection = 0;

    // loop until valid option is input
    while (fileSelection < 1 || fileSelection > MAX_SELECTION)
    {
        cout << "Select file to process:\n";
        cout << "1. mixed.txt\n";
        cout << "2. valid.txt\n";
        cout << "3. three.txt\n";
        cout << "4. missing.txt\n";
        #ifdef _DEBUG
        cout << "5. debug.txt\n";
        #endif
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

    cout << "Bar graph for data contained in ";

    if (fileSelection == 1) 
    {
        fileData.open("res/mixed.txt");
        cout << "mixed.txt";
    }
    if (fileSelection == 2) 
    {
        fileData.open("res/valid.txt");
        cout << "valid.txt";
    }
    if (fileSelection == 3) 
    {
        fileData.open("res/three.txt");
        cout << "three.txt";
    }
    if(fileSelection == 5)
    {
        fileData.open("res/debug.txt");
        cout << "debug.txt";
    }
    cout << " file:\n\n";

    // if file is unable to be opened, quit program
    if(!fileData.is_open())
    {
        cout << "ERROR: Couldn't open file!\n";
        exit(EXIT_FAILURE);
    }

    int invalidCount = 0;
    int idx = 1;

    while(!fileData.fail())
    {
        int nextVal;
        fileData >> nextVal;

        // watch for sentinel value
        if(nextVal == 9999) break;
        
        if(nextVal < 0)
        {
            nextVal = abs(nextVal);
            invalidCount++;
        }

        if(nextVal > MAX_RANGE) nextVal = MAX_RANGE;

        // calculate bar length and print
        int barWidth = ((nextVal * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;

        cout << setfill(' ') << setw(2) << right;
        cout << idx << " |";
        cout << setw(barWidth) << setfill('X');
        cout << "\n";

        idx++;
    }

    for(int i = 0; i < CONSOLE_WIDTH; i++) cout << "-";
    cout << "\n";

    // print y axis, scaled to console width
    string yScale = "    1";
    float stride = 10 * ((float)CONSOLE_WIDTH / MAX_RANGE);
    for(int i = 10; i < MAX_RANGE; i += 10)
    {
        int barWidth = ((i * (CONSOLE_WIDTH - 4)) / MAX_RANGE) + 1;
        string next = string(barWidth - yScale.size() + 2, ' ') + std::to_string(i);
        yScale.append(next);
    }

    cout << yScale << "\n";

    fileData.close();
    return EXIT_SUCCESS;
}