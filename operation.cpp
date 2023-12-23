#include "operation.h"
using namespace std;
// Definitions of methods for Operation class
template<typename Type>
Operation<Type>::Operation()
{
    arr = nullptr;
    size = 0;
    minPositive = 0;
    maxPositive = 0;
    minNegative = 0;
    maxNegative= 0;
    hasError = false;


}
template<typename Type>
void Operation<Type>::readData(const string& inputfilename)
{
}
template<typename Type>
void Operation<Type>::findMinMax()
{
}
template<typename Type>
void Operation<Type>::displayResults()
{
}
template<typename Type>
void Operation<Type>::writeResultsToFile(ostream& outputStream)
{
}
template<typename Type>
void Operation<Type>::inputData(const string& inputfilename)
{
}
template<typename Type>
void Operation<Type>::randominputData(const string& inputfilename)
{
}


template <typename Type>
void Operation<Type>::eraseData(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (file.is_open()) {
        file.close();
        cout << "File content erased: " << filename << endl;
    }
    else {
        cout << "Unable to open file for erasing: " << filename << endl;
    }
}
template <typename Type>
Operation<Type>::~Operation() {
    delete[] arr;
    cout << "Clear"<<endl;
}
template <typename Type>
void ProcessingData<Type>::readData(const string& inputfilename) {
   
    ifstream file(inputfilename);
    try {
        file.exceptions(ifstream::badbit | ifstream::failbit);
        if (file.is_open()) {
            if (file.peek() == ifstream::traits_type::eof()) {
                cout << "File is empty." << endl;
            }
            else {
                file >> this->size;
                this->arr = new Type[this->size];
                string value;
                for (int i = 0; i < this->size; ++i) {
                    file >> value;

                    // Check for non-numeric characters
                    bool isValid = true;
                    for (char ch : value) {
                        if (!isdigit(ch) && ch != '.' && ch != '-') {
                            isValid = false;
                            break;
                        }
                    }

                    if (!isValid) {
                        cout << "Error: Non-numeric character found in the file." << endl;
                        this->hasError = true;
                        // Handle error or exit
                        return;
                    }

                    // Convert string to Type (assuming Type is numeric)
                    this->arr[i] = static_cast<Type>(stod(value)); // For floating-point Type
                    //this->arr[i] = stoi(value); // For integer Type
                }
            }
            file.close();
        }
    }
    catch (const ifstream::failure& ex) {
        cout << "Unable to open file" << endl;
        this->hasError = true;
        cout << ex.what() << endl;
        cout << ex.code() << endl;
    }
 
}
template <typename Type>
void ProcessingData<Type>::inputData(const string& inputfilename) {
    ofstream file(inputfilename);
    try {
        file.exceptions(ofstream::badbit | ofstream::failbit);
        if (file.is_open()) {
            cout << "Enter the size of the array: ";
            while (!(cin >> this->size)) {
                cout << "Invalid input. Please enter a valid numeric value: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            file << this->size << endl;
            this->arr = new Type[this->size];
            cout << "Enter " << this->size << " data for the array:" << endl;
            cin.ignore(); // Очищення буфера

            for (int i = 0; i < this->size; ++i) {
                string input;
                getline(cin, input);

                stringstream ss(input);
                Type value;
                if (!(ss >> value) || ss.peek() != EOF) {
                    cout << "Invalid input. Please enter a valid numeric value: ";
                    --i; // Зменшуємо лічильник, щоб введено було враховано
                    continue;
                }

                if (typeid(Type) == typeid(int) && value != static_cast<int>(value)) {
                    cout << "Error: Non-integer value entered. Please enter integers only." << endl;
                    this->hasError = true;
                    return;
                }
                if (typeid(Type) == typeid(float) || typeid(Type) == typeid(double)) {
                    if (value == static_cast<int>(value)) {
                        cout << "Error: Integer value entered. Please enter non-integer values." << endl;
                        this->hasError = true;
                        return;
                    }
                }
                file << value << " ";
                this->arr[i] = value;
            }
            file.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
    catch (const ofstream::failure& ex) {
        cout << ex.what() << endl;
        cout << ex.code() << endl;
    }
}

template <typename Type>
void ProcessingData<Type>::randominputData(const string& inputfilename) {
    srand(static_cast<unsigned int>(time(NULL)));
    ofstream file(inputfilename);
    if (file.is_open()) {
        cout << "Enter the size of the array: ";
        cin >> this->size;
        file << this->size << endl;
        this->arr = new Type[this->size];
        bool unique;
        for (int i = 0; i < this->size;) {
            unique = false;
            Type newRandomValue = rand() % 2001 - 1000;
            for (int j = 0; j < i; j++) {
                if (this->arr[j] == newRandomValue) {
                    unique = true;
                    break;
                }
            }
            if (!unique) {
                this->arr[i] = newRandomValue;
                file << this->arr[i] << " ";
                ++i;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

template <typename Type>
void ProcessingData<Type>::findMinMax() {
    bool isMinPositiveSet = false;
    bool isMaxPositiveSet = false;
    bool isMinNegativeSet = false;
    bool isMaxNegativeSet = false;

    for (int i = 0; i < this->size; ++i) {
        if (this->arr[i] > 0) {
            if (!isMinPositiveSet || this->arr[i] < this->minPositive) {
                this->minPositive = this->arr[i];
                isMinPositiveSet = true;
            }
            if (!isMaxPositiveSet || this->arr[i] > this->maxPositive) {
                this->maxPositive = this->arr[i];
                isMaxPositiveSet = true;
            }
        }
        else if (this->arr[i] < 0) {
            if (!isMaxNegativeSet || this->arr[i] > this->maxNegative) {
                this->maxNegative = this->arr[i];
                isMaxNegativeSet = true;
            }
            if (!isMinNegativeSet || this->arr[i] < this->minNegative) {
                this->minNegative = this->arr[i];
                isMinNegativeSet = true;
            }
        }
    }
}

template <typename Type>
void ProcessingData<Type>::writeResultsToFile(ostream& outputStream) {

        if (this->minPositive >= 0 && this->minPositive <= this->maxPositive) {
            outputStream << "Min positive: " << this->minPositive << endl;
        } else {
            outputStream << "Min positive: none" << endl;
        }

        if (this->maxPositive >= 0 && this->maxPositive >= this->minPositive) {
            outputStream << "Max positive: " << this->maxPositive << endl;
        } else {
            outputStream << "Max positive: none" << endl;
        }

        if (this->minNegative < 0 && this->minNegative < this->maxNegative) {
            outputStream << "Min negative: " << this->minNegative << endl;
        } else {
            outputStream << "Min negative: none" << endl;
        }

        if (this->maxNegative < 0 && this->maxNegative >= this->minNegative) {
            outputStream << "Max negative: " << this->maxNegative << endl;
        } else {
            outputStream << "Max negative: none" << endl;
        }
}

template<typename Type>
ProcessingData<Type>::~ProcessingData()
{ 
 
}
template <typename Type>
void DisplayResult<Type>::displayResults() {
    if (!this->hasError) {
        cout << "Min positive: ";
        if (this->minPositive > 0 && this->minPositive <= this->maxPositive) {
            cout << this->minPositive << endl;
        }
        else {
            cout << "none" << endl;
        }

        cout << "Max positive: ";
        if (this->maxPositive > 0 && this->maxPositive >= this->minPositive) {
            cout << this->maxPositive << endl;
        }
        else {
            cout << "none" << endl;
        }

        cout << "Min negative: ";
        if (this->minNegative < 0 && this->minNegative < this->maxNegative) {
            cout << this->minNegative << endl;
        }
        else {
            cout << "none" << endl;
        }

        cout << "Max negative: ";
        if (this->maxNegative < 0 && this->maxNegative > this->minNegative) {
            cout << this->maxNegative << endl;
        }
        else {
            cout << "none" << endl;
        }
    }
    else {
        cout << "There was an error, cannot display results." << endl;
    }
   
   
}

template<typename Type>
DisplayResult<Type>::~DisplayResult()
{
 
}


void InterfaceInt() {
    DisplayResult<int> displayResultObject;
    Operation<int>* A = &displayResultObject;
    int key;
    do {
        cout << "Choose an action:" << endl;
        cout << "1 - [ - Input size and data for array - ]" << endl;
        cout << "2 - [ - Read data from file and find min/max - ]" << endl;
        cout << "3 - [ - Input size and set random data for array - ]" << endl;
        cout << "4 - [ - Content of file [Input.txt] - ]" << endl;
        cout << "5 - [ - Erase data from file [Input.txt] - ]" << endl;
        cout << "6 - [ - Erase data from file [Output.txt] - ]" << endl;
        cout << "0 - [ - Exit - ]" << endl;
        cout << "Enter your choice: ";
        cin >> key;

        switch (key) {
        case 1: {
            string inputfilename = "Input.txt";
            A->inputData(inputfilename);
            A->findMinMax();
            A->displayResults();

            string outputfilename = "Output.txt";
            ofstream outputFile(outputfilename);
            if (outputFile.is_open()) {
                A->writeResultsToFile(outputFile);
                outputFile.close();
                cout << "Results have been written to " << outputfilename << endl;
            }
            else {
                cout << "Unable to open file for writing" << endl;
            }
            break;
        }
        case 2: {
            string inputfilename;
            cout << "File name: ";
            cin >> inputfilename;
            A->readData(inputfilename);
            A->findMinMax();
            A->displayResults();
            break;
        }
        case 3: {
            string inputfilename = "Input.txt";
            A->randominputData(inputfilename);
            A->readData(inputfilename);
            A->findMinMax();
            A->displayResults();
            string outputfilename = "Output.txt";
            ofstream outputFile(outputfilename);
            if (outputFile.is_open()) {
                A->writeResultsToFile(outputFile);
                outputFile.close();
                cout << "Results have been written to " << outputfilename << endl;
            }
            break;
        }
        case 4: {
            string inputfilename = "Input.txt";
            A->readData(inputfilename);
            A->displayResults();
            break;
        }
        case 5: {
            string inputfilename = "Input.txt";
            A->eraseData(inputfilename);
            break;
        }
        case 6: {
            string outputfilename = "Output.txt";
            A->eraseData(outputfilename);
            break;
        }
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (key != 0);
}
void InterfaceFloat() {
    DisplayResult<float> displayResultObject;
    Operation<float>* B = &displayResultObject;
    int key;

    do {    
        cout << "Choose an action:" << endl;
        cout << "1 - [ - Input size and data for array - ]" << endl;
        cout << "2 - [ - Read data from file and find min/max - ]" << endl;
        cout << "3 - [ - Content of file [Input.txt] - ]" << endl;
        cout << "4 - [ - Erase data from file [Input.txt] - ]" << endl;
        cout << "5 - [ - Erase data from file [Output.txt] - ]" << endl;
        cout << "0 - [ - Exit - ]" << endl;
        cout << "Enter your choice: " << endl;
        cin >> key;

        switch (key) {
        case 1: {
            string inputfilename = "Input.txt";
            B->inputData(inputfilename);
            B->readData(inputfilename);
            B->findMinMax();
            B->displayResults();

            string outputfilename = "Output.txt";
            ofstream outputFile(outputfilename);
            if (outputFile.is_open()) {
                B->writeResultsToFile(outputFile);
                outputFile.close();
                cout << "Results have been written to " << outputfilename << endl;
            }
            else {
                cout << "Unable to open file for writing" << endl;
            }
            break;
        }
        case 2: {
            string inputfilename;
            cout << "File name: ";
            cin >> inputfilename;
            B->readData(inputfilename);
            B->findMinMax();
            B->displayResults();
            break;
        }

        case 3: {
            string inputfilename = "Input.txt";
            ifstream fin;
            fin.open(inputfilename);
            if (fin.is_open()) {
                char ch;
                while (fin.get(ch)) {
                    cout << ch;
                }
            }
            else {
                cout << "Unable to open file " << endl;
            }
            fin.close();
            break;
        }
        case 4: {
            string inputfilename = "Input.txt";
            B->eraseData(inputfilename);
            break;
        }
        case 5: {
            string outputfilename = "Output.txt";
            B->eraseData(outputfilename);
            break;
        }
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (key != 0);

}