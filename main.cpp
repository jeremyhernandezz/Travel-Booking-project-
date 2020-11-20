/* Created by Jeremy Hernandez on 4/21/19.
 * Purpose: This is an object-oriented program that will help the user plan a trip and calculate the total amount of expenses. The expenses will include flight tickets and hotel rates.
 
 *  Flex Project
 */

//Included necessary libraries and necessary files
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Hotel.hpp"
#include "Flight.hpp"

using namespace std;
//Struct that stores the values of a date
struct Date {
    int month, day, year;
};

//Functions declarations
bool check_date(int day, int month);
void get_num_days(Date start, Date end, int &days);
string show_trip (Trip &p);
bool airplane_choice(int input, string &airline);
void print_results(Flight &flight, Hotel &hotel);
void set_rooms(Hotel &num, int input);
string round_Num(double result);
//Initiated static variable to 0
double Trip::total = 0;

//Created a template to handle input validation
template <typename T>
//Accepts a auto variable to store input and a string that displays the questions for the user
void getChoice(T &choice, string output) {
    
    cout << output;
    cin >> setw(1) >> choice;
    //Checks if cin is not good
    while (!cin.good()) {
        cout << "Invalid input, please try again\n";
        
        cin.clear();
        cin.ignore(1000, '\n');
        
        cout << output;
        cin >> setw(1) >> choice;
    }
    cin.clear();
    cin.ignore(1000, '\n');
}

int main() {
    //Declared variables
    string destination, reason, start, end, city, state, depart_airline, return_airline, hotel;
    int rooms, party_size, days, hotel_choice, depart_choice, return_choice, reason_choice;
    char slash1, slash2, continue_choice = 'y';
    //Created two vectors to store the random variables for hotel and flight tickets
    vector<int> ticket_prices;
    vector<int> night_prices;
    //Created two structs for start and end date
    Date date1;
    Date date2;
    
    //Creates random prices for flights and hotels
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < 6; i++) {
        int tickets = rand() % (300 - 100 + 1) + 100;
        ticket_prices.push_back(++tickets);
        int nights = rand() % (200 - 80 + 1) + 80;
        night_prices.push_back(++nights);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //Loop that iterates until user enters n
    while (tolower(continue_choice) != 'n') {
        cout << "TRIP SERVICE\n\n";
    
        cout << "Enter desired destination: ";
        getline(cin, destination);
        
        cout << "\nIs this on:\n\n1)Business\n2)Vacation\n\n";
        
        //While loop that iterates until input is valid
        while (true) {
            getChoice(reason_choice, "Enter choice: ");
            
            if (reason_choice == 1){
                reason = "Business";
                break;
            }
            else if (reason_choice == 2){
                reason = "Vacation";
                break;
            }
            else {
                cout << "\nInvalid choice\n";
            }
        }
        cout << endl;

        //while loop that interates until start date format is correct and start date is valid
        while (true) {
            cout << "Starting date (MM/DD/YYYY): ";
            //Stores input into struct variables and check if format is valid
            if ((cin >> date1.month >> slash1 >> date1.day >> slash2 >> date1.year) && slash1 == '/' && slash2 == '/' && to_string(date1.year).length() == 4) {
                //Checks if date is valid
                if (check_date(date1.month, date1.day)) {
                    break;
                }
                else {
                    cout << "\nPlease enter a valid date\n";
                }
            }
            else {
                cout << "\nIncorrect format\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cout << endl;
        //while loop that interates until start date format is correct and start date is valid
        while (true) {
            cout << "Return date (MM/DD/YYYY): ";
            //Stores input into struct variables and check if format is valid
            if ((cin >> date2.month >> slash1 >> date2.day >> slash2 >> date2.year) && slash1 == '/' && slash2 == '/' && to_string(date2.year).length() == 4) {
                //Checks if date is valid
                if (check_date(date2.month, date2.day)) {
                    break;
                }
                else {
                    cout << "\nPlease enter a valid date\n";
                }
            }
            else {
                cout << "\nIncorrect format\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cin.ignore(1000, '\n');
        cout << endl;
    
        //Calculates number of days between start and end date
        get_num_days(date1, date2, days);
        
        // If the end date is before the start date, start and end date are switched
        if (days < 0) {
            string temp = start;
            start = end;
            end = start;
            days = abs(days);
        }
    
        //Created strings for the start and end dates that will be passed to the objects of the Trip, Flight and Hotel classes
        start = to_string(date1.month) + slash1 + to_string(date1.day) + slash2 + to_string(date1.year);
        end = to_string(date2.month) + slash1 + to_string(date2.day) + slash2 + to_string(date2.year);
    
        //////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "Which city are you departing from: ";
        getline(cin, city);
        //While loop that iterates until input is valid
        while (true) {
            //Checks if format is correct, if not, throws exception
            try {
                cout << "Please enter the state abbreviation (XX): ";
                getline(cin, state);
                
                if (state.length() > 2 || state.length() < 2) {
                    throw invalid_argument ("\nInvalid format, please use the format (XX)\n");
                }
                else if (isnumber(state[0]) || isnumber(state[1])) {
                    throw invalid_argument ("\nPlease use letters in the state abbreviation\n");
                }
                //Capitalizes input
                else {
                    toupper(state[0]);
                    toupper(state[1]);
                    break;
                }
            }
            //Handles exception
            catch (const invalid_argument &e) {
                cout << e.what() << "\n";
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "\n***SELECT YOUR DEPARTURE FLIGHT***\n\n";
    
        //Displays departure flight options for the user
        cout << "1)Southwest Airlines " << right << setw(3) << "$" << ticket_prices[0] << "\n" <<
                "2)Jetblue Airlines " << right << setw(5) << "$" << ticket_prices[1] << "\n" <<
                "3)American Airlines " << right << setw(4) << "$" << ticket_prices[2] << "\n\n";
        
        //While loop that iterates until input is valid
        while (true) {
            getChoice(depart_choice, "Enter choice: ");
            //Function that determines whice flight was choosen and if it was a valid command
            if (airplane_choice(depart_choice, depart_airline)) {
                break;
            }
        }
        cout << "\n***SELECT YOUR RETURN FLIGHT***\n\n";
        //Displays return flight options for the user
        cout << "1)Southwest Airlines " << right << setw(3) << "$" << ticket_prices[3] << "\n" <<
                "2)Jetblue Airlines " << right << setw(5) << "$" << ticket_prices[4] << "\n" <<
                "3)American Airlines " << right << setw(4) << "$" << ticket_prices[5] << "\n\n";
        
        //While loop that iterates until input is valid
        while (true) {
            getChoice(return_choice, "Enter choice: ");
            //Function that determines whice flight was choosen and if it was a valid command
            if (airplane_choice(return_choice, return_airline)) {
                break;
            }
        }
        //Fuction that ask the user for input and iterates until valid input is provided
        getChoice(party_size, "How many tickets would you like to purchase: ");
        cout << endl;
    
        //////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "\n***RECOMMENDED HOTELS***\n\n";
        //Displays the hotel options for the user
        cout << "1)Four Seasons " << right << setw(9) << "$" << night_prices[0] << "\n" <<
                "2)Best Western " << right << setw(9) << "$" << night_prices[1] << "\n" <<
                "3)Hyatt Hotels " << right << setw(9) << "$" << night_prices[2] << "\n\n";
        
        //While loop that iterates until input is valid
        while (true) {
            getChoice(hotel_choice, "Enter choice: ");
            int flag;
            //Switch that determines if input is a valid command
            switch(hotel_choice) {
                case 1:
                    hotel = "Four Seasons";
                    flag =  1;
                    break;
                case 2:
                    hotel = "Best Western";
                    flag =  1;
                    break;
                case 3:
                    hotel = "Hyatt Hotels";
                    flag =  1;
                    break;
                default:
                    cout << "\nInvalid choice!\n";
                    flag = 0;
                    break;
            }
            if (flag == 1){
                break;
            }
        }
        //While loop that iterates until input is valid and user has more than one room is party size is greater than 4
        while (true) {
            getChoice(rooms, "How many rooms would you like: ");
            //Checks if rooms is less than two and party size is greater than 4
            if (party_size > 4 && rooms < 2){
                cout << "\nThe number of rooms must be greater than 1 to accomodate all the guest!\n";
            }
            else {
                break;
            }
        }
        //Created Flight object and passed all the Trip and Flight information
        Flight myFlight = Flight(destination, reason, start, end, city, state, depart_airline, return_airline, ticket_prices[--depart_choice], ticket_prices[3 +(--return_choice)], party_size);
        //Created Hotel object and passed all the Trip and Flight information
        Hotel myHotel = Hotel(destination, reason, start, end, "pending", night_prices[--hotel_choice], days, rooms);
        //Checks if the days is zero to determine if a hotel will be used of not
        if (days == 0) {
            hotel =    "   (N/A)    ";
        }
        //Friend function that changes the private members of the hotel object and changes the name of the hotel
        change_Hotel(myHotel, hotel);
        //Overloaded -- that substracts one from the number of days to get the number of nights
        --myHotel.num_days;
     
        //////////////////////////////////////////////////////////////////////////////////////////////////
        //Fuction that prints the results
        print_results(myFlight, myHotel);
        cout << endl;
        //While loop that iterates until input is valid and ask the user if they like to continue using the program
        while (true) {
            getChoice(continue_choice, "Would you like to plan a new trip? (y/n): ");
            
            if (continue_choice == 'n' || continue_choice == 'y') {
                break;
            }
        }
        cout << endl;
    }
    return 0;
}

//Function that uses Polymorphism to call the correct get_description
string show_trip(Trip &p) {
    string str;
    str = "\n\n***************************************************\n" + p.get_description() + "\n\n";
    return str;
    
}

//Fuction that checks if the date is a valid date and returns true or false
bool check_date(int month, int day) {
    bool flag = 0;
    //Checks if day and month entered are valid
    if (day < 1 || day > 31 || month > 12 || month < 1) {
        flag = 0;
    }
    else {
        //Switch that checks if the number of days is valid for the appropriate month
        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day <= 31) {
                    flag = 1;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day <= 30) {
                    flag = 1;
                }
            case 2:
                if (day <= 28) {
                    flag = 1;
                }
                
            default:
                break;
        }
    }
    //Returns the flag
    return flag;
}

//Function that calculates the number of days between the start and end date
void get_num_days(Date start, Date end, int &days) {
    //Vector that stores the number of days in each month
    vector<int> days_in_months = {31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};
    //Variables to store total days in each date
    int days_in_start, days_in_end;
    //Calculate the total days in each date
    days_in_start = 365 * start.year + start.day;
    days_in_end = 365 * end.year + end.day;
    
    //Loop that adds the days in each month until the month entered
    for (int i = 0; i < start.month - 1; i++) {
        days_in_start += days_in_months[i];
    }
    //Loop that adds the days in each month until the month entered
    for (int i = 0; i < end.month - 1; i++) {
        days_in_end += days_in_months[i];
    }
    //Substracts the total days of start and end date to calculate the difference
    days = days_in_end - days_in_start;
    
}

//Function that verifies if the command entered is valid and determines which airline the user choosed
bool airplane_choice(int input, string &airline){
    bool flag;
    
    switch(input){
        case 1:
            airline = "Southwest Airlines";
            flag =  1;
            break;
        case 2:
            airline = "Jetblue Airlines";
            flag =  1;
            break;
        case 3:
            airline = "American Airlines";
            flag =  1;
            break;
        default:
            cout << "\nInvalid choice!\n";
            flag = 0;
            break;
    }
    return flag;
}

//Function that prints the results of the program
void print_results (Flight &flight, Hotel &hotel) {
    
    double discount = 0;
    double total = flight.get_total();
    string original_total, discounted, final_price;
    
    //String where results are written to
    string results = show_trip(flight) + "From: " + flight.get_city() + ", " + flight.get_state() + " to " + flight.get_destination() + "\n" + "Departure: " + flight.get_start() + "\n" + "Airline: " + flight.get_depart_airline() + "\t Price per ticket: $" + std::to_string(flight.get_ticket_price1()) + "\nTravelers: " + std::to_string(flight.get_num_party());
    
    results += "\n\nReturn Flight\nFrom: " + flight.get_destination() + " to " + flight.get_city() + ", " + flight.get_state() + "\n" + "Departure: " + flight.get_end() + "\n" + "Airline: " + flight.get_return_airline() + "\t Price per ticket: $" + std::to_string(flight.get_ticket_price2()) + "\nTravelers: " + std::to_string(flight.get_num_party());
    
    results += show_trip(hotel) + "Hotel company: " + hotel.get_hotel() + "\t Price per night:  $" + std::to_string(hotel.get_night_price()) + "\n" + "Number of nights: " + std::to_string(hotel.get_num_days()) + "\n" + "Number of rooms:  " + std::to_string(hotel.get_num_rooms()) + "\n" +
        "\n***************************************************\n***Expenses***\n\n";
    
    //Checks the Trip reason in order to calculate the appropiate discount
    if (flight.get_reason() == "Business") {
        discount = total * .1;
        total = total - discount;
    }
    else {
        discount = total * .05;
        total = total - discount;
    }
    //Called function that returns the rounded results as a string
    original_total = round_Num(flight.get_total());
    discounted = round_Num(discount);
    final_price = round_Num(total);
    
    results += "Starting price:            $" + original_total + "\n" + flight.get_reason() + " bundled savings: -$" + discounted + "\n---------------------------------\nTotal Trip price:          $" + final_price + "\n";
    cout << results;
    //Writes results into an output file
    ofstream output_file;
    output_file.open("Trip details.txt");
    output_file << results << endl;
    output_file.close();
}
//Function that round number to 2 decimal places and returns it as string
string round_Num(double result)
{
    std::ostringstream stream;
    stream << setprecision(2) << fixed << result;
    string rounded_result =  stream.str();
    return rounded_result;
}
//Friend function that changes the hotel name of a Hotel object
void change_Hotel(Hotel &hotel, string input) {
        hotel.hotel = input;
}

