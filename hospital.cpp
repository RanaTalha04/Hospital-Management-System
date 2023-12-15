#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

class NodeForDoc
{

public:
    string userName;
    string Password;

    NodeForDoc *next;

    NodeForDoc(string name, string password)
    {
        userName = name;
        Password = password;
        next = NULL;
    }
};

class queueForPatient
{
public:
    string Name;
    string password;
    queueForPatient *next;

    queueForPatient(string name, string pass)
    {
        Name = name;
        password = pass;
        next = NULL;
    }
};

class Admin
{
private:
    NodeForDoc *head = NULL;

public:
    void RegisterAdmin(string name, string password)
    {
        NodeForDoc *current = head;
        while (current != NULL)
        {
            if (current->userName == name)
            {
                cout << "Warning!!!!!" << endl;
                cout << "Name already exist." << endl;
                cout << "Please Enter a unique name...." << endl;
                return;
            }
            current = current->next;
        }

        NodeForDoc *newNode = new NodeForDoc(name, password);
        newNode->next = head;
        head = newNode;

        fstream File;
        File.open("Admin.txt", ios::app);
        if (File.is_open())
        {
            File << name << " " << password << endl;
            File.close();
            cout << name << " Registered Successfully....." << endl;
        }
        else
        {
            cout << "Error in file opening>>" << endl;
        }
    }

    bool LoginAdmin(string name, string password)
    {
        fstream File("Admin.txt");

        if (!File.is_open())
        {
            cout << "There is an error in opening file..." << endl;
            return false;
        }
        else
        {
            string checkname;
            string checkpassword;

            while (File >> checkname >> checkpassword)
            {
                if (checkname == name && checkpassword == password)
                {
                    cout << "Login Successfully!" << endl;
                    return true;
                    File.close();
                }
            }
            cout << "Login Failed.... Wrong user name or Password" << endl;
            File.close();
            return false;
        }
    }

    void RegisterDoc(string name, string password)
    {
        NodeForDoc *current = head;
        fstream File;
        File.open("Doctor.txt", ios::app);
        while (current != NULL)
        {
            if (current->userName == name)
            {
                cout << "Warning!!!!!" << endl;
                cout << "Name already exist." << endl;
                cout << "Please Enter a unique name...." << endl;
                return;
            }
            current = current->next;
        }

        NodeForDoc *newNode = new NodeForDoc(name, password);
        newNode->next = head;
        head = newNode;

        if (File.is_open())
        {
            File << name << " " << password << endl;
            File.close();
            cout << "Dr." << name << " Registered Successfully....." << endl;
        }
        else
        {
            cout << "Error in file opening>>" << endl;
        }
    }

    void DisplayDoc()
    {
        ifstream File("Doctor.txt");
        if (!File.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        else
        {
            string username, password;
            while (File >> username >> password)
            {
                cout << "Dr. " << username << endl;
            }

            File.close();
        }
    }
    void RemovePatient(string name)
    {
        ifstream inputFile("Doctor.txt");
        ofstream outputFile("temp.txt");

        if (!inputFile.is_open() || !outputFile.is_open())
        {
            cout << "Error opening files" << endl;
            return;
        }

        string username, password;

        while (inputFile >> username >> password)
        {
            if (username != name)
            {
                outputFile << username << " " << password << endl;
            }
        }

        inputFile.close();
        outputFile.close();

        remove("Doctor.txt");
        rename("temp.txt", "Doctor.txt");

        cout << "Dr. " << username << "removed successfully!" << endl;
    }
};

class Doctor
{
public:
    bool LoginDoc(string name, string password)
    {
        fstream File("Doctor.txt");

        if (!File.is_open())
        {
            cout << "There is an error in opening file..." << endl;
            return false;
        }
        else
        {
            string checkname;
            string checkpassword;

            while (File >> checkname >> checkpassword)
            {
                if (checkname == name && checkpassword == password)
                {
                    cout << "Login Successfully!" << endl;
                    return true;
                    File.close();
                }
            }

            cout << "Login Failed.... Wrong user name or Password" << endl;

            File.close();
            return false;
        }
    }

    void DocList()
    {
        ifstream File("Doctor.txt");
        if (!File.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        else
        {
            string username, password;
            while (File >> username >> password)
            {
                cout << "Dr. " << username << endl;
            }
            File.close();
        }
    }

    void PatientLine()
    {
        ifstream File("Patient.txt");
        if (!File.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        else
        {
            string username, password;
            while (File >> username >> password)
            {
                cout << "Patient " << username << endl;
            }
            File.close();
        }
    }

    void RemovePatient(string name)
    {
        ifstream inputFile("Patient.txt");
        ofstream outputFile("temp.txt");

        if (!inputFile.is_open() || !outputFile.is_open())
        {
            cout << "Error opening files" << endl;
            return;
        }

        string username, password;

        while (inputFile >> username >> password)
        {
            if (username != name)
            {
                outputFile << username << " " << password << endl;
            }
        }

        inputFile.close();
        outputFile.close();

        remove("Patient.txt");
        rename("temp.txt", "Patient.txt");

        cout << "Patient removed successfully!" << endl;
    }
};
class Patient
{
private:
    queue<queueForPatient> PatientQueues;

public:
    void EnquingPatient(const queueForPatient &patient)
    {
        PatientQueues.push(patient);
        fstream File("Patient.txt");

        if (File.is_open())
        {
            queue<queueForPatient> tempQueue = PatientQueues;
            while (!tempQueue.empty())
            {
                File << tempQueue.front().Name << " " << tempQueue.front().password << endl;
                tempQueue.pop();
            }
            File.close();
        }
        else
        {
            cout << "File not opening" << endl;
        }
    }

    bool LoginPatient(string name, string password)
    {
        fstream File("Patient.txt");

        if (!File.is_open())
        {
            cout << "There is an error in opening file..." << endl;
            return false;
        }
        else
        {
            string checkname;
            string checkpassword;

            while (File >> checkname >> checkpassword)
            {
                if (checkname == name && checkpassword == password)
                {
                    cout << "Login Successfully!" << endl;
                    return true;
                    File.close();
                }
            }

            cout << "Login Failed.... Wrong user name or Password" << endl;
            File.close();
            return false;
        }
    }

    void Doc_List()
    {
        ifstream File("Doctor.txt");
        if (!File.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        else
        {
            string username, password;
            while (File >> username >> password)
            {
                cout << "Dr. " << username << endl;
            }
            File.close();
        }
    }

    void PatientList()
    {
        ifstream File("Patient.txt");
        if (!File.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        else
        {
            string username, password;
            while (File >> username >> password)
            {
                cout << "Patient " << username << endl;
            }
            File.close();
        }
    }
};

int main()
{
    Doctor doc;
    Patient patient;
    Admin AdminList;
    bool loginSuccess = false;

    while (true)
    {
        cout << "--------------------------------------------------------Welcome To Shalamar Hospital-----------------------------------------------------------";
        cout << endl;
        cout << endl;

        int choice;

        cout << "                   Please identify yourself! " << endl;
        cout << "                   Press the number: " << endl;
        cout << "1. Doctor" << endl;
        cout << "2. Patient" << endl;
        cout << "3. Admin" << endl;
        cout << "4. Exit the portal." << endl;

        cin >> choice;

        if (choice == 1)
        {
            cout << endl;
            cout << endl;
            cout << "--------------------------------------------------------Welcome to Doctor's side of the portal---------------------------------------------------" << endl;

            int choice;
            cout << "                 Press the number: " << endl;
            cout << "1. Login" << endl;
            cout << "2. Main Menu" << endl;
            cout << "Press any key to exit from program" << endl;

            cin >> choice;

            if (choice == 1)
            {
                string name;
                string password;

                cout << "Enter your name to Login: ";
                cin >> name;
                cout << "\nEnter your password: ";
                cin >> password;
                if (doc.LoginDoc(name, password))
                {
                    int choi;
                    cout << "                 Enter Your choice: " << endl;
                    cout << "1. List of Doctors" << endl;
                    cout << "2. Queue of Patients" << endl;
                    cout << "3. DeQueue a patient from the line" << endl;
                    cout << "4. Main Menu" << endl;
                    cout << "Press any key to exit from program" << endl;

                    cin >> choi;
                    if (choi == 1)
                    {
                        doc.DocList();
                    }
                    else if (choi == 2)
                    {
                        doc.PatientLine();
                    }
                    else if (choi == 3)
                    {
                        doc.PatientLine();

                        string name;
                        char cho;

                        cout << "Enter the name of patient to dequeue: ";
                        cin >> name;

                        do
                        {

                            doc.RemovePatient(name);
                            cout << "Remaining Patients: " << endl;
                            doc.PatientLine();

                            cout << "Do you want to De Queue other patients?" << endl;
                            cin >> cho;
                        } while (cho == 'Y' || cho == 'y');
                    }
                    else if (choi == 4)
                    {
                        main();
                    }
                    else
                    {
                        exit(0);
                    }
                }

                else
                {
                    main();
                }
            }
            else if (choice == 2)
            {
                main();
            }
            else
            {
                exit(0);
            }
        }
        else if (choice == 2)
        {
            Patient PatientList;

            cout << endl;
            cout << endl;
            cout << "--------------------------------------------------------Welcome to Patient's side of the portal---------------------------------------------------" << endl;

            int choice;

            cout << "                   Press the number: " << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Main Menu" << endl;
            cout << "Press any key to exit from program" << endl;

            cin >> choice;

            if (choice == 1)
            {
                char choice;

                do
                {

                    string name;
                    string password;

                    cout << "Enter Name: " << endl;
                    cin >> name;

                    cout << "Enter Password: " << endl;
                    cin >> password;

                    PatientList.EnquingPatient(queueForPatient(name, password));

                    cout << "Do you want to enter more Pateint's data?" << endl;
                    cin >> choice;
                } while (choice == 'Y' || choice == 'y');

                int choi;

                cout << "         Enter your choice: " << endl;
                cout << "1. Queue of Patients" << endl;
                cout << "2. List of Doctors" << endl;
                cout << "3. Main Menu" << endl;
                cout << "Press any key to exit from portal" << endl;

                cin >> choi;

                if (choi == 1)
                {
                    PatientList.PatientList();
                }

                else if (choi == 2)
                {
                    PatientList.Doc_List();
                }

                else if (choi == 3)
                {
                    main();
                }

                else
                {
                    exit(0);
                }
            }

            else if (choice == 2)
            {
                string name;
                string password;

                cout << "Enter your name to Login: ";
                cin >> name;
                cout << "\nEnter your password: ";
                cin >> password;
                if (doc.LoginDoc(name, password))

                {
                    int choi;

                    cout << "         Enter your choice: " << endl;
                    cout << "1. Queue of Patients" << endl;
                    cout << "2. List of Doctors" << endl;
                    cout << "3. Main Menu" << endl;
                    cout << "Press any key to exit from portal" << endl;

                    cin >> choi;

                    if (choi == 1)
                    {
                        PatientList.PatientList();
                    }

                    else if (choi == 2)
                    {
                        PatientList.Doc_List();
                    }

                    else if (choi == 3)
                    {
                        main();
                    }

                    else
                    {
                        exit(0);
                    }
                }

                else
                {
                    main();
                }
            }
            else if (choice == 3)
            {
                main();
            }
            else
            {
                exit(0);
            }
        }
        else if (choice == 3)
        {
            Admin AdminList;

            cout << endl;
            cout << endl;
            cout << "--------------------------------------------------------Welcome to Admin's side of the portal!---------------------------------------------------" << endl;

            int choice;

            cout << "                   Press the number: " << endl;
            cout << "1. Register an admin" << endl;
            cout << "2. Login as an admin" << endl;
            cout << "3. Main Menu" << endl;
            cout << "Press any key to exit from program" << endl;

            cin >> choice;

            if (choice == 1)
            {
                char choice;

                do
                {

                    string name;
                    string password;
                    cout << "Enter Name: " << endl;
                    cin >> name;

                    cout << "Enter Password: " << endl;
                    cin >> password;

                    AdminList.RegisterAdmin(name, password);

                    cout << "Do you want to enter any other admin?" << endl;
                    cin >> choice;
                } while (choice == 'Y' || choice == 'y');

                int choi;

                cout << "                   Press the number: " << endl;
                cout << "1. Register a doctor" << endl;
                cout << "2. Display List of Doctors" << endl;
                cout << "3. Remove a doctor" << endl;
                cout << "4. Main Menu" << endl;
                cout << "Press any key to exit from portal" << endl;

                cin >> choi;

                if (choi == 1)
                {
                    char choice;

                    do
                    {

                        string name;
                        string password;

                        cout << "Enter Name: " << endl;
                        cin >> name;

                        cout << "Enter Password: " << endl;
                        cin >> password;

                        AdminList.RegisterDoc(name, password);

                        cout << "Do you want to enter more Doctor's data?" << endl;

                        cin >> choice;
                    } while (choice == 'Y' || choice == 'y');

                    main();
                }
                else if (choi == 2)
                {
                    AdminList.DisplayDoc();
                }
                else if (choi == 3)
                {
                    AdminList.DisplayDoc();

                    string name;
                    char cho;

                    cout << "Enter the name of Doctor to remove: ";
                    cin >> name;

                    do
                    {

                        AdminList.RemovePatient(name);
                        cout << "Remaining Doctors: " << endl;
                        AdminList.DisplayDoc();

                        cout << "Do you want to De Queue other patients?" << endl;
                        cin >> cho;
                    } while (cho == 'Y' || cho == 'y');
                }
                else if (choi == 4)
                {
                    main();
                }
                else
                {
                    exit(0);
                }
            }

            else if (choice == 2)
            {
                string name;
                string password;

                cout << "Enter Name: " << endl;
                cin >> name;

                cout << "Enter Password: " << endl;
                cin >> password;

                if (AdminList.LoginAdmin(name, password))

                {
                    int choi;

                    cout << "                   Press the number: " << endl;
                    cout << "1. Register a doctor" << endl;
                    cout << "2. Display List of Doctors" << endl;
                    cout << "3. Remove a doctor" << endl;
                    cout << "4. Main Menu" << endl;
                    cout << "Press any key to exit from portal" << endl;
                    cin >> choi;

                    if (choi == 1)
                    {
                        char choice;

                        do
                        {

                            string name;
                            string password;

                            cout << "Enter Name: " << endl;
                            cin >> name;

                            cout << "Enter Password: " << endl;
                            cin >> password;

                            AdminList.RegisterDoc(name, password);

                            cout << "Do you want to enter more Doctor's data?" << endl;

                            cin >> choice;
                        } while (choice == 'Y' || choice == 'y');

                        main();
                    }
                    else if (choi == 2)
                    {
                        AdminList.DisplayDoc();
                    }
                    else if (choi == 3)
                    {
                        AdminList.DisplayDoc();

                        string name;
                        char cho;

                        cout << "Enter the name of Doctor to remove: ";
                        cin >> name;

                        do
                        {

                            AdminList.RemovePatient(name);
                            cout << "Remaining Doctors: " << endl;
                            AdminList.DisplayDoc();

                            cout << "Do you want to De Queue other patients?" << endl;
                            cin >> cho;
                        } while (cho == 'Y' || cho == 'y');
                    }
                    else if (choi == 4)
                    {
                        main();
                    }
                    else
                    {
                        exit(0);
                    }
                }

                else
                {
                    main();
                }
            }

            else if (choice == 3)
            {
                main();
            }
            else
            {
                exit(0);
            }
        }

        else if (choice == 4)
        {
            cout << "Thank you for using Shalamar Portal....." << endl;

            exit(0);
        }

        else
        {
            char choice;

            cout << "Invalid Choice!" << endl;
            cout << "Please Try Again...." << endl;

            cout << "Do you want to Try Again or want to exit? " << endl;
            cout << "Press Y/y for re-try and any other key to exit....." << endl;

            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                main();
            }
            else
            {
                exit(0);
            }
        }
    }
    return 0;
}
