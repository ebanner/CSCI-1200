#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <list>

using namespace std;

class Student {
   public:
      // constructor
      Student(const string &name) : decided_school() { this->name = name; has_offer = false; }

      // accessors
      const string& GetName() const { return name; }
      const list<string>& GetPreferredSchools() const { return preferred_schools; }
      bool HasOffer() const { return has_offer; }

      // modifiers
      void AddSchool(const string &school_name) { preferred_schools.push_back(school_name); }
      void RemoveSchool(const string &school_name);

      // Gale-Shapley stuff
      void PrepareToReceiveOffers();
      const string& GetBestOffer() const { return decided_school; }
      bool IsOfferTentativelyAccepted(const string &school_name);

      void PrintStudentDecision(ostream &ostr) const;
      void PrintStudentPreference(ostream &ostr) const;

   private:
      string name;
      list<string> preferred_schools;
      string decided_school;
      bool has_offer;
};

bool operator==(const Student &student1, const Student &student2);

#endif