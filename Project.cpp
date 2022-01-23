#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

//implementation of the class Repair where all the information will be saved
class Repair {
private:
	// Private data members
	std::string client;
	std::string problem;
	std::string solution;
	int time, taskId;
	bool status;
	static int id;
public:
	// Public member functions
	Repair(){
		client = problem = solution = "";
		time = 0;
		status = false;
		taskId = id;
		id++;
	}

	Repair(std::string cl, std::string prob, std::string sol, int t = 0, bool s = false) {
		client = cl;
		problem = prob;
		solution = sol;
		time = t;
		status = s;
		taskId = id;
		id++;
	}
    void setTime(int t);
    void setStatus(bool s);
    void addToSolution();
    void addToTime();
    int getTime();
    bool getStatus();
    std::string getClient();
    std::string getProblem();
    std::string getSolution();
    int getTaskId();
    void writeToFile(std::ofstream& fout);
    void readFromFile(std::ifstream& fin);
    void display();
    void edit();
    void inputFromUser();
};


void Repair::setTime(int t) {
		time = t;
}

void Repair::setStatus(bool s) {
		status = s;
}

void Repair::addToSolution() {
		string sol;
		cout << "Enter what you want to add to the solution: ";
		cin.ignore();
		getline(cin, sol);
		solution += (" " + sol);
}

void Repair::addToTime() {
		int min;
		cout << "Enter the time you want to add in the repair (in minutes): ";
		cin >> min;
		while (cin.fail()){
			cout << "Please enter a correct amount of time: ";
			cin >> min;
		}
		time += min;
}

int Repair::getTime() {
		return time;
}

bool Repair::getStatus() {
		return status;
}

string Repair::getClient(){
		return client;
}

string Repair::getProblem(){
		return problem;
}

string Repair::getSolution(){
		return solution;
}

int Repair::getTaskId(){
		return taskId;
}

void Repair::writeToFile(ofstream& fout){
		fout << client << endl << problem << endl << solution << endl;
		fout << time << endl << status << endl;
}

void Repair::readFromFile(ifstream& fin){
		fin.ignore();
		getline(fin, client);
		getline(fin, problem);
		getline(fin, solution);
		fin >> time >> status;
}

void Repair::display(){
		cout << endl;
		cout << "Client Name: " << client << endl;
		cout << "Problem: " << problem << endl;
		if (status){
			cout << "Solution: " << solution << endl;
			cout << "Time taken: " << time << "min(s)" << endl;
		}
		cout << "Status: ";
		if (status)
			cout << "Completed";
		else cout << "Pending";
		cout << endl;
}

void Repair::edit() {
		display();
		cin.ignore();
		cout << endl << "Enter the client's name: ";
		getline(cin, client);
		cout << "Enter the problem: ";
		getline(cin, problem);
		if (status){
			cout << "Enter the solution: ";
			getline(cin, solution);
			cout << "Enter the time spent on this repair (in minutes): ";
			cin >> time;
		}
		else{
			cout << endl << "Task status: pending" << endl;
		}
}

void Repair::inputFromUser(){
		cin.ignore();
		cout << "Enter the client's name: ";
		getline(cin, client);
		cout << "Enter the problem: ";
		getline(cin, problem);
		status = false;
		cout << endl << "Your Task ID is: " << taskId << endl;
}

int Repair::id = 1111;

// Function prototypes
void title();
int menu();
int findRepair(vector<Repair> r);
void saveRecordsToFile(vector<Repair> r);
void readRecordsFromFile(vector<Repair>& r);
void display3MostDifficultRepairs(vector<Repair> r);
void displayPendingRepairs(vector<Repair> r);
void printReport(vector<Repair> r);

int main() {
	// local variables
	int ind;

	title();
	cout << endl << "\n\t\tPress any key to be start the repair program";
	_getch();

	system(CLEAR);
	int ch = menu();

	//creating the vector
	vector <Repair> repairs;

	while (1) {
		// switch-case for menu based interface
		switch (ch) {
		case 1:		// initialize database
			repairs.clear();
			break;
		case 2:		// save records to file
			saveRecordsToFile(repairs);
			break;
		case 3:		// read records from file
			readRecordsFromFile(repairs);
			break;
		case 4:		// add new repair task
			repairs.push_back(Repair());
			repairs[repairs.size() - 1].inputFromUser();
			break;
		case 5:		// Edit a repair task
			ind = findRepair(repairs);
			if (ind != -1) {
				repairs[ind].edit();
			}
			break;
		case 6:		// Delete a repair task
			ind = findRepair(repairs);
			if (ind != -1) {
				repairs.erase(repairs.begin() + ind);
			}
			break;
		case 7:		// Add fix to a task
			ind = findRepair(repairs);
			if (ind != -1) {
				char c;
				cout << endl << "Do you want to add to the solution? (y/n): ";
				cin >> c;
				cin.ignore();
				if (c == 'y' || c == 'Y') {
					repairs[ind].addToSolution();
				}
				cout << endl << "Do you want to add to the time? (y/n): ";
				cin >> c;
				cin.ignore();
				if (c == 'y' || c == 'Y')
				{
					repairs[ind].addToTime();
				}
				repairs[ind].setStatus(true);
			}
			break;
		case 8:		// display the 3 most difficult repairs
			display3MostDifficultRepairs(repairs);
			break;
		case 9:		// display the pending repairs
			displayPendingRepairs(repairs);
			break;
		case 10:	// display the report
			printReport(repairs);
			break;
		case 0:		// exit the program
			cout << "\n\tYou have successfully exited the program.\n";
			return 0;
		}

		if (ch >= 4 && ch <= 7)
		{
			cout << endl << "Do you want to go again? (y/n) ";
			char c;
			cin >> c;
			if (c == 'y' || c == 'Y')
				continue;
		}

		cout << endl << "Press any key to be redirected to the menu...";
		_getch();
		system(CLEAR); //cleaning the screen so the menu won't repeat itself
		ch = menu();
	}
}

void title(){
	printf("\n     ======================================================================\n");
	printf("\t\t\t     REPAIR SHOP TRACKER \n");
	printf("\t   Welcome to the best program to keep track the repairs\n");
	printf("\t\t  Object-Oriented Programming final project\n");
	printf("     ======================================================================\n");

	for (int i=0; i < 75; i++) {
		putchar('_');
	}
}

// Display the menu and return the user choice
int menu() {
	cout << "\n\t\t\t\tMAIN MENU \n" << endl;
	cout << "\n\t[1] Initialize database" << endl;
	cout << "\n\t[2] Save records to file" << endl;
	cout << "\n\t[3] Read records from file" << endl;
	cout << "\n\t[4] Add a new repair task" << endl;
	cout << "\n\t[5] Edit a repair task" << endl;
	cout << "\n\t[6] Delete a repair task" << endl;
	cout << "\n\t[7] Perform fix to a task" << endl;
	cout << "\n\t[8] Display 3 most difficult repairs" << endl;
	cout << "\n\t[9] Display the pending repairs" << endl;
	cout << "\n\t[10] Print a report" << endl;
	cout << "\n\t[0] Exit" << endl;
	cout << endl << "\nEnter your choice: ";
	int choice;
	cin >> choice;
	return choice;
}

// Function which takes the taskID from the user and returns
// the index of the repair task
int findRepair(vector<Repair> r) {
	int taskId;
	cout << "Enter the task ID of the repair: ";
	cin >> taskId;
	for (int i = 0; i < r.size(); i++)
		if (r[i].getTaskId() == taskId)
			return i;

	cout << endl << "Task not found!" << endl;
	return -1;
}

// Function which writes all the records to the file
void saveRecordsToFile(vector<Repair> r) {
	ofstream fout("data.txt");
	fout << r.size() << endl;
	for (int i = 0; i < r.size(); i++)
	{
		r[i].writeToFile(fout);
	}
	fout.close();
	cout << endl << "Data was successfully written into the file \"data.txt\"" << endl;
}

// Function which reads the records from the file
void readRecordsFromFile(vector<Repair>& r) {
	ifstream fin("data.txt");

	int num;
	fin >> num;
	for (int i = 0; i < num; i++)
	{
		Repair repair;
		repair.readFromFile(fin);
		r.push_back(repair);
	}
	fin.close();
	cout << endl << "Data was successfully read from the file \"data.txt\"" << endl;
}

// Function to display the 3 most difficult repairs
void display3MostDifficultRepairs(vector<Repair> r) {
	cout << endl << "=============================================================================================" << endl;
	cout << "                                3 MOST DIFFICULT REPAIRS" << endl;
	cout << "==============================================================================================" << endl;
	cout << "Task ID    Client          Problem               Solution                  TimeTaken    Status" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;

	vector <bool> check(r.size(), false);
	for (int i = 0; i < 3; i++) {
		int max = 0;
		int maxInd = -1;
		for (int j = 0; j < r.size(); j++) {
			if (!check[j] && max < r[j].getTime()) {
				max = r[j].getTime();
				maxInd = j;
			}
		}

		if (maxInd != -1) {
			cout << setw(11) << left << r[maxInd].getTaskId();
			cout << setw(16) << left << r[maxInd].getClient();
			cout << setw(21) << left << r[maxInd].getProblem();
			cout << setw(27) << left << r[maxInd].getSolution();
			cout << r[maxInd].getTime() << setw(8) << left << "min(s)" << "Completed" << endl;
			check[maxInd] = true;
		}
		else {
			if (i == 0) cout << "No Completed Repairs!" << endl;
			break;
		}
	}
	cout << "----------------------------------------------------------------------------------------------" << endl;
}

// Function to display the pending repairs
void displayPendingRepairs(vector<Repair> r) {
	cout << endl << "===================================================================" << endl;
	cout << "                         PENDING REPAIRS" << endl;
	cout << "===================================================================" << endl;
	cout << "Task ID     Client            Problem                       Status" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	bool f = false;
	for (int j = 0; j < r.size(); j++) {
		if (!r[j].getStatus()) {
			cout << setw(12) << left << r[j].getTaskId();
			cout << setw(18) << left << r[j].getClient();
			cout << setw(30) << left << r[j].getProblem();
			cout << "Pending" << endl;
			f = true;
		}
	}
	if (!f) {
		cout << endl << "No pending repairs!" << endl;
	}
	cout << "-------------------------------------------------------------------" << endl;
}

// Function to print the report for the repairs
void printReport(vector<Repair> r) {
	cout << endl << "==========================================================================================" << endl;
	cout << "                                         REPORT" << endl;
	cout << "==========================================================================================" << endl;
	cout << "Task ID     Client          Problem            Solution               Time        Status" << endl;
	bool f = false;
	for (int j = 0; j < r.size(); j++) {
		if (r[j].getStatus()) {
			cout << setw(12) << left << r[j].getTaskId();
			cout << setw(16) << left << r[j].getClient();
			cout << setw(18) << left << r[j].getProblem();
			cout << setw(24) << left << r[j].getSolution();
			cout << setw(12) << left << to_string(r[j].getTime()) + "min(s)";
			cout << "Completed" << endl;
			f = true;
		}
	}

	for (int j = 0; j < r.size(); j++) {
		if (!r[j].getStatus()) {
			cout << setw(12) << left << r[j].getTaskId();
			cout << setw(16) << left << r[j].getClient();
			cout << setw(18) << left << r[j].getProblem();
			cout << setw(24) << left << r[j].getSolution();
			cout << setw(12) << left << to_string(r[j].getTime()) + "min(s)";
			cout << "Pending" << endl;
			f = true;
		}
	}

	if (!f) {
		cout << endl << "No repairs!" << endl;
	}
	cout << "------------------------------------------------------------------------------------------" << endl;
}