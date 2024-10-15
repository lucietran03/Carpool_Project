#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <iomanip>
// #include "User.h"
using namespace std;

class Request
{
private:
    int carID;
    string requestStatus;
    string passenger;

public:
    Request() {};
    Request(int ID, string passengername);
    Request(int ID, string passengername, string status);
    void showinfo_Request();
    void setCarID(int ID);
    void setRequestStatus(string status);
    void setPassenger(string passenger);
    int getCarID();
    string getRequestStatus() const;
    string getPassenger() const; 
    string to_stringRequest();
    void showrequestheader();
};
#endif