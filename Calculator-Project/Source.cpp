#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

int OperatorCheck(int c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return -1;

}

<<<<<<< HEAD
=======
double OperationPerformance(int c, double a, double b) {
    double result = 0;
    switch (c) {
    case '+': result = a + b;
        break;
    case '-': result = a - b;
        break;
    case '*': result = a * b;
        break;
    case '/': 
        if (b != 0) {
            result = a / b;
        }
        else
            return 3;
        break;
    case '^': result = pow(a, b);
        break;
    }    
    return result;
}

>>>>>>> 6718085f96159331840dc11dbf0494bae2490a5c
string ShuntingYard(const string& stringInfixNotation) {

    const string validOperations = "-+/*^";

    stringstream valuesStream;
    stack<int> value;

    stringstream inputStream(stringInfixNotation);
    string partOfNotation;

    while (getline(inputStream, partOfNotation, ' ')) {

        if (partOfNotation.empty()) {
            continue;
        }

        char firstToken = partOfNotation[0];
        size_t indexOfElement = validOperations.find(firstToken);

        if (indexOfElement != string::npos) {
            while (!value.empty()) {
                int firstPrecedence = indexOfElement / 2;
                int secondPrecedence = value.top() / 2;
                if (secondPrecedence >= firstPrecedence) {
                    valuesStream << validOperations[value.top()] << ' ';
                    value.pop();
                }
                else break;
            }
            value.push(indexOfElement);
        }

        else if (firstToken == '(') {

            value.push(-2);
        }
        else if (firstToken == ')') {

            while (value.top() != -2) {
                valuesStream << validOperations[value.top()] << ' ';
                value.pop();
            }
            value.pop();
        }
        else {
            valuesStream << partOfNotation << ' ';
        }
    }

    while (!value.empty()) {
        valuesStream << validOperations[value.top()] << ' ';
        value.pop();
    }

    return valuesStream.str();
}

double OperationPerformance(int c, double a, double b) {
    double result = 0;
    switch (c) {
    case '+': result = a + b;
        break;
    case '-': result = a - b;
        break;
    case '*': result = a * b;
        break;
    case '/':
        if (b != 0) {
            result = a / b;
        }
        else
            return 3;
        break;
    case '^': result = pow(a, b);
        break;
    }


    return result;
}

void ReversePolishNotation(char* input_str) {

    stack<double> stackOfNumbers;

    int operatorType;
    double firstNumber = 0, secondNumber = 0;
    double result = 0;
    char* splittedStingPart;
    char* nextToken = NULL;

    splittedStingPart = strtok_s(input_str, " ", &nextToken);

    while (splittedStingPart) {
        operatorType = splittedStingPart[0];
        if (OperatorCheck(operatorType) == 1) {
            if (stackOfNumbers.size() < 2) {
                cout << "NaN" << endl;
                return;
            }

            secondNumber = stackOfNumbers.top();
            stackOfNumbers.pop();
            firstNumber = stackOfNumbers.top();
            stackOfNumbers.pop();

            result = OperationPerformance(operatorType, firstNumber, secondNumber);
            if (result == 3) {
                cout << "NaN" << endl;
                return;
            }
            stackOfNumbers.push(result);
        }
        else {
            stackOfNumbers.push(atof(splittedStingPart));
        }

        splittedStingPart = strtok_s(nullptr, " ", &nextToken);
    }

    if (stackOfNumbers.size() == 1) {
        cout << "Calculation result: " << stackOfNumbers.top() << endl;
        return;
    }

    cout << "NaN" << endl;
}


int main() {
    ifstream myFile;
    myFile.open("Test1.txt");
    string input;
    if (!myFile)
    {
        cout << "NaN" << endl;
        return -1;
    }
    else
    {
        getline(myFile, input);
        myFile.close();
    }
    cout << "Postfix: " << ShuntingYard(input) << endl;

	return 0;
}
