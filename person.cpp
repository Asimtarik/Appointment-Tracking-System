// person.cpp

#include "person.h"
#include <iostream>

// Constructor for Person
Person::Person(int _id, const std::string &_name) : id(_id), name(_name) {}

// Getter methods
int Person::getId() const
{
    return id;
}

std::string Person::getName() const
{
    return name;
}

// Setter methods
void Person::setId(int newId)
{
    id = newId;
}

void Person::setName(const std::string &newName)
{
    name = newName;
}

// Virtual function to display information
void Person::displayInfo() const
{
    std::cout << "ID: " << id << "\nName: " << name << std::endl;
}