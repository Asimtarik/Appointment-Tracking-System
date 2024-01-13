// patient.cpp

#include "patient.h"
#include <iostream>

// Constructors
Patient::Patient() : Person(0, ""), age(0) {}

Patient::Patient(int _id, const std::string &_name, int _age)
    : Person(_id, _name), age(_age) {}

// Getter method for age
int Patient::getAge() const
{
    return age;
}

// Setter method for age
void Patient::setAge(int _age)
{
    age = _age;
}

// Display information about the patient
void Patient::displayInfo()
{
    std::cout << "Patient ID: " << id << std::endl;
    std::cout << "Patient Name: " << name << std::endl;
    std::cout << "Patient Age: " << age << std::endl;
}