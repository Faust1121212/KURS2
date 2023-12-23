#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <sstream>
using namespace std;

template <typename Type>
class Operation {
protected:
    Type* arr;
    int size; 
    Type minPositive;
    Type maxPositive;
    Type maxNegative;
    Type minNegative;
    bool hasError;
  
    
public:
  
    Operation();
    virtual void readData(const string& inputfilename);
    virtual void findMinMax();
    virtual void displayResults();
    virtual void writeResultsToFile(ostream& outputStream);
    virtual void inputData(const string& inputfilename);
    virtual void randominputData(const string& inputfilename);
    virtual void eraseData(const string& filename);
    virtual ~Operation();
};

template <typename Type>
class ProcessingData : public Operation<Type> {
public:
    void readData(const string& inputfilename) override;
    void inputData(const string& inputfilename) override;
    void randominputData(const string& inputfilename)override;
    void findMinMax() override;
    void writeResultsToFile(ostream& outputStream) override;

    ~ProcessingData();
};

template <typename Type>
class DisplayResult : public ProcessingData<Type> {
public:
    void displayResults() override;
    ~DisplayResult();
};

void InterfaceInt();
void InterfaceFloat();
