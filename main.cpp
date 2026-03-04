
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
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
    Person() = default;

    Person(std::string name, std::string surname, std::vector<int> hw, int exam)
        : name_(std::move(name)), surname_(std::move(surname)), hw_(std::move(hw)), exam_(exam) {}

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
        double sum = 0;
        for (int x : v) sum += x;
        return sum / v.size();
    }

    static double median(std::vector<int> v) {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        size_t n = v.size();
        if (n % 2 == 1) return v[n/2];
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    }

    double finalAvg() const {
        return 0.4 * average(hw_) + 0.6 * exam_;
    }

    double finalMed() const {
        return 0.4 * median(hw_) + 0.6 * exam_;
    }

    friend std::istream& operator>>(std::istream& in, Person& p) {
        std::cout << "Enter Name: ";
        in >> p.name_;

        std::cout << "Enter Surname: ";
        in >> p.surname_;

        std::cout << "Enter homework scores (-1 to finish): ";
        p.hw_.clear();

        while (true) {
            int x;
            in >> x;
            if (x == -1) break;
            if (!validScore(x)) {
                std::cout << "Invalid score. Enter 0..10\n";
                continue;
            }
            p.hw_.push_back(x);
        }

        std::cout << "Enter exam score: ";
        in >> p.exam_;

        return in;
    }
};

void sortStudents(std::vector<Person>& students) {
    std::sort(students.begin(), students.end(),
        [](const Person& a, const Person& b) {
            return a.name() < b.name();
        });
}

void printStudents(const std::vector<Person>& students) {
    std::cout << "\nName       Surname        Final (Avg.) | Final (Med.)\n";
    std::cout << "------------------------------------------------------\n";

    for (const auto& s : students) {
        std::cout << std::left << std::setw(10) << s.name()
                  << std::setw(13) << s.surname()
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2)
                  << s.finalAvg()
                  << " | "
                  << std::setw(10)
                  << s.finalMed()
                  << "\n";
    }
}

int main() {
    int n;
    std::vector<Person> students;

    std::cout << "Enter number of students: ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        Person p;
        std::cin >> p;
        students.push_back(p);
    }

    sortStudents(students);
    printStudents(students);

    return 0;
}
