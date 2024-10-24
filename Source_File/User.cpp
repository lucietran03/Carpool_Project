#include "../Header_File/User.h"
#include "../Header_File/Rating.h"
using namespace std;

User::User() : username(""), password(""), fullname(""), phone(""), email(""), city(""), IDtype(0), IDnum(""), ratingscore(-1), creditpoint(0), isAdmin(false), isDriver(false), isPassenger(false), isVerified(false) {}

// Parameterized constructor
User::User(string username, string password, string fullname, string phone, string email, string city, int IDtype, string IDnum, double creditpoint)
    : username(username), password(password), fullname(fullname), phone(phone), email(email), city(city), IDtype(IDtype), IDnum(IDnum), creditpoint(creditpoint), ratingscore(-1), isAdmin(false), isDriver(false), isPassenger(false), isVerified(false) {}

// Parameterized constructor with additional attributes
User::User(string username, string password, string fullname, string phone, string email, string city, int IDtype, string IDnum, double ratingscore, double creditpoint, bool isAdmin, bool isDriver, bool isPassenger, bool isVerified)
    : username(username), password(password), fullname(fullname), phone(phone), email(email), city(city), IDtype(IDtype), IDnum(IDnum), creditpoint(creditpoint), ratingscore(ratingscore), isAdmin(isAdmin), isDriver(isDriver), isPassenger(isPassenger), isVerified(isVerified) {}

// Custom function to delete spaces from a string
void deletespace(string &str) 
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (start != std::string::npos && end != std::string::npos)
    {
        str = str.substr(start, end - start + 1);
    }
    else
    {
        str.clear();
    }
}
void User ::setisVerirified(bool verrify)
{
    isVerified = verrify;
}
bool User::getisAdmin() const
{
    return isAdmin;
}

bool User::getisDriver() const
{
    return isDriver;
}

bool User::getisPassenger() const
{
    return isPassenger;
}

bool User::getisVerified() const
{
    return isVerified;
}

float User::getRatingScore() const
{
    return ratingscore;
}
string User::getUsername() const
{
    return username;
}
string User::getPassword() const
{
    return password;
}
string User::getFullName() const
{
    return fullname;
}
string User::getPhoneNumber() const
{
    return phone;
}
string User::getEmail() const
{
    return email;
}
int User::getIDType() const
{
    return IDtype;
}
string User::getIDNumber() const
{
    return IDnum;
}
double User::getCreditPoints() const
{
    return creditpoint;
}
bool User::checkVerified() const
{
    return isVerified;
}
string User::getCity() const
{
    return city;
}

// Function to register a new user
void User::userregister(vector<User> &userList)
{
    int check = 0; // Variable to check validation status

    // Loop to validate and input the username
    do
    {
        check = 0;

        cin.ignore();
        cout << "Enter your username (no spaces inside, spaces allowed at the end): ";
        getline(cin, username);
        deletespace(username); // Custom function to delete spaces from username

        // Check if username is empty
        if (username.empty())
        {
            cout << "Username cannot be empty. Please try again.\n";
            check = 1;
        }
        else
        {
            // Loop to check if username contains any spaces
            for (char c : username)
                if (c == ' ')
                {
                    cout << "Username cannot have spaces. Please try again.\n";
                    check = 1;
                    break;
                }
        }

        // Check if the username already exists in the list
        if (check == 0)
        {
            for (auto &i : userList)
                if (i.username == username)
                {
                    check = 1;
                    cout << "Username already exists.\n";
                    break;
                }
        }

    } while (check == 1); // Repeat until a valid username is entered

    // Loop to validate and input the password
    do
    {
        
        cout << "Enter your password (8 to 16 characters, no spaces or special characters): ";
        getline(cin, password);

    } while (!passwordCheck(password)); // Repeat until a valid password is entered

    // Input and validate full name
    do
    {
        cout << "Enter your full name: ";
        getline(cin, fullname);

        if (fullname.empty())
        {
            cout << "Full name cannot be empty. Please try again.\n";
        }

    } while (fullname.empty()); // Repeat until full name is entered

    // Input and validate phone number
    do
    {
        cout << "Enter your phone number: ";
        getline(cin, phone);

        if (phone.empty())
        {
            cout << "Phone number cannot be empty. Please try again.\n";
        }

    } while (phone.empty()); // Repeat until phone number is entered

    int id_choice;

    // Select ID type: Citizen ID or Passport
    do
    {

        cout << " ID type \n";
        cout << "[1] Citizen ID\n";
        cout << "[2] Passport\n";
        cout << "Enter your choice: ";
        cin >> id_choice;
        cin.ignore(); // Ignore leftover newline character in input

        if (id_choice != 1 && id_choice != 2)
            cout << "Invalid choice. Please select 1 or 2.\n";
        else
            IDtype = id_choice;

    } while (id_choice != 1 && id_choice != 2); // Repeat until valid ID type is selected

    // Input and validate ID number or passport serial
    do
    {
        if (id_choice == 1)
            cout << "Enter your ID number: ";
        else
            cout << "Enter your passport serial: ";

        getline(cin, IDnum);

        if (IDnum.empty())
        {
            cout << "Number cannot be empty. Please try again.\n";
        }

    } while (IDnum.empty()); // Repeat until a valid ID number or passport serial is entered

    // Input and validate email
    do
    {
        check = 0;
        cout << "Enter your email: ";
        getline(cin, email);

        if (email.empty())
        {
            cout << "Email cannot be empty. Please try again.\n";
            check = 1;
        }
        // Check if email is valid (ends with @gmail.com or @yahoo.com)
        else if (email.size() <= 10 || (email.substr(email.size() - 10) != "@gmail.com" && email.substr(email.size() - 10) != "@yahoo.com"))
        {
            cout << "Your email is invalid. It must end with '@gmail.com' or '@yahoo.com'.\n";
            check = 1;
        }

    } while (check == 1); // Repeat until a valid email is entered

    int choice = 0;

    // Select city
    do
    {
        cout << " City Choosing \n";
        cout << " [1] SAI GON \n";
        cout << " [2] HA NOI \n";
        cout << " [3] Others\n";
        cout << " NOTE: This app only supports Saigon and Hanoi.";
        cout << " Enter your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        if (choice == 1)
            city = "SAI GON"; // Saigon selected
        else if (choice == 2)
            city = "HA NOI"; // Hanoi selected
        else if (choice == 3)
            city = "OTHERS"; // Unsupported city selected
        else
            cout << "Invalid choice. Please choose 1, 2, or 3.\n";

    } while (choice != 1 && choice != 2 && choice != 3); // Repeat until valid city is selected

    bool addSuccess = false;
    while (true)
    {
        cout << "Please add at least $10 for first register. Press '0' if you want to know about this cost. \n";
        cout << "Please enter the money you want to add (You can only deposit round amounts): ";
        cin >> creditpoint;
        cin.ignore(1, '\n');

        if (creditpoint >= 10)
        {
            cout << "Register successfully! You can now log in to the program\n";
            addSuccess = true;
            break;
        }
        else
        {
            int decision;
            cout << "You can only add at least 10$ to sign up for the first time! \n";
            cout << "[1] Continue; [2] See you\n";
            cin >> decision;
            cin.ignore();
            if (decision == 1)
                cout << "Please do as the instruction\n";
            else
            {
                cout << "Thank you for your time! See you again! \n";
                break;
            }
        }
    }
    cout << "Registered successfully!" << "\n\n"; // Registration success message

    User new_user(username, password, fullname, phone, email, city, IDtype, IDnum, creditpoint);
    do
    {
        cout << "TYPE OF USER\n";
        cout << "[1] Admin\n";
        cout << "[2] Passenger\n";
        cout << "[3] Driver\n";
        cout << "[4] Passenger & Driver\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        switch (choice)
        {
        case 1:
            cout << "Enter admin registration confirmation code: ";
            int admincode;
            if (ADMIN_CODE == admincode)
            {
                cout << "You are registered as admin.\n";
                new_user.isAdmin = true;
                new_user.isVerified = true;
            }
            break;

        case 2:
            new_user.isPassenger = true;
            break;

        case 3:
            new_user.isDriver = true;
            break;

        case 4:
            new_user.isPassenger = true;
            new_user.isDriver = true;
            break;

        default:
            cout << "Please choose valid number from our menu!\n";
        }

    } while (choice < 1 || choice > 4);
    userList.push_back(new_user);
}

// Password checking for new user registering:
bool User::passwordCheck(string password)
{
    int upperIncluded = 0;

    // Check if password is empty
    if (password.empty())
    {
        cout << "\nPassword cannot be empty. Please try again.\n";
        return false;
    }
    // Check if password length is less than 8 or greater than 16
    else if (password.length() < 8 || password.length() > 16)
    {
        cout << "Password must be between 8 and 16 characters long. Please try again.\n";
        return false;
    }
    else
    {
        // Check if password contains spaces
        for (char c : password)
        {
            if (c == ' ')
            {
                cout << "Password cannot have spaces. Please try again.\n";
                return false;
            }
            else if(!isalpha(c))
            {
                cout << "Password cannot contain any special characters. Please try again.\n";
                return false;
            }
            else if(isupper(c))
            {
                upperIncluded = 1;
            }
        }
    }

    if(!upperIncluded)
    {
        cout << "Password must contain at least 1 upper character. Please try again.\n";
        return false; // No upper letter included 
    }

    return true;
}

// Function to log in
void User::viewheader()
{
    cout << left << setw(15) << "Name"
         << setw(15) << "Phone"
         << setw(20) << "Email"
         << setw(10) << "Type"
         << setw(15) << "ID/Passport"
         << setw(15) << "City"
         << setw(15) << "Credit Points"
         << setw(15) << "Rating Score" << '\n';
    cout << string(120, '-') << '\n'; // Separator line
}

// Function to view all users
void User::viewprofile()
{
    cout << left << setw(15) << "Name:" << this->fullname << '\n';
    cout << left << setw(15) << "Numberphone:" << this->phone << '\n';
    cout << left << setw(15) << "Email:" << this->email << '\n';
    cout << left << setw(15) << "Type:" << this->IDtype << '\n';
    if (this->IDtype == 1)
        cout << left << setw(15) << "ID:" << this->IDnum << '\n';
    else
        cout << left << setw(15) << "Passport:" << this->IDnum << '\n';
    cout << left << setw(15) << "City:" << this->city << '\n';
    cout << left << setw(15) << "Creditpoint:" << this->creditpoint << '\n';
    cout << left << setw(15) << "Rating score:" << this->ratingscore << '\n';
}

// Function to update user profile
void User::updateprofile()
{
    int choice;
    cout << "|=====================|\n";
    cout << "|        UPDATE       |\n";
    cout << "|=====================|\n";

    cout << "|1.Your name.         |\n|2.Your phone number.  |\n|3.Your email.        |\n";
    if (IDtype == 1)
        cout << "|4.Your ID.           |\n|5.Your address.       |\n|6.Your password.     |\n";
    else
        cout << "|4.Your passport.     |\n|5.Your address.       |\n|6.Your password.     | \n";
    cout << "-----------------------";
    cout << "\nWhat do you want to update.";

    cout << "Enter your choice(1-6): ";
    cin >> choice;
    cin.ignore(1, '\n');

    switch (choice)
    {
    case 1:
    {
        cin.ignore();
        do
        {
            cout << "Enter your full name: ";
            getline(cin, fullname);

            if (fullname.empty())
                cout << "Full name cannot be empty. Please try again.\n";

        } while (fullname.empty()); // Repeat until full name is entered

        cout << "Your new name: " << fullname << endl
             << endl;
        break;
    }
    case 2:
        cin.ignore();
        do
        {
            cout << "Enter your phone number: ";
            getline(cin, phone);

            if (phone.empty())
            {
                cout << "Phone number cannot be empty. Please try again.\n";
            }

        } while (phone.empty()); // Repeat until phone number is entered
        cout << "Your new numberphone: " << phone << endl
             << endl;
        break;

    case 3:
    {
        cin.ignore();
        int check1 = 0;
        do
        {
            check1 = 0;
            cout << "Enter your email: ";
            getline(cin, email);

            if (email.empty())
            {
                cout << "Email cannot be empty. Please try again.\n";
                check1 = 1;
            }
            // Check if email is valid (ends with @gmail.com or @yahoo.com)
            else if (email.size() <= 10 || (email.substr(email.size() - 10) != "@gmail.com" && email.substr(email.size() - 10) != "@yahoo.com"))
            {
                cout << "Your email is invalid. It must end with '@gmail.com' or '@yahoo.com'.\n";
                check1 = 1;
            }

        } while (check1 == 1); // Repeat until a valid email is entered
        cout << "Your new email: " << email << endl
             << endl;
        break;
    }

    case 4:
        cout << " ID type \n";
        cout << "[1] Citizen ID\n";
        cout << "[2] Passport\n";
        cout << "Enter your choice: ";
        cin >> IDtype;
        cin.ignore(); // Ignore leftover newline character in input
        if (IDtype == 1)
            cout << "Enter your new ID: ";
        else
            cout << "Enter your new passport serial: ";
        getline(cin, IDnum);
        cout << "Your new ID: " << IDtype << ", series: " << IDnum;
        break;

    case 5:
        cin.ignore();
        do
        {
            choice = 0;
            cout << " City Choosing \n";
            cout << " [1] SAI GON \n";
            cout << " [2] HA NOI \n";
            cout << " [3] Others\n";
            cout << " NOTE: This app only supports Saigon and Hanoi.";
            cout << " Enter your choice: ";
            cin >> choice;
            cin.ignore(1, '\n');

            if (choice == 1)
                city = "SAI GON"; // Saigon selected
            else if (choice == 2)
                city = "HA NOI"; // Hanoi selected
            else if (choice == 3)
                city = "OTHERS"; // Unsupported city selected
            else
                cout << "Invalid choice. Please choose 1, 2, or 3.\n";

        } while (choice != 1 && choice != 2 && choice != 3); // Repeat until valid city is selected

        cout << "Your new city: " << city << endl
             << endl;
        break;

    case 6:
        cin.ignore();
        changepassword();
        cout << "Change password successfully";
        break;
    default:
        cout << "Please Enter another choice. \n\n";
        break;
    }
}

// Function to change password
void User::changepassword()
{
    int choice = 0;
    string temp;

    do
    {
        choice = 0;
        cout << "Enter your new password (no spaces): ";
        getline(cin, temp);
        deletespace(temp);

        // Check if password is empty
        if (temp.empty())
        {
            cout << "\nPassword cannot be empty. Please try again.\n";
            choice = 1;
        }
        // Check if password length is less than 8 or greater than 16
        else if (temp.length() < 8 || temp.length() > 16)
        {
            cout << "Password must be between 8 and 16 characters long. Please try again.\n";
            choice = 1;
        }
        else
        {
            // Check if password contains spaces
            for (char c : temp)
            {
                if (c == ' ')
                {
                    cout << "Password cannot have spaces. Please try again.\n";
                    choice = 1;
                    break;
                }
            }
        }
    } while (choice == 1);

    this->password = temp;
}
void User ::setCredit(double amount)
{
    this->creditpoint = this->creditpoint - amount;
}

// Function to purchase credit points
void User::purchaseCreditPoints(double amount)
{
    if (amount > 0)
        creditpoint += amount;
    else
        cout << "Can not purchase because point is not more 0 \n";
}

// Function to log in
bool login(string &temp, User &user, vector<User> &userList, int role)
{
    

    string input1;
    cin.ignore();
    bool loginSuccess = false;

    cout << "Enter your username: ";
    getline(cin, input1);

    // Enable password hiding
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string input2;
    cout << "Enter your password: ";
    getline(cin, input2);

    // Reset terminal state and cleans up
    SetConsoleMode(hStdin, mode);

    // Attempt to log in
    for (auto &i : userList)
    {
        if ((input1 == i.getUsername()) && (input2 == i.getPassword()))
        {
            user = i;
            cout << "Login successfully!\n";
            loginSuccess = true;
            break;
        }
    }

    if (!loginSuccess)
    {
        cout << "Failed to login!\n";
        return false; // Failed login
    }

    temp = input1;
    // Check if the logged-in user matches the role
    switch (role)
    {
    case 1: // Admin
        if (user.getisAdmin())
        {
            cout << "Enter admin registration confirmation code: ";
            int admincode;
            cin >> admincode;
            cin.ignore(1, '\n');

            if (admincode == ADMIN_CODE && user.getisAdmin())
            {
                cout << "You are logged in as Admin.\n";
                return true; // Admin role successful
            }
            else
            {
                cout << "Failed to log in as Admin.\n";
                return false;
            }
        }
        else
        {
            cout << "You are not an Admin.\n";
            return false;
        }
        break;

    case 2: // Passenger
        if (user.getisPassenger())
        {
            cout << "You are logged in as Passenger.\n";
            return true; // Passenger role successful
        }
        else
        {
            cout << "You are not a Passenger.\n";
            return false;
        }
        break;

    case 3: // Driver
        if (user.getisDriver())
        {
            cout << "You are logged in as Driver.\n";
            return true; // Driver role successful
        }
        else
        {
            cout << "You are not a Driver.\n";
            return false;
        }
        break;

    default:
        cout << "Invalid role selected.\n";
        return false;
    }

    return false; // Default return in case no role is selected
}

void User ::setRating(double r)
{
    this->ratingscore = r;
}

vector<Rating> User ::getRatedlist()
{
    return rated_list;
}

// Function to calculate average rating
void User ::calculateAverage()
{
    double sum, ave;
    int index;
    for (Rating &rating : this->getRatedlist())
    {
        sum += rating.getScore();
        index++;
    }
    ave = sum / index;
    this->setRating(ave);
}

void User::set_rating(Rating &a_rating)
{
    rated_list.push_back(a_rating);
}

// Function to convert user data to string
string User::to_stringUser()
{
    return this->username + "," +
           this->password + "," +
           this->fullname + "," +
           this->phone + "," +
           this->email + "," +
           this->city + "," +
           to_string(this->IDtype) + "," +
           this->IDnum + "," +
           to_string(this->ratingscore) + "," +
           to_string(this->creditpoint) + "," +
           to_string(this->isAdmin) + "," +
           to_string(this->isDriver) + "," +
           to_string(this->isPassenger) + "," +
           to_string(this->isVerified) + "\n";
}