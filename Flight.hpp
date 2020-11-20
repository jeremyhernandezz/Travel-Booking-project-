//Flight subclass

#ifndef Flight_hpp
#define Flight_hpp
#include "Trip.hpp"

//Flight subclass that inherits the Trip superclass
class Flight: public Trip {

//Private data members
private:
    string city;
    string state;
    string depart_airline;
    string return_airline;
    int ticket_price1;
    int ticket_price2;
    int num_party;
//Public data functions
public:
    //Constructor that calls the Trip constructor and initializes the variables and that initializes the new private data members
    Flight (string destination_, string reason_, string start_, string end_, string city_, string state_, string depart_airline_, string return_airline_,
            double ticket_price1_, double ticket_price2_,  int num_party_) : Trip(destination_, reason_, start_, end_) {
        city = city_;
        state = state_;
        depart_airline = depart_airline_;
        return_airline = return_airline_;
        ticket_price1 = ticket_price1_;
        ticket_price2 = ticket_price2_;
        num_party = num_party_;
        //Adds the flight expeses to Trip total
        add_total((ticket_price1 * num_party) + (ticket_price2 * num_party));
    }
    //Function that returns the city
    string get_city() const {
        return city;
    }
    //Function that returns the state
    string get_state() const {
        return state;
    }
    //Function that returns the depart_airline
    string get_depart_airline() const {
        return depart_airline;
    }
    //Function that returns the return_airline
    string get_return_airline() const {
        return return_airline;
    }
    //Function that returns the ticket_price1
    int get_ticket_price1() const {
        return ticket_price1;
    }
    //Function that returns the ticket_price2
    int get_ticket_price2() const {
        return ticket_price2;
    }
    //Function that returns the num_party
    int get_num_party() const {
        return num_party;
    }
    //Function that overrides the Trip get_description
    string get_description() const {
        return "***Roundtrip Flight***";
    }
};
#endif /* Flight_hpp */
