#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>
#include <iomanip>

#include <TTree.h>
#include <TF1.h>
#include <TApplication.h>
#include "TH2.h"
#include "TCanvas.h"
using namespace std;
int main()
{
    TApplication tapp("Test", 0, nullptr);
    string fileName ="/home/kurbanov/dat-161208-230005.txt";
    //cout << "Enter the path to the file " << endl;
    //cin >> fileName;
    ifstream fileData(fileName);
    if (!fileData.is_open())
    {
        cout << "The file can not be opened, or it does not exist " << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Start reading the file..." << endl;
    return 0;
}
