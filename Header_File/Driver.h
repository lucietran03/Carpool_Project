#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
// #include "Carpooling.h"
// #include "Passenger.h"
#include <vector>
using namespace std;

class Carpool;
class Passenger;

class Driver : public User
{
private:
    vector<Carpool> carpool_list;

public:
    Driver() {};
    Driver(User user) : User(user) {};

    void create_carpool_list(vector<Carpool> &carpoollist);
    void delete_list(vector <Carpool> &carpoollist);
    void view_carpool_list(vector<Carpool> &carpoollist);

    void view_request(vector<Request> &requestlist, vector<Carpool> &carpool_list);
    bool accept_booking(vector<Passenger >& passlist, vector<Carpool> &carpoollist, vector<Request> &requestlist);
    bool reject_booking(vector<Carpool> &carpoollist, vector<Request> &requestlist);
    void change_carpool_status(vector<Carpool> &carpoollist);
    void set_rating(vector<Carpool> &carpool);
    void rate_passenger(vector<Carpool> &carpool, vector<Passenger> &passengerlist, vector<Rating> &ratinglist);
    vector<Carpool> get_carpool_list();

    friend bool loginDriver(string &temp, Driver &driver, vector<User> &userList);
    friend class Passenger;
    friend class Admin;
};

#endif