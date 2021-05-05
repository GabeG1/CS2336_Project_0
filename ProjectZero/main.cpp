// Gabriel (Gabe) Goldstein
// gjg180000
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;
void displayReport(char auditorium[10][26], int numberOfRows, int numberOfSeats);
int bestAvailable(char auditorium[10][26], int row, int totalQuantity, int numberOfSeats);
void displayAuditorium(char auditorium[10][26], int numberOfRows, int numberOfSeats);
void reserveSeats(char auditorium[10][26], int row, int seat, int adultQuantity, int seniorQuantity, int childQuantity);
bool checkAvailability(char auditorium[10][26], int row, char seat, int totalQuantity, int numberOfSeats);

int main()
{
    int menuOption = 0;
    char auditorium[10][26];

    //Initializing the auditorium array
    for(int row = 0; row < 10; row++)
    {
        for(int cols = 0; cols < 26; cols++)
        {
            auditorium[row][cols] = '\0';
        }
    }

    string fileLine;
    int numberOfRows = -1;
    int numberOfSeats = 0;
    ifstream inputfile("A1.txt");

    //checking to see that file has successfully opened
    if (inputfile.is_open())
    {

    getline(inputfile, fileLine);
    numberOfSeats = (int)fileLine.length();

    //Read each line of file and save to 2d array. When no more lines left in file, while loop ends.
    while(inputfile)
    {

        numberOfRows++;
        for(int seat = 0; seat < numberOfSeats; seat++)
        {
            auditorium[numberOfRows][seat] = fileLine.at(seat);
        }

        getline(inputfile, fileLine);
    }
    }
//User to decide if they want to reserve ticket or Exit. Once they exit, do...while statement ends
    do
    {


        cout << "Press 1 to Reserve Seats. \nPress 2 to Exit." << endl;
        cin  >> menuOption;
        cout << endl;
        if(menuOption == 1)
        {
            //Showing Seating Arrangement to the user
            displayAuditorium(auditorium, numberOfRows, numberOfSeats);
            int selectedRow;
            char selectedStartingSeat;
            cout << "In what row would you like to be seated?\nRow Number: ";
            cin >> selectedRow;
            cout << endl;

            //Makes sure user entered a row number that exists in auditorium
            while(selectedRow > numberOfRows + 1 || selectedRow < 1)
            {
                cout << "Row " << selectedRow << " is not a row offered in this theater. Please enter a row number shown in the above auditorium display\nRow Number: ";
                cin >> selectedRow;
                cout << endl;

            }
            cout << "What seat would you like to start with in Row " << selectedRow << "?\nSeat Letter: ";
            cin >> selectedStartingSeat;
            cout << endl;


            //Makes sure user entered a seat letter that exists in auditorium. DOes not matter if user entered upper or lower case letter.
            while(toupper(selectedStartingSeat) > numberOfSeats+64 || selectedStartingSeat < 'A')
            {
                cout << "Seat " << selectedStartingSeat << " is not a Seat offered in this theater. Please enter a seat letter shown in the above auditorium display\nSeat Letter: ";
                cin >> selectedStartingSeat;
                cout << endl;
            }

            int adultTickets;
            int childTickets;
            int seniorTickets;

            cout << "How many Adult tickets would you like?\nAdult Tickets: ";
            cin >> adultTickets;
            cout << endl;

            //Each of the three while loops that follow the user input checks to see if user entered a quantity less than zero.
            while(adultTickets < 0)
            {
                cout << "Please enter a valid quantity for the number of Adult tickets you wish to purchase (At least zero tickets)\nAdult Tickets: ";
                cin >> adultTickets;
                cout << endl;
            }

            cout << "How many Child tickets would you like?\nChild Tickets: ";
            cin >> childTickets;
            cout << endl;

            while(childTickets < 0)
            {
                cout << "Please enter a valid quantity for the number of Child tickets you wish to purchase (at least zero tickets)\nChild Tickets: ";
                cin >> childTickets;
                cout << endl;
            }

            cout << "How many Senior tickets would you like?\nSenior Tickets: ";
            cin >> seniorTickets;
            cout << endl;

            while(seniorTickets < 0)
            {
                cout << "Please enter a valid quantity for the number of Senior tickets you wish to purchase (at least zero tickets)\nSenior Tickets: ";
                cin >> seniorTickets;
                cout << endl;
            }

            //Now that user has entered valid quantities, check to see that the seats requested are available
            int totalQuantity = adultTickets + childTickets + seniorTickets;
            bool isAvailable = checkAvailability(auditorium, selectedRow, (char)toupper(selectedStartingSeat),totalQuantity, numberOfSeats);
            int seatSuggestion = -1;

            //If seats are available, they are reserved. Otherwise, find best available seats for user in requested row
            if (isAvailable ==  true && totalQuantity !=  0)
            {
                reserveSeats(auditorium, selectedRow, toupper(selectedStartingSeat), adultTickets, seniorTickets, childTickets);
                cout << "Thanks for doing business with us!" << "\n\n";
            }
            else if(totalQuantity == 0)
            {
                cout << "We are sorry no seats were of interest to you. " << "\n\n";
            }

            else
            {
                seatSuggestion = bestAvailable(auditorium, selectedRow, totalQuantity, numberOfSeats);
            }

            //If bestAvailable function identifies seats, suggest them to the user
            if(seatSuggestion != -1)
            {


                char StartingSeatLetter = 'A';
                StartingSeatLetter = (char)(seatSuggestion + (int)StartingSeatLetter);
                char userResponse;

                //Ask user to accept or decline seats
                if(totalQuantity == 1)
                {
                    cout << "\nWe could not reserve this seat. If you instead would like to reserve seat " <<  StartingSeatLetter << ", please enter 'Y'. Enter 'N' if you do not wish to accept this seat." << endl << "Your Response: ";
                    cin >> userResponse;
                    cout << endl;
                }
                else
                {
                    char lastSeat = (char)((int)StartingSeatLetter + totalQuantity - 1);
                    cout << "\nWe could not reserve those seats. If you instead would like to reserve seats " <<  StartingSeatLetter << " through " << lastSeat << ", please enter 'Y'. Enter 'N' if you do not wish to accept these seats." << endl << "Your Response: ";
                    cin >> userResponse;
                    cout << endl;

                }

                //If user fails to type one of two options, keep requesting that the user types in a correct letter (Y or N).
                while (toupper(userResponse) != 'Y' && toupper(userResponse) != 'N')
                {
                    cout << "\nPlease Enter ""Y"" to accept seats or ""N"" to decline. \nYour Response: ";
                    cin >> userResponse;
                    cout << endl;
                }

                if (toupper(userResponse) == 'Y')
                {
                    reserveSeats(auditorium, selectedRow, StartingSeatLetter, adultTickets, seniorTickets, childTickets);
                    cout << "\nThanks for doing business with us!\n" << endl;
                }
                else if (toupper(userResponse) == 'N')
                {
                    cout << "\nSorry we couldn't find you a seat.\n" << endl;
                }


            }
            //If there were no available seats found, inform user
            else if (seatSuggestion == -1 && isAvailable == false)
            {
                cout << "\nSorry, we could not find available seats on Row " << selectedRow << "\n\n";
            }



        }


        //If the user inputs a number other than 1 or 2 (reserve seat or exit, respectively), request a correct response
        else if(menuOption != 2)
        {
            cout << menuOption << " is not a valid option." << "\n\n";
        }
    }
    while(menuOption != 2);

    inputfile.close();

    //prints report to console
    displayReport(auditorium, numberOfRows, numberOfSeats);
    return 0;
}

//Finds best possible seats in the row the user entered
int bestAvailable(char auditorium[10][26], int row, int totalQuantity, int numberOfSeats)
{
    double distance = -1.0;
    double smallestDistance = numberOfSeats;
    int seatNumber = -1;
    bool seatsAreOpen = false;

    for(int seat = 0; seat <= numberOfSeats - totalQuantity; seat++)
    {
        for (int i = 0; i < totalQuantity; i++)
        {
            seatsAreOpen = false;
            if (auditorium[row - 1][seat+i] != '.')
            {
                break;

            }
            //If we have found the correct number of adjacent seats  that are empty
            if(i == totalQuantity - 1)
            {
                seatsAreOpen = true;
            }
        }

        //Now that a group of seats were found that can hold the number of seats the user requested in the row, find out how far away the midpoint of those seats is from the midpoint of the total number of seats in the row
        if(seatsAreOpen == true)
        {
            distance = abs((double)(seat + (seat + totalQuantity) - 1) / 2.0 - ((double)(numberOfSeats - 1) / 2.0));

            //If the distance found above is the smallest distance yet, save that distance and save the starting seat letter for that group of seats
            if (distance < smallestDistance)
            {
                smallestDistance = distance;
                seatNumber = seat;
            }
        }
    }

    //Either returns the starting seat letter saved above or -1: the latter implies no best available seat was found
    return seatNumber;
}

//Shows the seating arrangement to the user
void displayAuditorium(char auditorium[10][26], int numberOfRows, int numberOfSeats)
{

//First display the column headers
    char columnHeader = 'A';
    //Writing the column headers to the console
    cout << "   ";
    for(int numOfColHeads = 0; numOfColHeads < numberOfSeats; ++numOfColHeads)
    {
        cout << columnHeader;
        columnHeader++;
    }
    cout << endl;

//Display row number
    for(int row = 0; row <= numberOfRows; ++row)
    {
        //Because Row 10 has two digits, spacing problems arise. The following if else statement makes sure all rows line up properly.
        if(row + 1 < 10)
        {
            cout << row + 1 << "  ";
        }
        else
        {
            cout << row + 1 << " ";
        }
        //Display '#' to denote seat in the row is filled or '.' to denote the seat in the row is empty
        for(int seat=0; seat<numberOfSeats; ++seat)
        {
            if(auditorium[row][seat] == '.')
            {

                cout << auditorium[row][seat];
            }
            else
            {
                cout << "#";

            }

        }
        cout << endl;
    }
    cout << endl;
}

//If available seats found, this function is called to reserve those seats
void reserveSeats(char auditorium[10][26], int row, int seat, int adultquantity, int seniorquantity, int childquantity)
{
    //Save adult, children, and senior tickets to 2d array in that order
    for(int adultTicket = 0; adultTicket < adultquantity; adultTicket++)
    {
        auditorium[row-1][seat - 65] = 'A';
        seat++;
    }
    for(int childTicket = 0; childTicket < childquantity; childTicket++)
    {
        auditorium[row-1][seat - 65] = 'C';
        seat++;
    }
    for(int seniorTicket = 0; seniorTicket < seniorquantity; seniorTicket++)
    {
        auditorium[row-1][seat - 65] = 'S';
        seat++;
    }
}

//Checks to see if the seats the user requested are available in the row the user entered
bool checkAvailability(char auditorium[10][26], int row, char seat, int totalQuantity, int numberOfSeats)
{
    for(int seatNum = 0; seatNum < totalQuantity; ++seatNum)
    {
        //if we're checking a seat that is outside the range of seats in the row, then seats not available
        //Note: we subtract 65 from seat because seat is a char value. For example, Seat 'A' has value 65, so in the 2d array, seat - 65 would be seat 0.
        if(seat - 65 >= numberOfSeats)
        {
            return false;
        }

        //If a seat not available in the group of seats the user requested, them seats not available
        if(auditorium[row - 1][seat - 65] != '.')
        {
            return false;
        }

        seat++;
    }
    return true;
}

//Writes updated auditorium to file and writes a report to the console
void displayReport(char auditorium[10][26], int numberOfRows, int numberOfSeats)
{
    int numAdultTickets;
    int numChildTickets;
    int numSeniorTickets;

    for(int row = 0; row <= numberOfRows; ++row)
    {
        for(int seat = 0; seat < numberOfSeats; ++seat)
        {
            switch(auditorium[row][seat])
            {
            case 'A':
                numAdultTickets++;
                break;
            case 'C':
                numChildTickets++;
                break;
            case 'S':
                numSeniorTickets++;
                break;

            }


        }

    }
    ofstream outputFile("A1.txt");
    for(int row = 0; row <= numberOfRows; row++)
    {
        for(int seat = 0; seat < numberOfSeats; seat++)
        {
            outputFile << auditorium[row][seat];
        }
        outputFile << "\n";
    }
    double totalSales = numAdultTickets * 10 + numChildTickets * 5 + numSeniorTickets * 7.50;
    outputFile.close();
    cout << "\nTotal Seats: " << setw(11) << (numberOfRows + 1) * numberOfSeats << "\nTotal Sold: "<< setw(11) << numAdultTickets+numChildTickets+numSeniorTickets << endl;
    cout << "Adult Tickets: " << setw(8) << numAdultTickets << "\nChild Tickets: " << setw(8) << numChildTickets << "\nSenior Tickets: " << setw(7) << numSeniorTickets << endl;
    cout << "Total Tickets Sales: $";
    printf("%.2f", totalSales);
    cout << "\n\n";


}
