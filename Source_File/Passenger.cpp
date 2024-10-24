#include "../Header_File/User.h"
#include "../Header_File/Passenger.h"
#include "../Header_File/Carpooling.h"
#include "../Header_File/Request.h"
#include "../Header_File/Departure.h"

// Passenger ::Passenger()
// {
//     this->isPassenger = true;
// }
// Passenger ::Passenger(User user) : User(user)
// {
//     this->isPassenger = true;
// }
vector<Request> Passenger::get_request_list() const
{
    return request_list;
}
bool Passenger::book_carpool(vector<Carpool> &carpools, vector<Request> &requests)
{
    int Id;
    string city_name;
    int i = 0;

    carpools[0].show_header_carpool();

    for (auto &acarpool : carpools)
    {
        string dest = acarpool.getDestinationLocation();
        int city = getIndexDeparture(dest);
        if (city < 5)
        {
            city_name = "Saigon";
        }
        else
        {
            city_name = "Hanoi";
        }
        if (acarpool.getAvailableSeats() > 0 && this->getCity() == city_name && this->creditpoint >= acarpool.getMinimumPassengerRating())
        {
            cout << '[' << i + 1 << "] ";
            acarpool.Show_Carpool_detail();
            i++;
        }
    }

    city_name = this->getCity();

    bool check = false;

    do
    {
        cout << "Enter the carID (Press 0 to exit): ";
        cin >> Id;
        cin.ignore(1, '\n');

        if (Id == 0)
        {
            return false;
            // Out
        }
        check = true;
        for (auto &arequest : requests)
        {
            if (arequest.getCarID() == Id && this->getUsername() == arequest.getPassenger() && (arequest.getRequestStatus() == "ACCEPTED" || arequest.getRequestStatus() == "PENDING"))
            {
                cout << "You can not book this car. Because you may already successfully book it.";
                check = false;
                // Out
                break;
            }
        }
    } while (check == false);

    Request request(Id, this->getUsername());

    for (auto &acarpool : carpools)
    {
        if (acarpool.getCarID() == Id && acarpool.getAvailableSeats() > 0 && this->getCity() == city_name && this->getRatingScore() >= acarpool.getMinimumPassengerRating())
        {
            // Add the request to the list of requests
            acarpool.getRequets().push_back(request);
            this->request_list.push_back(request);
            requests.push_back(request);

            // Announce the booking request
            std::cout << "Your request has been sent to the driver. Please wait for the driver to accept your request.\n";

            this->setCredit(acarpool.getContributionAmount() / (acarpool.getPassenger().size() + 1)); // Update the credit points

            // Print the updated credit points
            cout << "You have transact " << acarpool.getContributionAmount() / (acarpool.getPassenger().size() + 1) << " to pay for your carpool" << endl;
            cout << "Your account's credit amount: " << this->getCreditPoints() << endl;
            return true;
        }
    }

    cout << "There is no suitable car for you to book. Thank you!\n";
    return false;
}

void Passenger::view_all_request(vector<Request> &requestlist)
{
    requestlist[0].showrequestheader();
    for (int i = 0; i < requestlist.size(); i++)
    {
        if (this->getUsername() == requestlist[i].getPassenger())
        {
            cout << '[' << i + 1 << "] ";
            requestlist[i].showinfo_Request();
        }
    }
}
bool Passenger::cancel_carpool(vector<Carpool> &carpools, vector<Request> &requests)
{
    // Show all the carpool requests booked by the passenger
    requests[0].showrequestheader();
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i].getPassenger() == this->getUsername() && requests[i].getRequestStatus() == "PENDING")
        {
            cout << '[' << i + 1 << "] ";
            requests[i].showinfo_Request();
        }
    }

    // Prompt the passenger to enter the carID to cancel
    int ID;
    cout << "Enter your booked carID (0 for cancel): ";
    while (!(cin >> ID))
    {
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Enter a valid carID (0 for cancel): ";
    }

    // Handle cancelation
    if (ID == 0)
    {
        cout << "Cancel booking request failed!\n";
        return false;
    }

    // Remove the request from the passenger's request list
    bool requestFound = false;
    for (auto it = requests.begin(); it != requests.end();)
    {
        if (it->getCarID() == ID && it->getPassenger() == this->getUsername() && it->getRequestStatus() == "PENDING")
        {
            it = requests.erase(it);
            this->request_list.erase(remove_if(this->request_list.begin(), this->request_list.end(),
                                               [ID, this](Request &r)
                                               {
                                                   return r.getCarID() == ID && r.getPassenger() == this->getUsername() && r.getRequestStatus() == "PENDING";
                                               }),
                                     this->request_list.end());
            requestFound = true;
            break;
        }
        else
        {
            ++it;
        }
    }

    // Remove the request from the carpool's request list
    if (requestFound)
    {
        for (auto &acarpool : carpools)
        {
            // Debugging: Print carpool details
            // cout << "Debug: Checking carpool with CarID: " << acarpool.getCarID() << endl;

            bool found = false;
            for (auto it = acarpool.getRequets().begin(); it != acarpool.getRequets().end();)
            {
                if (it->getCarID() == ID && it->getPassenger() == this->getUsername() && it->getRequestStatus() == "PENDING")
                {
                    it = acarpool.getRequets().erase(it);
                    cout << "Your carpool booking request is canceled" << endl;
                    return true;
                }
                else
                {
                    ++it;
                }
            }
        }
        cout << "Your request is not found or it is already accepted by the driver" << endl;
    }
    else
    {
        cout << "Your request is not found or it is already accepted by the driver" << endl;
    }
    return false;
}

bool loginPassenger(string &temp, Passenger &passenger, vector<User> &userList)
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
            // If login is successful, cast to Passenger
            if (i.getisPassenger())
            {
                passenger = static_cast<Passenger>(i); // Assuming proper copy assignment is defined
                cout << "Login successfully!\n";
                loginSuccess = true;
                break;
            }
            else
            {
                cout << "You are not a Passenger.\n";
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
    return true; // Passenger role successful
}

// Method to update the passenger's profile
void Passenger::rating_carpool(vector<Carpool> &carpool_list, vector<Rating> &rating_list)
{
    int carID;
    int rating;
    cout << "Enter the carID you want to rate: ";
    cin >> carID;
    cout << "Enter the rating score (1-5): ";
    cin >> rating;
    cout << "Enter your comment: ";
    string comment;
    cin.ignore();
    getline(cin, comment);

    PassengerRating rate(carID, comment, rating); // Create a new rating object
    rating_list.push_back(rate);

    for (auto &acarpool : carpool_list) // Add the rating to the carpool
    {
        if (acarpool.getCarID() == carID && acarpool.getisCompleted())
        {
            acarpool.getlistRatingg().push_back(rate);
            cout << "Rating successful!\n";
            return;
        }
    }

    cout << "CarID not found. Rating failed!\n"; // CarID not found
}