//Trip superclass which is also and abstract class

#ifndef Trip_hpp
#define Trip_hpp

//Included necessary libraries
#include <string>

using std::string;
//Trip class
class Trip {

//Private data members
private:
    string destination;
    string reason;
    string start;
    string end;
    static double total;
//Public functions
public:
    //Constructor that initializes private data members
    Trip (string destination_, string reason_, string start_, string end_) {
        destination = destination_;
        reason = reason_;
        start = start_;
        end = end_;
    }
    //Function that returns the reason
    string get_reason() const {
        return reason;
    }
    //Function that returns the start date
    string get_start() const {
        return start;
    }
    //Function that returns the end date
    string get_end() const {
        return end;
    }
    //Function that returns destination
    string get_destination() const {
        return destination; 
    }
    //Function that adds input to the total
    void add_total(int price) {
        total += price;
    }
    //Function returns the total
    double get_total() const {
        return total;
    }
    //Pure vitual functions 
    virtual string get_description() const = 0;
    
};
#endif /* Trip_hpp */
