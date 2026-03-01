#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Task {
	public:
		int id;
		string description;
		Task* next;
	Task(int val,string desc) {
		id = val;
		description = desc;
		next = nullptr;
	}
};


class TodoList {
	private:
		Task* head;
		int nextId;
	public:
		TodoList() {
			head = nullptr;
			nextId = 1;
			loadFromFile();
		}

		~TodoList() {
			saveToFile();
			Task* current = head;
			while(current != nullptr) {
				Task* nextTask = current->next;
				delete current;
				current = nextTask;
			}
			cout<<"Memory Cleaned Up!"<<endl;
		}

	void saveToFile() {
		ofstream outFile("tasks.txt");
		Task* current = head;

		while(current != nullptr) {
			outFile << current->id << "|" << current->description << endl;
			current = current->next;
		}
		outFile.close();
	}

	void loadFromFile() {
		ifstream inFile("tasks.txt");
		if(!inFile) return;

		string line;
		while(getline(inFile, line)) {
			size_t pos = line.find('|');
			if(pos == string::npos) continue;

			int idFromFile = stoi(line.substr(0,pos));
			string desc = line.substr(pos+1);

			addTask(desc, idFromFile);
		}
	}

	void deleteTask(int targetId) {
		if(head == nullptr) {
			cout << "List is already empty!" << endl;
			return;
		}
		if(head->id == targetId) {
			Task* temp = head;
			head = head->next;
			delete temp;
		} else {
			Task* temp = head;
			while(temp->next != nullptr && temp->next->id != targetId) {
				temp = temp->next;
			}
			if(temp->next == nullptr) {
				cout << "Task ID not found!" << endl;
				return;
			}
			Task* victim = temp->next;
			temp->next = victim->next;
			delete victim;
		}	
	}

	void addTask(string desc, int forcedId = -1) {

		int idToUse;
		if (forcedId != -1) {
			idToUse = forcedId;
			if(idToUse >= nextId) {
				nextId = idToUse + 1;
			}
		} else {
			idToUse = nextId++;
		}

		Task* newNode = new Task(idToUse,desc);

		if(head == nullptr) {
			head = newNode;
		} else {
			Task* temp = head;
			while(temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	void showTask() {
		Task* current = head;

		while(current != nullptr) {
			cout<<"ID: "<< current->id << " - " << current->description << endl;
			current = current->next;
		}
	}
};

int main(int argc, char* argv[]) {
	TodoList myTasks;

	if(argc < 2) {
		cout << "Usage: ./main [command] [argument]" << endl;
		cout << "Commands : --add, --list, -del" <<endl;
		return 0;
	}

	string command = argv[1];

	if(command == "--add" && argc > 2) {
		myTasks.addTask(argv[2]);
	}
	else if(command == "--list") {
		myTasks.showTask();
	}

	else if(command == "--del" && argc > 2) {
		//stoi converts string to int
		myTasks.deleteTask(stoi(argv[2]));
	} else {
		cout<<"Unknown command or missing argument!" << endl;
	}

	return 0;
}
