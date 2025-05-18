// Paddle.cpp
#include "Paddle.h"

int Paddle::allBookings = 0;

Time t;
int nowDay = t.getDay();
int nowMonth = t.getMonth();
int nowYear = t.getYear();
int nowHour = t.getHour();
vector<Paddle::Location> Paddle::initializer(vector<Location>& locations)
{
    for (int locIndex = 0; locIndex < 2; locIndex++)
    {
        Location l;
        l.locID = locIndex + 1;
        l.name = (locIndex == 0 ? "Tagamoa" : "Almaza");
        for (int courtIndex = 0; courtIndex < 2; courtIndex++)
        {
            Court c;
            c.courtID = courtIndex + 1;
            c.type = (courtIndex == 0 ? "indoors" : "outdoors");
            for (int dayIndex = 0; dayIndex < 7; dayIndex++)
            {
                tm temp = {};
                temp.tm_year = nowYear - 1900;
                temp.tm_mon = nowMonth - 1;
                temp.tm_mday = nowDay + dayIndex;
                mktime(&temp);

                string keyDate = (temp.tm_mday < 10 ? "0" : "") + to_string(temp.tm_mday) + "-" +
                    (temp.tm_mon + 1 < 10 ? "0" : "") + to_string(temp.tm_mon + 1) + "-" +
                    to_string(temp.tm_year + 1900);

                vector<Slot> slots;
                int start = 10, end = 12;
                for (int slotIndex = 0; slotIndex < 8; slotIndex++)
                {
                    Slot s;
                    s.isBooked = false;
                    s.bookingID = -1;
                    s.slotID = slotIndex + 1;
                    if (start != 24)
                        start %= 24;
                    if (end != 24)
                        end %= 24;
                    s.time = to_string(start) + ":00 - " + to_string(end) + ":00";
                    start = end;
                    end += 2;
                    slots.push_back(s);
                }
                c.datesOfbooking[keyDate] = slots;
            }
            l.courts.push_back(c);
        }
        locations.push_back(l);
    }
    return locations;
}

bool Paddle::isSlotAvailable(Slot s)
{
    return !s.isBooked;
}

void Paddle::displaySlot(Slot s)
{
    cout << "Slot " << s.slotID << ": " << s.time << endl;
}

bool Paddle::isDateValid(int day, int month, int year, bool isVIP)
{
    //if vip then they can book a court 14 days beforehand not only 7
    int daysAllowed = isVIP ? 14 : 7;
    for (int i = 0; i < daysAllowed; i++)
    {
        tm temp = {};
        temp.tm_year = nowYear - 1900;
        temp.tm_mon = nowMonth - 1;
        temp.tm_mday = nowDay + i;
        mktime(&temp);

        if (temp.tm_mday == day && (temp.tm_mon + 1) == month && (temp.tm_year + 1900) == year)
            return true;
    }
    return false;
}

int Paddle::countAvailableSlots(Court c, string keyDate)
{
    int count = 0;
    for (auto& slot : c.datesOfbooking[keyDate])
    {
        if (!slot.isBooked) count++;
    }
    return count;
}

void Paddle::displayConfirmation(string date, string locationName, string courtType, string timeSlot, int bookingID)
{
    cout << "Your booking is confirmed!\n"
        << "Date: " << date
        << "\nLocation: " << locationName
        << "\nCourt type: " << courtType
        << "\nTime slot: " << timeSlot
        << "\nBooking ID: " << bookingID;
    cout << "\nTake care, cancellation can only be done maximum 3 hours prior to the start of the time slot.\n\n" << endl;
}

void Paddle::displayAvailableSlots(vector<Slot> slots)
{
    for (int i = 0; i < slots.size(); i++)
    {
        if (isSlotAvailable(slots[i]))
            displaySlot(slots[i]);
    }
}

void Paddle::bookingCourt(vector<Location>& locations, bool isVIP)
{
    Location l;
    cout << "Which location?\n1- Tagamoa\n2- Almaza\nChoice: ";
    while (true)
    {
        cin >> l.locID;
        if (l.locID >= 1 && l.locID <= 2) break;
        cout << "Invalid location. Try again: ";
    }
    l.name = (l.locID == 1 ? "Tagamoa" : "Almaza");

    int day, month, year;
    cout << "Enter a date within the next 7 days (DD MM YYYY): ";
    while (true)
    {
        cin >> day >> month >> year;
        if (isDateValid(day, month, year, isVIP)) break;
        cout << "Invalid date. Try again: ";
    }

    string keyDate = (day < 10 ? "0" : "") + to_string(day) + "-" +
        (month < 10 ? "0" : "") + to_string(month) + "-" +
        to_string(year);

    Court c;
    cout << "Do you prefer the court to be: \n1- indoors\n2- outdoors\nChoice: ";
    while (true)
    {
        cin >> c.courtID;
        if (c.courtID >= 1 && c.courtID <= 2) break;
        cout << "Invalid court. Try again: ";
    }

    c = locations[l.locID - 1].courts[c.courtID - 1];
    c.type = (c.courtID == 1 ? "indoors court" : "outdoors court");

    if (countAvailableSlots(c, keyDate) == 0)
    {
        cout << "All slots are booked on this day.\n";
        return;
    }

    cout << "Available slots for " << keyDate << " (" << c.type << "):\n";
    vector<Slot>& availableSlots = locations[l.locID - 1].courts[c.courtID - 1].datesOfbooking[keyDate];
    displayAvailableSlots(availableSlots);

    // Allow the user to choose the slot they want
    Slot* selectedSlot = nullptr;
    int slotID;
    while (true)
    {
        cout << "Which slot do you want to book? ";
        cin >> slotID;
        if (slotID < 1 || slotID > 8)
        {
            cout << "Invalid slot. Try again: ";
            continue;
        }
        selectedSlot = &availableSlots[slotID - 1];
        if (!isSlotAvailable(*selectedSlot))
        {
            cout << "Slot already booked. Try again: ";
            continue;
        }
        break;
    }

    // Mark the selected slot as booked
    selectedSlot->isBooked = true;
    selectedSlot->bookingID = ++allBookings;
    bookingRegistry[selectedSlot->bookingID] = selectedSlot;

    displayConfirmation(keyDate, l.name, c.type, selectedSlot->time, selectedSlot->bookingID);
}


void Paddle::cancelBookingByID(int bookingID, bool isVIP)
{
    auto it = bookingRegistry.find(bookingID);
    if (it == bookingRegistry.end())
    {
        cout << "Booking ID not found.\n";
        return;
    }

    Slot* s = it->second;
    if (!s->isBooked)
    {
        cout << "Slot already free.\n";
        return;
    }
    int time = stoi(s->time.substr(0, 2));
    int cancelWindow = isVIP ? 1 : 3; // VIP: can cancel 1 hour beforehand , Regular: 3 hours 
    if (nowHour + cancelWindow <= time)
    {
        s->isBooked = false;
        s->bookingID = -1;
        bookingRegistry.erase(it);
        cout << "Booking " << bookingID << " successfully canceled.\n";
    }
    else
    {
        cout << "Can't cancel booking because it starts in less than 3 hours.\n";
    }
}
