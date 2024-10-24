// Main-program here
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <regex>
#include <limits>
#include "../Header_File/User.h"
#include "../Header_File/Carpooling.h"
#include "../Header_File/Rating.h"
#include "../Header_File/File.h"
#include "../Header_File/Admin.h"
#include "../Header_File/Passenger.h"
#include "../Header_File/Driver.h"
#include "../Header_File/Request.h"
#include "../Header_File/Departure.h"

using namespace std;

void Nonmem_dashboad(vector<User> &userlist, vector<Carpool> &Carpool_list);
void Admin_dashboad(Admin &admin, vector<User> &userlist, vector<Carpool> &carpool_list);
void Passenger_dashboad(string &temp, vector<Passenger> &passList, vector<Carpool> &carpool_list, vector<Request> &requests, vector<Rating> &rating_list);
void Driver_dashboad(string &temp, vector<Driver> &driverList, vector<Carpool> &carpool_list, vector<Request> &requests, vector<Passenger> &passlist, vector<Rating> &rating_list);
void view_carpool(vector<Carpool> &Carpool_list);

int main()
{
    // Create objects for each class
    Admin admin;
    User user;
    Passenger passenger;
    Driver driver;
    FileSaving fileSave;
    string temp;

    // Load Rating data from file
    vector<DriverRating> driver_rate;                               // Create vector to store DriverRating objects (driver rate passenger)
    vector<PassengerRating> passenger_rate;                         // Create vector to store PassengerRating objects (passenger rate driver)
    vector<Rating> rating_list;                                     // Create vector to store PassengerRating objects (passenger rate driver)
    rating_list = fileSave.loadRating(driver_rate, passenger_rate); // Load Rating data from file

    // Load Request data from file
    vector<Request> requests = fileSave.loadRequest();

    // Load Carpool data from file
    vector<Carpool> carpool_list = fileSave.loadCarpool(requests, passenger_rate);

    // Load User data from file, and divide the data into 3 vectors: userList, driverList, and passengerList
    vector<Driver> driverList;
    vector<Passenger> passengerlist;
    vector<User> userList;
    userList = fileSave.loadUser(userList, driverList, passengerlist, driver_rate, requests, carpool_list);

    // Display the program information
    cout << "EEET2482/EEET2653 ASSIGNMENT" << '\n';
    cout << "CARPOOLING APPLICATION" << "\n\n";
    cout << "Instructor: Dr Ling Huo Chong, Dr Jeff Nijsse" << '\n';
    cout << "Group: 3" << '\n'
         << '\n';

    // Display the student information
    cout << "s3914633 - Tran Dong Nghi" << '\n';
    cout << "s4012480 - Tran Tin Dat" << '\n';
    cout << "s4010228 - Nguyen Dinh Khoi" << '\n';
    cout << "s3978554 - To Bao Minh Hoang" << '\n';
    cout << "s3980490 - Nguyen Thanh Long" << "\n\n\n";

    // Display the main menu
    int input = 0;
    do
    {
        cout << "\n\n";
        cout << "|======================|\n";
        cout << "|     LOGIN OPTIONS    |\n";
        cout << "|     [1] Guest        |\n";
        cout << "|     [2] Admin        |\n";
        cout << "|     [3] Passenger    |\n";
        cout << "|     [4] Driver       |\n";
        cout << "|     [0] Exit         |\n";
        cout << "|======================|\n";

        cout << "Enter your choice: ";
        cin >> input;
        cin.ignore(1, '\n');

        switch (input)
        {
        case 1:
            Nonmem_dashboad(userList, carpool_list); // Display the dashboard for non-members
            break;
        case 2:
            if (login(temp, user, userList, 1)) // Login as admin
                Admin_dashboad(admin, userList, carpool_list);
            break;
        case 3:
            if (loginPassenger(temp, passenger, userList)) // Login as passenger
                Passenger_dashboad(temp, passengerlist, carpool_list, requests, rating_list);
            break;
        case 4:
            if (loginDriver(temp, driver, userList)) // Login as driver
                Driver_dashboad(temp, driverList, carpool_list, requests, passengerlist, rating_list);
            break;
        case 0:
            cout << "Thank you for using the app, Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (input != 0);

    fileSave.saveCarpool(carpool_list);               // Save Carpool data to file
    fileSave.saveRequest(requests);                   // Save Request data to file
    fileSave.saveRating(passenger_rate, driver_rate); // Save Rating data to file
    fileSave.saveUser(userList);                      // Save User data to file
    return 0;
}

// Function to view carpool with average rating less than or equal to 3
void view_carpool(vector<Carpool> &Carpool_list)
{
    double sum = 0;
    int index = 0;
    double ave;
    for (Carpool &acar : Carpool_list)
    {
        for (Rating &arate : acar.getlistRatingg())
        {
            sum += arate.getScore();
            index++;
        }
        ave = sum / index;
        if (ave <= 3 && acar.getAvailableSeats() != 0) // Display carpool with average rating less than or equal to 3
        {
            acar.Show_Carpool_detail();
        }
        sum = 0;
        index = 0;
    }
}

// Function to display the dashboard for non-members
void Nonmem_dashboad(vector<User> &userlist, vector<Carpool> &Carpool_list)
{
    User user;
    int input = 0;
    do
    {
        cout << "\n\n";
        // Display the dashboard for non-members
        cout << "|=======================|\n";
        cout << "|    GUEST DASHBOARD    |\n";
        cout << "|   [1] View Carpool    |\n";
        cout << "|   [2] Register        |\n";
        cout << "|   [0] Exit            |\n";
        cout << "|=======================|\n";

        cout << "Enter your choice: ";
        cin >> input;
        cin.ignore(1, '\n');

        switch (input)
        {
        case 1:
            cout << "Here are the available carpools:\n";
            view_carpool(Carpool_list); // Display carpool with average rating less than or equal to 3
            break;
        case 2:
            user.userregister(userlist); // Register as a user
            break;
        case 0:
            cout << "Exiting Guest Dashboard...\n";
            break;
        default:
            cout << "Please select from the menu!\n";
        }
    } while (input != 0);
}

// Function to display the admin dashboard
void Admin_dashboad(Admin &admin, vector<User> &userlist, vector<Carpool> &carpool_list)
{
    int choice = 0;

    do
    {
        cout << "\n\n";
        // Display the admin dashboard
        cout << "|==============================|\n";
        cout << "|       ADMIN DASHBOARD        |\n";
        cout << "|      [1] View all user       |\n";
        cout << "|      [2] View all carpool    |\n";
        cout << "|      [0] Exit                |\n";
        cout << "|==============================|\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        switch (choice)
        {
        case 1:
            admin.view_all_user(userlist); // Display all users
            break;
        case 2:
            admin.view_all_carpool(carpool_list); // Display all carpools
            break;
        case 0:
            cout << "Exiting Admin Dashboard...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Function to display the passenger dashboard
void Passenger_dashboad(string &temp, vector<Passenger> &passList, vector<Carpool> &carpool_list, vector<Request> &requests, vector<Rating> &rating_list)
{
    int input = 0;
    double amount;
    int index = 0;

    // Find the index of the passenger in the passenger list
    for (auto &apassenger : passList)
    {
        if (apassenger.getUsername() == temp)
        {
            break;
        }
        index++;
    }

    do
    {
        cout << "\n\n";
        // Display the user dashboard
        cout << "|=================================================|\n";
        cout << "|               PASSENGER DASHBOARD               |\n";
        cout << "|  [1] View Profile          [2] Update Profile   |\n";
        cout << "|  [3] Change Password       [4] Purchase Credit  |\n";
        cout << "|  [5] Search & Book Carpool [6] Cancel Booking   |\n";
        cout << "|  [7] View All Requests     [8] Rating Carpool   |\n";
        cout << "|  [0] Exit                                       |\n";
        cout << "|=================================================|\n";
        cout << "Enter your choice: ";
        cin >> input;
        cin.ignore(1, '\n');

        switch (input)
        {
        case 1:
            passList[index].viewprofile(); // View user profile
            break;
        case 2:
            passList[index].updateprofile(); // Update user profile
            break;
        case 3:
            passList[index].changepassword(); // Change user password
            break;
        case 4: // Purchase credit
            cout << "Enter the amount you want to purchase: ";
            cin >> amount;
            cin.ignore(1, '\n');
            passList[index].purchaseCreditPoints(amount);
            break;
        case 5:
            passList[index].book_carpool(carpool_list, requests); // Book carpool
            break;
        case 6:
            passList[index].cancel_carpool(carpool_list, requests); // Cancel carpool
            break;
        case 7:
            passList[index].view_all_request(requests); // View all requests
            break;
        case 8:
            passList[index].rating_carpool(carpool_list, rating_list); // Rate carpool
            break;
        case 0:
            cout << "Exiting Passenger Dashboard...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (input != 0);
}

// Function to display the driver dashboard
void Driver_dashboad(string &temp, vector<Driver> &driverList, vector<Carpool> &carpool_list, vector<Request> &requests, vector<Passenger> &passlist, vector<Rating> &rating_list)
{
    // Display the driver dashboard
    int input = 0;
    double amount;
    int index = 0;

    // Find the index of the driver in the driver list
    for (auto &adriver : driverList)
    {
        if (adriver.getUsername() == temp)
        {
            break;
        }
        index++;
    }
    do
    {
        cout << "\n\n";
        cout << "|=================================================|\n";
        cout << "|                DRIVER DASHBOARD                 |\n";
        cout << "|  [1] View Profile          [2] Update Profile   |\n";
        cout << "|  [3] Change Password       [4] Purchase Credit  |\n";
        cout << "|  [5] Create Carpool        [6] Unlist Carpool   |\n";
        cout << "|  [7] View All Carpools     [8] View All Requests|\n";
        cout << "|  [9] Change Carpool Status [10] Accept_booking  |\n";
        cout << "|  [11] Reject_booking       [12] Rating Passenger|\n";
        cout << "|  [0] Exit                                       |\n";
        cout << "|=================================================|\n";

        cout << "Enter your choice: ";
        cin >> input;
        cin.ignore(1, '\n');

        switch (input)
        {
        case 1:
            driverList[index].viewprofile(); // View user profile
            break;
        case 2:
            driverList[index].updateprofile(); // Update user profile
            break;
        case 3:
            driverList[index].changepassword(); // Change user password
            break;
        case 4:
            cout << "Enter the amount you want to purchase: ";
            cin >> amount;
            cin.ignore(1, '\n');
            driverList[index].purchaseCreditPoints(amount); // Purchase credit
            break;
        case 5:
            driverList[index].create_carpool_list(carpool_list); // Add carpool
            break;
        case 6:
            driverList[index].delete_list(carpool_list); // Unlist carpool
            break;
        case 7:
            driverList[index].view_carpool_list(carpool_list); // View all carpools
            break;
        case 8:
            driverList[index].view_request(requests, carpool_list); // View all requests
            break;
        case 9:
            driverList[index].change_carpool_status(carpool_list); // Change carpool status
            break;
        case 10:
            driverList[index].accept_booking(passlist, carpool_list, requests); // Accept booking
            break;
        case 11:
            driverList[index].reject_booking(carpool_list, requests); // Reject booking
            break;
        case 12:
            driverList[index].rate_passenger(carpool_list, passlist, rating_list); // Rate passenger
            break;
        case 0:
            cout << "Exiting driver dashboard...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (input != 0);
}
