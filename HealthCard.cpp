/*****************************************************************************
                        Workshop 6
Full Name  : Yusuff Oyediran
Student ID#: 142813203
Email      : yooyediran@myseneca.ca
Section    : ZEE
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "HealthCard.h"
using namespace std;

namespace sdds {

    bool HealthCard::validID(const char* name, long long number, const char vCode[], const char sNumber[]) const {
        // Check if name is not null, has a length greater than 0, 
        // number is within the valid range, vCode has a length of 2, and sNumber has a length of 9

        return name != nullptr && strlen(name) > 0 &&
            number > 999999999 && number < 9999999999 &&
            strlen(vCode) == 2 && strlen(sNumber) == 9;
    }

    void HealthCard::setEmpty() {
        // Set m_name to nullptr, indicating an empty HealthCard
        m_name = nullptr;
    }

    void HealthCard::allocateAndCopy(const char* name) {
        // Deallocate existing memory, allocate new memory, and copy 'name' to m_name
        delete[] m_name;
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }

    ostream& HealthCard::printIDInfo(ostream& ostr) const {
        // Print the formatted HealthCard information to the output stream
        ostr << m_number << "-" << m_vCode << ", " << m_sNumber;
        return ostr;
    }

    void HealthCard::extractChar(istream& istr, char ch) const {
        char next;
        next = istr.peek();

        // Check if the next character in the input stream matches 'ch'
        if (next == ch)
            istr.ignore();

        else {
            // If not, ignore input up to the next occurrence of 'ch' and set failbit
            istr.ignore(1000, ch);
            istr.setstate(ios::failbit);
        }
    }

    HealthCard::HealthCard(const char* name, long long number, const char vCode[], const char sNumber[]) {
        // Initialize the HealthCard using the provided information
        set(name, number, vCode, sNumber);
    }

    void HealthCard::set(const char* name, long long number, const char vCode[], const char sNumber[]) {
        if (validID(name, number, vCode, sNumber)) {
            // Allocate and copy name
            allocateAndCopy(name);

            // Set number, vCode, and sNumber
            m_number = number;
            strcpy(m_vCode, vCode);
            strcpy(m_sNumber, sNumber);
        }
        else {
            // In case of an invalid ID, clean up and set to empty
            delete[] m_name;
            setEmpty();
        }
    }

    HealthCard::HealthCard(const HealthCard& hc) {
        // Copy the information from the source HealthCard 'hc' to this HealthCard object
        set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
    }

    HealthCard& HealthCard::operator=(const HealthCard& hc) {
        // Check for self-assignment to avoid unnecessary work
        if (this != &hc) {
            // Copy the information from the source HealthCard 'hc' to this HealthCard object
            set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
        }
        // Return a reference to this HealthCard object for potential chaining
        return *this;
    }


    HealthCard::~HealthCard() {
        // Deallocate the dynamically allocated 'm_name' memory to prevent memory leaks
        delete[] m_name;
        // Set 'm_name' to nullptr to indicate that it no longer points to valid memory
        m_name = nullptr;
    }


    HealthCard::operator bool() const {
        // Check if 'm_name' is not nullptr, which indicates whether the HealthCard is valid
        return m_name != nullptr;
    }

    ostream& HealthCard::print(ostream& ostr, bool toFile) const { // issue: records not being saved to goodInfo.csv 
        // Check if the HealthCard is valid
        if (validID(m_name, m_number, m_vCode, m_sNumber)) {

            if (toFile) {
                // Print the HealthCard information with comma separators for file output
                ostr << m_name << ",";
                printIDInfo(ostr);
                ostr << endl;
            }

            else {
                // Format and print the HealthCard information with a left-aligned 50-character width
                ostr.setf(ios::left);
                ostr.fill('.');
                ostr.width(50);
                ostr << m_name;
                printIDInfo(ostr);
            }
        }
        return ostr;
    }

    istream& HealthCard::read(istream& istr) {

        char name[MaxNameLength + 1];
        long long number;
        char vCode[3];
        char sNumber[10];

        // Read the values from the input stream 'istr'
        istr.get(name, MaxNameLength, ',');
        extractChar(istr, ',');
        istr >> number;
        extractChar(istr, '-');
        istr.get(vCode, 3, ',');
        extractChar(istr, ',');
        istr.get(sNumber, 10, '\n');

        // If reading was successful, set the HealthCard values
        if (!istr.fail())  {
            set(name, number, vCode, sNumber);
        }

        // Clear any error flags, and ignore any remaining input up to the newline character
        istr.clear();
        istr.ignore(1000, '\n');
        return istr;
    }

    ostream& operator<<(ostream& ostr, const HealthCard& hc) {
        // Check if the HealthCard 'hc' is valid
        if (bool(hc)) {
            // If valid, print the HealthCard details
            hc.print(ostr);
        }
        else {
            // If not valid, indicate that it's an invalid Health Card Record
            ostr << "Invalid Health Card Record";
        }
        return ostr;
    }

    istream& operator>>(istream& istr, HealthCard& hc) {
        // Use the 'read' method of the HealthCard class to read input from the stream 'istr' into the HealthCard 'hc'
        return hc.read(istr);
    }
}