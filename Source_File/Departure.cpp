#include "../Header_File/Departure.h"

// Initialization of location list
const std::string location[] = {
    "City center",
    "RMIT Saigon Campus",
    "Tan Son Nhat airport",
    "Ben Thanh Market",
    "War Remnants Museum",
    "Buu Dien Ha Noi",
    "RMIT Hanoi Campus",
    "Hoan Kiem Lake",
    "Old Quarter",
    "Temple of Literature"};

// Number of locations in  list
const int numLocations = sizeof(location) / sizeof(location[0]);

// Function to display the list of locations for a specific city
void showLocations(const std::string &cityName)
{
    if (cityName == "Saigon")
    {
        std::cout << "List of locations in Saigon:" << std::endl;
        for (int i = 0; i < numLocations - 5; ++i)
        {
            std::cout << "[" << (i + 1) << "]: " << location[i] << std::endl;
        }
    }
    else if (cityName == "Hanoi")
    {
        std::cout << "List of locations in Hanoi:" << std::endl;
        for (int i = 5; i < numLocations; ++i)
        {
            std::cout << "[" << (i - 4) << "]: " << location[i] << std::endl;
        }
    }
    else
    {
        std::cout << "City not found." << std::endl;
    }
}

// Function to get the location based on the index and city
string getLocation(int i, string &city)
{
    if (city == "Saigon")
    {
        return location[i - 1];
    }
    else if (city == "Hanoi")
    {
        return location[i + 4];
    }
    else
    {
        std::cout << "Location not found." << std::endl;
        return "-1";
    }
}

// Function to get the index of the departure location
int getIndexDeparture(string &somewhere)
{

    for (int i = 0; i < numLocations; ++i)
    {
        if (location[i] == somewhere)
        {
            return i;
        }
    }

    return -1;
}

// Function to get the city based on the index
string getCity(int i)
{
    if (i > 0 && i < 5)
    {
        return "Saigon";
    }
    else if (i >= 5 && i <= 9)
    {
        return "Hanoi";
    }
    else
    {
        return "Unknown";
    }
}