#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "pipeline.h"
#include "menu.h"
#include <sstream>

using std::cout;
using std::cin;

void add_pipe(std::unordered_map<int, Pipeline>& pipes);
void out_pipes(const std::unordered_map<int, Pipeline>& pipes);
void add_cs(std::unordered_map<int, CS>& cs);
void out_cs(const std::unordered_map<int, CS>& cs);
void out_to_file(const std::unordered_map<int, Pipeline>& pipes, const std::unordered_map<int, CS>& cs);
void main_get_from_file(std::unordered_map<int, Pipeline>& pipes, std::unordered_map<int, CS>& cs);
void delete_pipe(std::unordered_map<int, Pipeline>& pipes);
void delete_cs(std::unordered_map<int, CS>& cs);
void change_pipes(std::unordered_map<int, Pipeline>& pipes);
void change_cs(std::unordered_map<int, CS>& cs);


int main()
{
	std::unordered_map<int, Pipeline> pipes;
	std::unordered_map<int, CS> cs;

	short int choice_menu = 1;

	while (true) 
	{
		choice_menu = menu();
		switch (choice_menu)
		{
		case 1: add_pipe(pipes); break;
		case 2: out_pipes(pipes); break;
		case 3: add_cs(cs); break;
		case 4: out_cs(cs); break;
		case 5: out_to_file(pipes, cs); break;
		case 6: main_get_from_file(pipes, cs); break;
		case 7: out_pipes(pipes); out_cs(cs); break;
		case 8: delete_pipe(pipes); break;
		case 9: delete_cs(cs); break;
		case 10: filter_pipes_by_name(pipes); break;
		case 11: filter_pipes_by_repair(pipes); break;
		case 12: change_pipes(pipes); break;
		case 13: change_cs(cs); break;
		case 0: return 0;
		}
	}

	return 0;
};


void add_pipe(std::unordered_map<int, Pipeline>& pipes)
{
	Pipeline new_pipe;
	cin >> new_pipe;
	pipes.insert({ new_pipe.GetID(), new_pipe });
};

void out_pipes(const std::unordered_map<int, Pipeline>& pipes)
{
	cout << "pipes:\n";
	for (const auto& pair : pipes) {
		std::cout << pair.second << std::endl;
	}
}

void add_cs(std::unordered_map<int, CS>& cs)
{
	CS new_cs;
	cin >> new_cs;
	cs.insert({ new_cs.GetID(), new_cs });
};

void out_cs(const std::unordered_map<int, CS>& cs)
{
	cout << "CS:\n";
	for (const auto& pair : cs) {
		std::cout << pair.second << std::endl;
	}
}

void out_to_file(const std::unordered_map<int, Pipeline>& pipes, const std::unordered_map<int, CS>& cs)
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter file: ";
	std::string file;
	getline(cin, file);

	std::ofstream out(file);

	for (const auto& pipe : pipes) {
		file_out_pipe(out, pipe.second);
	}

	for (const auto& myCS : cs) {
		file_out_cs(out, myCS.second);
	}

	out.close();
}


void main_get_from_file(std::unordered_map<int, Pipeline>& pipes, std::unordered_map<int, CS>& cs)
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter file: ";
	std::string file;
	getline(cin, file);
	std::string line;

	std::ifstream in(file);

	if (!in.is_open()) {
		std::cerr << "Error: Could not open file " << file << std::endl;
		return;
	}

	if (in.peek() == std::ifstream::traits_type::eof()) {
		std::cerr << "Error: File " << file << " is empty." << std::endl;
		in.close();
		return;
	}

	while (getline(in, line))
	{
		if (line == "@pipeline@")
		{
			get_from_file(in, pipes);
		}
		else if (line == "@cs@")
		{
			get_from_file(in, cs);
		}
	}
}

void delete_pipe(std::unordered_map<int, Pipeline>& pipes)
{
	out_pipes(pipes);

	int choice = -1;
	while (true)
	{
		cout << "Enter id of pipe: ";
		while (!(cin >> choice) || (cin.peek() != '\n') || (choice < 0)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item:\n";
		};

		if (!(pipes.find(choice) == pipes.end()))
		{
			pipes.erase(choice);
			return;
		}
		else { cout << "You don't have pipe with " << choice << " id\n"; }
	}
}

void delete_cs(std::unordered_map<int, CS>& cs)
{
	out_cs(cs);

	int choice = -1;
	while (true)
	{
		cout << "Enter id of cs: ";
		while (!(cin >> choice) || (cin.peek() != '\n') || (choice < 0)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item:\n";
		};

		if (!(cs.find(choice) == cs.end()))
		{
			cs.erase(choice);
			return;
		}
		else { cout << "You don't have pipe with " << choice << " id\n"; }
	}
}

void change_pipes(std::unordered_map<int, Pipeline>& pipes)
{
	out_pipes(pipes);

	std::string ids_input;
	cout << "Enter IDs of pipes (separated by spaces): ";
	cin.ignore();
	getline(cin, ids_input);

	// Разбиваем строку на отдельные ID
	std::istringstream ss(ids_input);
	std::vector<int> ids;
	int id;

	while (ss >> id) {
		if (id >= 0) {
			ids.push_back(id);
		}
		else {
			cout << "Invalid ID ignored: " << id << std::endl;
		}
	}

	if (ids.empty()) {
		cout << "No valid IDs entered.\n";
		return;
	}

	cout << "Enter repair status (0 - working, 1 - under repair): ";
	int repair = -1;
	while (!(cin >> repair) || (cin.peek() != '\n') || (repair < 0 || repair > 1)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Select correct item:\n";
	}

	// Изменение статуса ремонта для всех введённых ID
	bool any_pipe_found = false;
	for (int id : ids) {
		auto it = pipes.find(id);
		if (it != pipes.end()) {
			ChangeRepair(it->second, repair);
			cout << "Updated pipe with ID " << id << ": " << it->second << std::endl;
			any_pipe_found = true;
		}
		else {
			cout << "No pipe found with ID " << id << std::endl;
		}
	}

	if (!any_pipe_found) {
		cout << "No pipes were updated.\n";
	}
}

void change_cs(std::unordered_map<int, CS>& cs)
{
	out_cs(cs);

	int id = -1;
	while (true)
	{
		cout << "Enter id of pipe: ";
		while (!(cin >> id) || (cin.peek() != '\n') || (id < 0)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item:\n";
		};

		if (!(cs.find(id) == cs.end()))
		{
			int work = -1;
			cout << "Enter working workshops: ";
			while (!(cin >> work) || (cin.peek() != '\n') || (work < 0 || work > 1)) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "" << "Select correct item:\n";
			}

			auto it = cs.find(id);
			int w = ChangeWorkshopsInWork(it->second, work);
			if (!(w == -1))
			{
				cout << "Error in this cs have " << w << " workshops\n";
				return;
			}
			cout << it->second << std::endl;
			return;
		}
		else { cout << "You don't have pipe with " << id << " id\n"; }
	}
}
