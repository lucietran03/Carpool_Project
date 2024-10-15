#ifndef CARPOOLING_H
#define CARPOOLING_H

#include <iostream> 
#include <vector> 
// #include "Passenger.h"
//#include "User.h"
//#include "Departure.h"
//#include "Rating.h"
//#include "Request.h"
using namespace std;

class Rating;
class User;
class Passenger;

class Carpool
{
private:
    int carID; // Unique identifier for the carpool 
    static int currentID; // Static variable to generate unique car IDs
    string departure; // Departure location of the carpool
    string destination; // Destination location of the carpool
    string depart_time; // Time of departure
    string depart_date; // Date of departure
    float estimated_time; // Estimated travel time
    string car_model; // Model of the car
    string color; // Color of the car
    string plate_num; // License plate number of the car
    int available_seats; // Number of available seats in the carpool
    double credit_total; // Credit contribution for the carpool
    float minimum_passenger_rating; // Minimum rating required for passengers 
    string driver; // Pointer to the Driver object 
    bool isCompleted; // Flag to indicate if the carpool is completed
    vector<Passenger*> passengers; // List of passengers
    vector<Request> bookingRequests; // List of booking requests
    vector<Rating> listofRating;

public:
    Carpool() {}; // Default constructor
    Carpool(string dep, string dest, string time, string date, string model, string color, int seats, string driver, double rating);
    Carpool(int dep, int dest, string time, string date, string model, string color, string plate_num, int seats, string driver, double rating, string city);
    Carpool(int carID, int dep, int dest, string time, string date, string model, string color, string plate, int seats, double credit, float rating, string driver, string city);
    Carpool(int carID, string dep, string dest, string time, string date, string model, string color, string plate, int seats, double credit, float rating, string driver, bool isCompleted);
    
    // Set and get functions for the data members 
    void setDepartureLocation(int choice, User &auser); // Set departure location
    string getDepartureLocation() ; // Get departure location
    void setDestinationLocation(int location, User &auser); // Set destination location
    string getDestinationLocation() ; // Get destination location
    void setDepartureTime(string &time); // Set departure time
    string getDepartureTime() const; // Get departure time
    void setDate(string &date); // Set departure date
    string getDate() const; // Get departure date
    int getEstimatedDuration() const; // Get estimated travel duration
    void setVehicleModel(string &model); // Set vehicle model
    string getVehicleModel() const; // Get vehicle model
    void setColor(string &color); // Set vehicle color
    string getColor() const; // Get vehicle color
    void setPlateNumber(string &plateNumber); // Set plate number
    string getPlateNumber() const; // Get plate number
    void setAvailableSeats(int seats); // Set available seats
    int getAvailableSeats() const; // Get available seats
    void setContributionAmount(double amount); // Set contribution amount
    double getContributionAmount() const;
    double credit_calculate(int dep, int dest); // Get contribution amount
    void setMinimumPassengerRating(float rating); // Set minimum passenger rating
    float getMinimumPassengerRating() const; // Get minimum passenger rating
    void setCarID(int car);
    int getCarID(); 
    string getDrivername() const;
    void setDrivername(string drivername);
    void addRating(Rating &rating); // Add a rating to the carpool
    void setisCompleted(); // Set the status of the carpool
    bool getisCompleted() const; // Get the status of the carpool
    double rating_calculate(); // Calculate the average rating of the carpool
    
    vector <Request> &getRequets() ; 
    vector <Rating> getlistRatingg();
    vector <Passenger*> getPassenger() const;

    void show_header_carpool(); // Display the header for the carpool details
    void Show_Carpool_detail(); // Display carpool details
    void add_Passenger(Passenger *passenger); // Add a passenger to the carpool
    void removePassenger(Passenger *passenger); // Remove a passenger from the carpool
    void addBookingRequest(Passenger *passenger, Request &arequest); // Add a booking request
    int time_calculate(int dep, int dest); 
    string toStringCarpool();
};

#endif