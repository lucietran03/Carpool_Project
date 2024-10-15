#ifndef DEPARTURE_H
#define DEPARTURE_H

#include <string>
#include <iostream>

using namespace std;

// Define the location arrays and their sizes
extern const std::string location[];
extern const int numSaigonLocations;

// Function to display the list of locations for a specific city
void showLocations(const std::string& cityName);

string getLocation(int i, string &city);
int getIndexDeparture(string &location);
string getCity(int i);

#endif // DEPARTURE_H
