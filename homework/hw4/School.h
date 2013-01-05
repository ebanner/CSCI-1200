#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <string>
#include <list>

using namespace std;

class School {
  public:
    // constructor
    School(const string &name, const int num_slots) { this->name = name; this->num_slots = num_slots; }

    // accessors
    const string& GetName() const { return name; }
    const list<string>& GetPreferredStudents() const { return preferred_students; }
    int NumAcceptedStudents() { return accepted_students.size(); }
    int MaxAcceptedStudents() { return num_slots; }

    // modifiers
    void AddStudent(const string &student_name) { preferred_students.push_back(student_name); }
    void AddStudent(const string &student_name, const string &before_this_student);
    void PrepareToMakeOffers();
    // Gale-Shapely stuff
    const string MakeNextOffer();
    void StudentTentativelyAcceptsOffer(const string &student);
    void StudentDeclinesTentativeAcceptance(const string &student);

    void PrintSchoolEnrollment(ostream &ostr) const;
    void PrintSchoolPreference(ostream &ostr) const;

  private:
    string name;
    int num_slots;
    list<string> preferred_students;
    list<string>::iterator offer_itr;
    list<string> accepted_students;
};

#endif
