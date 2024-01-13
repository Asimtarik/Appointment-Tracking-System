// person.h

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

// Person class (superclass)
class Person
{
protected:
    int id;
    std::string name;

public:
    // Constructor for Person
    Person(int id, const std::string &name);

    // Getter methods
    int getId() const;
    std::string getName() const;

    // Setter methods
    void setId(int newId);
    void setName(const std::string &newName);

    // Virtual function to display information
    virtual void displayInfo() const;

    // Virtual destructor to support polymorphism
    virtual ~Person() = default;
};

#endif // PERSON_H