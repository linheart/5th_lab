#include "planes.h"

void CREATE_PLANE(list &information) {
  string plane;
  string town;

  cin >> plane;
  information[plane] = {};
  getline(cin, town);
  istringstream iss(town);

  while (iss >> town)
    information[plane].insert(town);
}

void PLANES_FOR_TOWN(list &information, string town) {
  for (auto [plane, towns] : information)
    if (towns.find(town) != towns.end())
      cout << plane << endl;
}

void TOWNS_FOR_PLANE(list &information) {
  string plane;
  cin >> plane;

  for (auto town : information[plane]) {
    cout << town << ": ";
    for (auto [key, value] : information)
      if (key != plane && value.find(town) != value.end())
        cout << key << ' ';
    cout << endl;
  }
}

void PLANES(list information) {
  for (auto plane : information)
    cout << plane.first << endl;
}
