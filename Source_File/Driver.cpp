// #include "../Header_File/User.h"
#include "../Header_File/Driver.h"
// #include "../Header_File/Rating.h"
#include "../Header_File/Departure.h"
#include "../Header_File/Carpooling.h"
#include "../Header_File/Passenger.h"
#include "../Header_File/Request.h"

// Method to view the carpool list of the driver
void Driver::view_carpool_list(vector<Carpool> &carpoollist)
{
    carpoollist[0].show_header_carpool();
    for (Carpool &acarpool : carpoollist)
    {
        if (acarpool.getDrivername() == this->getUsername())
        {
            acarpool.Show_Carpool_detail();
        }
    }
}

// Method to create a carpool list
void Driver::create_carpool_list(vector<Carpool> &carpoollist)
{
    int des_choice = 0;
    int dep_choice = 0;
    string depart_time;
    string depart_date;
    string car_model;
    string color;
    string plate_num;
    int available_seats = 0;
    float minimum_passenger_rating = 0.0;
    string temp;

    string city = this->getCity(); // Assume getCity() returns either "Saigon" or "Hanoi"
    showLocations(city);

    // Validate departure and destination
    do
    {
        cout << "Enter departure location (1-5): ";
        cin >> dep_choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        if (dep_choice < 1 || dep_choice > 5)
            cout << "Please choose from the menu!\n";
    } while (dep_choice < 1 || dep_choice > 5);

    do
    {
        cout << "Enter destination location (1-5): ";
        cin >> des_choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (des_choice < 1 || des_choice > 5)
            cout << "Please choose from the menu!\n";
        else if (des_choice == dep_choice)
            cout << "Pick up location must be different from destination location\n";
    } while (des_choice < 1 || des_choice > 5 || des_choice == dep_choice);

    // Validate departure time (hh.mm)
    regex time_regex("^([0-2][0-9])\\.([0-5][0-9])$");
    do
    {
        cout << "Enter departure time (hh.mm): ";
        getline(cin, depart_time);
    } while (!regex_match(depart_time, time_regex));

    // Validate departure date (xx.xx.xxxx)
    regex date_regex("^[0-3][0-9]\\.[0-1][0-9]\\.[0-9]{4}$");
    do
    {
        cout << "Enter departure date (dd.mm.yyyy): ";
        getline(cin, depart_date);
    } while (!regex_match(depart_date, date_regex));

    // Validate color (no special characters)
    regex color_regex("^[a-zA-Z0-9 ]+$");
    do
    {
        cout << "Enter car color: ";
        getline(cin, color);
    } while (!regex_match(color, color_regex));

    // Validate car model (hyphen allowed, no other special characters)
    regex model_regex("^[a-zA-Z0-9- ]+$");
    do
    {
        cout << "Enter car model: ";
        getline(cin, car_model);
    } while (!regex_match(car_model, model_regex));

    // Validate plate number (XXXXX)
    do
    {
        cout << "Enter plate number (XXXXX): ";
        getline(cin, plate_num);
        try
        {
            // Ensure the plate number is numeric and has exactly 5 digits
            if (plate_num.length() != 5 || stoi(plate_num) < 10000 || stoi(plate_num) > 99999)
            {
                throw invalid_argument("Invalid plate number");
            }
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid plate number. Please enter a 5-digit number." << endl;
            plate_num.clear(); // Reset to prompt again
        }
    } while (plate_num.empty());

    // Validate available seats
    do
    {
        cout << "Enter number of available seats (4, 7, 9, 16, 30): ";
        getline(cin, temp);
        try
        {
            available_seats = stoi(temp);
            // Check if the number of seats is valid
            if (available_seats != 4 && available_seats != 7 && available_seats != 9 && available_seats != 16 && available_seats != 30)
            {
                throw invalid_argument("Invalid seat count");
            }
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid input for seats. Please enter one of the following: 4, 7, 9, 16, 30." << endl;
            temp.clear(); // Reset to prompt again
        }
    } while (temp.empty());

    // Validate minimum passenger rating
    float max_rating = this->getRatingScore(); // Retrieve the current object's rating score
    float lower_limit, upper_limit;            // Variables to store the rating limits for input validation

    // Determine the valid range for minimum passenger rating based on the current rating
    // If the current rating is less than 3, allow setting the rating from 1 to (current rating + 1)
    // Otherwise, allow setting the rating from (current rating - 1) to 5
    if (max_rating < 3)
    {
        lower_limit = 1;              // Lower limit is set to 1 for ratings less than 3
        upper_limit = max_rating + 1; // Upper limit is set to the current rating plus 1
    }
    else
    {
        lower_limit = max_rating - 1; // Lower limit is set to the current rating minus 1 for ratings above 3
        upper_limit = 5;              // Upper limit is always 5 for ratings above 3
    }

    do
    {
        // Prompt the user to enter a valid minimum passenger rating within the specified range
        cout << "Enter minimum passenger rating (" << lower_limit << " to " << upper_limit << "): ";
        cin >> minimum_passenger_rating;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character to handle input properly
    } while (minimum_passenger_rating < lower_limit || minimum_passenger_rating > upper_limit);

    Carpool new_carpool(dep_choice, des_choice, depart_time, depart_date, car_model, color, plate_num, available_seats, this->getUsername(), minimum_passenger_rating, city);
    carpoollist.push_back(new_carpool);

    std::cout << "Carpool created and saved to file successfully!" << std::endl;
}

// Method to login as a driver
bool loginDriver(string &temp, Driver &driver, vector<User> &userList)
{
    string input1, input2;
    cin.ignore();
    bool loginSuccess = false;

    cout << "Enter your username: ";
    getline(cin, input1);
    cout << "Enter your password: ";
    getline(cin, input2);

    // Attempt to log in
    for (auto &i : userList)
    {
        if ((input1 == i.getUsername()) && (input2 == i.getPassword()))
        {
            // If login is successful, cast to Driver
            if (i.getisDriver())
            {
                driver = static_cast<Driver>(i); // Assuming proper copy assignment is defined
                cout << "Login successfully!\n";
                loginSuccess = true;
                break;
            }
            else
            {
                cout << "You are not a Driver.\n";
                return false;
            }
        }
    }

    if (!loginSuccess)
    {
        cout << "Failed to login!\n";
        return false; // Failed login
    }

    temp = input1;
    return true; // Driver role successful
}

// Method to update the driver's profile
void Driver::delete_list(vector<Carpool> &carpoollist)
{
    // Display the carpool list
    carpoollist[0].show_header_carpool();
    this->view_carpool_list(carpoollist);
    int input = 0;

    // Prompt the driver to enter the carID to delete
    cout << "Please enter your carID that you want to delete: ";
    cin >> input;
    int i = 0;

    // Iterate through the carpool list to find the carpool with the specified carID
    for (Carpool &acarpool : carpoollist)
    {
        if (acarpool.getDrivername() == this->getUsername()) // Check if the driver owns the carpool
        {
            if (acarpool.getPassenger().empty() && acarpool.getCarID() == input) // Check if the carpool has no passengers
            {
                carpoollist.erase(carpoollist.begin() + i);
                cout << "Deleted successfully\n";
                return;
            }
            else if (!acarpool.getPassenger().empty() && acarpool.getCarID() == input) // Check if the carpool has passengers
            {
                cout << "You can not delete this carpool because it has passengers\n";
            }
            else if (acarpool.getCarID() != input) // Check if the carID does not exist
            {
                cout << "The carID does not exist\n";
            }
        }

        i++;
    }
}

// Method to view the booking requests for the driver
void Driver::view_request(vector<Request> &requestlist, vector<Carpool> &carpool_list)
{
    int i = 0;
    requestlist[0].showrequestheader();
    for (auto &apool : carpool_list)
    {
        if (apool.getDrivername() == this->getUsername()) // Check if the driver owns the carpool
        {
            for (auto &each : apool.getRequets())
            {
                if (each.getCarID() == apool.getCarID())
                {
                    i++;
                    cout << "[" << i << "] ";
                    each.showinfo_Request();
                }
            }
        }
    }
}

// Method to accept a booking request
bool Driver::accept_booking(vector<Passenger> &passlist, vector<Carpool> &carpoollist, vector<Request> &requestlist)
{
    requestlist[0].showrequestheader();
    view_request(requestlist, carpoollist); // Display the list of booking requests

    // Prompt the driver to enter the index of the request to accept
    cout << "Enter the index of the request you want to accept: ";
    int index;
    cin >> index;

    // Iterate through the carpool list to find the request at the specified index
    int i = 0;
    for (Carpool &apool : carpoollist)
    {
        if (this->getUsername() == apool.getDrivername())
        {
            for (Request &arequest : apool.getRequets()) // Loop through the booking requests for the carpool
            {

                if (i == (index - 1)) // Check if the current request is the one to be accepted
                {
                    // Update the request status to "ACCEPTED" and remove it from the list
                    arequest.setRequestStatus("ACCEPTED");
                    for (Passenger &p : passlist)
                    {
                        if (arequest.getPassenger() == p.getUsername())
                        {
                            apool.add_Passenger(&p); // Add the passenger to the carpool
                            break;
                        }
                    }
                    apool.setAvailableSeats(apool.getAvailableSeats() - 1); // Decrement the available seats

                    // Update the global request list
                    for (auto &r : requestlist)
                    {
                        if (r.getCarID() == apool.getCarID() && r.getPassenger() == arequest.getPassenger())
                        {
                            r.setRequestStatus("ACCEPTED");
                        }
                    }

                    cout << "Booking request accepted successfully!\n";
                    return true;
                }
                i++; // Increment the index counter
            }
        }
    }

    cout << "No request found at the given index!\n";
    return false;
}

// Function to reject a booking request
bool Driver ::reject_booking(vector<Carpool> &carpoollist, vector<Request> &requestlist)
{
    requestlist[0].showrequestheader();
    view_request(requestlist, carpoollist); // Display the list of booking requests

    // Prompt the driver to enter the index of the request to reject
    cout << "Enter the index of the request you want to reject: ";
    int index;
    cin >> index;

    // Iterate through the carpool list to find the request at the specified index
    int i = 0;

    // Loop through the carpool list to find the request at the specified index
    for (Carpool &apool : carpoollist)
    {
        // cout << "Checking carpool with Driver: " << apool.getDrivername() << " and carID: " << apool.getCarID() << endl;

        if (apool.getDrivername() == this->getUsername())
        {
            // cout << "Driver matches! Username: " << this->getUsername() << endl;

            int i = 0; // Initialize the index counter for request list
            for (Request &arequest : apool.getRequets())
            {
                // cout << "Checking request from passenger: " << arequest.getPassenger()
                    //  << " with status: " << arequest.getRequestStatus() << " at index: " << i << endl;

                if (i == (index - 1)) // Check if the current request is the one to be accepted
                {
                    // cout << "Found the request at index: " << i << " to be rejected.\n";
                    // Update the request status to "REJECTED" and remove it from the list
                    arequest.setRequestStatus("REJECTED");
                    // cout << "Setting request status to REJECTED for passenger: " << arequest.getPassenger() << endl;

                    string requester = arequest.getPassenger();

                    apool.getRequets().erase(apool.getRequets().begin() + i);
                    // cout << "Removed the request from the list at index: " << i << endl;

                    // Now update the global request list
                    for (Request &r : requestlist)
                    {
                        // cout << "Checking request list for carID: " << r.getCarID()
                        //      << " and passenger: " << r.getPassenger() << endl;

                        if (r.getCarID() == apool.getCarID() && r.getPassenger() == requester)
                        {
                            // cout << "Updating status for global request list. Passenger: " << r.getPassenger() << " for carID: " << r.getCarID() << endl;
                            r.setRequestStatus("REJECTED");
                        }
                    }

                    cout << "Booking request rejected successfully!\n";
                    return true;
                }
                i++; // Increment the index counter
            }
        }
        else
        {
            cout << "Driver does not match for this carpool. Skipping.\n";
        }
    }

    cout << "No request found at the given index!\n";
    return false;
}

// Method to set the minimum rating for passengers
void Driver::set_rating(vector<Carpool> &carpool)
{
    carpool[0].show_header_carpool();
    this->view_carpool_list(carpool);
    int input;
    int set_score;

    // Prompt the driver to enter the car ID and the minimum rating
    cout << "Please enter the car ID that you want to set the minimum rating: ";
    cin >> input;

    // Iterate through the carpool list to find the carpool with the specified carID
    for (Carpool &apool : carpool)
    {
        if (apool.getCarID() == input)
        {
            cout << "Please enter the minimum rating: ";
            cin >> set_score;
            apool.setMinimumPassengerRating(set_score);
        }
    }
}

vector<Carpool> Driver::get_carpool_list()
{
    return carpool_list;
}

// Method to change the carpool status
void Driver::change_carpool_status(vector<Carpool> &carpool)
{
    int input;
    do
    {
        // Display the carpool list
        carpool[0].show_header_carpool();
        for (Carpool &apool : carpool)
        {
            if (apool.getDrivername() == this->getUsername())
            {
                apool.Show_Carpool_detail();
            }
        }

        // Prompt the driver to enter the car ID to change the status
        cout << "Please enter the car ID that you want to change the status (Press 0 to exit): ";
        cin >> input;

        // Iterate through the carpool list to find the carpool with the specified carID
        for (Carpool &apool : carpool)
        {
            // Check if the carpool is owned by the driver and the carID matches
            if (apool.getCarID() == input && apool.getisCompleted() == false && apool.getDrivername() == this->getUsername())
            {
                apool.setisCompleted();
                cout << "The trip has been completed\n";
            }
            else if (apool.getCarID() == input && apool.getisCompleted() == true && apool.getDrivername() == this->getUsername())
            {
                cout << "The trip status was completed\n";
                break;
            }
        }
    } while (input != 0);
}

// Method to rate the passenger
void Driver::rate_passenger(vector<Carpool> &carpool, vector<Passenger> &passengerlist, vector<Rating> &ratinglist)
{
    int input;
    int rate;
    string passenger;
    int i = 0;

    // Display the carpool list
    carpool[0].show_header_carpool();
    for (Carpool &apool : carpool)
    {
        if (i == 0)
            apool.show_header_carpool();

        if (apool.getDrivername() == this->getUsername() && apool.getisCompleted() == true)
        {

            apool.Show_Carpool_detail();
        }
        i++;
    }

    if (i == 0)
    {
        cout << "You have no completed trip\n";
        return;
    }

    // Prompt the driver to enter the car ID and the passenger to rate
    cout << "Please enter the car ID that you want to rate the passenger: ";
    cin >> input;

    // Iterate through the carpool list to find the carpool with the specified carID
    for (Carpool &apool : carpool)
    {
        // Check if the carpool is owned by the driver and the carID matches
        if (apool.getCarID() == input && apool.getDrivername() == this->getUsername() && apool.getisCompleted() == true)
        {
            cout << "Please enter the passenger name that you want to rate: ";
            cin >> passenger;
            cout << "Please enter the rating: ";
            cin >> rate;
            cout << "Please enter the comment: ";
            string comment;
            cin.ignore();
            getline(cin, comment);

            // Create a new rating object and add it to the rating list
            DriverRating new_rating(passenger, comment, rate);
            apool.addRating(new_rating);

            // Update the passenger's rating
            for (Passenger &p : passengerlist)
            {
                if (p.getUsername() == passenger)
                {
                    p.getRatedlist().push_back(new_rating);
                    p.calculateAverage();
                    cout << "Rating added successfully\n";
                    break;
                }
            }

            // Add the rating to the global rating list
            for (Passenger *p : apool.getPassenger())
            {
                if (p->getUsername() == passenger)
                {
                    p->getRatedlist().push_back(new_rating);
                    p->calculateAverage();
                    cout << "Rating added successfully\n";
                    break;
                }
            }

            ratinglist.push_back(new_rating); // Add the rating to the global rating list
        }
    }
}