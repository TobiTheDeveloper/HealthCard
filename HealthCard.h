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


#ifndef SDDS_HEALTHCARD_H_
#define SDDS_HEALTHCARD_H_
namespace sdds {
    const int MaxNameLength = 55;

    class HealthCard {

        char* m_name{};
        long long m_number;
        char m_vCode[3];
        char m_sNumber[10];

        bool validID(const char* name, long long number, const char vCode[], const char sNumber[]) const;

        void setEmpty();
        void allocateAndCopy(const char* name);
        void extractChar(std::istream& istr, char ch) const;
        std::ostream& printIDInfo(std::ostream& ostr)const;
        void set(const char* name, long long number, const char vCode[], const char sNumber[]);

    public:

        HealthCard(const HealthCard& hc);
        HealthCard& operator=(const HealthCard& hc);

        HealthCard(const char* name = nullptr, long long number = 0, const char vCode[] = {}, const char sNumber[] = {});
        ~HealthCard();

        operator bool() const;

        std::ostream& print(std::ostream& ostr, bool toFile = false) const;
        std::istream& read(std::istream& istr);
    };

    std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc);
    std::istream& operator>>(std::istream& istr, HealthCard& hc);
}
#endif // !SDDS_HEATHCARD_H_

