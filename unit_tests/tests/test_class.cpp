#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/class.h"
#include "../../Mini-Student-Management-System/include/interface.h"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include "../../Mini-Student-Management-System/include/date.h"
#include <sstream>
#include <fstream>

using namespace SMS;

struct SetupClassTests {
    SetupClassTests() {
        init_all_csvs();  
    }
};

TEST_CASE_METHOD(SetupClassTests, "Adding a new student", "[addStudent]") {
    Csv::table& student_table = students.get_table();
    int preRowCount = student_table.num_rows();

    std::ostringstream inputStr;
    inputStr << "19020001\nJohn Doe\n2000/05/15\nMale\n19APCS1\n";
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(addStudent());

    std::cin.rdbuf(std::cin.rdbuf());  

    REQUIRE(student_table.num_rows() == preRowCount + 1);
}


TEST_CASE_METHOD(SetupClassTests, "Editing student information", "[editStudent]") {
    Csv::table& student_table = students.get_table();
    
    std::ostringstream inputStr;
    inputStr << "19020001\n2\nJohn Smith\n3\n2000/05/16\n"
             << "4\nMale\n5\n19APCS1\n1\n19020002\n6\n";
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_NOTHROW(editStudent());
    
    std::cin.rdbuf(std::cin.rdbuf());
    
    REQUIRE(std::string(student_table.get_where("Student ID", "19020002", "Fullname").to_str()) == "John Smith");
}

TEST_CASE_METHOD(SetupClassTests, "Viewing students in a class", "[viewStudentInClass]") {
    std::ostringstream inputStr;
    inputStr << "19APCS1\n";
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(viewStudentInClass());

    std::cin.rdbuf(std::cin.rdbuf());
}

TEST_CASE_METHOD(SetupClassTests, "Importing students from a file", "[newClass]") {
    Csv::table& student_table = students.get_table();
    int preRowCount = student_table.num_rows();

    std::ostringstream inputStr;
    inputStr << "19APCS3\ndemo/students_add.csv\n";
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(newClass());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(student_table.num_rows() > preRowCount);
}


TEST_CASE_METHOD(SetupClassTests, "View all classes", "[viewClass]") {
    std::ostringstream outputStream;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());

    REQUIRE_NOTHROW(viewClass());

    std::cout.rdbuf(oldCoutBuffer);

    std::string output = outputStream.str();
    REQUIRE(output.find("Class") != std::string::npos);
    REQUIRE(output.find("19APCS3") != std::string::npos);
}

TEST_CASE_METHOD(SetupClassTests, "Removing multiple students", "[removeStudent]") {
    Csv::table& student_table = students.get_table();
    int preRowCount = student_table.num_rows();

    std::vector<std::string> studentIDs = { "19020002", "19125001", "19125083"};

    for (const auto& studentID : studentIDs) {
        std::ostringstream inputStr;
        inputStr << studentID << "\n"; 
        std::istringstream input(inputStr.str());
        std::cin.rdbuf(input.rdbuf());

        REQUIRE_NOTHROW(removeStudent());

        std::cin.rdbuf(std::cin.rdbuf());
    }

    REQUIRE(student_table.num_rows() == preRowCount - 3);
}
