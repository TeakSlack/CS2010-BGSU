//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// SlackT_pgm3.cpp
//
// Program: A simulation of an ice cream shop in BG.
// Process: Ice cream (1-5) is fetched from input, and is mapped accordingly
// to the right name & price. If an invalid option is input, the user is
// prompted again until a valid choice is selected. The cone choice is fetched
// next, with the same validation process repeated. The program then displays
// the ice cream choice and price. A payment amount is then prompted for and
// fetched from input, which is repeated until the full balance is paid.
// Results: Ice cream type, cone type, total, amount paid, and change back.
//
// Class: CS 2010
// Section: 1005
// Term: Fall 2024
// Author: Teak Slack
//
// Reflection: I overcomplicated this program. I could have easily wrote it
// in the main function but I decided to "modularize" it without properly
// doing what I set out to do. Next time I think I will sit down and sketch
// out what I want the program to do using "black-boxes" and design each
// function to work with more or less inputs, actually making the program
// modular and extensible, unlike it is now.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <unordered_map>

const int LINE_LENGTH = 35;

enum class IceCreamType // used to store & parse input
{
    Rocky,
    Stormy,
    Blizzard,
    SuperCell
};

enum class ConeType
{
    Waffle,
    Sugar
};

const double ROCKY_PRICE        = 2.50;
const double STORMY_PRICE       = 3.25;
const double BLIZZARD_PRICE     = 3.75;
const double SUPERCELL_PRICE    = 4.25;

const std::unordered_map<IceCreamType, double> ICE_CREAM_PRICE
{
    {IceCreamType::Rocky,       ROCKY_PRICE},
    {IceCreamType::Stormy,      STORMY_PRICE},
    {IceCreamType::Blizzard,    BLIZZARD_PRICE},
    {IceCreamType::SuperCell,   SUPERCELL_PRICE}
};

const std::unordered_map<IceCreamType, std::string> ICE_CREAM_NAME
{
    {IceCreamType::Rocky,       "Rocky"},
    {IceCreamType::Stormy,      "Stormy"},
    {IceCreamType::Blizzard,    "Blizzard"},
    {IceCreamType::SuperCell,   "SuperCell"}
};

const std::unordered_map<ConeType, std::string> CONE_NAME
{
    {ConeType::Waffle,          "Waffle"},
    {ConeType::Sugar,           "Sugar"}
};

void displayOption(int num, std::string name, double price) // displays input option in certain format
{
    std::stringstream partial1; // stringstream used to parse numbers in to string format
    partial1 << "| " << num << ". " << name.c_str();
    std::stringstream partial2;
    partial2 << std::fixed << std::setprecision(2) << "$" << price << " |";

    int partial1Len = partial1.str().length();
    std::cout << partial1.str() << std::setw(LINE_LENGTH - partial1Len) << std::right << partial2.str() << std::endl;
}

void displayOption(int num, std::string name) // displays input option in certain format w/o price
{
    std::stringstream partial1;
    partial1 << "| " << num << ". " << name.c_str();

    int partial1Len = partial1.str().length();
    std::cout << partial1.str() << std::setw(LINE_LENGTH - partial1Len) << std::right << "|" << std::endl;
}

// displays menu for ice creams
void displayIceCreams()
{
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "|" << std::setw(28) << std::right << "THE BG ICE CREAM PARLOR" << std::setw(6) << "|" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    displayOption(1, "Rocky", 2.50);
    displayOption(2, "Stormy", 3.25);
    displayOption(3, "Blizzard", 3.75);
    displayOption(4, "SuperCell", 4.25);
    displayOption(5, "Quit");
    std::cout << "-----------------------------------" << std::endl;
}

// appends menu for cones
void displayCones()
{
    std::cout << "-----------------------------------" << std::endl;
    displayOption(1, "Waffle");
    displayOption(2, "Sugar");
    std::cout << "-----------------------------------" << std::endl;
}

// displays ice cream, cone, & price of order
void displayPrice(IceCreamType iceCreamType, ConeType coneType, double& price)
{
    std::string iceCream = ICE_CREAM_NAME.find(iceCreamType)->second;
    std::string cone = CONE_NAME.find(coneType)->second;
    double iceCreamPrice = ICE_CREAM_PRICE.find(iceCreamType)->second;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "You ordered the " << iceCream << " in a " << cone << " cone." <<  std::endl;
    std::cout << "Your total is $" << iceCreamPrice << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    price = iceCreamPrice;
}

// gets ice cream and cone choice w/ input validation
void getIceCreamAndCone(IceCreamType& iceCreamType, ConeType& coneType)
{
    // get ice cream choice
    int choiceCode = 0;

    std::cout << "Enter your choice of ice cream (1-5): ";
    std::cin >> choiceCode;

    while(choiceCode < 1 || choiceCode > 5) // loops when invalid input is entered
    {
        std::cout << "Invalid ice cream code! Please re-enter: ";
        std::cin >> choiceCode;
    }

    if(choiceCode == 5)
    {
        std::cout << "Goodbye!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    // get cone choice
    std::string coneString;

    std::cout << "Enter your choice of cone (Waffle/Sugar): ";
    std::cin >> coneString;

    while(coneString != "Waffle" && coneString != "Sugar")
    {
        std::cout << "Invalid cone choice! Please re-enter: ";
        std::cin >> coneString;
    }

    // parse input values into selected enums
    if(choiceCode == 1) iceCreamType = IceCreamType::Rocky;
    if(choiceCode == 2) iceCreamType = IceCreamType::Stormy;
    if(choiceCode == 3) iceCreamType = IceCreamType::Blizzard;
    if(choiceCode == 4) iceCreamType = IceCreamType::SuperCell;

    if(coneString == "Waffle") coneType = ConeType::Waffle;
    if(coneString == "Sugar") coneType = ConeType::Sugar;
}

// gets payment amount w/ validation
void getPayment(double& price, double& paid)
{
    double payment;
    std::cout << "Enter the amount to pay: ";
    std::cin >> payment;

    if(payment > 0.0)
    {
        price -= payment;
        paid += payment;
    }

    while(price > 0.0)
    {
        std::cout << "You still owe: $" << price << std::endl;
        std::cout << "Enter additional payment amount: ";
        std::cin >> payment;

        if(payment > 0.0)
        {
            price -= payment;
            paid += payment;
        }
    }

    std::cout << "-----------------------------------" << std::endl;
}

// prints total of order, amount paid, and change
void printReceipt(IceCreamType iceCreamType, ConeType coneType, double price, double paid)
{
    double changeBack = std::fabs(price);

    std::string iceCream = ICE_CREAM_NAME.find(iceCreamType)->second;
    std::string cone = CONE_NAME.find(coneType)->second;
    std::cout << "Here is your " << cone << " " << iceCream << " ice cream!" << std::endl;
    std::cout << "Cost:" << std::setw(14) << std::right << "$" << ICE_CREAM_PRICE.find(iceCreamType)->second << std::endl;
    std::cout << "Paid:" << std::setw(14) << std::right << "$" << paid << std::endl;
    std::cout << "Change back:" << std::setw(7) << std::right << "$" << changeBack << std::endl;
    std::cout << "-----------------------------------" << std::endl;

}

int main()
{
    IceCreamType iceCreamType;
    ConeType coneType;
    double price;
    double paid;

    displayIceCreams();
    getIceCreamAndCone(iceCreamType, coneType);
    displayPrice(iceCreamType, coneType, price);
    getPayment(price, paid);
    printReceipt(iceCreamType, coneType, price, paid);

    return EXIT_SUCCESS;
}