#include <iostream>
#include <fstream>
#include <string>
#include "pipeline.h"
#include <unordered_map>

using namespace std;


int Pipeline::MaxIDPipe = 0;
int CS::MaxIDCS = 0;

void max_id()
{
	Pipeline::MaxIDPipe = std::max(Pipeline::MaxIDPipe, CS::MaxIDCS);
	CS::MaxIDCS = std::max(Pipeline::MaxIDPipe, CS::MaxIDCS);
}

Pipeline::Pipeline()
{
	PipeID = MaxIDPipe++;
	max_id();
}

CS::CS()
{
	CSID = MaxIDCS++;
	max_id();
}

static int correct_int(int min, int max)
{
	int get_cin;
	while (!(cin >> get_cin) || (cin.peek() != '\n') || (get_cin < min || get_cin > max)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "" << "Enter correct number\n";
	};
	return get_cin;
};

static int correct_int()
{
	int get_cin;
	while (!(cin >> get_cin) || (cin.peek() != '\n') || (get_cin < 0)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "" << "Enter correct number\n";
	};
	return get_cin;
};

static int correct_int(std::string& str_numb)
{
	int int_numb = std::stoi(str_numb);
	if (std::to_string(int_numb).size() == str_numb.size() && !(int_numb < 0) )
	{
		return 1;
	}
	else
	{
		return -1;
	}
};


std::istream& operator >> (std::istream& in, Pipeline& pipe)
{
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter name pipe: ";
	getline(cin, pipe.PipeName);
	cerr << pipe.PipeName << endl;
	cout << "Enter lenght: ";
	pipe.LengthOfPipe = correct_int();
	cout << "Enter diametr: ";
	pipe.Diameter = correct_int();
	cout << "Enter repair (0 - working, 1 - on repearing): ";
	pipe.RepairIndicator = correct_int(0, 1);
	return in;
}

std::ostream& operator << (std::ostream& out, const Pipeline& pipe)
{
	if ((pipe.PipeName) == "None")
	{
		out << "You have 0 pipe" << endl;
		return out;
	}
	out << "\nID: " << pipe.PipeID
		<< "\nPipe name: " << pipe.PipeName
		<< "\nPipe length: " << pipe.LengthOfPipe
		<< "\nPipe diameter: " << pipe.Diameter
		<< "\nThe pipe attribute: " << pipe.RepairIndicator << endl;
	return out;
};


std::istream& operator >> (std::istream& in, CS& cs)
{
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter name CS: ";
	getline(cin, cs.CSName);
	cerr << cs.CSName << endl;
	cout << "Enter number of workshops: ";
	cs.NumberOfWorkshops = correct_int();
	cout << "Enter workshops in work: ";
	cs.WorkshopsInWork = correct_int(0, cs.NumberOfWorkshops);
	cout << "Enter efficiency (0-100): ";
	cs.Efficiency = correct_int(0, 100);
	return in;
}

std::ostream& operator << (std::ostream& out, const CS& cs)
{
	if ((cs.CSName) == "None")
	{
		out << "You have 0 CS" << endl;
		return out;
	}
	out << "\nID: " << cs.CSID
		<< "\ncs name: " << cs.CSName
		<< "\ncs number of workshops: " << cs.NumberOfWorkshops
		<< "\ncs workshops in work: " << cs.WorkshopsInWork
		<< "\nThe cs attribute: " << cs.Efficiency << endl;
	return out;
};

void file_out_pipe(std::ofstream& out, const Pipeline& pipe)
{
	out << "@pipeline@" << '\n'
		<< pipe.PipeName << '\n'
		<< pipe.LengthOfPipe << '\n'
		<< pipe.Diameter << '\n'
		<< pipe.RepairIndicator << '\n';
}

void file_out_cs(std::ofstream& out, const CS& cs)
{
	out << "@cs@" << '\n'
		<< cs.CSName << '\n'
		<< cs.NumberOfWorkshops << '\n'
		<< cs.WorkshopsInWork << '\n'
		<< cs.Efficiency << '\n';
}

void get_from_file(std::ifstream& in, std::unordered_map<int, Pipeline>& pipes)
{
	try {
		Pipeline pipe;

		std::string line;

		std::getline(in, line);
		pipe.PipeName = line;

		std::getline(in, line);
		if (correct_int(line) != -1)
		{
			pipe.LengthOfPipe = std::stoi(line);
		}
		else { cout << "Error in file!!!\n"; return; }

		std::getline(in, line);
		if (correct_int(line) != -1)
		{
			pipe.Diameter = std::stoi(line);
		}
		else { cout << "Error in file!!!\n"; return; }

		std::getline(in, line);
		if (correct_int(line) != -1)
		{

			int numb = std::stoi(line);
			if (numb <= 1)
			{
				pipe.RepairIndicator = numb;
			}
			else { cout << "Error in file!!!\n"; return; }
		}
		else { cout << "Error in file!!!\n"; return; }

		pipes.insert({ pipe.GetID(), pipe });
	}
	catch (const std::exception& e)
	{
		cout << "Error in file\n";
		return;
	}
};

void get_from_file(std::ifstream& in, std::unordered_map<int, CS>& cs)
{
	try {

		CS new_cs;

		std::string line;
		int numb = 0;

		std::getline(in, line);
		new_cs.CSName = line;

		std::getline(in, line);
		if (correct_int(line) != -1)
		{
			new_cs.NumberOfWorkshops = std::stoi(line);
		}
		else { cout << "Error in file!!!\n"; return; }

		std::getline(in, line);
		if (correct_int(line) != -1)
		{
			numb = std::stoi(line);
			if (numb <= new_cs.NumberOfWorkshops)
			{
				new_cs.NumberOfWorkshops = numb;
			}
			else { cout << "Error in file!!!\n"; return; }
		}
		else { cout << "Error in file!!!\n"; return; }

		std::getline(in, line);
		if (correct_int(line) != -1)
		{
			numb = std::stoi(line);
			if (numb <= 100)
			{
				new_cs.Efficiency = numb;
			}
		}
		else { cout << "Error in file!!!\n"; return; }

		cs.insert({ new_cs.GetID(), new_cs });
	}
	catch(const std::exception& e)
	{
		cout << "Error in file\n"; 
		return;
	}
};

int ChangeWorkshopsInWork(CS& cs, int& new_WorkshopsInWork)
{
	if (new_WorkshopsInWork <= cs.NumberOfWorkshops)
	{
		cs.WorkshopsInWork = new_WorkshopsInWork;
		return cs.NumberOfWorkshops;
	}
	else { return -1; }
}

void ChangeRepair(Pipeline& pipe, bool repair)
{
	pipe.RepairIndicator = repair;
}

void filter_pipes_by_name(std::unordered_map<int, Pipeline>& pipes)
{
	string name;
	cout << "Enter name of pipe: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, name);
	cout << "pipes:\n";
	
	for (const auto& pipe : pipes) {
		if (pipe.second.PipeName.find(name) != string::npos) {
			cout << pipe.second;
		}
	}
}

void filter_pipes_by_repair(std::unordered_map<int, Pipeline>& pipes)
{
	cout << "Enter name of pipe: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int repair = correct_int(0, 1);
	cout << "pipes:\n";

	for (const auto& pipe : pipes) {
		if (pipe.second.RepairIndicator == repair) {
			cout << pipe.second;
		}
	}
}