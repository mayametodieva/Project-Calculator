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
