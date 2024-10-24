#ifndef PASSENGER_H
#define PASSENGER_H
#include "User.h"
// #include "Carpooling.h"
// #include "Request.h"  // Include any other headers needed
#include <vector>
#include <limits>
class Request;
class Carpool;

class Passenger : public User
{
private:
    vector<Request> request_list;

public:
    Passenger() {};
    Passenger(User user) : User(user) {};

    bool book_carpool(vector<Carpool> &carpools, vector<Request> &requests);
    bool cancel_carpool(vector<Carpool> &carpools, vector<Request> &requests);
    void view_all_request(vector<Request> &requestlist);
    vector<Request> get_request_list() const;
    void rating_carpool(vector<Carpool> &carpool, vector<Rating> &ratinglist);

    friend class Admin;
    friend class Driver;
    // friend class Carpool;
    // friend bool loginPassenger(string &Temp, Passenger &passenger, vector<User> &userList);
};

#endif