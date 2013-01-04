#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <list>

using namespace std;

class Student {
   public:
      // constructor
      Student(const string &name) { this->name = name; }

      // accessors
      const string& GetName() const { return name; }
      int GetNumPrefs() const { return num_prefs; }
      const list<string>& GetPreferredSchools() const { return preferred_schools; }
      bool HasOffer() const;

      // modifiers
      void AddSchool(const string &school_name) { preferred_schools.push_back(school_name); }
      void RemoveFromSchoolPreference(const string &school_name);

      // Gale-Shapley stuff
      void PrepareToReceiveOffers();
      string GetBestOffer();
      bool IsOfferTentativelyAccepted(const string &school_name);
      void PrintStudentDecision(ofstream &ostr);

   private:
      string name;
      int num_prefs;
      list<string> preferred_schools;
      string decided_school;
      bool has_offer;
};

bool operator==(const Student &student1, const Student &student2);

#endif
