// Database.h

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "doctor.h"
#include "patient.h"
#include "appointment.h"

class Database
{
private:
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Appointment> appointments;
    std::vector<Person *> people;

public:
    // Doctor Operations
    void addPerson();
    void addDoctor(const Doctor &doctor);
    const std::vector<Doctor> &getAllDoctors() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    void deleteDoctorAndAppointments(int doctorId);
    void updateDoctor(int doctorId, const Doctor &updatedDoctor);
    void showAllDoctors(const std::string &filename) const;

    // Patient Operations
    void addPatient(const Patient &patient);
    const std::vector<Patient> &getAllPatients() const;
    void savePatientsToFile(const std::string &filename) const;
    void loadPatientsFromFile(const std::string &filename);
    void deletePatientAndAppointments(int patientId);
    void updatePatient(int patientId, const Patient &updatedPatient);
    void showAllPatientsFromFile(const std::string &filename) const;
    void calculateAndPrintPatientStatistics(const std::vector<Patient> &patients);

    // Appointment Operations
    void addAppointment(const Appointment &appointment);
    const std::vector<Appointment> &getAllAppointments() const;
    void saveAppointmentsToFile(const std::string &filename) const;
    void loadAppointmentsFromFile(const std::string &filename);
    void deleteAppointmentById(int appointmentId);
    void updateAppointment(int appointmentId, const Appointment &updatedAppointment);
    void showAllAppointmentsFromFile(const std::string &filename) const;
};

#endif // DATABASE_H