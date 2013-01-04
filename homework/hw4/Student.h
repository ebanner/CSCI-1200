#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <list>

using namespace std;

class Student {
   public:
      // constructor
      Student(const string &student_name) { this->student_name = student_name; }

      // accessors
      const string& GetStudentName() const { return student_name; }
      int GetNumPrefs() const { return num_prefs; }
      const list<string>& GetPreferredSchools() const { return preferred_schools; }

      // modifiers
      void AddSchool(const string &school_name) { preferred_schools.push_back(school_name); }
      void RemoveFromSchoolPreferenceList(const string &school_name);

   private:
      string student_name;
      int num_prefs;
      list<string> preferred_schools;
};

#endif
