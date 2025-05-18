#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<unordered_map>
#include"Time.h"

using namespace std;

class Paddle
{
    struct Slot
    {
        string time;
        int slotID;
        bool isBooked;
        int bookingID;
    };
    struct Court
    {
        int courtID;
        string type;
        unordered_map<string, vector<Slot>> datesOfbooking;
    };
    static int allBookings;
    int bookingID = 0;
    unordered_map<int, Slot*> bookingRegistry;
public:
    struct Location
    {
        string name;
        int locID;
        vector<Court> courts;
    };
    vector<Location> locations;
    vector<Location> initializer(vector<Location>& locations);
    void bookingCourt(vector<Location>& locations, bool isVIP);
    void cancelBookingByID(int bookingID, bool isVIP);

private:
    bool isSlotAvailable(Slot);
    void displaySlot(Slot);
    bool isDateValid(int day, int month, int year, bool isVIP);
    int countAvailableSlots(Court c, string);
    void displayConfirmation(string, string, string, string, int);
    void displayAvailableSlots(vector<Slot> slots);
    /*void menu(Paddle& paddle, vector<Paddle::Location>& locations);*/
};
