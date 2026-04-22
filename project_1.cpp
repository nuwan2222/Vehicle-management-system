#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
using namespace std;

// Functions declaration
void LOGIN();//after th login(customer/staff)
void Register();// main register
void registration();// inside registration
void forgot();//if you forgot password
void customer();//cusomer for registration
void Customer();//customer for login
void Customer_details();//inside the customer part 4
void service_recods();//view records on appointment
void Update();//customer can update details

// Staff functions
void Staff_login();
void Staff_Reg();
void staff_details();
void staff_schedule(); // staff 1
void staff_access(); // staff 2
void staff_update(); // staff 3
void staff_mark(); // staff 4


class Appointment {
public:
    string customername;
    string servicetype;
    string date;
    string time;
    bool completed; // Add this member

    Appointment(string name, string service, string date, string time, bool completed = false)
        : customername(name), servicetype(service), date(date), time(time), completed(completed) {}
};

void scheduleappointment(vector<Appointment>& appointments, const string& customername);
void Cancel(vector<Appointment>& appointments);



// Add appointment to "appointment.txt"
vector<Appointment> appointments;
const string appointment_file = "appointment.txt";



// Save appointment
void saveAppointmentsToFile(const vector<Appointment>& appointments) {
    ofstream outFile(appointment_file, ios::trunc); // Overwrite the file
    for (const auto& appointment : appointments) {
        outFile << appointment.customername << " "
                << appointment.servicetype << " "
                << appointment.date << " "
                << appointment.time << endl;
    }
    outFile.close();
}

// Function to load appointments from file
void loadAppointmentsFromFile(vector<Appointment>& appointments) {
    ifstream inFile(appointment_file, ios::in);
    string customername, servicetype, date, time;
    while (inFile >> customername >> servicetype >> date >> time) {
        appointments.emplace_back(customername, servicetype, date, time);
    }
    inFile.close();
}

// Schedule Service Appointments
void scheduleappointment(vector<Appointment>& appointments, const string& customername) {
    string servicetype, date, time ;
    cout << "Enter the type of service required: ";
    cin.ignore();
    getline(cin, servicetype);
    cout << "Enter the date (DD-MM-YYYY): ";
    getline(cin, date);
    cout << "Enter the time (HH:MM): ";
    getline(cin, time);


    appointments.emplace_back(customername, servicetype, date, time );
    saveAppointmentsToFile(appointments);
    cout << "Appointment has been scheduled successfully\n";
}

// View service records
void service_recods() {
    system("cls");
    string mytext;
    ifstream myreadfile("appointment.txt");

    while (getline(myreadfile, mytext)) {
        cout << mytext << endl;
    }

    myreadfile.close();
}

// Cancel Service Appointments
void Cancel(vector<Appointment>& appointments) {
    system("cls");
    cout << "Cancel Service Appointments:\n";

    string date, time;
    cout << "Enter the date (DD-MM-YYYY) of the appointment to cancel: ";
    cin.ignore();
    getline(cin, date);
    cout << "Enter the time (HH:MM) of the appointment to cancel: ";
    getline(cin, time);

    bool found = false;
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->date == date && it->time == time) {
            found = true;
            appointments.erase(it);
            saveAppointmentsToFile(appointments);
            cout << "Appointment on " << date << " at " << time << " has been cancelled successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "No appointment found on " << date << " at " << time << ".\n";
    }
}



// Main function
int main() {
    system("color F1");
    loadAppointmentsFromFile(appointments);
    int c;
    cout << "\t\t\t------- Vehicle Service Center Management System-------\n\n\n";                
    cout << "__________________________________________";         
    cout << "______________________________________________________________________________\n\n\n";
    cout << "\t\t\t       Welcome to the Login Page      \n\n\n";
    cout << "\t\t\t___________MENU_________  \n\n";
    cout << "\t\t\t\t| Press 1 to LOGIN |" << endl;
    cout << "\t\t\t\t| Press 2 to REGISTER |" << endl;
    cout << "\t\t\t\t| Press 3 if you FORGOT YOUR PASSWORD |" << endl;
    cout << "\t\t\t\t| Press 4 to EXIT |" << endl;
    cout << "\n\t\t\t Please enter your choice: ";
    cin >> c;
    cout << endl;

    switch (c) {
    case 1:
        LOGIN();
        break;
    case 2:
        Register();
        break;
    case 3:
        forgot();
        break;
    default:
        system("cls");
        cout << "\t\t\t Please select from the options given above\n" << endl;
        main();
    }
}

// Update Personal Information
void Update() {
    string name;
    int age;
    int Telephone;
    system("cls");
    ofstream appendFile("view.txt", ios_base::trunc);
    cout << "Enter name: ";
    cin >> name;
    appendFile << "Name is: " << name << "\n";
    cout << "Enter age: ";
    cin >> age;
    appendFile << "Age is: " << age << "\n";
    cout << "Enter Telephone: ";
    cin >> Telephone;
    appendFile << "Telephone number is: " << Telephone << "\n";
    appendFile.close();

    cout << "Your details updated successfully.";
    system("cls");
    main();
}

// Customer details
void Customer_details() {
    int e;
    string userName;
    system("cls");
    cout << "\t\t\t | Press 1 to View Service Records:| " << endl;
    cout << "\t\t\t | Press 2 to Schedule Service Appointments:| " << endl;
    cout << "\t\t\t | Press 3 to Cancel Service Appointments:| " << endl;
    cout << "\t\t\t | Press 4 to Update Personal Information:| " << endl;
    cout << "\t\t\t | Press 5 to Main Menu:| " << endl;

    cin >> e;
    cout << endl;

    switch (e) {
    case 1:
        service_recods();
        break;
    case 2:
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, userName);
        scheduleappointment(appointments, userName);
        break;
    case 3:
        Cancel(appointments);
        break;
    case 4:
        Update();
        break;
    case 5:
        system("cls");
        main();
        break;
    default:
        system("cls");
        cout << "\t\t\t Please select \n" << endl;
        main();
    }
}

// Customer login
void Customer() {
    int count;
    int ch;
    string userId, password, id, pass, confirmPass;
    system("cls");
    cout << "\t\t\t Please enter the username and password : " << endl;
    cout << "\t\t\t USERNAME:      ";
    cin >> userId;
    cout << "\t\t\t PASSWORD:     ";
    cin >> password;
    cout << "\t\t\t CONFIRM PASSWORD:    ";
    cin >> confirmPass;

    if (password != confirmPass) {
        cout << "\n ERROR: Passwords do not match.\n";
        return;
    }

    ifstream input("records.txt");

    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
        }
    }
    input.close();

    if (count == 1) {
        cout << userId << "\n Your login is successful. \n Thanks for logging in!\n";
        system("cls");
        Customer_details();
    } else {
        cout << "\n LOGIN ERROR \n Please check your username and password\n";
        main();
    }
}

// Customer registration
void customer() {
    string ruserId, rpassword, rid, rpass, confirmPass;
    system("cls");
    cout << "\t\t\t Enter the username : ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password : ";
    cin >> rpassword;
    cout << "\t\t\t Confirm the password : ";
    cin >> confirmPass;

    if (rpassword != confirmPass) {
        cout << "\n ERROR: Passwords do not match.\n";
        return;
    }

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "\n\t\t\t Registration is successful!\n";
    main();
}

// Main login
void LOGIN() {
    int a;
    system("cls");
    cout << "\t\t\t | Press 1 for Customer | " << endl;
    cout << "\t\t\t | Press 2 for Staff | " << endl;
    cout << "\t\t\t | Press 3 for main menu | " << endl;
    cin >> a;
    cout << endl;

    switch (a) {
    case 1:
        Customer();
        break;
    case 2:
        Staff_login();
        break;
    case 3:
        main();
        break;
    default:
        system("cls");
        cout << "\t\t\t Please select \n" << endl;
        main();
    }
}

// Main register
void Register() {
    int d;
    system("cls");
    cout << "\t\t\t | Press 1 for Customer | " << endl;
    cout << "\t\t\t | Press 2 for Staff | " << endl;
    cout << "\t\t\t | Press 3 for main menu | " << endl;    
    cin >> d;
    cout << endl;

    switch (d) {
    case 1:
        customer();
        break;
    case 2:
        Staff_Reg();
        break;
    case 3:
        main();
        break;
    default:
        system("cls");
        cout << "\t\t\t Please select \n" << endl;
        main();
    }
}

// Forgot password
void forgot() {
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your ID by username " << endl;
    cout << "Press 2 to go back to the main menu " << endl;
    cout << "\t\t\t Enter your choice: ";
    cin >> option;

    switch (option) {
    case 1: {
        int count = 0;
        string suserId, sId, spass;
        cout << "\n\t\t\tEnter the username: ";
        cin >> suserId;

        ifstream f2("records.txt");
        while (f2 >> sId >> spass) {
            if (sId == suserId) {
                count = 1;
            }
        }
        f2.close();
        if (count == 1) {
            cout << "\n\n Your account is found!\n";
            cout << "\n\n Your password is: " << spass;
            main();
        } else {
            cout << "\n\t Sorry! Your account is not found!\n";
            main();
        }
        break;
    }
    case 2:
        main();
        break;
    default:
        cout << "\t\t\t Wrong choice! Please try again" << endl;
        forgot();
    }
}

// Registration
void registration() {
    string ruserId, rpassword, rid, rpass;
    system("cls");
    cout << "\t\t\t Enter the username: ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "\n\t\t\t Registration is successful!\n";
    main();
}








// Staff login
void Staff_login() {
    int count;
    int ch;
    string userId, password, id, pass, confirmPass;
    system("cls");
    cout << "\t\t\t Please enter the username and password: " << endl;
    cout << "\t\t\t USERNAME:      ";
    cin >> userId;
    cout << "\t\t\t PASSWORD:     ";
    cin >> password;
    cout << "\t\t\t CONFIRM PASSWORD:    ";
    cin >> confirmPass;

    if (password != confirmPass) {
        cout << "\n ERROR: Passwords do not match.\n";
        return;
    }

    ifstream input("staff.txt");

    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
        }
    }
    input.close();

    if (count == 1) {
        cout << userId << "\n Your login is successful. \n Thanks for logging in!\n";
        system("cls");
        staff_details();
    } else {
        cout << "\n LOGIN ERROR \n Please check your username and password\n";
        main();
    }
}

// Staff registration
void Staff_Reg() {
    string ruserId, rpassword, rid, rpass, confirmPass;
    system("cls");
    cout << "\t\t\t Enter the username: ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password: ";
    cin >> rpassword;
    cout << "\t\t\t Confirm the password: ";
    cin >> confirmPass;

    if (rpassword != confirmPass) {
        cout << "\n ERROR: Passwords do not match.\n";
        return;
    }

    ofstream f1("staff.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "\n\t\t\t Registration is successful!\n";
    main();
}

// Staff details
void staff_details() {
    int s;
    system("cls");
    cout << "\t\t\t | Press 1 to View Schedule:| " << endl;
    cout << "\t\t\t | Press 2 to Access Vehicle Records:| " << endl;
    cout << "\t\t\t | Press 3 to Update Service Records:| " << endl;
    cout << "\t\t\t | Press 4 to Mark Service as Complete:| " << endl;
    cout << "\t\t\t | Press 5 to Main menu:| " << endl;

    cin >> s;
    cout << endl;

    switch (s) {
    case 1:
        service_recods();
        break;
    case 2:
        staff_access();
        break;
    case 3:
	    
        break;
    case 4:
        system("cls");
        staff_mark();
        break;
    case 5:
    	system("cls");
    	main();
    default:
        system("cls");
        cout << "\t\t\t Please select \n" << endl;
        main();
    }
}

// Staff 1;
void staff_schedule() {
    system("cls");
    string mytext;
    ifstream myreadfile("appointment.txt");

    while (getline(myreadfile, mytext)) {
        cout << mytext << endl;
    }

    myreadfile.close();
}



// staff 4
void staff_mark() {
    system("cls");
    cout << "Mark Completed Appointments:\n";

    string date, time;
    cout << "Enter the date (DD-MM-YYYY) of the appointment to mark as completed: ";
    cin.ignore();
    getline(cin, date);
    cout << "Enter the time (HH:MM) of the appointment to mark as completed: ";
    getline(cin, time);

    bool found = false;
    for (auto& appointment : appointments) {
        if (appointment.date == date && appointment.time == time) {
            found = true;
            appointment.completed = true;
            saveAppointmentsToFile(appointments);
            cout << "Appointment on " << date << " at " << time << " has been marked as completed.\n";
            break;
        }
    }

    if (!found) {
        cout << "No appointment found on " << date << " at " << time << ".\n";
    }
}






//staff 2;

// struct for ServiceRecord 

struct servicerecord{
	 string date;
	 string serviceperformed;
	 string recomondation;
	
};

//struct for Vehicle ; 
     
struct Vehicle{
	string regnumber;
     string owner;
     vector<servicerecord>servicehistory;
};	 
	 

void display_service_history(const Vehicle& vehicle){
	cout<<"service history for vehicle:" <<vehicle.regnumber<<endl;
	for(const auto& record : vehicle.servicehistory){
		cout<<"date: "<<record.date<<endl;
		cout<<"service performed: "<<record.serviceperformed<<endl;
		cout<<"recomondation: "<<record.recomondation<<endl;
	}
		
}

//vehicle search;

bool searchvehicle(const vector<Vehicle>& vehicles, const string& regnumber, Vehicle& result) {
    for (const auto& vehicle : vehicles) {
        if (vehicle.regnumber == regnumber) {
            result = vehicle;
            return true;
        }
    }
    return false;
}
void staff_access(){
    vector<Vehicle> vehicles = {
        {
            "ABC123",
            "John Doe",
            {
                {"2024-01-01", "Oil Change", "Next service due in 6 months."},
                {"2023-06-15", "Brake Pad Replacement", "Check brake fluid levels regularly."}
            }
        },
        {
            "XYZ789",
            "Jane Smith",
            {
                {"2023-11-20", "Tire Rotation", "Rotate tires every 10,000 miles."},
                {"2023-04-10", "Battery Replacement", "Check battery terminals for corrosion."}
            }
        }
    };

string regnumber;
cout<<"enter register number: ";
cin.ignore();
getline(cin,regnumber);


 Vehicle result;
     if(searchvehicle(vehicles,regnumber,result)){
     	display_service_history(result);
	 }else{
	 	cout<<"vehicle registration number"<<"  "<<regnumber<<"  "<<"not found"<<endl;
	 }

}


//staff 3


