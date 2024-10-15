#include "../Header_File/User.h"
#include "../Header_File/Rating.h" 
#include "../Header_File/Carpooling.h"
#include "../Header_File/Request.h"
#include "../Header_File/Passenger.h"
using namespace std;

Rating::Rating(string comment, double score) : comment(comment), score(score) {}

void Rating::setScore(double score) {this->score = score;}
void Rating::setComment(string comment) {this->comment = comment;}
double Rating :: getScore() const{
    return score;
}

DriverRating::DriverRating(string username, string comment, double score)
    : Rating(comment, score), username(username) {}
string DriverRating::getusername() { return username; }

void DriverRating::submit_rating(Carpool &acarpool) // Call this one when status of carpool is done
{
    for (auto &passenger : acarpool.getPassenger())
    {
        cout << "Rating for passenger '" << passenger->getUsername() << "': ";
        cout << "Score: ";
        double score_draft;
        cin >> score_draft;
        cout << "Comment: ";
        string comment_draft;
        cin.ignore();
        getline(cin, comment_draft);
        DriverRating rating(passenger->getUsername(), comment_draft, score_draft);
        passenger->set_rating(rating); // Set rating for passenger
    }
}

PassengerRating::PassengerRating(int carID, string comment, double score)
    : Rating(comment, score), carID(carID) {}

int PassengerRating::getCarID() { return carID; }

void PassengerRating::submit_rating(Carpool &acarpool) // Call this one when status of carpool is done
{
    cout << "Rating for car with ID(" << to_string(acarpool.getCarID()) << "): ";
    cout << "Score: ";
    double score_draft;
    cin >> score_draft;
    cout << "Comment: ";
    string comment_draft;
    cin.ignore();
    getline(cin, comment_draft);
    PassengerRating rating(acarpool.getCarID(), comment_draft, score_draft);
    acarpool.addRating(rating); // Set rating for carpool
} 

string DriverRating::to_stringDriverRating()  // Convert to string
{
    return this->getusername() + "," + this->getComment() + ',' + to_string(this->getScore()) + "\n";
} 

string PassengerRating::to_stringPassengerRating()  // Convert to string
{
    return to_string(this->getCarID()) + "," + this->getComment() + ',' + to_string(this->getScore()) + "\n";
}

string Rating::getComment() const
{
    return comment;
}

void DriverRating::showheader_DriverRating() // Show header
{
    cout << left << setw(15) << "Username" << left << setw(15) << "Score" << left << setw(15) << "Comment" << endl;
    cout << string(50, '-') << endl; // Header line
}

void PassengerRating::showheader_PassengerRating() // Show header
{
    cout << left << setw(15) << "Car ID" << left << setw(15) << "Score" << left << setw(15) << "Comment" << endl;
    cout << string(50, '-') << endl; // Header line
}

// Show info
void DriverRating::showinfo_DriverRating()
{
    cout << this->getusername() << this->getScore() << this->getComment() << endl;
}

// Show info
void PassengerRating::showinfo_PassengerRating()
{
    cout << this->getCarID() << this->getScore() << this->getComment() << endl;
}