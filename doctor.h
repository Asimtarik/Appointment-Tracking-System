// doctor.h

#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"

// Forward declaration
class Appointment;

// Enumeration for doctor specialization
enum class Specialization
{
    GENERAL_PRACTITIONER,
    CARDIOLOGIST,
    DERMATOLOGIST,
    GYNECOLOGIST,
    NEUROLOGIST,
    ONCOLOGIST,
    PEDIATRICIAN,
    SURGEON,
    OTHER
};

class Doctor : public Person
{
private:
    Specialization specialization;
    static const int MAX_APPOINTMENTS = 10;

    int numberOfAppointments = 2;

public:
    Doctor();
    Doctor(int _id, const std::string &_doctorName, Specialization _specialization);

    int getId() const;
    std::string getDoctorName() const;
    Specialization getSpecialization() const;
    int getNumberOfAppointments() const;

    void setId(int _id);
    void setDoctorName(const std::string &_doctorName);
    void setSpecialization(Specialization _specialization);
    void setNumberOfAppointments(int _numberOfAppointments);

    void incrementAppointments();

    // Operator overloading
    friend bool operator<=(const Doctor &doctor, const Appointment &appointment);

    void displayInfo();
};

#endif // DOCTOR_H