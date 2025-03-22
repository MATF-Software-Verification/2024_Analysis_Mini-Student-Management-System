#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/scoreboard.h"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include "../../Mini-Student-Management-System/include/interface.h"
#include <sstream>
#include <fstream>

using namespace SMS;

struct SetupScoreboardTests {
    SetupScoreboardTests() {
        init_all_csvs();  
    }
};


TEST_CASE_METHOD(SetupScoreboardTests, "Importovanje ocena iz CSV fajla", "[import_scoreboard]") {
    Csv::table& scoreboard_table = scoreboard.get_table();
    int preBrojRedova = scoreboard_table.num_rows();

    std::ostringstream inputStr;
    inputStr << "2\n"  
             << "demo/scoreboard_add.csv\n6\n";  
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(import_scoreboard());

    std::cin.rdbuf(std::cin.rdbuf());

    REQUIRE(scoreboard_table.num_rows() > preBrojRedova);
}


TEST_CASE_METHOD(SetupScoreboardTests, "Izmena ocena studenta", "[edit_scoreboard]") {
    Csv::table& scoreboard_table = scoreboard.get_table();

    std::ostringstream inputStr;
    inputStr << "2\n" << "19125123\n" << "10\n" << "9\n" << "8\n" << "9\n" << "6\n";
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());


    REQUIRE_NOTHROW(edit_scoreboard());

    std::cin.rdbuf(std::cin.rdbuf());


    for (int i = 0; i < scoreboard_table.num_rows(); ++i)
        if (scoreboard_table.get(i, "Course ID").equal("CM101") &&
            scoreboard_table.get(i, "Student ID").equal("19125123"))
        {
            
            REQUIRE(scoreboard_table.get_row(i).at(2).to_int() == 10);
            REQUIRE(scoreboard_table.get_row(i).at(3).to_int() == 9);
            REQUIRE(scoreboard_table.get_row(i).at(4).to_int() == 8);
            REQUIRE(scoreboard_table.get_row(i).at(5).to_int() == 9);
        }


}

TEST_CASE_METHOD(SetupScoreboardTests, "Pregled ocena za kurs", "[view_scoreboard]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("2\n6\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(view_scoreboard());

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(oldCout);

    std::string result = output.str();
    REQUIRE(result.find("Scoreboard of CM101") != std::string::npos);
}

TEST_CASE_METHOD(SetupScoreboardTests, "Pregled ocena studenta", "[student_view_scoreboard]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    std::istringstream input("2\n4\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(student_view_scoreboard("19125123"));

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(oldCout);

    std::string result = output.str();
    REQUIRE(result.find("19125123's scoreboard") != std::string::npos);
}

TEST_CASE_METHOD(SetupScoreboardTests, "Izvoz ocena u CSV fajl", "[export_scoreboard_to_csv]") {
    std::istringstream input("2\n6\n");
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(export_scoreboard_to_csv());

    std::cin.rdbuf(std::cin.rdbuf());

    std::ifstream file("CM101-Scoreboard.csv");
    REQUIRE(file.good());
    file.close();
}
