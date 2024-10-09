#include <iostream>

// imo this is much better practice than "using namespace std"
// namespace contamination is not a very cool issue!
using std::cout, std::cin;

int main()
{
    int fileSelection = 0;

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

    if (fileSelection == 4)
    {
        cout << "ERROR: File not found!\n";
        exit(EXIT_FAILURE);
    }

}