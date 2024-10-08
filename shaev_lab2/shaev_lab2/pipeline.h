#pragma once
#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <string>
#include <iostream>
#include <unordered_map>


class Pipeline
{
private:
    static int MaxIDPipe;
    int PipeID = 0;
    int LengthOfPipe = 0;
    short int Diameter = 0;
    std::string PipeName = "None";
    bool RepairIndicator = 0;
public:

    Pipeline();
    int GetID() const { return PipeID; };
    friend void ChangeRepair(Pipeline& pipe, bool repair);
    friend std::istream& operator >> (std::istream& in, Pipeline& pipe);
    friend std::ostream& operator << (std::ostream& out, const Pipeline& pipe);
    friend void file_out_pipe(std::ofstream& out, const Pipeline& pipe);
    friend void get_from_file(std::ifstream& in, std::unordered_map<int, Pipeline>& pipes);
    friend void max_id();
    friend void filter_pipes_by_name(std::unordered_map<int, Pipeline>& pipes);
    friend void filter_pipes_by_repair(std::unordered_map<int, Pipeline>& pipes);
};


class CS
{
private:
    static int MaxIDCS;
    int CSID = 0;
    std::string CSName = "None";
    int NumberOfWorkshops = -1;
    int WorkshopsInWork = -1;
    short int Efficiency = -1;
public:

    CS();
    int GetID() const { return CSID; };
    friend int ChangeWorkshopsInWork(CS& cs, int& new_WorkshopsInWork);
    friend std::istream& operator >> (std::istream& in, CS& cs);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    friend void file_out_cs(std::ofstream& out, const CS& cs);
    friend void get_from_file(std::ifstream& in, std::unordered_map<int, CS>& cs);
    friend void max_id();


};

#endif

