#include "Person.hpp"
#include <cassert>
#include <stdexcept>
#include <string>

class PersonTest {
private:
  void get_fullname_test();
  void constructor_empty_firstname_test();

public:
  void run();
};

void PersonTest::get_fullname_test() {
  Person person("Edsger", "Dijkstra");
  assert(person.get_fullname() == "Edsger Dijkstra");
}

void PersonTest::constructor_empty_firstname_test() {
  try {
    Person person("", "Dijkstra");
    assert(false);
  } catch (std::invalid_argument) {
  }
}

void PersonTest::run() {
  get_fullname_test();
  constructor_empty_firstname_test();
}

int main(int argc, char const *argv[]) {
  PersonTest person_test;
  person_test.run();

  return 0;
}
