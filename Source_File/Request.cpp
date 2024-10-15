#include "../Header_File/Request.h"

Request::Request(int ID, string passengername) : carID(ID), passenger(passengername)
{
    this->requestStatus = "PENDING";
}

Request::Request(int ID, string passengername, string status) : carID(ID), passenger(passengername), requestStatus(status) {}

void Request::setCarID(int ID) { carID = ID; }
void Request::setRequestStatus(string status) { this->requestStatus = status; }
void Request::setPassenger(string passenger) { this->passenger = passenger; }
string Request::getPassenger() const { return passenger; }
int Request::getCarID()  { return carID; }
string Request::getRequestStatus() const { return requestStatus; }
void Request::showrequestheader()
{
    cout << left << setw(10) << "Car ID" << left << setw(15) << "Request Status" << left << setw(15) << "Passenger" << endl;
    cout << string(50, '-') << endl; // Header line
}
void Request ::showinfo_Request()
{
    cout << left << setw(10) << this->getCarID() << setw(15) << this->requestStatus << setw(15) << this->passenger << endl;
}
string Request::to_stringRequest()
{
    return to_string(carID) + "," + passenger + "," + requestStatus + "\n";
}