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
  if (has_offer == false) {
    // student now has an offer
    has_offer = true;
    
    // make this school the decided school tentatively
    decided_school = school_name;

    // we are accepting the offer
    return true;
  } else { 
    /* We've already tenatively accepted another offer and we need to 
     * check if this is a better offer. */
    
    // we need a way to rank the schools, so we'll use numbers
    int current_offer_rank, proposed_offer_rank;
    current_offer_rank = proposed_offer_rank = 0;

    list<string>::iterator it;
    for (it = preferred_schools.begin(); *it != decided_school; it++, current_offer_rank++)
      if (it == preferred_schools.end())
	break; // we're at the end of the list and we didn't find the decided school (SHOULD NOT HAPPEN)

    // make sure we actually found the decided school
    assert(it != preferred_schools.end());

    for (it = preferred_schools.begin(); *it != school_name; it++, proposed_offer_rank++)
      if (it == preferred_schools.end())
	break; // we're at the end of the list and we didn't find the school that proposed the offer (SHOULD NOT HAPPEN)

    // make sure we actually found the school that proposed the offer
    assert(it != preferred_schools.end());
    
    if (proposed_offer_rank < current_offer_rank) {
      decided_school = school_name;
      return true; // the propsed offer is higher up on our list than the current offer

    } else { // the proposed offer is lower down on our list than the current offer
      return false;
    }
  }
}

void Student::PrintStudentDecision( ostream &ostr ) const {
  ostr << name << " will be attending " << decided_school << endl;
}

void Student::PrintStudentPreference(ostream &ostr) const {
  ostr << name << " preference list:" << endl;
  int i = 1;
  list<string>::iterator it;
  for ( it = preferred_schools.begin(); it != preferred_schools.end(); it++, i++ )
    ostr << setw(2) << right << i << ". " << *it << endl;
}
