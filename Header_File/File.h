#ifndef FILE_H
#define FILE_H

// Full class declarations if needed
#include "User.h"
// #include "Driver.h"
// #include "Passenger.h"
// #include "Rating.h"
#include "Request.h"
#include "Carpooling.h"
#include <tuple>

class Rating;
class Passenger;
class Driver;
class Request;
class Carpool;

class FileSaving
{
private:
    // const string userfile = "Driver.h";
    const string RequestFile = "../Files/Request.txt";
    const string RatingFile = "../Files/Rating.txt";
    const string CarpoolFile = "../Files/Carpool.txt";
    const string UserFile = "../Files/User.txt";

public:
    vector<Rating> loadRating(vector<DriverRating> &driver_rate, vector<PassengerRating> &passenger_rate);
    vector<Request> loadRequest();
    vector<Carpool> loadCarpool(vector<Request> &requests, vector<PassengerRating> &passenger_rate);
    tuple<vector<User>, vector<Driver>, vector<Passenger>> loadUser(vector<User> &userlist, vector<Driver> &driverlist, vector<Passenger> &passengerlist, vector<DriverRating> &driver_rate, vector<Request> &requests, vector<Carpool> &carpool_list);
    void saveCarpool(vector<Carpool> &carpool_list); 
    void saveRequest(vector<Request> &requests); 
    void saveRating(vector<PassengerRating> &passenger_rate, vector<DriverRating> &driver_rate); 
    void saveUser(vector<User> &userlist);
};

#endif