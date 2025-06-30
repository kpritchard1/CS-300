// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Kamirah Pritchard 
//Project Two
//CS 300
// June 25th 2025

#include <iostream>
#include <string>
#include <fstream> // essential for reading data from a file
#include <algorithm>
#include <vector>

using namespace std;

// structure for the course information

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

vector<Course> courses;

void dataStructure(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file...Try Again" << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        size_t pos = line.find(",");
        course.courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        course.courseTitle = line.substr(0, pos);
        line.erase(0, pos + 1);

        while (!line.empty()) {
            pos = line.find(",");
            string prerequisite = line.substr(0, pos);
            course.prerequisites.push_back(prerequisite);
            if (pos == string::npos) break;
            line.erase(0, pos + 1);
        }
        // reading the data line by line
        courses.push_back(course);
    }

    file.close();
    // once the data is read from the file..close it!
}
void printCourseList() {
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Here is a list of courses:" << endl;
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

void printCourse(const string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.courseNumber == courseNumber;
        });

    if (it != courses.end()) {
        cout << it->courseNumber << ", " << it->courseTitle << endl;
        cout << "Prerequisites: ";
        if (it->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const auto& prerequisite : it->prerequisites) {
                cout << prerequisite << ", ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {
    string fileName;
    int choice;
    string courseNumber;
    //to print menu

    cout << "Welcome to the course planner." << endl;
    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            cin >> fileName;
           dataStructure(fileName);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourse(courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
