use std::collections::HashMap;
use std::io::{stdin, stdout, Write};

#[derive(Debug, Clone)]
struct Course {
    course_code: String,
    course_credit: f64,
    grade_percent: i32,
}

impl Course {
    fn get_weighted_gpa(&self) -> f64 {
        let exam_credit_points: [f64; 11] = [0.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0];
        let index = if self.grade_percent >= 40 && self.grade_percent < 45 {
            1
        } else {
            (self.grade_percent - 40) / 5
        }.clamp(0, 10);
        exam_credit_points[index as usize] * self.course_credit
    }

    fn get_letter_grade(&self) -> &'static str {
        let grade_bounds: [i32; 10] = [0, 45, 50, 55, 60, 65, 70, 75, 80, 85];
        let grades: [&str; 10] = ["F", "E", "D", "C", "B-", "B", "B+", "A-", "A", "A+"];

        let mut i = 0;
        while i < grade_bounds.len() - 1 && self.grade_percent >= grade_bounds[i] {
            i += 1;
        }
        grades[i]
    }
}

#[derive(Debug)]
struct Student {
    student_name: String,
    student_id: i32,
    courses: Vec<Course>,
}

impl Student {
    fn add_course(&mut self, course: Course) {
        self.courses.push(course);
    }

    fn calculate_gpa(&self) -> f64 {
        let mut total_weighted_gpa = 0.0;
        let mut total_credits = 0.0;
        for course in &self.courses {
            total_weighted_gpa += course.get_weighted_gpa();
            total_credits += course.course_credit;
        }
        total_weighted_gpa / total_credits
    }
}

fn main() {
    let mut report = std::fs::File::create("report.txt").expect("Failed to create report.txt");

    println!("---------------Welcome to the GPA Calculator----------------------");
    println!("---------------Select your service------------------------ \n 1. Calculate GPA \n 2. Quit \n");

    let mut choice1 = 0;
    loop {
        print!("Enter your choice: ");
        stdout().flush().expect("Failed to flush stdout");
        choice1 = read_int();
        if choice1 == 1 || choice1 == 2 {
            break;
        }
        println!("Please choose the correct input.");
    }

    if choice1 == 1 {
        print!("Enter your name: ");
        stdout().flush().expect("Failed to flush stdout");
        let student_name = read_string();

        print!("Enter your student ID: ");
        stdout().flush().expect("Failed to flush stdout");
        let student_id = read_int();

        let mut student = Student {
            student_name,
            student_id,
            courses: Vec::new(),
        };

        print!("Enter the number of courses you are taking: ");
        stdout().flush().expect("Failed to flush stdout");
        let course_count = read_int();

        if course_count > 7 {
            println!("You can't enter more than 7 courses.");
            return;
        }

        for i in 0..course_count {
            print!("Please enter the course code for course {}: ", i + 1);
            stdout().flush().expect("Failed to flush stdout");
            let course_code = read_string();

            print!("Please enter the credit number for the course {}: ", course_code);
            stdout().flush().expect("Failed to flush stdout");
            let course_credit = read_float();

            print!("Enter your grade for {}: ", course_code);
            stdout().flush().expect("Failed to flush stdout");
            let grade_percent = read_int();

            let course = Course {
                course_code,
                course_credit,
                grade_percent,
            };
            student.add_course(course);
        }

        let gpa = student.calculate_gpa();
        println!("{}, your GPA is {:.2}", student.student_name, gpa);

        writeln!(
            report,
            "{:<20} {:<10} {:<10} {:<10} {:<10}",
            "Course Code", "Credits", "Grade", "Symbol", "WGP"
        )
        .expect("Failed to write to report.txt");

        for course in &student.courses {
            writeln!(
                report,
                "{:<20} {:<10} {:<10} {:<10} {:<10.2}",
                course.course_code,
                course.course_credit,
                course.grade_percent,
                course.get_letter_grade(),
                course.get_weighted_gpa()
            )
            .expect("Failed to write to report.txt");
        }
        writeln!(report, "GPA: {:.2}", gpa).expect("Failed to write to report.txt");

        if gpa < 2.0 {
            writeln!(report, "Status: Proceed Conditionally with Academic Warning")
                .expect("Failed to write to report.txt");
        } else {
            writeln!(report, "Status: Proceed Unconditionally")
                .expect("Failed to write to report.txt");
        }
    }
}

fn read_string() -> String {
    let mut input = String::new();
    stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    input.trim().to_string()
}

fn read_int() -> i32 {
    let mut input = String::new();
    stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}

fn read_float() -> f64 {
    let mut input = String::new();
    stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}