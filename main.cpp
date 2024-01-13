#include <iostream>
#include <algorithm>
#include "database.cpp"
#include "doctor.cpp"
#include "person.cpp"
#include "patient.cpp"

int main()
{

    // Create an instance of the Database class
    Database myDatabase;

    myDatabase.addPerson();

    int choice;
    int subchoice;
    do
    {

        std::cout << "\n==== Main Menu ====\n";
        std::cout << "1. Doctor Operations\n";
        std::cout << "2. Patient Operations\n";
        std::cout << "3. Appointment Operations\n";
        std::cout << "4. Display All People\n";
        std::cout << "5. Exit\n";
        std::cin >> choice;

        switch (choice)
        {

        case 1:

            do
            {

                std::cout << "\n==== Doctor Management ====\n";
                std::cout << "1. Add Doctor\n";
                std::cout << "2. Delete Doctor\n";
                std::cout << "3. Update Doctor\n";
                std::cout << "4. Show All Doctors\n";
                std::cout << "5. Exit\n";
                std::cout << "Enter your choice: ";
                std::cin >> subchoice;

                switch (subchoice)
                {
                case 1:
                    // Add a new doctor
                    {
                        int id;
                        std::string name;
                        int specialization;

                        std::cout << "Enter Doctor ID: ";
                        std::cin >> id;

                        std::cout << "Enter Doctor Name: ";
                        std::cin.ignore();
                        std::getline(std::cin, name);

                        std::cout << "Enter Specialization (as an integer):\n"
                                  << "0. GENERAL_PRACTITIONER\n"
                                  << "1. CARDIOLOGIST\n"
                                  << "2. DERMATOLOGIST\n"
                                  << "3. GYNECOLOGIST\n"
                                  << "4. NEUROLOGIST\n"
                                  << "5. ONCOLOGIST\n"
                                  << "6. PEDIATRICIAN\n"
                                  << "7. SURGEON\n"
                                  << "8. OTHER\n";
                        std::cin >> specialization;

                        Specialization spec = static_cast<Specialization>(specialization);

                        Doctor newDoctor(id, name, spec);
                        myDatabase.addDoctor(newDoctor);
                    }
                    break;

                case 2:
                    // Delete a doctor
                    {
                        int id;
                        std::cout << "Enter the ID of the doctor to delete: ";
                        std::cin >> id;
                        myDatabase.deleteDoctorAndAppointments(id);
                    }
                    break;

                case 3:
                    // Update a doctor
                    {
                        int id;
                        std::cout << "Enter the ID of the doctor to update: ";
                        std::cin >> id;

                        // Fetch the existing doctor information
                        auto existingDoctors = myDatabase.getAllDoctors();
                        auto it = std::find_if(existingDoctors.begin(), existingDoctors.end(),
                                               [id](const Doctor &doctor)
                                               { return doctor.getId() == id; });

                        if (it != existingDoctors.end())
                        {
                            // Input updated information
                            std::string name;
                            int specialization;

                            std::cout << "Enter Updated Doctor Name: ";
                            std::cin.ignore(); // Ignore newline in the buffer
                            std::getline(std::cin, name);

                            std::cout << "Enter Updated Specialization (as an integer):\n"
                                      << "0. GENERAL_PRACTITIONER\n"
                                      << "1. CARDIOLOGIST\n"
                                      << "2. DERMATOLOGIST\n"
                                      << "3. GYNECOLOGIST\n"
                                      << "4. NEUROLOGIST\n"
                                      << "5. ONCOLOGIST\n"
                                      << "6. PEDIATRICIAN\n"
                                      << "7. SURGEON\n"
                                      << "8. OTHER\n";
                            std::cin >> specialization;

                            Specialization spec = static_cast<Specialization>(specialization);

                            Doctor updatedDoctor(id, name, spec);
                            myDatabase.updateDoctor(id, updatedDoctor);
                        }
                        else
                        {
                            std::cout << "Doctor with ID " << id << " not found." << std::endl;
                        }
                    }
                    break;

                case 4:
                    // Show all doctors
                    myDatabase.showAllDoctors("doctors.txt");
                    break;

                case 5:
                    std::cout << "Exiting...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            }

            while (subchoice != 5);
            break;

        case 2:

            int patientChoice;

            do
            {

                std::cout << "\n==== Patient Management ====\n";
                std::cout << "1. Add Patient\n";
                std::cout << "2. Delete Patient\n";
                std::cout << "3. Update Patient\n";
                std::cout << "4. Show All Patients\n";
                std::cout << "5. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> patientChoice;

                switch (patientChoice)
                {
                case 1:
                    // Add a new patient
                    {
                        int id;
                        std::string name;
                        int age;

                        std::cout << "Enter Patient ID: ";
                        std::cin >> id;

                        std::cout << "Enter Patient Name: ";
                        std::cin.ignore(); // Ignore newline in the buffer
                        std::getline(std::cin, name);

                        std::cout << "Enter Patient Age: ";
                        std::cin >> age;

                        Patient newPatient(id, name, age);
                        myDatabase.addPatient(newPatient);
                    }
                    break;

                case 2:
                    // Delete a patient
                    {
                        int id;
                        std::cout << "Enter the ID of the patient to delete: ";
                        std::cin >> id;
                        myDatabase.deletePatientAndAppointments(id);
                    }
                    break;

                case 3:
                    // Update a patient
                    {
                        int id;
                        std::cout << "Enter the ID of the patient to update: ";
                        std::cin >> id;

                        // Fetch the existing patient information
                        auto existingPatients = myDatabase.getAllPatients();
                        auto it = std::find_if(existingPatients.begin(), existingPatients.end(),
                                               [id](const Patient &patient)
                                               { return patient.getId() == id; });

                        if (it != existingPatients.end())
                        {
                            // Input updated information
                            std::string name;
                            int age;

                            std::cout << "Enter Updated Patient Name: ";
                            std::cin.ignore(); // Ignore newline in the buffer
                            std::getline(std::cin, name);

                            std::cout << "Enter Updated Patient Age: ";
                            std::cin >> age;

                            Patient updatedPatient(id, name, age);
                            myDatabase.updatePatient(id, updatedPatient);
                        }
                        else
                        {
                            std::cout << "Patient with ID " << id << " not found." << std::endl;
                        }
                    }
                    break;

                case 4:
                    // Show all patients
                    myDatabase.showAllPatientsFromFile("patients.txt");
                    myDatabase.calculateAndPrintPatientStatistics(myDatabase.getAllPatients());
                    break;

                case 5:
                    std::cout << "Returning to Main Menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            } while (patientChoice != 5);
            break;

        case 3:

            int appointmentChoice;

            do
            {
                // Display appointment menu
                std::cout << "\n==== Appointment Management ====\n";
                std::cout << "1. Add Appointment\n";
                std::cout << "2. Delete Appointment\n";
                std::cout << "3. Update Appointment\n";
                std::cout << "4. Show All Appointments\n";
                std::cout << "5. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> appointmentChoice;

                switch (appointmentChoice)
                {
                case 1:
                    // Add a new appointment
                    {
                        int id;
                        int doctorId;
                        int patientId;
                        int hour;
                        int day;
                        int month;
                        int year;

                        std::cout << "Enter Appointment ID: ";
                        std::cin >> id;

                        std::cout << "Enter Doctor ID: ";
                        std::cin >> doctorId;

                        std::cout << "Enter Patient ID: ";
                        std::cin >> patientId;

                        std::cout << "Enter Hour: ";
                        std::cin >> hour;

                        std::cout << "Enter Day: ";
                        std::cin >> day;

                        std::cout << "Enter Month: ";
                        std::cin >> month;

                        std::cout << "Enter Year: ";
                        std::cin >> year;

                        // Fetch the doctor and patient objects from their respective vectors
                        auto doctorIt = std::find_if(myDatabase.getAllDoctors().begin(), myDatabase.getAllDoctors().end(),
                                                     [doctorId](const Doctor &doctor)
                                                     { return doctor.getId() == doctorId; });

                        auto patientIt = std::find_if(myDatabase.getAllPatients().begin(), myDatabase.getAllPatients().end(),
                                                      [patientId](const Patient &patient)
                                                      { return patient.getId() == patientId; });

                        if (doctorIt != myDatabase.getAllDoctors().end() && patientIt != myDatabase.getAllPatients().end())
                        {
                            Doctor doctor = *doctorIt;
                            Patient patient = *patientIt;

                            Appointment newAppointment(id, doctor, patient, hour, day, month, year);

                            if (operator<=(newAppointment.getDoctor(), newAppointment))
                            {
                                myDatabase.addAppointment(newAppointment);
                            }
                            else
                            {
                                std::cout << "Maximum appointment limit for this doctor is exceeded\n";
                            }
                        }
                        else
                        {
                            std::cout << "Doctor or Patient with ID not found. Please make sure they exist.\n";
                        }
                    }
                    break;

                case 2:
                    // Delete an appointment
                    {
                        int id;
                        std::cout << "Enter the ID of the appointment to delete: ";
                        std::cin >> id;
                        myDatabase.deleteAppointmentById(id);
                    }
                    break;

                case 3:
                    // Update an appointment
                    {
                        int id;
                        std::cout << "Enter the ID of the appointment to update: ";
                        std::cin >> id;

                        // Fetch the existing appointment information
                        auto existingAppointments = myDatabase.getAllAppointments();
                        auto it = std::find_if(existingAppointments.begin(), existingAppointments.end(),
                                               [id](const Appointment &appointment)
                                               { return appointment.getId() == id; });

                        if (it != existingAppointments.end())
                        {
                            // Input updated information
                            int doctorId;
                            int patientId;
                            int hour;
                            int day;
                            int month;
                            int year;

                            std::cout << "Enter Updated Doctor ID: ";
                            std::cin >> doctorId;

                            std::cout << "Enter Updated Patient ID: ";
                            std::cin >> patientId;

                            std::cout << "Enter Updated Hour: ";
                            std::cin >> hour;

                            std::cout << "Enter Updated Day: ";
                            std::cin >> day;

                            std::cout << "Enter Updated Month: ";
                            std::cin >> month;

                            std::cout << "Enter Updated Year: ";
                            std::cin >> year;

                            // Fetch the doctor and patient objects from their respective vectors
                            auto doctorIt = std::find_if(myDatabase.getAllDoctors().begin(), myDatabase.getAllDoctors().end(),
                                                         [doctorId](const Doctor &doctor)
                                                         { return doctor.getId() == doctorId; });

                            auto patientIt = std::find_if(myDatabase.getAllPatients().begin(), myDatabase.getAllPatients().end(),
                                                          [patientId](const Patient &patient)
                                                          { return patient.getId() == patientId; });

                            if (doctorIt != myDatabase.getAllDoctors().end() && patientIt != myDatabase.getAllPatients().end())
                            {
                                Doctor doctor = *doctorIt;
                                Patient patient = *patientIt;

                                Appointment updatedAppointment(id, doctor, patient, hour, day, month, year);
                                myDatabase.updateAppointment(id, updatedAppointment);
                            }
                            else
                            {
                                std::cout << "Doctor or Patient with ID not found. Please make sure they exist.\n";
                            }
                        }
                        else
                        {
                            std::cout << "Appointment with ID " << id << " not found.\n";
                        }
                    }
                    break;

                case 4:
                    // Show all appointments
                    myDatabase.showAllAppointmentsFromFile("appointments.txt");
                    break;

                case 5:
                    std::cout << "Returning to Main Menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            } while (appointmentChoice != 5);
            break;

        case 4:
            myDatabase.displayAllPersons(myDatabase.getAllPersons());

        case 5:

            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 4);
}
