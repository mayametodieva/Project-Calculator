
/**
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Maya Metodieva
* @idnumber 62639
* @compiler VC
*
*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

bool isOperator(char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    default:
        return false;
    }
}

bool isParen(char c) {
    switch (c) {
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}

bool isDigit(char c) {
    switch (c) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
        return true;
    default:
        return false;
    }
}

//Function that checks if a single element is valid according to the requirements.
bool valueIsValid(string values) {
    for (int i = 0; i < values.length(); i++) {
        if (!isOperator(values[i]) && !isParen(values[i]) && !isDigit(values[i]) && values[i] != ' ') {
            return false;
        }
    }
    return true;
}

//Function that sorts the input notation in proper order (infix to postfix notation), as it prepairs it for further actions.
string ShuntingYard(const string& stringInfixNotation) {

    stack<char> op;
    //Initialising string with valid operations.
    const string validOperations = "-+/*^";
    stack<int> operands;

    stringstream valuesStream;
    stack<int> value;

    stringstream inputStream(stringInfixNotation);
    string line;

    string currentWord;
    string normalisedInput;
    //Normalising the input-string.
    getline(inputStream, line);
    for (int i = 0; i < line.size(); i++) {
        if (isOperator(line[i])) {
            if (i == line.size() - 1) {
                normalisedInput.append({ ' ', line[i] });
            }
            normalisedInput.append({ ' ', line[i], ' ' });
        }
        else {
            normalisedInput += line[i];
        }
    }

    stringstream normalisedStream(normalisedInput);
    string partOfNotation;
    while (getline(normalisedStream, partOfNotation, ' ')) {
        //Check whether the newly-created part is empty.
        if (partOfNotation.empty()) {
            continue;
        }
        //Getting the value of the first elemet of the new part.
        char firstToken = partOfNotation[0];
        //Getting an element that saves the value of the inspection of the first element of the part.
        int Element = validOperations.find(firstToken);

        //Check whether the element is not the last element in the string.
        if (Element != string::npos) {
            //Executing thr following actions until empyfying the string.
            while (!value.empty()) {
                //Dividing element and the value of the newest element in the stack making it possible to be compared later.
                int firstPr = Element / 2;
                int secondPr = value.top() / 2;
                //Comparing the elements.
                if (secondPr >= firstPr) {

                    valuesStream << validOperations[value.top()] << ' ';
                    value.pop();
                }
                else break;
            }
            //Inserting element into the stack.
            value.push(Element);
        }
        //Check for brckets.
        else if (firstToken == '(') {

            //Iserting bracket value into the stack.
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
    //Returning the new string.
    return valuesStream.str();
}

//Function that calculates the result int the specific cases of the operator's kind.
double OperationPerformance(int c, double a, double b) {
    double result = 0;
    switch (c) {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    case '^':
        result = pow(a, b);
        break;
    }

    return result;
}

//Function that calculates the final result using the converted postfix input.
void ReversePolishNotation(char* input) {

    stack<double> stackOfNumbers;
    int operatorType;
    double firstNumber = 0, secondNumber = 0, result = 0;
    char* splitStringPart;
    char* nextToken = NULL;

    //Split the string into parts.
    splitStringPart = strtok_s(input, " ", &nextToken);

    while (splitStringPart) {
        operatorType = splitStringPart[0];
        //Check whether the operator is valid.
        if (isOperator(operatorType)) {
            //Check for duplicate operators.
            if (stackOfNumbers.size() < 2) {
                cout << "NaN" << endl;
                return;
            }

            //Getting elemets in the stack.
            secondNumber = stackOfNumbers.top();
            stackOfNumbers.pop();
            firstNumber = stackOfNumbers.top();
            stackOfNumbers.pop();

            // Checking for divison by zero.
            if (secondNumber == 0 && operatorType == '/') {
                cout << "NaN" << endl;
                return;
            }

            //Getting the result of executing the performance function.
            result = OperationPerformance(operatorType, firstNumber, secondNumber);

            //Pushing result into the stack.
            stackOfNumbers.push(result);
        }
        else {
            //Pushing the decimal result.
            stackOfNumbers.push(atof(splitStringPart));
        }
        //Repeating, starting from next position.
        splitStringPart = strtok_s(nullptr, " ", &nextToken);
    }
    //Returning the final result.
    if (stackOfNumbers.size() == 1) {
        cout << "Calculation result: " << stackOfNumbers.top() << endl;
        return;
    }

    cout << "NaN" << endl;
}


int main() {
    //Opening, reading and getting input line from file.
    ifstream myFile;
    myFile.open("Test1.txt");
    string input;
    if (!myFile) {
        //Check whether the file exists.
        cout << "NaN" << endl;
        return -1;
    }
    else {
        getline(myFile, input);
        myFile.close();
    }
    //Check whether the input is correct.
    if (!valueIsValid(input)) {
        cout << "NaN" << endl;
        return -1;
    }

    cout << "Infix: " << input << endl;
    cout << "Postfix: " << ShuntingYard(input) << endl;

    string myNewString = ShuntingYard(input);
    int length = myNewString.length();
    //Using memory allocation, making it possisble to convert from string to char* type.
    char* myString = (char*)malloc(sizeof(char) * (myNewString.length() + 1));

    for (int i = 0; i < length; i++) {
        myString[i] = myNewString[i];
    }

    myString[length] = '\0';

    //Calculating.
    ReversePolishNotation(myString);

    free(myString);

    return 0;
}
