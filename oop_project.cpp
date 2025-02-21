
// 2024-2025 KTU Computer Engineering 
// Object Oriented Programming Assignment-1

// 425425 - Ege YOLSAL
// 412905 - Murat KAÇAĞAN




#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif


enum choice {

    st_fail = 0,
    st_success = 1,
    st_all = 2,
    st_file = 3,
    user_exit = 4,
} choice;


class Student {
    private:
        string* name;
        string* student_no;
        float* mid_term;
        float* second_exam;
        float*homework;
        float* final;
        int* attendance_number;
        float* avg;
        int SIZE = 0;
    
    public:
        Student();
        ~Student();
        void calculateSIZE();
        void readFromCSV();
        int average(int);
        void print();
        void print(int);
        void print(string,int);
        int countTurkishChar(string);
};  


int main() {

    Student std;
    int choose;

    while (true) {

        cout << "Display failed students: " << "(" << st_fail << ")" << endl;
        cout << "Display successful students: " << "(" <<  st_success << ")" << endl;
        cout << "Display all students: " << "(" <<  st_all << ")" << endl;
        cout << "To write students' information to the file: " << "(" <<  st_file << ")" << endl;
        cout << "To exit the program: " << "(" << user_exit << ")" <<  endl;   

        cout << "Enter your choose: ";
        cin >> choose;

        if(cin.fail()){
            cin.clear();
            cin.ignore();
            // system(CLEAR);
            cout << "Entered wrong choice.\n\n";
            continue;
        }

        if (choose == user_exit) break;
        
        std.readFromCSV();
        string file_name; // name of the file to be created
        int file_include; // selection of student' information to be included in the file
        
        switch(choose) {

            case st_fail:
                std.print(st_fail);
                break;

            case st_success:
                std.print(st_success);
                break;
            
            case st_all:
                std.print();
                break;

            case st_file:
                cout << "What would you like to name the file: ";
                cin >> file_name;
                cout << "Press 0 to write failed students to the file, 1 to write successful students to the file, 2 to write all students to the file: ";
                cin >> file_include;
                if(cin.fail() || (file_include != 0 && file_include != 1 && file_include != 2)){
                    cin.clear();
                    cin.ignore();
                    //system(CLEAR);
                    cout << "Entered wrong choice.\n\n";
                    continue;
                    }
                if (file_include == 0) std.print(file_name, 0);
                else if (file_include == 1) std.print(file_name, 1);
                else std.print(file_name, 2); 
                break;         
            
            default:
                //system(CLEAR);
                cout << "Entered wrong choice.\n" << endl;
                break;
        }
        
    }
    cout << "\nGood bye..";
    return 0;
}

Student::Student() {
    calculateSIZE();
    name = new string[SIZE];
    student_no = new string[SIZE];
    mid_term = new float[SIZE];
    second_exam = new float[SIZE];
    homework = new float[SIZE];
    final = new float[SIZE];
    attendance_number = new int[SIZE];
}

Student::~Student() {
    delete[] name;
    delete[] student_no;
    delete[] mid_term;
    delete[] second_exam;
    delete[] homework;
    delete[] final;
    delete[] attendance_number;
}

void Student::calculateSIZE(){

    ifstream tmp_file("girdi.csv");

    if(!tmp_file) {
        cerr << "File could not be opened!" << endl;
        return;
    }

    string tmp_line;

    getline(tmp_file, tmp_line); // to skip to first line
    //tmp_line.clear();
    // SIZE++;
    while(!tmp_file.eof()){
        getline(tmp_file, tmp_line);
        SIZE++;
    }
    tmp_file.close();
}

void Student::readFromCSV() {

    ifstream file("girdi.csv");

    if(!file) {
        cerr << "File could not be opened!" << endl;
        return;
    }

    string line;
    int current_index = 0; // pos
    int comma_end;
    int i = -1;

    getline(file, line); // to skip to first line
    line.clear();
  
    while(getline(file, line)) {

        // cout << line << endl; // print the data in the file for control
        int current_index = 0; // pos
        int comma_end=0;
        int caseKey=0;
        i++;
        attendance_number[i] = 0;       
        while(current_index != string::npos) { // checking whether the searched character is found or not
            comma_end = line.find(",", current_index);
            string columnValue = line.substr(current_index, comma_end - current_index);

            if(!columnValue.empty()){
                switch (caseKey)
                {
                case 0:
                    name[i] = columnValue; break;
                case 1:
                    student_no[i] = columnValue; break;                    
                case 2:
                    if(columnValue == " "){
                        columnValue = '0';
                    } 
                        mid_term[i] = stof(columnValue); 
                        break;
                case 3:
                    second_exam[i] = stof(columnValue); break;
                case 4:
                    homework[i] = stof(columnValue); break;
                case 5:
                    final[i] = stof(columnValue); break;
                case 6:
                    attendance_number[i] = stof(columnValue); break;
                default: 
                    break;
                }
                
                current_index =  comma_end + 1;
                caseKey++; 
            }
            if(comma_end == string::npos){
                break;
            }             
        }     
    }

    file.close();
}

int Student::average(int i) {
    
    return mid_term[i]/5 + second_exam[i]/5 + homework[i]/5 + final[i]*2/5;
}

void Student::print() {

    cout << left;
    cout << setw(12) << "AD"
    << setw(12)<< "OGR.NO"
    << setw(12) << "ARA SINAV"
    << setw(12) << "2.SINAV"
    << setw(12) << "ODEV"
    << setw(12) << "FINAL"
    << setw(12) << "DEVAM SAYISI" << endl;

    for(int j = 0; j < SIZE; j++){
            if(name[j].empty()) break;
            cout << left;
            cout << setw(12) <<name[j] 
                 << setw(12)<< student_no[j] 
                 << setw(12) << mid_term[j] 
                 << setw(12) << second_exam[j] 
                 << setw(12) << homework[j]
                 << setw(12) << final[j] 
                 << setw(12) << attendance_number[j]<< endl;
    }            
}

void Student::print(int choose) {

    cout << left;
    cout << setw(12) << "AD"
    << setw(12)<< "OGR.NO"
    << setw(12) << "ARA SINAV"
    << setw(12) << "2.SINAV"
    << setw(12) << "ODEV"
    << setw(12) << "FINAL"
    << setw(12) << "DEVAM SAYISI" << endl;
    
    if(choose == 1){
        for(int j = 0; j < SIZE; j++){
            if(average(j) >= 50 && !name[j].empty()){
                cout << left;
                cout << setw(12) <<name[j] 
                << setw(12)<< student_no[j] 
                << setw(12) << mid_term[j] 
                << setw(12) << second_exam[j] 
                << setw(12) << homework[j]
                << setw(12) << final[j] 
                << setw(12) << attendance_number[j]<< endl;
            }    
        }
    }
    else if(choose == 0){
        for(int j=0;j<SIZE;j++){
            if(average(j) < 50 && !name[j].empty()){
                cout << left;
                cout << setw(12) <<name[j] 
                << setw(12)<< student_no[j] 
                << setw(12) << mid_term[j] 
                << setw(12) << second_exam[j] 
                << setw(12) << homework[j]
                << setw(12) << final[j] 
                << setw(12) << attendance_number[j]<< endl;
            }          
        }
    }
}

void Student::print(string fileName,int choose){
    fileName += ".txt";
    ofstream file(fileName);

    if(!file) {
        cerr << "File could not be opened!" << endl;
        return;
    }
    
    file << left;
    file << setw(12) << "AD"
    << setw(12)<< "OGR.NO"
    << setw(12) << "ARA SINAV"
    << setw(12) << "2.SINAV"
    << setw(12) << "ODEV"
    << setw(12) << "FINAL"
    << setw(12) << "DURUM"
    << setw(12) << "DEVAM SAYISI" << endl;         

    if(choose == 1){
        for(int j = 0; j < SIZE; j++){
            if(average(j) >= 50 && !name[j].empty()) {
                int turkishChar = countTurkishChar(name[j]);
                file << left;
                file << setw(12+turkishChar) <<name[j] 
                << setw(12)<< student_no[j] 
                << setw(12) << mid_term[j] 
                << setw(12) << second_exam[j] 
                << setw(12) << homework[j]
                << setw(12) << final[j] 
                << setw(12) << ((average(j) >= 50) ? "Gecti" : "Kaldi")
                << setw(12) << attendance_number[j] << endl;
            }
        }
    }
    else if(choose == 0){
        for(int j=0;j < SIZE;j++){
            if(average(j) < 50 && !name[j].empty()) {
                int turkishChar = countTurkishChar(name[j]);
                file << left;
                file << setw(12+turkishChar) <<name[j]
                << setw(12)<< student_no[j] 
                << setw(12) << mid_term[j] 
                << setw(12) << second_exam[j] 
                << setw(12) << homework[j]
                << setw(12) << final[j] 
                << setw(12) << ((average(j) > 50) ? "Gecti" : "Kaldi")
                << setw(12) << attendance_number[j]<< endl;
            }
        }
    }
    else if(choose == 2){
        for(int j = 0; j < SIZE; j++){
            if(name[j].empty()) break;
            int turkishChar = countTurkishChar(name[j]);
            file << left;
            file << setw(12+turkishChar) <<name[j] 
            << setw(12)<< student_no[j] 
            << setw(12) << mid_term[j] 
            << setw(12) << second_exam[j] 
            << setw(12) << homework[j]
            << setw(12) << final[j] 
            << setw(12) << ((average(j) > 50) ? "Gecti" : "Kaldi")
            << setw(12) << attendance_number[j]<< endl;         
        }
    }

    file.close();
}

int Student::countTurkishChar(string text){
    int count=0;
    const string englishChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i=0; i< text.length();i++){
        if(englishChar.find(text[i]) == string::npos) count++;
    }
    return count/2;
}