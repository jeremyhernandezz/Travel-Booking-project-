//Hotel subclass

#ifndef Hotel_hpp
#define Hotel_hpp
#include "Trip.hpp"

//Hotel subclass that inherits the Trip superclass
class Hotel: public Trip {
//Private data members
private:
    string hotel;
    int night_price;
    int num_rooms;
//Public data members and functions
public:
    //public data member
    int num_days;
    //Constructor that calls the Trip constructor and initializes the variables and that initializes the new private data members
    Hotel(string destination_, string reason_, string start_, string end_, string hotel_, int night_price_, int num_days_, int num_rooms_) : Trip (destination_, reason_, start_, end_) {
        hotel = hotel_;
        night_price = night_price_;
        num_days = num_days_;
        num_rooms = num_rooms_;
        
        //Checks if the trip is 1 day long and there is no need for a hotel.
        if (num_days == 0){
            //Made the necessary arrangement so that the program displays the correct values when a hotel info was not applicable
            add_total(0);
            num_days = 1;
            num_rooms = 0;
            night_price = 0;
        }
        else {
            //Adds the hotel expenses to the Trip total
            add_total(night_price * --num_days_ * num_rooms);
        }
    }
    
    //Function that returns the hotel
    string get_hotel() const {
        return hotel;
    }
    //Function that returns the night_price
    int get_night_price() const {
        return night_price;
    }
    //Function that returns the num_rooms
    int get_num_rooms() const {
        return num_rooms;
    }
    //Function that returns the num_days
    int get_num_days() const {
        return num_days;
    }
    //Function that overrides the Trip get_description
    string get_description() const {
        return "***Hotel info***";
    }
    //Friend function that changes the hotel name 
    friend void change_Hotel(Hotel &hotel, string input);
    
    //Overloaded -- operator that substract one from num_days to get number of nights
    Hotel & operator-- () {
        --num_days;
        return *this;
    }
    

};
#endif /* Hotel_hpp */
