#include "Student.h"

#include <list>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

void Student::RemoveSchool( const string &school_name ) {
  list<string>::iterator it;
  it = find( preferred_schools.begin(), preferred_schools.end(), school_name );
  assert( it != preferred_schools.end() );
  preferred_schools.erase( it );
}

void Student::PrepareToReceiveOffers() {
  // we haven't decided a school yet
  decided_school = "";

  // no one has given us an offer
  has_offer = false;
}

bool Student::IsOfferTentativelyAccepted(const string &school_name) {
  // we need a way to rank the schools, so we'll use numbers
  int current_offer_rank, proposed_offer_rank;
  current_offer_rank = proposed_offer_rank = 0;

  if (has_offer) {
    // find the ranking of the school whose offer you accepted
    list<string>::iterator it;
    for (it = preferred_schools.begin(); *it != decided_school; it++, current_offer_rank++)
      if (it == preferred_schools.end())
        break; // we're at the end of the list and we didn't find the decided school (SHOULD NOT HAPPEN)

    // make sure we actually found the decided school
    assert(it != preferred_schools.end());
  }

  /* Find out the ranking of the possible school (or respond with no if
   * they're not on your list. */
  list<string>::iterator it;
  for (it = preferred_schools.begin(); *it != school_name; it++, proposed_offer_rank++) {
    if (it == preferred_schools.end()) // no acceptable offer from any school
      return false;
  }

  if (has_offer) { // compare this school with your current acceptance
    if (proposed_offer_rank < current_offer_rank) {
      decided_school = school_name;
      has_offer = true;
      return true; // the propsed offer is higher up on our list than the current offer

    } else { // the proposed offer is lower down on our list than the current offer
      return false;
    }
  } else { // you don't already have an offer, so just accept this one
    decided_school = school_name;
    has_offer = true;
    return true;
  }
}

void Student::PrintStudentDecision( ostream &ostr ) const {
  ostr << name << " will be attending " << decided_school << endl;
}

void Student::PrintStudentPreference(ostream &ostr) const {
  ostr << name << " preference list:" << endl;
  int i = 1;
  list<string>::const_iterator it;
  for ( it = preferred_schools.begin(); it != preferred_schools.end(); it++, i++ )
    ostr << setw(2) << right << i << ". " << *it << endl;
  ostr << std::endl;
}
