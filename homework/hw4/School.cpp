#include <list>
#include <string>
#include "School.h"

using namespace std;

void School::AddStudent(const string &student_name, const string &before_this_student) {
   list<string>::iterator itr;
   for(itr = preferred_students.begin(); *itr != before_this_student; itr++)
      ; // ride along until you get to the student that will be pushed back in the list

   preferred_students.insert(itr, student_name);
}
