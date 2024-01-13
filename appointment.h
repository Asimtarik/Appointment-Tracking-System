// Appointment.h

#include "doctor.h"
#include "patient.h"

class Appointment
{
private:
    int id;
    Doctor doctor;
    Patient patient;
    int hour;
    int day;
    int month;
    int year;

public:
    Appointment() : id(0), hour(0), day(0), month(0), year(0) {}

    Appointment(int _id, const Doctor &_doctor, const Patient &_patient, int _hour, int _day, int _month, int _year)
        : id(_id), doctor(_doctor), patient(_patient), hour(_hour), day(_day), month(_month), year(_year) {}

    int getId() const { return id; }
    const Doctor &getDoctor() const { return doctor; }
    const Patient &getPatient() const { return patient; }
    int getHour() const { return hour; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void setId(int _id) { id = _id; }
    void setDoctor(const Doctor &_doctor) { doctor = _doctor; }
    void setPatient(const Patient &_patient) { patient = _patient; }
    void setHour(int _hour) { hour = _hour; }
    void setDay(int _day) { day = _day; }
    void setMonth(int _month) { month = _month; }
    void setYear(int _year) { year = _year; }
    friend bool operator<=(const Doctor &doctor, const Appointment &appointment);

    void displayInfo()
    {
        std::cout << "Appointment ID: " << id << std::endl;
        std::cout << "Doctor Information:" << std::endl;
        doctor.displayInfo();
        std::cout << "Patient Information:" << std::endl;
        patient.displayInfo();
        std::cout << "Date and Time: " << day << "/" << month << "/" << year << " at " << hour << ":00" << std::endl;
    }
};