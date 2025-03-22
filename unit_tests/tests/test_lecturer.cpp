#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/interface.h"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include "../../Mini-Student-Management-System/include/lecturer.h"
#include <sstream>

using namespace SMS;

struct SetupLecturerTests {
    SetupLecturerTests() {
        init_all_csvs();  
    }
};

TEST_CASE_METHOD(SetupLecturerTests, "Dodavanje novog predavača", "[add_lecturer]") {
    Csv::table& lecturer_table = lecturers.get_table();
    int preBrojRedova = lecturer_table.num_rows();

    std::istringstream input("nixon\nNikola Stojanovic\nTS\nMale\n");
    std::cin.rdbuf(input.rdbuf());
    add_lecturer();
    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(lecturer_table.num_rows() == preBrojRedova + 1);
}

TEST_CASE_METHOD(SetupLecturerTests, "Izmena podataka predavača", "[edit_lecturer]") {
    Csv::table& lecturer_table = lecturers.get_table();
    int preBrojRedova = lecturer_table.num_rows();

    std::istringstream editInput("nixon\nNikola M. Stojanovic\nPhD\nMale\n");
    std::cin.rdbuf(editInput.rdbuf());
    edit_lecturer();
    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(lecturer_table.num_rows() == preBrojRedova);
}

TEST_CASE_METHOD(SetupLecturerTests, "Brisanje predavača", "[delete_lecturer]") {
    Csv::table& lecturer_table = lecturers.get_table();
    int preBrojRedova = lecturer_table.num_rows();

    std::istringstream deleteInput("nixon\n");
    std::cin.rdbuf(deleteInput.rdbuf());
    delete_lecturer();
    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(lecturer_table.num_rows() == preBrojRedova - 1);
}

TEST_CASE_METHOD(SetupLecturerTests, "Pregled svih predavača", "[view_all_lecturers]") {
    REQUIRE_NOTHROW(view_all_lecturers());
}

TEST_CASE_METHOD(SetupLecturerTests, "Pregled predavača određenog kursa", "[view_lecturers_of_course]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("1\n6\n"); 
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(view_lecturers_of_course());

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(oldCout);

    std::string result = output.str();
    REQUIRE(result.find("List of lecturers in") != std::string::npos);
}
