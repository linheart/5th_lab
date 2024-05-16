#include <functional>
#include <iostream>
#include <map>

using namespace std;
using list = map<pair<char, int>, int>;
using functions = map<string, function<void(list &)>>;

void ADD(list &);
void REMOVE(list &);
void INFO(list &);
list init();

int main() {
  functions commands = {{"ADD", ADD}, {"REMOVE", REMOVE}, {"INFO", INFO}};
  list warehouse = init();
  while (1) {
    string command;
    cin >> command;
    if (commands.find(command) != commands.end())
      commands[command](warehouse);
    else
      cout << "Invalid input" << endl;
  }
  return 0;
}

void INFO(list &warehouse) {
  int total_space = 640;
  list non_empty_cells;
  int units_of_goods = 0;
  map<char, int> zone_occupancy = {{'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}};
  cout << "Empty cells:" << endl;
  for (auto it : warehouse) {
    auto key = it.first;
    if (!it.second)
      cout << key.first << key.second << ' ';
    else {
      non_empty_cells[{key.first, key.second}] = it.second;
      units_of_goods += it.second;
      zone_occupancy[key.first] += it.second;
    }
  }
  if (units_of_goods == 0)
    cout << "\nThere are no occupied cells" << endl;
  else {
    cout << "\nNon-empty cells:" << endl;
    for (auto it : non_empty_cells) {
      auto key = it.first;
      cout << key.first << key.second << " = " << it.second << endl;
    }
  }
  cout << "Warehouse occupancy is "
       << double(units_of_goods) / total_space * 100 << '%' << endl;
  cout << "Zone occupancy:" << endl;
  for (auto zone : zone_occupancy)
    cout << zone.first << " - " << double(zone.second) / (total_space / 4) * 100
         << '%' << endl;
}

void ADD(list &warehouse) {
  string product;
  int quantity;
  char zone;
  int place;
  cin >> product >> quantity >> zone >> place;
  if (warehouse.find({zone, place}) != warehouse.end()) {
    if (warehouse[{zone, place}] + quantity <= 10)
      warehouse[{zone, place}] += quantity;
    else
      cout << "Not enough space" << endl;
  } else
    cout << "There is no cell " << zone << place << endl;
}

void REMOVE(list &warehouse) {
  string product;
  int quantity;
  char zone;
  int place;
  cin >> product >> quantity >> zone >> place;
  if (warehouse.find({zone, place}) != warehouse.end()) {
    if (warehouse[{zone, place}] - quantity >= 0)
      warehouse[{zone, place}] -= quantity;
    else
      cout << "Units of goods less than " << quantity << endl;
  } else
    cout << "There is no cell " << zone << place << endl;
}

list init() {
  list warehouse;
  for (char c = 'A'; c <= 'D'; c++)
    for (int i = 1; i <= 8; i++)
      for (int j = 1; j <= 2; j++)
        warehouse[{c, i * 100 + j * 10 + 1}] = 0;
  return warehouse;
}
