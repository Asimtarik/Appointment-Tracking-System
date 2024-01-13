// doctor.cpp
#include "doctor.h"
#include <iostream>

// Constructors
Doctor::Doctor() : Person(0, ""), specialization(Specialization::OTHER) {}

Doctor::Doctor(int _id, const std::string &_doctorName, Specialization _specialization)
    : Person(_id, _doctorName), specialization(_specialization) {}

// Getter methods
int Doctor::getId() const
{
    return Person::getId();
}

std::string Doctor::getDoctorName() const
{
    return Person::getName();
}

Specialization Doctor::getSpecialization() const
{
    return specialization;
}
int Doctor::getNumberOfAppointments() const
{
    return numberOfAppointments;
}

// Setter methods
void Doctor::setId(int _id)
{
    Person::setId(_id);
}

void Doctor::setDoctorName(const std::string &_doctorName)
{
    Person::setName(_doctorName);
}

void Doctor::setSpecialization(Specialization _specialization)
{
    specialization = _specialization;
}
void Doctor::setNumberOfAppointments(int _numberOfAppointments)
{
    numberOfAppointments = _numberOfAppointments;
}

void Doctor::incrementAppointments()
{
    numberOfAppointments++;
}

bool operator<=(const Doctor &doctor, const Appointment &appointment)
{
    if (doctor.numberOfAppointments < Doctor::MAX_APPOINTMENTS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Display information about the doctor
void Doctor::displayInfo()
{
    std::cout << "Doctor ID: " << getId() << std::endl;
    std::cout << "Doctor Name: " << getDoctorName() << std::endl;
    std::cout << "Specialization: ";

    switch (specialization)
    {
    case Specialization::GENERAL_PRACTITIONER:
        std::cout << "General Practitioner";
        break;
    case Specialization::CARDIOLOGIST:
        std::cout << "Cardiologist";
        break;
    case Specialization::DERMATOLOGIST:
        std::cout << "Dermatologist";
        break;
    case Specialization::GYNECOLOGIST:
        std::cout << "Gynecologist";
        break;
    case Specialization::NEUROLOGIST:
        std::cout << "Neurologist";
        break;
    case Specialization::ONCOLOGIST:
        std::cout << "Oncologist";
        break;
    case Specialization::PEDIATRICIAN:
        std::cout << "Pediatrician";
        break;
    case Specialization::SURGEON:
        std::cout << "Surgeon";
        break;
    case Specialization::OTHER:
        std::cout << "Other";
        break;
    }

    std::cout << std::endl;
}