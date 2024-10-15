#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User
{
public:
    Admin();
    void verrified_user(vector <User> &user_list);
    void view_all_user(vector<User> &userList);
    void view_all_carpool(vector<Carpool> &carpool_list);

    friend class Passenger;
    friend class Driver;
};

#endif