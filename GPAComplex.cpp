#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Course {
public:
    string course_code;
    double course_credit;
    int grade_percent;

    Course(string code, double credit, int grade) : course_code(code), course_credit(credit), grade_percent(grade) {}

    double getWeightedGPA() {
        vector<double> exam_credit_points = {0.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0};

        int index = 0;
        if(grade_percent >= 40 && grade_percent < 45){
            index = 1;
        }
        else{
            index = (grade_percent - 40) / 5;
            if(index > 10){
                index = 10;
            }
            else if(index < 0){
                index = 0;
            }
        }

        return exam_credit_points[index] * course_credit;
    }

    string getLetterGrade() {
        vector<int> gradeBounds = {0, 45, 50 ,55 ,60 ,65 ,70 ,75 ,80 ,85};
        vector<string> grades = {"F", "E", "D", "C", "B-", "B", "B+", "A-", "A", "A+"};

        int i = 0;
        while(i < gradeBounds.size() - 1 && grade_percent >= gradeBounds[i]){
            i++;
        }
        return grades[i];
    }
};

class Student {
public:
    string student_name;
    int student_ID;
    vector<Course> courses;

    Student(string name, int ID) : student_name(name), student_ID(ID) {}

    void addCourse(Course course) {
        courses.push_back(course);
    }

    double calculateGPA() {
        double total_weighted_GPA = 0.0;
        double total_credits = 0.0;
        for(auto &course : courses){
            total_weighted_GPA += course.getWeightedGPA();
            total_credits += course.course_credit;
        }
        return total_weighted_GPA / total_credits;
    }
};

int main(){
    int choice1;
    ofstream report;

    vector<string> gradeLetterTable = { "F", "E", "D", "C", "B-", "B", "B+", "A-", "A", "A+"};

    report.open("report.txt");

    cout << "---------------Welcome to the GPA Calculator----------------------\n";
    cout << "---------------Select your service------------------------ \n 1. Calculate GPA \n 2.Quit \n";

    cin >> choice1;

    while(choice1 != 1 && choice1 !=2){
        cout << "Please choose the correct input: ";
        cin >> choice1;
    }

    if(choice1 == 1){
        string student_name;
        int student_ID;

        cout << "Enter your name: ";
        cin >> student_name;

        cout << "\nEnter your student ID: ";
        cin >> student_ID;

        Student student(student_name, student_ID);

        int course_count;
        cout << "\nEnter the number of courses you are taking: ";
        cin >> course_count;

        if(course_count > 7){
            cout << "You can't enter more than 7 courses.";
            return 0;
        }

        for(int counter = 0; counter < course_count; ++counter ){
            string course_code;
            double course_credit;
            int grade_percent;

            cout << "Please enter the course code for course " << counter+1 << ": ";
            cin >> course_code;

            cout << "Please enter the credit number for the course " << course_code << ": ";
            cin >> course_credit;

            cout << "Enter your grade for " << course_code << ": ";
            cin >> grade_percent;

            Course course(course_code, course_credit, grade_percent);
            student.addCourse(course);
        }

        double GPA = student.calculateGPA();

        cout << student_name << ", your GPA is " << fixed << setprecision(2) << GPA << endl;

        report << left << setw(20) << "Course Code" << setw(10) << "Credits" << setw(10) << "Grade" << setw(10) << "Symbol" << setw(10) << "WGP" << endl;
        for(auto &course : student.courses){
            report << left << setw(20) << course.course_code << setw(10) << course.course_credit << setw(10) << course.grade_percent << setw(10) << course.getLetterGrade() << setw(10) << course.getWeightedGPA() << endl;
        }
        report << "GPA: " << GPA << endl;

        if(GPA < 2.0) {
            report << "Status: Proceed Conditionally with Academic Warning" << endl;
        } else {
            report << "Status: Proceed Unconditionally" << endl;
        }
    }

    report.close();

    return 0;
}
