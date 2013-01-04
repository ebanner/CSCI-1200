#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <string>
#include <list>
#include "Student.h"

using namespace std;

class School {
    public:
        // constructor
        School(const string &name, const int num_slots);

        // accessors
        const string& GetName() const { return name; }
        int GetNumSlots() const { return num_slots; }
        const list<Student>& GetPreferredStudents() const { return preferred_students; }
        int NumAcceptedStudents();
        int MaxAcceptedStudents();

        // modifiers
        void AddStudent(const string &student_name) { preferred_students.push_back(student_name); }
        void AddStudent(const string &student_name, const string &before_this_student);
        void PrepareToMakeOffers();

        // Gale-Shapely stuff
        string MakeNextOffer();
        void StudentTentativelyAcceptsOffer();
        void PrintSchoolEnrollment(ofstream &ostr);
        void StudentDeclinesTentativeAcceptance(const string &student);

    private:
        string name;
        list<Student> preferred_students;
        list<Student>::iterator offer_itr;
        int num_slots;
        int num_accepted_students;
};

bool operator==(const School &school1, const School &school2);

#endif
