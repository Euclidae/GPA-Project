#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

// Use using declarations for specific objects, or use std:: prefix
using std::string, std::cin, std::cout, std::setprecision, std::endl, std::ofstream, std::fixed;

int main(){
    // Declare and initialize variables as close as possible to where they are used

    // Basic Information
    string first_name, last_name, course, faculty;
    int student_ID, course_number;
    float total_course_credit;

    cout << "Hello, what is your first name? : ";
    cin >> first_name;

    cout << "\nWhat is your last name? : ";
    cin >> last_name;

    cout << "\nWhat is your student ID? : ";
    cin >> student_ID;

    cout << "\nWhat course do you do? : ";
    getline(cin,course);

    cout << "\nWhat faculty is it under? : ";
    getline(cin,faculty);

    cout << "\nHow many courses do you do (GNS included)? : ";
    cin >> course_number;
    --course_number;

    // Declare and initialize arrays with the size of course_number
    float weighted_GPA[course_number];
    string courses[course_number];
    float course_exam_scores[course_number];
    float course_credits[course_number];

    // Use const to declare variables that are not meant to be changed
    const float exam_credit_points[11] = {0.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0};
    const string GNS = "GNS111"; // GNS will always be a part of your courses

    // Assign GNS to the first element of courses array
    courses[0] = GNS;

    // Collects information from student regarding courses
    for (int i = 0; i < course_number; ++i){
        if(i >= 1){
            cout <<"Your previous course was " << courses[i-1] << ". Enter your next course please: ";
        }
        else{
            cout << "\nYour first course is " << GNS << ". Enter your second course: ";
        }
        cin >> courses[i];
    }

    // Collects information from students on credits
    for(int i = 0; i < course_number; ++i){
        cout << "What are the credits for " << courses[i] << "? : ";
        cin >> course_credits[i];
    }

    // Collects information from students regarding their exam scores
    for(int i = 0; i < course_number; ++i){
        cout << "\nWhat did you get in " << courses[i] << "? : ";
        cin >> course_exam_scores[i];
    }

    // Assign credit points to exam and calculate total weighted GPA
    float total_weighted_GPA = 0.0;
    for(int i = 0; i < course_number; ++i){
        // Declare and initialize index inside the loop
        int index = 0;

        //Using index to cheat the system
        if(course_exam_scores[i] >= 40 && course_exam_scores[i] < 45){
            index = 1;
        }
        else{
            index = (course_exam_scores[i] - 40) / 5;
            if(index > 10){
                index = 10;
            }
            else if(index < 0){
                index = 0;
            }
        }

        // Calculate the weighted GPA for each course
        weighted_GPA[i] = exam_credit_points[index] * course_credits[i];
        cout << "\nFor " << courses[i] << " your weight GP is: " << weighted_GPA[i] << endl;

        // Add the weighted GPA to the total weighted GPA
        total_weighted_GPA += weighted_GPA[i];
    }

    // Calculate the total course credit
    total_course_credit = 0.0;
    for(int i = 0; i < course_number; ++i){
        total_course_credit += course_credits[i];
    }

    // Calculate the GPA by dividing the total weighted GPA by the total course credit
    float GPA = total_weighted_GPA / total_course_credit;

    // Output the GPA with two decimal places
    cout << first_name << ", your GPA is " << fixed << setprecision(2) << GPA << endl;
    cout << "Generating report";
    ofstream report;
    report.open("report.txt");
    string fullname = first_name + last_name;
    string subject_marks;
    for (int i = 0; i < course_number; ++i){
        subject_marks += (courses[i] + " " + course_exam_scores + '\n');
        
    }


    string status;
    if (GPA < 2.0){
        status = "Proceed Conditional With Academic Warning";
    }


    report << fullname + "\n" <<faculty + '\n'<< subject_marks << '\n' <<GPA << " " + status;

    report.close();

    return 0;
}
