

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>


using namespace std;

// funcition prototypes
void readDataFromKeyboard(string names[], double scores[], int size);
void readDataFromFile(ifstream& fin, string names[], double score[], int size);
void openInputFile(ifstream& fin);
double getLowest(double scores[], int numberOfstudents);
double getHighest(double scores[], int numberOfstudents);
double getMean(double scores[], int numberOfstudents);
int getNumOfStudents();
char isLowest(double lowest, double target);
char isHighest(double highest, double target);
char isNotLessThanMean(double mean, double target);
void printReport(string names[], double scores[], int numberOfstudents);



int main()
{
    //The first thing is to ask is if the user wishes to enter the scores via the keyboard or from a scores file.
    char dataChoice;// hold the choice of input
    cout << "Type 'K' or 'k' if you want to assess data from the keyboard. Enter 'F' or 'f' if you want to assess data from a file in your computer:";
    cin >> dataChoice;
    
    int numberOfStudents;
    
    if (dataChoice == 'k' || dataChoice == 'K'){
    //If the user chooses keyboard, then the user will be first asked the total number of scores they want to enter and then ask the user for each student name and test score.
        numberOfStudents = getNumOfStudents(); // get number of student from the prompt
        string names[numberOfStudents];
        double score[numberOfStudents];
        
        readDataFromKeyboard(names, score, numberOfStudents);
        printReport(names, score, numberOfStudents);
        
    }
    //If the user chooses file, then ask the user for the file name and location.  The first line in the file should be the total number of scores.
    else if (dataChoice == 'F' || dataChoice == 'f'){
        ifstream fin;
        openInputFile(fin);
        fin >> numberOfStudents; // get number of the student from the inputfile
        string names[numberOfStudents];
        double score[numberOfStudents];
        
        readDataFromFile(fin, names, score, numberOfStudents);
        printReport(names, score, numberOfStudents);
        fin.close(); // clost the input file.
    }
    else{
        cout << "You did not enter the right choice." << endl;
        exit(1);
    }
    
    
    system("pause");
    
    
    return 0;
}


/**
 To be called if the user chose to assess data from the keyboard
 */

void readDataFromKeyboard(string names[], double scores[], int size)
{
    for (int i =0 ; i < size; i++)
    {
        cout << "Enter the name of student number" << i+1 << " in FirtName, LastName format: ";
        cin.ignore();
        getline(cin, names[i]);
        
        do{
        cout << "Enter the score of this student  the score should between 0 - 100 : ";
        cin >> scores[i];
        }while(scores[i] > 100 || scores[i] < 0);

    }
    
}
/**
 To be called if the user chose to assess data from a score file on computer
 */
void readDataFromFile(ifstream& fin, string names[], double score[], int size)
{
    string firstName, lastName;
    for(int i = 0; i < size; i++){
        fin >> firstName >> lastName;
        names[i] = firstName+ " " + lastName;
        fin >> score[i];
        if (score[i]){
            cout << "The score is not valid in the inputfile, the score should between 0 - 100  \n" << endl;
            exit(2);
        }
        
    }
    
}
/**
 * Open the inputFile, prompt the user for the input file path until it is valid.
 */
void openInputFile(ifstream& fin)
{
    bool validInputFile = false;
    string inputFile;
    do{
        cout << "Enter the input file path: ";
        cin >> inputFile;
        fin.open(inputFile.c_str());
        if( !fin)
        {
            cerr << "Can not open the input file, invalid file path: " << inputFile << endl;
            validInputFile = false;
        }
        else validInputFile = true;
        
    }
    while (!validInputFile);
}

double getLowest(double scores[], int numberOfstudents)
{
    int low = scores[0];
    for (int i = 1 ; i<numberOfstudents;i++)
    {
        if (low > scores[i]) low = scores[i];
    }
    
    return low;
}

double getHighest(double scores[], int numberOfstudents)
{
    int high = scores[0];
    for (int i = 1 ; i<numberOfstudents;i++)
    {
        if (high < scores[i]) high = scores[i];
    }
    
    return high;
}

double getMean(double scores[], int numberOfstudents)
{
    double total = 0;
    for (int i =0 ; i<numberOfstudents; i++){
        total += scores[i];
    }
    return total/numberOfstudents;
}

int getNumOfStudents()
{
    int num;
    do{
        cout << "Enter how many number students you want to enter(the number should between 1 - 1024: ";
        cin >> num;
    }while (num > 1024 || num < 1);
    
    return num;
    
}

char isLowest(double lowest, double target)
{
    if (lowest == target)
        return 'Y';
    else
        return 'N';
}

char isHighest(double highest, double target)
{
    if (highest == target)
        return 'Y';
    else
        return 'N';
}

char isNotLessThanMean(double mean, double target)
{
    if (target >= mean)
        return 'Y';
    else
        return 'N';
}

/**
 Print out the report
 */
void printReport(string names[], double scores[], int numberOfstudents)
{
    
    
    double lowest =  getLowest(scores, numberOfstudents);
    double highest =  getHighest(scores, numberOfstudents);
    double mean = getMean(scores, numberOfstudents);
    
    cout << "The following is the report of students:\n---------------------------------------------------" << endl;
    // print out the first part of the summary
    cout << "Number of scores = " << numberOfstudents << endl << endl;
    cout << "Lowest Score  = " << lowest << endl << endl;
    cout << "Highest Score = " << highest << endl << endl;
    cout << "Mean Score  = " << mean << endl << endl;
    
    // print out the record in a formatted order
    cout << left << setw(15) << "Name" << setw(10) << "Score" << setw(10) << "IsLowest" << setw(10) << "IsHighest" << setw(10) << ">=Mean" << endl;
    for (int i = 0; i <numberOfstudents; i++)
    {
        cout << left << setw(15) << names[i] << setw(10) << scores[i] << setw(10) << isLowest(lowest, scores[i]) << setw(10) << isHighest(highest, scores[i]) << setw(10) << isNotLessThanMean(mean, scores[i]) << endl;
        
    }
    
    
} 






