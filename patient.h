// Patient.h

#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "person.h"

class Patient : public Person
{
private:
    int age;

public:
    Patient();
    Patient(int _id, const std::string &_name, int _age);

    int getAge() const;

    void setAge(int _age);

    void displayInfo();
};

#endif // PATIENT_H