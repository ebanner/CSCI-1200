#ifndef SUPERHERO_H_
#define SUPERHERO_H_

#include <iostream>
#include <string>
#include <vector>

class Superhero {
  private:
    // representation
    std::string name;
    std::string true_identity;
    std::string superhuman_power;
    bool good;
    
    // ranking of superpowers
    static std::vector<std::pair<std::string, std::string> > superpower_rank;

  public:
    // constructor
    Superhero(const std::string &name_, const std::string &true_identity_, const std::string &superhuman_power_) : 
      name(name_), true_identity(true_identity_), superhuman_power(superhuman_power_), good(true) { }

    // accessors
    const std::string& getName() const { return name; }
    const std::string& getPower() const { return superhuman_power; }
    bool isGood() { return good; }
    const std::string& getTrueIdentity() const { return true_identity; }

    // output
    friend std::ostream& operator<<(std::ostream &ostr, const Superhero &superhero) {
      ostr << "Super" << (superhero.good? "hero":"villan") << superhero.name << 
        " has power " << superhero.superhuman_power << std::endl;

      return ostr;
    }

    // operators
    friend bool operator==(const Superhero &superhero1, const std::string &true_identity_guess) {
      return superhero1.true_identity == true_identity_guess;
    }

    friend bool operator==(const Superhero &superhero1, const Superhero &superhero2) {
      return superhero1.name == superhero2.name;
    }

    friend bool operator!=(const Superhero &superhero1, const std::string &true_identity_guess) {
      return superhero1.true_identity != true_identity_guess;
    }

    friend Superhero operator-(Superhero &superhero) {
      superhero.good = ! superhero.good;
      return superhero;
    }

    friend bool operator>(const Superhero &superhero1, const Superhero &superhero2) {
      std::vector<std::pair<std::string, std::string> >::iterator it;
      for (it = superpower_rank.begin(); it != superpower_rank.end(); it++)
        if (it->first == superhero1.superhuman_power && it->second == superhero2.superhuman_power)
          return true;
      return false;
    }

    static void populateSuperpowerRank() {
      superpower_rank.push_back(std::pair<std::string, std::string>("Fire", "Wood"));
      superpower_rank.push_back(std::pair<std::string, std::string>("Wood", "Water"));
      superpower_rank.push_back(std::pair<std::string, std::string>("Water", "Fire"));
    }
};

#endif
