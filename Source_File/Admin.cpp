#include "../Header_File/User.h"
#include "../Header_File/Admin.h"
#include "../Header_File/Rating.h"
#include "../Header_File/Carpooling.h"

Admin::Admin() {} // Default constructor

// Function to verify user
void Admin ::verrified_user(vector<User> &user_list)
{
    string name;
    for (User &user : user_list)
    {
        if (user.getisVerified() == false)
        {
            user.viewprofile();
        }
    }
    do
    {
        cout << "Please enter username you want to verify (Press 0 to exit): ";
        getline(cin, name);
        cout << endl;
        for (User &user : user_list)
        {
            if (name == user.getUsername())
            {
                user.setisVerirified(true);
                cout << "You have verrified " << user.getUsername() << endl;
            }
        }
    } while (name != "0");
}

// Function to view all users
void Admin::view_all_user(vector<User> &userList)
{
    this->viewheader();

    for (auto &i : userList)
    {
        i.viewprofile();
    }
}

// Function to view all carpool
void Admin::view_all_carpool(vector<Carpool> &carpool_list)
{
    carpool_list[0].show_header_carpool();

    for (auto &acarpool : carpool_list)
    {
        acarpool.Show_Carpool_detail();
    }
}
