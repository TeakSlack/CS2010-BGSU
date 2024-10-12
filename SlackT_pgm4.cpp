#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>

#ifdef _WIN32
#include <windows.h>
#elif __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// imo this is much better practice than "using namespace std"
// namespace contamination is not a very cool issue!
using std::cout, std::cin, std::ifstream, std::abs;

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


int main()
{
    int fileSelection = 0;

    // loop until valid option is input
    while (fileSelection < 1 || fileSelection > 4)
    {
        cout << "Select file to process:\n";
        cout << "1. mixed.txt\n";
        cout << "2. valid.txt\n";
        cout << "3. three.txt\n";
        cout << "4. missing.txt\n\n";

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
    cout << " file:\n\n";

    // if file is unable to be opened, quit program
    if(!fileData.is_open())
    {
        cout << "ERROR: Couldn't open file!\n";
        exit(EXIT_FAILURE);
    }

    int invalidCount = 0;

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
    }

    fileData.close();
    return EXIT_SUCCESS;
}