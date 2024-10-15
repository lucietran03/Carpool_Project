#ifndef RATING_H
#define RATING_H

//#include "User.h"
//#include "Carpooling.h"
using namespace std;

class Carpool;
class Rating
{
private: 
    string comment;
    double score;

public:
    Rating() {}
    Rating(string comment, double score);

    // Setter
    void setScore(double score);
    void setComment(string comment);
    double getScore()const;
    string getComment()const;
};

class DriverRating : public Rating
{
private:
    string username;

public:
    DriverRating() {}
    DriverRating(string username, string comment, double score);
    
    // Getter
    string getusername();

    void submit_rating(Carpool &acarpool); 
    string to_stringDriverRating(); 
    void showinfo_DriverRating();
    void showheader_DriverRating();
};

class PassengerRating : public Rating
{
private:
    int carID;

public:
    PassengerRating() {}
    PassengerRating(int carID, string comment, double score);

    // Getter
    int getCarID();

    void submit_rating(Carpool &acarpool); 
    string to_stringPassengerRating();
    void showinfo_PassengerRating();
    void showheader_PassengerRating();
};
#endif