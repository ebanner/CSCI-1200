#include "School.h"

#include <algorithm>
#include <cassert>
#include <list>
#include <iomanip>
#include <fstream>

using namespace std;

void School::AddStudent(const string &student_name, const string &before_the_student){
  // check the before_the_student is a valid student in preference list in school
  list<string>::iterator it = find(preferred_students.begin(), preferred_students.end(), before_the_student);

  // ensure the student that will go after the inserted student is acutally in the student list
  assert( it != preferred_students.end() );

  preferred_students.insert( it, student_name );
}

void School::PrepareToMakeOffers() {
  // point offer iterator to beginning of preferred students
  offer_itr = preferred_students.begin();
}

const string School::MakeNextOffer() {
  // return the empty string if we are at the end of the list
  if (offer_itr == preferred_students.end())
    return "";

  // return the name of student we are currently making the offer to and increment the offer iterator
  return *offer_itr++;
}

void School::StudentTentativelyAcceptsOffer(const string &student) {
  // add the student to accepted students list
  accepted_students.push_back(student);
}

// delte student from the list of accepted students
void School::StudentDeclinesTentativeAcceptance(const string &student) {
  list<string>::iterator it;
  it = find(accepted_students.begin(), accepted_students.end(), student);

  // ensure the student to be removed has been accepted previously
  assert(it != accepted_students.end());

  // remove the student from the list of accpeted students
  accepted_students.erase(it);
}

void School::PrintSchoolEnrollment(ostream &ostr) const {
  ostr << "student(s) who will be attending " << name << ":" << endl;
  list<string>::const_iterator it;
  for ( it = accepted_students.begin(); it != accepted_students.end(); it++ )
    ostr << "  " << *it << endl;
}
void School::PrintSchoolPreference(ostream &ostr) const {
  ostr << name << " preference list:" << endl;
  int i = 1;
  list<string>::const_iterator it;
  for ( it = preferred_students.begin(); it != preferred_students.end(); it++, i++ ) {
    ostr << setw(2) << right << i << ". "<< *it << endl;
  }
  ostr << std::endl;
}
