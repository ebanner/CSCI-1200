#ifndef SUPERHERO_H_
#define SUPERHERO_H_

#include <iostream>
#include <string>

class Superhero {
  private:
    // representation
    std::string name;
    std::string true_identity;
    std::string superhuman_power;

  public:
    // constructor
    Superhero(const std::string &name_, const std::string &true_identity_, const std::string &superhuman_power_) : 
      name(name_), true_identity(true_identity_), superhuman_power(superhuman_power_) { }

    // accessors
    const std::string& getName() const { return name; }
    const std::string& getPower() const { return superhuman_power; }

    // output
    friend std::ostream& operator<<(std::ostream &ostr, const Superhero &superhero) {
      ostr << "Superhero " << superhero.name << " has power " << superhero.superhuman_power << std::endl;
    }

    // operators
    friend bool operator==(const Superhero &superhero1, const std::string &true_identity_guess) {
      return superhero1.true_identity == true_identity_guess;
    }
    friend bool operator!=(const Superhero &superhero1, const std::string &true_identity_guess) {
      return superhero1.true_identity != true_identity_guess;
    }

};

#endif
