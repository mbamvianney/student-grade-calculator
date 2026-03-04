#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Person {
private:
    std::string name_;
    std::string surname_;
    std::vector<int> hw_;
    int exam_{0};

public:
    // Constructors
    Person() = default;

    Person(std::string name, std::string surname, std::vector<int> hw, int exam)
        : name_(std::move(name)), surname_(std::move(surname)), hw_(std::move(hw)), exam_(exam) {}

    // Rule of Three
    Person(const Person& other)
        : name_(other.name_), surname_(other.surname_), hw_(other.hw_), exam_(other.exam_) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            name_ = other.name_;
            surname_ = other.surname_;
            hw_ = other.hw_;
            exam_ = other.exam_;
        }
        return *this;
    }

    ~Person() {}

    const std::string& name() const { return name_; }
    const std::string& surname() const { return surname_; }

    static bool validScore(int x) { return x >= 0 && x <= 10; }

    static double average(const std::vector<int>& v) {
        if (v.empty()) return 0.0;
        long long sum = 0;
        for (int x : v) sum += x;
        return static_cast<double>(sum) / static_cast<double>(v.size());
    }

    static double median(std::vector<int> v) {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        const size_t n = v.size();
        if (n % 2 == 1) return static_cast<double>(v[n / 2]);
        return (static_cast<double>(v[n / 2 - 1]) + static_cast<double>(v[n / 2])) / 2.0;
    }

    double finalAvg() const { return 0.4 * average(hw_) + 0.6 * static_cast<double>(exam_); }
    double finalMed() const { return 0.4 * median(hw_) + 0.6 * static_cast<double>(exam_); }
};

// Trim helper
static inline std::string trim(const std::string& s) {
    const auto b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    const auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// Read file with header like:
// Vardas Pavarde ND1 ND2 ... Egz.
static bool readStudents(const std::string& path, std::vector<Person>& out) {
    std::ifstream fin(path);
    if (!fin) return false;

    out.clear();

    std::string header;
    if (!std::getline(fin, header)) return false; // header line
    // We accept any header text; we just skip it.

    std::string line;
    while (std::getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string name, surname;
        if (!(iss >> name >> surname)) continue;

        std::vector<int> marks;
        int x;
        while (iss >> x) marks.push_back(x);

        if (marks.empty()) continue;

        int exam = marks.back();
        marks.pop_back(); // rest are homework

        if (!Person::validScore(exam)) continue;
        bool ok = true;
        for (int hw : marks) ok = ok && Person::validScore(hw);
        if (!ok) continue;

        out.emplace_back(name, surname, marks, exam);
    }

    return true;
}

static void sortStudents(std::vector<Person>& v, const std::string& mode) {
    if (mode == "surname") {
        std::sort(v.begin(), v.end(), [](const Person& a, const Person& b) {
            if (a.surname() != b.surname()) return a.surname() < b.surname();
            return a.name() < b.name();
        });
    } else { // default: name
        std::sort(v.begin(), v.end(), [](const Person& a, const Person& b) {
            if (a.name() != b.name()) return a.name() < b.name();
            return a.surname() < b.surname();
        });
    }
}

static void printTable(const std::vector<Person>& v) {
    std::cout << "Name      Surname        Final (Avg.) | Final (Med.)\n";
    std::cout << "----------------------------------------------------\n";
    for (const auto& s : v) {
        std::cout << std::left << std::setw(10) << s.name()
                  << std::left << std::setw(13) << s.surname()
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2) << s.finalAvg()
                  << " | "
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2) << s.finalMed()
                  << "\n";
    }
}

int main(int argc, char** argv) {
    std::string filePath = "Students.txt";
    std::string sortMode = "name";

    if (argc >= 2) filePath = argv[1];
    if (argc >= 3) sortMode = argv[2];

    if (sortMode != "name" && sortMode != "surname") {
        std::cerr << "Invalid sort mode. Use: name or surname\n";
        return 1;
    }

    std::vector<Person> students;
    if (!readStudents(filePath, students)) {
        std::cerr << "Failed to read file: " << filePath << "\n";
        std::cerr << "Tip: run with a path, e.g. ./app students10000.txt surname\n";
        return 1;
    }

    sortStudents(students, sortMode);
    printTable(students);

    return 0;
}
