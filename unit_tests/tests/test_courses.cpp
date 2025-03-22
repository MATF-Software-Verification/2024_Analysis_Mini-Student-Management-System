// #define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/courses.h"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include "../../Mini-Student-Management-System/include/interface.h"
#include "../../Mini-Student-Management-System/include/date.h"
#include <sstream>

using namespace SMS;

struct SetupCoursesTests {
    SetupCoursesTests() {
        init_all_csvs();  
    }
};

TEST_CASE_METHOD(SetupCoursesTests, "Create a new academic year", "[create_academic_year]") {
    Csv::table& years_table = years.get_table();
    int preYearCount = years_table.num_rows();

    std::istringstream input("2024-2025\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(create_academic_year());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(years_table.num_rows() == preYearCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Update academic year name", "[update_academic_year_name]") {
    Csv::table& years_table = years.get_table();

    std::istringstream input("3\n2025-2026\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(update_academic_year_name());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(std::string(years_table.get_where("Year name", "2025-2026", "Year name").to_str()) == "2025-2026");
}

TEST_CASE_METHOD(SetupCoursesTests, "Add semester to academic year", "[add_new_semester_to_academic_year]") {
    Csv::table& semester_table = semesters.get_table();
    int preSemesterCount = semester_table.num_rows();

    std::istringstream input("3\n2025-2026 HK1\n4\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(add_new_semester_to_academic_year());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(semester_table.num_rows() == preSemesterCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Update semester name", "[update_semester_name]") {
    Csv::table& semester_table = semesters.get_table();

    std::istringstream input("6\n2025-2026 HK2\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(update_semester_name());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(std::string(semester_table.get_where("Semester name", "2025-2026 HK2", "Semester name").to_str()) == "2025-2026 HK2");
}


TEST_CASE_METHOD(SetupCoursesTests, "Manual course creation", "[create_new_course_manually]") {
    Csv::table& courses_table = courses.get_table();
    int preCourseCount = courses_table.num_rows();

    std::istringstream input("CM202\nComputer Networks\n19APCS4\n2025/01/01\n2025/09/29\nMON\n7\n30\n11\n30\n200\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(create_new_course_manually());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(courses_table.num_rows() == preCourseCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Update existing course", "[update_course_manually]") {
    Csv::table& courses_table = courses.get_table();

    std::istringstream input("6\nComputer Networks Advanced\n19APCS4\n2025/01/02\n2025/09/30\nMON\n7\n30\n11\n30\n200\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(update_course_manually());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(courses_table.get_row(5).at(1).to_str() == std::string("Computer Networks Advanced"));
}




TEST_CASE_METHOD(SetupCoursesTests, "Add student to a course", "[add_student_to_course]") {
    Csv::table& student_table = coursestudent.get_table();
    int preStudentCount = student_table.num_rows();

    std::istringstream input("6\n19125066\n7\n");  
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(add_student_to_course());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(student_table.num_rows() == preStudentCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Add lecturer to a course", "[add_lecturer_to_course]") {
    Csv::table& lecturer_table = courselecturer.get_table();
    int preLecturerCount = lecturer_table.num_rows();

    std::istringstream input("6\ndbtien\n7\n");  
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(add_lecturer_to_course());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(lecturer_table.num_rows() == preLecturerCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Add a course to a semester", "[add_course_to_semester]") {
    Csv::table& semester_course_table = semestercourse.get_table();
    int preCourseCount = semester_course_table.num_rows();

    std::istringstream input("6\n6\n7\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(add_course_to_semester());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(semester_course_table.num_rows() == preCourseCount + 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "View students of a course", "[view_students_of_course]") {
    std::ostringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("6\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(view_students_of_course());

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(coutBuffer);

    REQUIRE(output.str().find("Student List of CM202") != std::string::npos);
}

TEST_CASE_METHOD(SetupCoursesTests, "View courses of a semester", "[view_course_of_semester]") {
    std::ostringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("6\n7\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(view_course_of_semester());

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(coutBuffer);

    REQUIRE(output.str().find("Course list in 2025-2026 HK2") != std::string::npos);
}

TEST_CASE_METHOD(SetupCoursesTests, "View all academic years", "[view_all_academic_year]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    view_all_academic_year();

    std::cout.rdbuf(oldCout);

    REQUIRE(output.str().find("School Years") != std::string::npos);
}

TEST_CASE_METHOD(SetupCoursesTests, "View semesters in an academic year", "[view_semester_in_academic_year]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("3\n4\n");
    std::cin.rdbuf(input.rdbuf());

    view_semester_in_academic_year();

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(oldCout);

    REQUIRE(output.str().find("Semester of year 2025-2026") != std::string::npos);
}

TEST_CASE_METHOD(SetupCoursesTests, "View student schedule", "[view_schedule_of_student]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    view_schedule_of_student("19125123");

    std::cout.rdbuf(oldCout);

    REQUIRE(output.str().find("19125123's Schedule") != std::string::npos);
}


TEST_CASE_METHOD(SetupCoursesTests, "Remove lecturer from a course", "[remove_lecturer_from_course]") {
    Csv::table& lecturer_table = courselecturer.get_table();
    int preLecturerCount = lecturer_table.num_rows();

    std::istringstream input("6\ndbtien\n7\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(remove_lecturer_from_course());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(lecturer_table.num_rows() == preLecturerCount - 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Import courses from CSV", "[import_course_from_csv]") {
    Csv::table& courses_table = courses.get_table();
    int preCourseCount = courses_table.num_rows();

    std::istringstream input("6\ndemo/course_add.csv\n7\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(import_course_from_csv());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(courses_table.num_rows() > preCourseCount);
}



TEST_CASE_METHOD(SetupCoursesTests, "Remove student from a course", "[remove_student_from_course]") {
    Csv::table& student_table = coursestudent.get_table();
    int preStudentCount = student_table.num_rows();


    std::vector<std::string> courseNums = {"7", "6"};
    std::vector<std::string> studentIDs = {"19125066", "19125038", "19125003"};

    std::ostringstream inputStr;
    std::istringstream input;
    for (const auto& courseNum : courseNums) {
        for (const auto& studentID : studentIDs) {
            inputStr << courseNum << "\n" << studentID << "\n"; 
            
            if (courseNum == "6"){
                inputStr << "8\n";
                break;
            }
        }
    }
    input.str(inputStr.str());
    std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_NOTHROW(remove_student_from_course());
    
    std::cin.rdbuf(std::cin.rdbuf()); 
    
    REQUIRE(student_table.num_rows() == preStudentCount - 4);


}

TEST_CASE_METHOD(SetupCoursesTests, "Delete a course from a semester", "[delete_course_from_semester]") {
    Csv::table& semester_course_table = semestercourse.get_table();
    int preCourseCount = semester_course_table.num_rows();

    std::istringstream input("6\n3\n6\n2\n6\n1\n7\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(delete_course_from_semester());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(semester_course_table.num_rows() == preCourseCount - 3);
}

TEST_CASE_METHOD(SetupCoursesTests, "Delete a course", "[delete_course]") {
    Csv::table& courses_table = courses.get_table();
    int preCourseCount = courses_table.num_rows();

    std::vector<std::string> courseNums = {"7", "6"};

    for (const auto& courseNum : courseNums) {
        std::ostringstream inputStr;
        inputStr << courseNum << "\n"; 
        std::istringstream input(inputStr.str());
        std::cin.rdbuf(input.rdbuf());

        REQUIRE_NOTHROW(delete_course());

        std::cin.rdbuf(std::cin.rdbuf()); 
    }

    REQUIRE(courses_table.num_rows() == preCourseCount - 2);
}

TEST_CASE_METHOD(SetupCoursesTests, "Delete a semester from an academic year", "[delete_semester_from_academic_year]") {
    Csv::table& semester_table = semesters.get_table();
    int preSemesterCount = semester_table.num_rows();

    std::istringstream input("3\n1\n4\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(delete_semester_from_academic_year());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(semester_table.num_rows() == preSemesterCount - 1);
}

TEST_CASE_METHOD(SetupCoursesTests, "Delete an academic year", "[delete_academic_year]") {
    Csv::table& years_table = years.get_table();
    int preYearCount = years_table.num_rows();

    std::istringstream input("3\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(delete_academic_year());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(years_table.num_rows() == preYearCount - 1);
}

