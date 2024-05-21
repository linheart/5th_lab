#include "planes.h"

using namespace std;

int main() {
  map<string, Type> functions = {{"CREATE_PLANE", Type::CREATE_PLANE},
                                 {"PLANES_FOR_TOWN", Type::PLANES_FOR_TOWN},
                                 {"TOWNS_FOR_PLANE", Type::TOWNS_FOR_PLANE},
                                 {"PLANES", Type::PLANES}};
  list information;
  string func;
  while (1) {
    cin >> func;

    if (functions.find(func) == functions.end()) {
      cout << "Invalid input" << endl;
      continue;
    }

    switch (functions[func]) {
    case Type::CREATE_PLANE:
      CREATE_PLANE(information);
      break;
    case Type::PLANES_FOR_TOWN: {
      string town;
      cin >> town;
      PLANES_FOR_TOWN(information, town);
      break;
    }
    case Type::TOWNS_FOR_PLANE:
      TOWNS_FOR_PLANE(information);
      break;
    case Type::PLANES:
      PLANES(information);
      break;
    }
  }
}
