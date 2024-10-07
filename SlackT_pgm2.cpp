//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// SlackT_pgm2.cpp
//
// Program: To calculate the cost of a trip to Cedar Point.
// Process: Program first gets admission type and number of admission,
// meal type and number of meal purchased. It then determines the cost of
// admission and meals for the day, plus discounts applied based upon 
// admission cost and waves the parking cost if the admission is platinum
// or gold. A 7% tax rate is applied to the total.
// Results: Results are neatly formatted used setw & setfill, and results
// include admission cost, meal cost, parking cost, admission discount,
// subtotal, tax, and total.
//
// Class: CS 2010
// Section: 1005
// Term: Fall 2024
// Author: Teak Slack
//
// Reflection: Program was fairly rudimentary to complete, the only thing
// that I struggled with was output formatting. That code is not the cleanest!
// In order to minimize the number of if statements used, an unordered map
// was used in order to reduce mapping to just a few lines.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

const int PLATINUM_COST     = 230;
const int GOLD_COST         = 135;
const int TWODAY_COST       = 70;
const int DAY_COST          = 45;
const double ALLDAY_COST    = 31.55;
const double SINGLE_COST    = 14.95;
const double ENTREE_COST    = 8.25;
const double NONE_COST      = 0.0;

const std::unordered_map<std::string, int> ADMISSION_MAP = 
{
    {"platinum",    PLATINUM_COST},
    {"gold",        GOLD_COST},
    {"twoday",      TWODAY_COST},
    {"day",         DAY_COST}
}; // maps admission type to cost

const std::unordered_map<std::string, double> MEAL_MAP =
{
    {"allday",  ALLDAY_COST},
    {"single",  SINGLE_COST},
    {"entree",  ENTREE_COST},
    {"none",    NONE_COST}
}; // maps meal type to cost

bool validateAdmission(const std::string& admissionType)
{
    if(admissionType == "platinum") return true;
    if(admissionType == "gold") return true;
    if(admissionType == "twoday") return true;
    if(admissionType == "day") return true;
    return false;
}

bool validateMeal(const std::string& mealType)
{
    if(mealType == "allday") return true;
    if(mealType == "single") return true;
    if(mealType == "entree") return true;
    if(mealType == "none") return true;
    return false;
}

int main()
{
    // INPUT SECTION: get admission type, amount, meal type, and meal amount. validates input.
    std::cout << "Enter your admission type (platinum, gold, twoday or day): " << std::flush;

    std::string admissionType;
    std::cin >> admissionType; // cin due to no need to consume whitespace

    if(!validateAdmission(admissionType)) 
    {
        std::cout << admissionType << " is not a valid entry type." << std::endl;
        return EXIT_FAILURE; // returns error on exit
    }

    std::cout << "How many " << admissionType << ": " << std::flush;

    int numAdmission = 0;
    std:: cin >> numAdmission;

    std::cout << "Enter your meal choice (allday, single, entree or none): " << std::flush;

    std::string mealType;
    std::cin >> mealType;

    if(!validateMeal(mealType))
    {
        std::cout << mealType << " is not a valid meal type." << std::endl;
        return EXIT_FAILURE;
    }

    int numMeals = 0;
    if(mealType != "none")
    {
        std::cout << "How many " << mealType << " meals: " << std::flush;
        std::cin >> numMeals;
    }

    // CALCULATIONS: finds admission cost, meal cost, parking, discount, subtotal, tax, and total
    double admission;
    double meal;
    double parking;
    double discount;
    double subtotal;
    double tax;
    double total;

    admission = ADMISSION_MAP.find(admissionType)->second * numAdmission;
    meal = MEAL_MAP.find(mealType)->second * numMeals;

    parking = (admissionType == "platinum" || admissionType == "gold") ? 0.0 : 20.0;

    if(admission >= 1000.0) discount = admission * 0.15;
    else if(admission >= 500.0) discount = admission * 0.10;
    else if(admission >= 100.0) discount = admission * 0.05;
    else discount = 0.0;

    subtotal = admission + meal + parking - discount;
    tax = subtotal * 0.07;
    total = subtotal + tax;

    // OUTPUT SECTION: formats output of calculation section to console
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Cedar Point:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "Admission" << std::right << ":" << numAdmission << std::setw(9) << std::right << admissionType << std::endl;
    std::cout << std::setw(25) << std::left << "Meal" << std::right << ":" << numMeals << std::setw(9) << std::right << mealType << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "Admission cost" << std::right << "$" << std::setw(10) << std::right << admission << std::endl;
    std::cout << std::setw(25) << std::left << "Meal cost" << std::right << "$" << std::setw(10) << std::right << meal << std::endl;
    std::cout << std::setw(25) << std::left << "Parking cost" << std::right << "$" << std::setw(10) << std::right << parking << std::endl;
    std::cout << std::setw(25) << std::left << "Admission discount" << std::right << "$" << std::setw(10) << std::right << discount << std::endl;
    std::cout << std::setw(25) << std::left << "Subtotal" << std::right << "$" << std::setw(10) << std::right << subtotal << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "Tax" << std::right << "$" << std::setw(10) << std::right << tax << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "Final Total" << std::right << "$" << std::setw(10) << std::right << total << std::endl;

    return EXIT_SUCCESS; // return success on exit
}