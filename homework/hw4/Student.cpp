#include "Student.h"

#include <list>

void Student::RemoveFromSchoolPreferenceList(const string &school_name) {
   // find position in the school list that `school_name' is at
   
   list<string>::iterator itr;
   for (itr = preferred_schools.begin(); *itr != school_name; itr++)
      ; // ride along until you get to the position in the list that points to the school

   // remove the school from the Student's list of preferred schools
   preferred_schools.erase(itr);
}

bool operator==(const Student &student1, const Student &student2)
{
    return student1.GetName() == student2.getName();
}
