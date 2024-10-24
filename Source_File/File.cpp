#include "../Header_File/File.h"
#include "../Header_File/Request.h"
#include "../Header_File/Carpooling.h"
#include "../Header_File/User.h"
#include "../Header_File/Driver.h"
#include "../Header_File/Passenger.h"
#include "../Header_File/Rating.h"
#include "../Header_File/Departure.h"
#include <regex>

// CarID/username,score,comment
vector<Rating> FileSaving::loadRating(vector<DriverRating> &driver_rate, vector<PassengerRating> &passenger_rate)
{
    fstream myFile;
    myFile.open(RatingFile, ios::in);
    string line;

    while (getline(myFile, line))
    {
        istringstream iss(line);
        string carID_or_username;
        string score_str;
        string comment;

        // Use getline to split by comma
        if (!getline(iss, carID_or_username, ',') ||
            !getline(iss, comment, ',') ||
            !getline(iss, score_str))
        {
            continue; // Skip invalid lines
        }

        // Convert score string to double
        double score;
        try
        {
            score = stod(score_str);
        }
        catch (const invalid_argument &)
        {
            continue; // Skip lines with invalid score format
        }

        // Check if carID_or_username is numeric or not
        try
        {
            // If it's a number, it's a passenger rating
            passenger_rate.push_back(PassengerRating(stod(carID_or_username), comment, score));
        }
        catch (const invalid_argument &)
        {
            // Otherwise, it's a driver rating
            driver_rate.push_back(DriverRating(carID_or_username, comment, score));
        }
    }

    myFile.close();

    // Combine driver and passenger ratings
    vector<Rating> combined;
    combined.insert(combined.end(), driver_rate.begin(), driver_rate.end());
    combined.insert(combined.end(), passenger_rate.begin(), passenger_rate.end());

    return combined;
}

// ID, passenger, status
vector<Request> FileSaving::loadRequest()
{
    fstream myFile;
    myFile.open(RequestFile, ios::in);
    string temp;
    vector<Request> requests;

    while (getline(myFile, temp))
    {
        istringstream iss(temp);
        string part;
        vector<string> parts;

        while (getline(iss, part, ','))
        {
            parts.push_back(part);
        }

        int ID = stoi(parts[0]);
        string passenger = parts[1];
        string status = parts[2]; // Default "PENDING"

        // Skip invalid lines
        if (parts.size() < 3)
            continue;

        requests.push_back(Request(ID, passenger, status));
    }

    myFile.close();

    return requests;
}

// Method to load carpool data from file
// ID, departure, destination, depart_time, depart_date, car_model, color, plate_num, available_seats, credit_contribution, minimum_passenger_rating, driver
vector<Carpool> FileSaving::loadCarpool(vector<Request> &requests, vector<PassengerRating> &passenger_rate)
{
    fstream myFile;
    myFile.open(CarpoolFile, ios::in);
    string temp;
    vector<Carpool> carpool_list;

    if (!myFile.is_open())
    {
        cout << "Failed to open file: " << CarpoolFile << endl;
        return carpool_list; // Return an empty list if the file cannot be opened
    }

    cout << "Loading carpool data from file..." << endl;

    while (getline(myFile, temp))
    {
        istringstream iss(temp);
        string part;
        vector<string> parts;

        while (getline(iss, part, ','))
        {
            parts.push_back(part);
        }

        if (parts.size() < 13)
        {
            cout << "Skipped invalid line: " << temp << endl; // Debug output for invalid lines
            continue;                                         // Skip invalid lines
        }

        int carID = stoi(parts[0]);
        string dep = parts[1];
        string des = parts[2];
        string depart_time = parts[3];
        string depart_date = parts[4];
        string car_model = parts[5];
        string color = parts[6];
        string plate_num = parts[7];
        int available_seats = stoi(parts[8]);
        double credit_total = stod(parts[9]);
        float minimum_passenger_rating = stof(parts[10]);
        string driver_username = parts[11];
        bool isCompleted = (parts[12] == "1");

        // Create a new carpool object and add it to the list
        Carpool carpool(carID, dep, des, depart_time, depart_date, car_model, color, plate_num, available_seats, credit_total, minimum_passenger_rating, driver_username, isCompleted);
        carpool_list.push_back(carpool);
    }

    // Load requests and ratings
    for (auto &carpool : carpool_list)
    {
        for (auto &request : requests) // Add requests to carpool
        {
            if (carpool.getCarID() == request.getCarID() && (request.getRequestStatus() == "PENDING" || request.getRequestStatus() == "ACCEPTED"))
            {
                carpool.getRequets().push_back(request);
            }
        }
        for (auto &arating : passenger_rate) // Add ratings to carpool
        {
            if (arating.getCarID() == carpool.getCarID())
            {
                carpool.getlistRatingg().push_back(arating);
            }
        }
    }

    myFile.close();
    // cout << "Carpool loading completed." << endl; // Debug output

    return carpool_list;
}

// Method to load user data from file
tuple<vector<User>, vector<Driver>, vector<Passenger>> FileSaving::loadUser(vector<User> &userlist, vector<Driver> &driverlist, vector<Passenger> &passengerlist, vector<DriverRating> &driver_rate, vector<Request> &requests, vector<Carpool> &carpool_list)
{
    fstream myFile;
    myFile.open(UserFile, ios::in);
    string temp;
    vector<User> user_list;

    while (getline(myFile, temp))
    {
        istringstream iss(temp);
        string token;
        vector<string> tokens;

        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() < 13)
        {
            continue; // Skip invalid lines
        }

        string username = tokens[0];
        string password = tokens[1];
        string fullname = tokens[2];
        string phone = tokens[3];
        string email = tokens[4];
        string city = tokens[5];
        int IDtype = stoi(tokens[6]);
        string IDnum = tokens[7];
        double ratingscore = stod(tokens[8]);
        double creditpoint = stod(tokens[9]);
        bool isAdmin = (tokens[10] == "1");
        bool isDriver = (tokens[11] == "1");
        bool isPassenger = (tokens[12] == "1");
        bool isVerified = (tokens[13] == "1");

        // Create a new user object and add it to the list
        User user(username, password, fullname, phone, email, city, IDtype, IDnum, ratingscore, creditpoint, isAdmin, isDriver, isPassenger, isVerified);

        user_list.push_back(user);
    }

    for (auto &user : user_list)
    {
        if (user.getisDriver()) // Add driver to driver list
        {
            Driver driver(user);
            driverlist.push_back(driver);
        }
        if (user.getisPassenger()) // Add passenger to passenger list
        {
            Passenger passenger(user);
            passengerlist.push_back(passenger);
        }
    }

    // Add carpool to driver
    for (auto &driver : driverlist)
    {
        for (auto &carpool : carpool_list) // Add carpool to driver
        {
            if (driver.getUsername() == carpool.getDrivername())
            {
                driver.get_carpool_list().push_back(carpool);
            }
        }
    }

    // Add request to passenger
    for (auto &passenger : passengerlist)
    {
        for (auto &request : requests) // Add request to passenger
        {
            if (passenger.getUsername() == request.getPassenger())
            {
                passenger.get_request_list().push_back(request);
            }
        }
    }

    myFile.close();
    return make_tuple(user_list, driverlist, passengerlist);
}

// Method to save carpool data to file
void FileSaving::saveCarpool(vector<Carpool> &carpool_list)
{
    ofstream myFile(CarpoolFile, ios::out);

    if (!myFile.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (auto &carpool : carpool_list) // Write each carpool to file
    {
        myFile << carpool.toStringCarpool();
    }

    myFile.close();
}

// Method to save request data to file
void FileSaving::saveRequest(vector<Request> &requests)
{
    ofstream myFile(RequestFile, ios::out);

    if (!myFile.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (auto &request : requests) // Write each request to file
    {
        myFile << request.to_stringRequest();
    }

    myFile.close();
}

// Method to save rating data to file
void FileSaving::saveRating(vector<PassengerRating> &passenger_rate, vector<DriverRating> &driver_rate)
{
    ofstream myFile(RatingFile, ios::out);

    if (!myFile.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (auto &rating : passenger_rate)
    {
        myFile << rating.to_stringPassengerRating(); // Write each passenger rating to file
    }

    for (auto &rating : driver_rate)
    {
        myFile << rating.to_stringDriverRating(); // Write each driver rating to file
    }
}

// Method to save user data to file
void FileSaving::saveUser(vector<User> &userlist)
{
    ofstream myFile(UserFile, ios::out);

    if (!myFile.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (auto &user : userlist)
    {
        myFile << user.to_stringUser();
    }

    myFile.close();
}