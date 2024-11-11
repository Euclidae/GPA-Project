#include <stdio.h>
#include <string.h>

int main() {
    // Basic Information
    char first_name[50], last_name[50], course[50], faculty[50];
    int student_ID, course_number;
    float total_course_credit;

    printf("Hello, what is your first name? : ");
    scanf("%s", first_name);

    printf("\nWhat is your last name? : ");
    scanf("%s", last_name);

    printf("\nWhat is your student ID? : ");
    scanf("%d", &student_ID);

    printf("\nWhat course do you do? : ");
    scanf("%s", course);

    printf("\nWhat faculty is it under? : ");
    scanf("%s", faculty);

    printf("\nHow many courses do you do (GNS included)? : ");
    scanf("%d", &course_number);
    --course_number;

    // Declare and initialize arrays with the size of course_number
    float weighted_GPA[course_number];
    char courses[course_number][50];
    float course_exam_scores[course_number];
    float course_credits[course_number];

    // Use const to declare variables that are not meant to be changed
    const float exam_credit_points[11] = {0.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0};
    const char GNS[] = "GNS111"; // GNS will always be a part of your courses

    // Assign GNS to the first element of courses array
    strcpy(courses[0], GNS);

    // Collects information from student regarding courses
    for (int i = 1; i < course_number; ++i){
        printf("\nYour previous course was %s. Enter your next course please: ", courses[i-1]);
        scanf("%s", courses[i]);
    }

    // Collects information from students on credits
    for(int i = 0; i < course_number; ++i){
        printf("What are the credits for %s? : ", courses[i]);
        scanf("%f", &course_credits[i]);
    }

    // Collects information from students regarding their exam scores
    for(int i = 0; i < course_number; ++i){
        printf("\nWhat did you get in %s? : ", courses[i]);
        scanf("%f", &course_exam_scores[i]);
    }

    
    float total_weighted_GPA = 0.0;
    for(int i = 0; i < course_number; ++i){
        int index = 0;

      
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

        weighted_GPA[i] = exam_credit_points[index] * course_credits[i];
        printf("\nFor %s your weight GP is: %.2f\n", courses[i], weighted_GPA[i]);

        
        total_weighted_GPA += weighted_GPA[i];
    }

   
    total_course_credit = 0.0;
    for(int i = 0; i < course_number; ++i){
        total_course_credit += course_credits[i];
    }

    
    float GPA = total_weighted_GPA / total_course_credit;

    printf("%s, your GPA is %.2f\n", first_name, GPA);

    return 0;
}
