#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <string>
#include <list>

using namespace std;

class School {
   public:
      // constructor
      School(const string &school_name, const int num_slots) { this->school_name = school_name; this->num_slots = num_slots; }
      // accessors
      const string& GetSchoolName() const { return school_name; }
      int GetNumSlots() const { return num_slots; }
      const list<string>& GetPreferredStudents() const { return preferred_students; }

      // modifiers
      void AddStudent(const string &student_name) { preferred_students.push_back(student_name); }
      void AddStudent(const string &student_name, const string &before_this_student);

   private:
      string school_name;
      int num_slots;
      list<string> preferred_students;
};

#endif
