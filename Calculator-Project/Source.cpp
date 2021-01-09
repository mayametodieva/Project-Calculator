#include <iostream>
#include <fstream>
#include <string>
using namespace std;



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

	return 0;
}