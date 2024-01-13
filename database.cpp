#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.h"
#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include <algorithm>

class Database
{
private:
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Appointment> appointments;
    std::vector<Person *> people;

public:
    void addPerson()
    {

        // Create 3 doctors
        people.push_back(new Doctor(1, "Dr. Smith", Specialization::GENERAL_PRACTITIONER));
        people.push_back(new Doctor(2, "Dr. Johnson", Specialization::CARDIOLOGIST));
        people.push_back(new Doctor(3, "Dr. Davis", Specialization::PEDIATRICIAN));

        doctors.push_back(Doctor(1, "Dr. Smith", Specialization::GENERAL_PRACTITIONER));
        doctors.push_back(Doctor(2, "Dr. Johnson", Specialization::CARDIOLOGIST));
        doctors.push_back(Doctor(3, "Dr. Davis", Specialization::PEDIATRICIAN));

        // Create 6 patients
        people.push_back(new Patient(1, "John", 25));
        people.push_back(new Patient(2, "Alice", 30));
        people.push_back(new Patient(3, "Bob", 40));
        people.push_back(new Patient(4, "Eva", 22));
        people.push_back(new Patient(5, "Michael", 35));
        people.push_back(new Patient(6, "Sophia", 28));

        patients.push_back(Patient(1, "John", 25));
        patients.push_back(Patient(2, "Alice", 30));
        patients.push_back(Patient(3, "Bob", 40));
        patients.push_back(Patient(4, "Eva", 22));
        patients.push_back(Patient(5, "Michael", 35));
        patients.push_back(Patient(6, "Sophia", 28));

        // Create appointments with fixed dates
        appointments.push_back(Appointment(1, doctors[0], patients[0], 9, 10, 1, 2023));
        appointments.push_back(Appointment(2, doctors[1], patients[1], 14, 15, 2, 2023));
        appointments.push_back(Appointment(3, doctors[2], patients[2], 11, 20, 3, 2023));
        appointments.push_back(Appointment(4, doctors[0], patients[3], 15, 5, 4, 2023));
        appointments.push_back(Appointment(5, doctors[1], patients[4], 10, 1, 5, 2023));
        appointments.push_back(Appointment(6, doctors[2], patients[5], 13, 8, 6, 2023));
    }

    // Add a doctor to the database
    void addDoctor(const Doctor &doctor)
    {
        // Check if the ID is already in use
        if (std::find_if(doctors.begin(), doctors.end(),
                         [id = doctor.getId()](const Doctor &d)
                         { return d.getId() == id; }) != doctors.end())
        {
            std::cerr << "Error: Doctor with ID " << doctor.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the doctor to the vector
            doctors.push_back(doctor);
            people.push_back(new Doctor(doctor));

            // Update the file after adding the doctor
            saveToFile("doctors.txt");

            std::cout << "Doctor with ID " << doctor.getId() << " added to the database and file." << std::endl;
        }
    }

    // Retrieve all doctors from the database
    const std::vector<Doctor> &getAllDoctors() const
    {
        return doctors;
    }

    const std::vector<Person *> &getAllPersons() const
    {
        return people;
    }

    // Other methods for managing doctors can be added here

    void saveToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &doctor : doctors)
            {
                outFile << doctor.getId() << ","
                        << doctor.getDoctorName() << ","
                        << static_cast<int>(doctor.getSpecialization()) << "\n";
            }

            outFile.close();
            std::cout << "Doctors saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadFromFile(const std::string &filename)
    {
        doctors.clear(); // Clear existing doctors before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            std::string doctorName;
            int specialization;

            while (inFile >> id >> std::ws && std::getline(inFile, doctorName, ',') && inFile >> specialization)
            {
                Specialization spec = static_cast<Specialization>(specialization);
                doctors.emplace_back(id, doctorName, spec);
            }

            inFile.close();
            std::cout << "Doctors loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void deleteDoctorAndAppointments(int doctorId)
    {
        // Remove the doctor from the vector
        auto doctorIt = std::remove_if(
            doctors.begin(), doctors.end(),
            [doctorId](const Doctor &doctor)
            { return doctor.getId() == doctorId; });

        doctors.erase(doctorIt, doctors.end());

        // Update the file after removing the doctor
        saveToFile("doctors.txt");

        if (doctorIt != doctors.end())
        {
            // Get the deleted doctor
            Doctor deletedDoctor = *doctorIt;

            // Remove the doctor's appointments from the vector
            appointments.erase(
                std::remove_if(
                    appointments.begin(), appointments.end(),
                    [doctorId](const Appointment &appointment)
                    { return appointment.getDoctor().getId() == doctorId; }),
                appointments.end());

            // Update the file after removing the appointments
            saveAppointmentsToFile("appointments.txt");

            std::cout << "Doctor with ID " << doctorId << " and associated appointments deleted from the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Doctor with ID " << doctorId << " not found in the database." << std::endl;
        }
    }
    void updateDoctor(int doctorId, const Doctor &updatedDoctor)
    {
        // Find the doctor in the vector
        auto it = std::find_if(
            doctors.begin(), doctors.end(),
            [doctorId](const Doctor &doctor)
            { return doctor.getId() == doctorId; });

        if (it != doctors.end())
        {
            // Update the doctor in the vector
            *it = updatedDoctor;

            // Update the file after modifying the doctor
            saveToFile("doctors.txt");

            std::cout << "Doctor with ID " << doctorId << " updated in the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Doctor with ID " << doctorId << " not found in the database." << std::endl;
        }
    }

    void showAllDoctors(const std::string &filename) const
    {
        std::cout << "All Doctors in the Database:" << std::endl;

        for (Doctor doctor : doctors)
        {
            doctor.displayInfo();
            std::cout << std::endl;
        }
    }
    void displayAllPersons(const std::vector<Person *> &people)
    {
        for (const Person *person : people)
        {
            person->displayInfo();
        }
    }

    // Patient Operations
    // Save all patients to a file
    void savePatientsToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &patient : patients)
            {
                outFile << patient.getId() << ","
                        << patient.getName() << ","
                        << patient.getAge() << "\n";
            }

            outFile.close();
            std::cout << "Patients saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadPatientsFromFile(const std::string &filename)
    {
        patients.clear(); // Clear existing patients before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            std::string patientName;
            int age;

            while (inFile >> id >> std::ws && std::getline(inFile, patientName, ',') && inFile >> age)
            {
                patients.emplace_back(id, patientName, age);
            }

            inFile.close();
            std::cout << "Patients loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void addPatient(const Patient &patient)
    {
        // Check if the ID is already in use
        if (std::find_if(patients.begin(), patients.end(),
                         [id = patient.getId()](const Patient &p)
                         { return p.getId() == id; }) != patients.end())
        {
            std::cerr << "Error: Patient with ID " << patient.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the patient to the vector
            patients.push_back(patient);
            people.push_back(new Patient(patient));

            // Update the file after adding the patient
            // Assuming you have a saveToFile method similar to the one for doctors
            // saveToFile("patients.txt");
            savePatientsToFile("patients.txt");

            std::cout << "Patient with ID " << patient.getId() << " added to the database." << std::endl;
        }
    }
    const std::vector<Patient> &getAllPatients() const
    {
        return patients;
    }

    void deletePatientAndAppointments(int patientId)
    {
        // Remove the patient from the vector
        auto patientIt = std::remove_if(
            patients.begin(), patients.end(),
            [patientId](const Patient &patient)
            { return patient.getId() == patientId; });
        patients.erase(patientIt, patients.end());
        // Update the file after removing the patient
        savePatientsToFile("patients.txt");

        if (patientIt != patients.end())
        {
            // Get the deleted patient
            Patient deletedPatient = *patientIt;

            // Remove the patient's appointments from the vector
            appointments.erase(
                std::remove_if(
                    appointments.begin(), appointments.end(),
                    [patientId](const Appointment &appointment)
                    { return appointment.getPatient().getId() == patientId; }),
                appointments.end());

            // Update the file after removing the appointments
            saveAppointmentsToFile("appointments.txt");

            std::cout << "Patient with ID " << patientId << " and associated appointments deleted from the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Patient with ID " << patientId << " not found in the database." << std::endl;
        }
    }

    void updatePatient(int patientId, const Patient &updatedPatient)
    {
        // Find the patient in the vector
        auto it = std::find_if(
            patients.begin(), patients.end(),
            [patientId](const Patient &patient)
            { return patient.getId() == patientId; });

        if (it != patients.end())
        {
            // Update the patient in the vector
            *it = updatedPatient;

            // Update the file after modifying the patient
            // Assuming you have a saveToFile method similar to the one for doctors
            // saveToFile("patients.txt");
            savePatientsToFile("patients.txt");

            std::cout << "Patient with ID " << patientId << " updated in the database." << std::endl;
        }
        else
        {
            std::cerr << "Error: Patient with ID " << patientId << " not found in the database." << std::endl;
        }
    }

    void showAllPatientsFromFile(const std::string &filename) const
    {
        std::cout << "All Patients in the Database:" << std::endl;

        for (Patient patient : patients)
        {
            patient.displayInfo();
            std::cout << std::endl;
        }
    }

    void calculateAndPrintPatientStatistics(const std::vector<Patient> &patients)
    {
        if (patients.empty())
        {
            std::cerr << "Error: Empty vector of patients." << std::endl;
            return;
        }

        // Allocate memory for an array of Patient pointers using malloc
        Patient **patientArray = static_cast<Patient **>(malloc(patients.size() * sizeof(Patient *)));

        // Populate the array with pointers to Patient objects
        for (size_t i = 0; i < patients.size(); ++i)
        {
            patientArray[i] = new Patient(patients[i]);
        }

        // Calculate statistics
        int totalAge = 0;
        for (size_t i = 0; i < patients.size(); ++i)
        {
            totalAge += patientArray[i]->getAge();
        }

        double averageAge = static_cast<double>(totalAge) / patients.size();
        int numberOfPatients = patients.size();

        // Output statistics
        std::cout << "Number of Patients: " << numberOfPatients << std::endl;
        std::cout << "Average Age of Patients: " << averageAge << std::endl;

        // Deallocate memory using free
        for (size_t i = 0; i < patients.size(); ++i)
        {
            delete patientArray[i];
        }
        free(patientArray);
    }

    // Appointments operations

    void addAppointment(Appointment &appointment)
    {

        if (std::find_if(appointments.begin(), appointments.end(),
                         [appointment](const Appointment &a)
                         {
                             return a.getHour() == appointment.getHour() &&
                                    a.getDay() == appointment.getDay() &&
                                    a.getMonth() == appointment.getMonth() &&
                                    a.getYear() == appointment.getYear();
                         }) != appointments.end())
        {
            std::cerr << "Error: Appointment with the same date already exists in the database." << std::endl;
        } // Check if the ID is already in use
        else if (std::find_if(appointments.begin(), appointments.end(),
                              [id = appointment.getId()](const Appointment &a)
                              { return a.getId() == id; }) != appointments.end())
        {
            std::cerr << "Error: Appointment with ID " << appointment.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the appointment to the vector
            appointments.push_back(appointment);

            // Update the file after adding the appointment
            saveAppointmentsToFile("appointments.txt");

            std::cout << "Appointment with ID " << appointment.getId() << " added to the database and file." << std::endl;

            Doctor doctor = appointment.getDoctor();
            doctor.incrementAppointments();
        }
    }

    const std::vector<Appointment> &getAllAppointments() const
    {
        return appointments;
    }

    void saveAppointmentsToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &appointment : appointments)
            {
                outFile << appointment.getId() << ","
                        << appointment.getDoctor().getId() << ","
                        << appointment.getPatient().getId() << ","
                        << appointment.getHour() << ","
                        << appointment.getDay() << ","
                        << appointment.getMonth() << ","
                        << appointment.getYear() << "\n";
            }

            outFile.close();
            std::cout << "Appointments saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadAppointmentsFromFile(const std::string &filename)
    {
        appointments.clear(); // Clear existing appointments before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            int doctorId;
            int patientId;
            int hour;
            int day;
            int month;
            int year;

            while (inFile >> id >> std::ws && inFile >> doctorId >> std::ws && inFile >> patientId >> std::ws &&
                   inFile >> hour >> std::ws && inFile >> day >> std::ws && inFile >> month >> std::ws && inFile >> year)
            {
                // Retrieve doctor and patient objects from their respective vectors
                auto doctorIt = std::find_if(doctors.begin(), doctors.end(),
                                             [doctorId](const Doctor &doctor)
                                             { return doctor.getId() == doctorId; });

                auto patientIt = std::find_if(patients.begin(), patients.end(),
                                              [patientId](const Patient &patient)
                                              { return patient.getId() == patientId; });

                if (doctorIt != doctors.end() && patientIt != patients.end())
                {
                    Doctor doctor = *doctorIt;
                    Patient patient = *patientIt;

                    appointments.emplace_back(id, doctor, patient, hour, day, month, year);
                }
            }

            inFile.close();
            std::cout << "Appointments loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void deleteAppointmentById(int appointmentId)
    {
        // Remove the appointment from the vector

        auto appointmentIt = std::remove_if(
            appointments.begin(), appointments.end(),
            [appointmentId](const Appointment &appointment)
            { return appointment.getId() == appointmentId; });

        appointments.erase(appointmentIt, appointments.end());

        // Update the file after removing the appointment
        saveAppointmentsToFile("appointments.txt");

        std::cout << "Appointment with ID " << appointmentId << " deleted from the database and file." << std::endl;
    }

    void updateAppointment(int appointmentId, const Appointment &updatedAppointment)
    {
        // Find the appointment in the vector
        auto it = std::find_if(
            appointments.begin(), appointments.end(),
            [appointmentId](const Appointment &appointment)
            { return appointment.getId() == appointmentId; });

        if (it != appointments.end())
        {
            // Update the appointment in the vector
            *it = updatedAppointment;

            // Update the file after modifying the appointment
            saveAppointmentsToFile("appointments.txt");

            std::cout << "Appointment with ID " << appointmentId << " updated in the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Appointment with ID " << appointmentId << " not found in the database." << std::endl;
        }
    }

    void showAllAppointmentsFromFile(const std::string &filename) const
    {
        std::cout << "All Doctors in the Database:" << std::endl;

        for (Appointment appointment : appointments)
        {
            appointment.displayInfo();
            std::cout << std::endl;
        }
    }
};