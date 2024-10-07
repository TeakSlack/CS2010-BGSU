//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// SlackT_pgm1.cpp
//
// Program: A calculator for a movie theater's gross and net profits, and distributor's fee.
// Process: Title (string), number of tickets sold for adults (int) and children
// (int) are input. An adult ticket is worth $11.50 and a child ticket is $7.75.
// The distributor is paid 20% of gross profits, while the theater nets the other 80%.
// Results: Gross ticket sales (double), net ticket sales (double), and distributor cut 
// (double) are the outputs.
//
// Class: CS 2010
// Section: 1005
// Term: Fall 2024
// Author: Teak Slack
//
// Reflection: This assignment was fairly rudimentary to complete. A list of values is
// read, processed then output. The 'using namespace std' convention was not followed
// due to potential namespace pollution. std::cin was chosen in place of std::getline
// due to the fact that whitespace was not to be consumed, and movie titles were to be
// limited to one word. std::flush was used when a newline was not required to free
// resources for the OS. And for newlines, std::endl was always used. Due to the fact
// that only one constant was allowed, the price of tickets was kept in a non-constant 
// variable for code clarity.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    const double PERCENT_PROFIT = 0.8;
    double priceAdultTicket = 11.50;
    double priceChildTicket = 7.75;

    std::string title;
    int numAdultTickets;
    int numChildTickets;
    
    // Input section: gets movie title, amount of adult tickets sold, amount of child tickets sold, and places them in the appropriate variables.
    std::cout << "Enter the movie title: " << std::flush;
    std::cin >> title; // Whitespace can be ignored, title is one word only.
    std::cout << "How many adult tickets were sold: " << std::flush;
    std::cin >> numAdultTickets;
    std::cout << "How many children's tickets were sold: " << std::flush;
    std::cin >> numChildTickets;

    // Processing section: calculates gross sales, net sales, and distributor cut.
    double grossSales = (numAdultTickets * priceAdultTicket) + (numChildTickets * priceChildTicket);
    double netSales = grossSales * PERCENT_PROFIT; // 80% of gross profits represents theater's cut.
    double distributorSales = grossSales * (1.0 - PERCENT_PROFIT); // PERCENT_DISTRIBUTORS_FEE

    // Output section: sets correct formatting and pipes calculated values to the console.
    std::cout << std::fixed << std::setprecision(2); // Set output format to xxxx.xx.

    std::cout << "Gross Ticket Sales for \'" << title << "\': $" << grossSales << std::endl; // Escape code used for single quote.
    std::cout << "Theater Net Profit: $" << netSales << std::endl;
    std::cout << "Amount Paid to Distributor: $" << distributorSales << std::endl;

    return 0; // Return 0 to represent program exit success.
}