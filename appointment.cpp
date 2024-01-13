// appointment.cpp

#include "appointment.h"
#include <iostream>

// Constructors
Appointment::Appointment() : id(0), hour(0), day(0), month(0), year(0) {}

Appointment::Appointment(int _id, const Doctor &_doctor, const Patient &_patient, int _hour, int _day, int _month, int _year)
    : id(_id), doctor(_doctor), patient(_patient), hour(_hour), day(_day), month(_month), year(_year) {}

// Getter methods
int Appointment::getId() const
{
    return id;
}

const Doctor &Appointment::getDoctor() const
{
    return doctor;
}

const Patient &Appointment::getPatient() const
{
    return patient;
}

int Appointment::getHour() const
{
    return hour;
}

int Appointment::getDay() const
{
    return day;
}

int Appointment::getMonth() const
{
    return month;
}

int Appointment::getYear() const
{
    return year;
}

// Setter methods
void Appointment::setId(int _id)
{
    id = _id;
}

void Appointment::setDoctor(const Doctor &_doctor)
{
    doctor = _doctor;
}

void Appointment::setPatient(const Patient &_patient)
{
    patient = _patient;
}

void Appointment::setHour(int _hour)
{
    hour = _hour;
}

void Appointment::setDay(int _day)
{
    day = _day;
}

void Appointment::setMonth(int _month)
{
    month = _month;
}

void Appointment::setYear(int _year)
{
    year = _year;
}

// Display information about the appointment
void Appointment::displayInfo()
{
    std::cout << "Appointment ID: " << id << std::endl;
    std::cout << "Doctor Information:" << std::endl;
    doctor.displayInfo();
    std::cout << "Patient Information:" << std::endl;
    patient.displayInfo();
    std::cout << "Date and Time: " << day << "/" << month << "/" << year << " at " << hour << ":00" << std::endl;
}