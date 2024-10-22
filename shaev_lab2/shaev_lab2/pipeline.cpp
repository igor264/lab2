#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "pipeline.h"
#include "log.h"  // Заголовочный файл для логирования

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
    if (std::to_string(int_numb).size() == str_numb.size() && !(int_numb < 0))
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
    log("Pipe name entered: " + pipe.PipeName);

    cout << "Enter length: ";
    pipe.LengthOfPipe = correct_int();
    log("Pipe length entered: " + std::to_string(pipe.LengthOfPipe));

    cout << "Enter diameter: ";
    pipe.Diameter = correct_int();
    log("Pipe diameter entered: " + std::to_string(pipe.Diameter));

    cout << "Enter repair (0 - working, 1 - on repairing): ";
    pipe.RepairIndicator = correct_int(0, 1);
    log("Pipe repair status entered: " + std::to_string(pipe.RepairIndicator));

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
    log("CS name entered: " + cs.CSName);

    cout << "Enter number of workshops: ";
    cs.NumberOfWorkshops = correct_int();
    log("Number of workshops entered for CS: " + std::to_string(cs.NumberOfWorkshops));

    cout << "Enter workshops in work: ";
    cs.WorkshopsInWork = correct_int(0, cs.NumberOfWorkshops);
    log("Workshops in work for CS entered: " + std::to_string(cs.WorkshopsInWork));

    cout << "Enter efficiency (0-100): ";
    cs.Efficiency = correct_int(0, 100);
    log("Efficiency entered for CS: " + std::to_string(cs.Efficiency));

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
        << "\nCS name: " << cs.CSName
        << "\nCS number of workshops: " << cs.NumberOfWorkshops
        << "\nCS workshops in work: " << cs.WorkshopsInWork
        << "\nThe CS attribute: " << cs.Efficiency << endl;
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
        log("Pipe loaded from file: " + pipe.PipeName);

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
            int numb = std::stoi(line);
            if (numb <= new_cs.NumberOfWorkshops)
            {
                new_cs.WorkshopsInWork = numb;
            }
            else { cout << "Error in file!!!\n"; return; }
        }
        else { cout << "Error in file!!!\n"; return; }

        std::getline(in, line);
        if (correct_int(line) != -1)
        {
            int numb = std::stoi(line);
            if (numb <= 100)
            {
                new_cs.Efficiency = numb;
            }
        }
        else { cout << "Error in file!!!\n"; return; }

        cs.insert({ new_cs.GetID(), new_cs });
        log("CS loaded from file: " + new_cs.CSName);

    }
    catch (const std::exception& e)
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
        log("Workshops in work changed for CS: " + cs.CSName + " to " + std::to_string(new_WorkshopsInWork));
        return cs.NumberOfWorkshops;
    }
    else { return -1; }
}

void ChangeRepair(Pipeline& pipe, bool repair)
{
    pipe.RepairIndicator = repair;
    log("Repair status changed for pipe: " + pipe.PipeName + " to " + std::to_string(repair));
}

void filter_pipes_by_name(std::unordered_map<int, Pipeline>& pipes)
{
    string name;
    cout << "Enter the name or part of the name of the pipe to filter: ";
    cin >> name;
    log("Filtering pipes by substring: " + name);
    vector<int> ids;

    for (const auto& p : pipes) {
        if (p.second.PipeName.find(name) != std::string::npos) {
            cout << p.second;
            ids.push_back(p.second.PipeID);
        }
    }

    int ch;
    cout << "" << "0 - menu:\n1 - chenge pipe\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0 || ch > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    if (ch == 0) { return; }
    cout << "Enter repair\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0 || ch > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    for (const auto& id : ids)
    {
        ChangeRepair(pipes[id], ch);
    }
}


void filter_pipes_by_repair(std::unordered_map<int, Pipeline>& pipes)
{
    int repair_status;
    cout << "Enter repair status (0 - working, 1 - on repairing): ";
    repair_status = correct_int(0, 1);
    log("Filtering pipes by repair status: " + std::to_string(repair_status));
    vector<int> ids;

    for (const auto& p : pipes) {
        if (p.second.RepairIndicator == repair_status) {
            cout << p.second;
            ids.push_back(p.second.PipeID);
        }
    }

    int ch;
    cout << "" << "0 - menu:\n1 - chenge pipe\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0 || ch > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    if (ch == 0) { return; }
    cout << "Enter repair\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0 || ch > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    for (const auto& id : ids)
    {
        ChangeRepair(pipes[id], ch);
    }
}

void filter_cs_by_name(std::unordered_map<int, CS>& cs)
{
    string name;
    cout << "Enter the name of the cs to filter: ";
    cin >> name;
    log("Filtering cs by name: " + name);
    vector<int> ids;

    for (const auto& p : cs) {
        if (p.second.CSName.find(name) != std::string::npos) {
            cout << p.second;
            ids.push_back(p.second.CSID);
        }
    }
    int ch;
    cout << "" << "0 - menu:\n1 - chenge cs\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0 || ch > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    if (ch == 0) { return; }
    cout << "Enter number of workshops in work\n";
    while (!(cin >> ch) || (cin.peek() != '\n') || (ch < 0)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "" << "Select correct item:\n";
    };

    for (const auto& id : ids)
    {
        if (ChangeWorkshopsInWork(cs[id], ch) == -1)
        {
            cout << "error in workshops in cs id=" << id << endl;
        }
    }
}


void filter_cs_by_work_percentage(std::unordered_map<int, CS>& cs)
{
    int percentage;
    cout << "Enter the work percentage to filter (0-100): ";
    percentage = correct_int(0, 100);
    log("Filtering CS by work percentage: " + std::to_string(percentage));

    int choice;
    cout << "Choose option: 1 - More than " << percentage << "%, 2 - Less than " << percentage << "%: ";
    while (!(cin >> choice) || (cin.peek() != '\n') || (choice < 1 || choice > 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Select correct option (1 or 2): ";
    }

    vector<int> ids;
    for (const auto& p : cs) {
        int current_percentage = (p.second.WorkshopsInWork * 100) / p.second.NumberOfWorkshops;
        if ((choice == 1 && current_percentage > percentage) ||
            (choice == 2 && current_percentage < percentage)) {
            cout << p.second;
            ids.push_back(p.second.CSID);
        }
    }

    int edit_choice;
    cout << "0 - menu\n1 - edit CS\n";
    while (!(cin >> edit_choice) || (cin.peek() != '\n') || (edit_choice < 0 || edit_choice > 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Select correct option (0 or 1): ";
    }

    if (edit_choice == 0) return;

    cout << "Enter new number of workshops in work: ";
    int new_workshops_in_work;
    new_workshops_in_work = correct_int();

    for (const auto& id : ids) {
        if (ChangeWorkshopsInWork(cs[id], new_workshops_in_work) == -1) {
            cout << "Error in workshops in CS ID=" << id << endl;
        }
    }
}
