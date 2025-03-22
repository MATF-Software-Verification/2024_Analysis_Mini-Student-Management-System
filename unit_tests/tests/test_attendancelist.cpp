// #define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../../Mini-Student-Management-System/include/attendancelist.h"
#include "../../Mini-Student-Management-System/include/date.h"
#include "../../Mini-Student-Management-System/include/interface.h"
#include "../../Mini-Student-Management-System/include/csv_import.h"
#include <fstream>
#include <sstream>

void updateLastCourseEntry() {
    std::string filename = "db/courses.csv";  
    std::ifstream file(filename);

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    time_t t = time(nullptr);
    struct tm now = *localtime(&t); 

    char currentDate[11], endDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y/%m/%d", &now);

    struct tm endDateStruct = now;
    endDateStruct.tm_year += 1;   
    mktime(&endDateStruct);
    strftime(endDate, sizeof(endDate), "%Y/%m/%d", &endDateStruct);

    const char* daysOfWeek[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    std::string currentDay = daysOfWeek[now.tm_wday];
    std::stringstream ss(lines.back());
    std::vector<std::string> tokens;
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    tokens[3] = currentDate;
    tokens[4] = endDate;
    tokens[5] = currentDay;

    std::ostringstream updatedLine;
    for (size_t i = 0; i < tokens.size(); ++i) {
        updatedLine << tokens[i];
        if (i != tokens.size() - 1) updatedLine << ",";
    }

    std::ofstream outFile(filename);
    for (size_t i = 0; i < lines.size() - 1; ++i) {
        outFile << lines[i] << "\n";
    }
    outFile << updatedLine.str() << "\n";
    outFile.close();

    std::cout << "Updated last course entry with:\n";
    std::cout << "Start Date: " << currentDate << "\n";
    std::cout << "End Date: " << endDate << "\n";
    std::cout << "Day of Week: " << currentDay << "\n";
}


using namespace SMS;
// Učitavanje baze podataka pre svih testova
struct SetupAttendanceTests {
    SetupAttendanceTests() {
        updateLastCourseEntry();
        init_all_csvs();  
    }
};

TEST_CASE_METHOD(SetupAttendanceTests, "Pregled prisustva studenta", "[view_check_in]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    view_check_in("19125066");  

    std::cout.rdbuf(oldCout);  

    std::cout << "DEBUG: Output: " << output.str();
    REQUIRE(output.str().find("19125066") != std::string::npos);
}

TEST_CASE_METHOD(SetupAttendanceTests, "Dodavanje prisustva studenta", "[student_check_in]") {
    Csv::table& attend_table = attendancelist.get_table();
    int preBrojRedova = attend_table.num_rows();


    std::ostringstream inputStr;
    inputStr << "1\n" << "2\n" ;
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    student_check_in("19125066");

    REQUIRE(attend_table.num_rows() == preBrojRedova + 1);
}

TEST_CASE_METHOD(SetupAttendanceTests, "Uređivanje prisustva po studentu", "[edit_attendance_by_student]") {
    std::ostringstream inputStr;
    inputStr << "19125066\n"  
             << "1\n"          
             << "1\n";         

    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(edit_attendance_by_student());

    std::cin.rdbuf(std::cin.rdbuf());  
}

TEST_CASE_METHOD(SetupAttendanceTests, "Izmena prisustva za kurs", "[edit_attendance_by_course]") {
    std::ostringstream inputStr;
    inputStr << "5\n"  
             << "4\n"
             << "1\n"
             << "6\n";  

    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(edit_attendance_by_course());

    std::cin.rdbuf(std::cin.rdbuf());
}

TEST_CASE_METHOD(SetupAttendanceTests, "Izvoz prisustva u CSV", "[export_attendance_list_to_csv]") {
    std::istringstream input("5\n6\n");
    std::cin.rdbuf(input.rdbuf());

    export_attendance_list_to_csv();

    std::cin.rdbuf(std::cin.rdbuf());

    std::ifstream file("Test-AttendanceList.csv");
    REQUIRE(file.good());
    file.close();}


TEST_CASE_METHOD(SetupAttendanceTests, "Viewing attendance list for a selected course", "[view_attendance_list]") {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    std::ostringstream inputStr;
    inputStr << "1\n6\n";  
    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    view_attendance_list();  

    std::cin.rdbuf(std::cin.rdbuf());  
    std::cout.rdbuf(oldCout);  

    REQUIRE(output.str().find("Attendance list of CS162") != std::string::npos);
}

TEST_CASE_METHOD(SetupAttendanceTests, "Brisanje prisustva po studentu", "[delete_attendance_by_student]") {
    std::ostringstream inputStr;
    inputStr << "19125066\n"  
             << "4\n"          
             << "2\n";         

    std::istringstream input(inputStr.str());
    std::cin.rdbuf(input.rdbuf());

    REQUIRE_NOTHROW(edit_attendance_by_student());

    std::cin.rdbuf(std::cin.rdbuf());  
}
