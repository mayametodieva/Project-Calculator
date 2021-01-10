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
//not done
int checkIfElementIsPros(string values) {
    for (int i = 0; i < values.length(); i++) {
        if (values[i] != '0' && values[i] != '1' && values[i] != '2' && values[i] != '3' && values[i] != '4' && values[i] != '5' && values[i] != '6'
            && values[i] != '7' && values[i] != '8' && values[i] != '9' && values[i] != ' ' && OperatorCheck(values[i]) != 1 && values[i] != '(' && values[i] != ')') {
            return -4;
        }
    }
    return 4;
}
//not done
int inputCheck(string input) {
    int openBrackets = 0;
    int closedBrackets = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(') {
            openBrackets++;

        }
        if (input[i] == ')') {
            closedBrackets++;
        }
        if (openBrackets != closedBrackets) {
            return -5;
        }
    }
    return 5;
}

string operationValue(char op1, char op2) {
    string result;
    if (op1 == '+' && op2 == '+') {
        result = '+';
    }
    if (op1 == '+' && op2 == '-') {
        result = '-';
    }
    if (op1 == '-' && op2 == '-') {
        result = '+';
    }
    if (op1 == '-' && op2 == '+') {
        result = '-';
    }

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
            /*for (int i = 0; i < partOfNotation.size(); i++) {
                if (partOfNotation[i] == '(') {
                    int n = i + 1;
                    while (partOfNotation[n] != ' ') {
                        n++;
                    }
                    if (partOfNotation[n] == '-') {
                        value.top();
                    }
                }
            }*/

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
//not done
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
    if (checkIfElementIsPros(input) == -4) {
        cout << "NaN" << endl;
    }
    else {
        /* if (inputCheck(input) == 5) {
             cout << "NaN" << endl;
         }*/
         /*else {*/
        cout << "Infix: " << input << endl;
        cout << "Postfix: " << ShuntingYard(input) << endl;
        //not done
        string myNewString = ShuntingYard(input);
        int length = myNewString.length();
        char* myString = (char*)malloc(sizeof(char) * (myNewString.length() + 1));

        for (int i = 0; i < length; i++)
        {
            myString[i] = myNewString[i];
        }

        myString[length] = '\0';

        ReversePolishNotation(myString);

        free(myString);

        return 0;
        /*}*/
    }


    /*}*/







}