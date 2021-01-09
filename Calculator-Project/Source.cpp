#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

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