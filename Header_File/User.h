#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Rating.h"
// #include "Carpooling.h"
#include "Request.h"
// #include "File.h"
// #include "Departure.h"

#define ADMIN_CODE 12345

using namespace std;

class Carpool;
// class Request;
class File;
class Departure;


class User
{
protected:
    string username;
    string password;
    string fullname;
    string phone;
    string email;
    string city;
    int IDtype;
    string IDnum;
    double ratingscore;
    double creditpoint;
    bool isAdmin;
    bool isDriver;
    bool isPassenger;
    bool isVerified;
    vector<User *> username_list;
    vector<Rating> rated_list;

public:
    User();
    User(string username, string password, string fullname, string phone, string email, string city, int IDtype, string IDnum, double creditpoint);
    User(string username, string password, string fullname, string phone, string email, string city, int IDtype, string IDnum, double ratingscore, double creditpoint, bool isAdmin ,bool isDriver, bool isPassenger, bool isVerified);

    string getUsername() const;
    string getPassword() const;
    string getFullName() const;
    string getPhoneNumber() const;
    string getEmail() const;
    void setisVerirified(bool verrify);
    int getIDType() const;
    string getIDNumber() const;
    double getCreditPoints() const;
    void setCredit(double amount);
    float getRatingScore() const;
    void setRating(double r);
    bool checkVerified() const;
    string getCity() const;
    vector<Rating> getRatedlist();
    void set_rating(Rating &a_rating);

    bool getisAdmin() const;
    bool getisDriver() const;
    bool getisPassenger() const;
    bool getisVerified() const;

    void userregister(vector<User> &userList);
    bool passwordCheck(string password);
    void viewprofile();
    void updateprofile();
    void changepassword();
    void purchaseCreditPoints(double amount);
    void calculateAverage();
    void viewheader();
    friend bool login(string &temp, User &user, vector<User> &userList, int role); 
    string to_stringUser();
};
#endif

// Feedback: Use friend functions instead of using getters and setters functions