#include "../Header_File/User.h"
#include "../Header_File/Carpooling.h"
#include "../Header_File/Driver.h"
#include "../Header_File/Passenger.h"
#include "../Header_File/Departure.h"
#include "../Header_File/Request.h"

int Carpool::currentID = 0;

Carpool::Carpool(string dep, string dest, string time, string date, string model, string color, int seats, string driver, double rating)
    : departure(dep), destination(dest), depart_time(time), depart_date(date), car_model(model), color(color), available_seats(seats), driver(driver), minimum_passenger_rating(rating)
{
    carID = ++currentID;

    // Assume each point in list takes 20 mins to move
    this->estimated_time = abs(getIndexDeparture(dep) - getIndexDeparture(dest)) * 20;
    this->credit_total = abs(getIndexDeparture(dep) - getIndexDeparture(dest)) * 50; // Each point in list takes $50
}

Carpool::Carpool(int dep, int dest, string time, string date, string model, string color, string plate_num, int seats, string driver, double rating, string city)
    : depart_time(time), depart_date(date), available_seats(seats), driver(driver), car_model(model), color(color), minimum_passenger_rating(rating), plate_num(plate_num)
{
    carID = ++currentID;

    departure = getLocation(dep, city);
    destination = getLocation(dest, city);

    // Assume each point in list takes 20 mins to move
    this->estimated_time = abs(dep - dest) * 20;
    this->credit_total = abs(dep - dest) * 50; // Each point in list takes $50

    this->isCompleted = false;
}
Carpool::Carpool(int carID, int dep, int dest, string time, string date, string model, string color, string plate, int seats, double credit, float rating, string driver, string city)
    : carID(carID), depart_time(time), depart_date(date), car_model(model), color(color), plate_num(plate), available_seats(seats), credit_total(credit), minimum_passenger_rating(rating), driver(driver)
{
    currentID++;
    this->departure = getLocation(dep, city);
    this->destination = getLocation(dest, city);

    // Assume each point in list takes 20 mins to move
    this->estimated_time = abs(dep - dest) * 20;
    this->credit_total = abs(dep - dest) * 50; // Each point in list takes $50
    this->isCompleted = false;
}

Carpool::Carpool(int carID, string dep, string dest, string time, string date, string model, string color, string plate, int seats, double credit, float rating, string driver, bool isCompleted)
    : carID(carID), departure(dep), destination(dest), depart_time(time), depart_date(date), car_model(model), color(color), plate_num(plate), available_seats(seats), credit_total(credit), minimum_passenger_rating(rating), driver(driver), isCompleted(isCompleted)
{
    currentID++;
    this->estimated_time = abs(getIndexDeparture(dep) - getIndexDeparture(dest)) * 20;
    this->credit_total = abs(getIndexDeparture(dep) - getIndexDeparture(dest)) * 50;
}

// Function to set departure location
void Carpool::setDepartureLocation(int choice, User &auser)
{
    string s = "Saigon";
    string h = "Hanoi";
    if (auser.getCity() == "SAI GON")
    {
        departure = getLocation(choice, s);
    }
    else
    {
        departure = getLocation(choice, h);
    }
}

// Function to set destination location
void Carpool ::setDestinationLocation(int location, User &auser)
{
    string s = "Saigon";
    string h = "Hanoi";
    if (auser.getCity() == "SAI GON")
    {
        destination = getLocation(location, s);
    }
    else
    {
        destination = getLocation(location, h);
    }
}

string Carpool ::getDepartureLocation()
{
    return departure;
}
string Carpool ::getDestinationLocation()
{
    return destination;
}
int Carpool ::getEstimatedDuration() const
{
    return estimated_time;
}

void Carpool::setDepartureTime(string &time)
{
    this->depart_time = time;
}
string Carpool::getDepartureTime() const
{
    return depart_time;
}
void Carpool::setDate(string &date)
{
    this->depart_date = date;
}
string Carpool::getDate() const
{
    return depart_date;
}
void Carpool::setColor(string &color)
{
    this->color = color;
}
string Carpool::getColor() const
{
    return color;
}
void Carpool::setPlateNumber(string &plateNumber)
{
    this->plate_num = plateNumber;
}
string Carpool::getPlateNumber() const
{
    return plate_num;
}
void Carpool::setMinimumPassengerRating(float rating)
{
    this->minimum_passenger_rating = rating;
} // Set minimum passenger rating
float Carpool::getMinimumPassengerRating() const
{
    return minimum_passenger_rating;
} // Get minimum passenger rating

void Carpool::add_Passenger(Passenger *passenger)
{
    passengers.push_back(passenger);
}
void Carpool ::setVehicleModel(string &model)
{
    car_model = model;
}
string Carpool ::getVehicleModel() const
{
    return car_model;
}
void Carpool ::setCarID(int car)
{
    carID = car;
}
int Carpool ::getCarID()
{
    return carID;
}
vector<Request> &Carpool ::getRequets()
{
    return bookingRequests;
}
void Carpool ::setAvailableSeats(int seats)
{
    this->available_seats = seats;
}
vector<Rating> Carpool::getlistRatingg()
{
    return listofRating;
}
vector<Passenger *> Carpool::getPassenger() const
{
    return passengers;
}

string Carpool::getDrivername() const
{
    return driver;
}

void Carpool::setDrivername(string drivername)
{
    driver = drivername;
}

// Function to calculate the average rating of the carpool
double Carpool::rating_calculate()
{
    double sum = 0;
    int index = 0;
    for (Rating &arate : listofRating)
    {
        sum += arate.getScore();
        index++;
    }
    return sum / index;
}

// Function to display the header for the carpool details
void Carpool::show_header_carpool()
{
    cout << left << setw(5) << "CarID"
         << setw(12) << "Date"
         << setw(8) << "Time"
         << setw(23) << "Departure"
         << "-> " << setw(23) << "Destination"
         << setw(7) << "Seats"
         << setw(11) << "Est. Time"
         << setw(15) << "Car Model"
         << setw(10) << "Color"
         << setw(7) << "Plate"
         << setw(8) << "Credits"
         << setw(8) << "Rating"
         << setw(15) << "Driver"
         << setw(15) << "Completed" << endl;
    cout << string(120, '-') << endl; // Separator line
}

// Function to display the carpool details
void Carpool::Show_Carpool_detail()
{
    // Print carpool details
    cout << left << setw(5) << carID
         << setw(12) << depart_date
         << setw(8) << depart_time
         << setw(23) << departure
         << "-> " << setw(23) << destination
         << setw(7) << available_seats
         << setw(11) << estimated_time << " mins"
         << setw(15) << car_model
         << setw(10) << color
         << setw(7) << plate_num
         << setw(8) << credit_total
         << setw(8) << this->rating_calculate()
         << setw(15) << driver
         << setw(15) << ((this->getisCompleted() == true) ? "true" : "false") << endl;
}

void Carpool::setisCompleted()
{
    isCompleted = true;
}

bool Carpool::getisCompleted() const
{
    return isCompleted;
}

double Carpool::credit_calculate(int dep, int dest)
{
    return abs(dep - dest) * 50;
}

int Carpool::time_calculate(int dep, int dest)
{
    return abs(dep - dest) * 20;
}

int Carpool::getAvailableSeats() const
{
    return available_seats;
}

void Carpool::setContributionAmount(double amount)
{
    credit_total = amount;
}

// Function to remove a passenger from the carpool
void Carpool::removePassenger(Passenger *passenger)
{
    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i]->getUsername() == passenger->getUsername())
        {
            passengers.erase(passengers.begin() + i);
            return;
        }
    }
}

// Function to add a booking request
void Carpool::addBookingRequest(Passenger *passenger, Request &arequest)
{
    Request request(carID, passenger->getUsername(), arequest.getRequestStatus());
    bookingRequests.push_back(request);
}

// Function to convert carpool details to string
string Carpool::toStringCarpool()
{
    return to_string(carID) + "," +
           this->departure + "," +
           this->destination + "," +
           this->depart_time + "," +
           this->depart_date + "," +
           this->car_model + "," +
           this->color + "," +
           this->plate_num + "," +
           to_string(available_seats) + "," +
           to_string(this->credit_total) + "," +
           to_string(this->minimum_passenger_rating) + "," +
           this->driver + "," +
           to_string(this->isCompleted) + "\n";
}

void Carpool::addRating(Rating &rating)
{
    listofRating.push_back(rating);
}
double Carpool ::getContributionAmount() const
{
    return credit_total;
}