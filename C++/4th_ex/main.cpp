#include <functional>
#include <iostream>
#include <map>
#include <string>

using namespace std;

string CHANGE(map<string, string> &);
string RENAME(map<string, string> &);
string ABOUT(map<string, string> &);
string ALL(map<string, string> &);
bool find_region(map<string, string>, string);

int main() {
  map<string, function<string(map<string, string> &)>> options = {
      {"CHANGE", CHANGE}, {"RENAME", RENAME}, {"ABOUT", ABOUT}, {"ALL", ALL}};
  map<string, string> guide;
  int N;
  string option;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> option;
    if (options.find(option) != options.end())
      cout << options[option](guide) << endl;
    else
      cout << "There's no option" << endl;
  }

  return 0;
}

bool find_region(map<string, string> guide, string region) {
  return guide.find(region) == guide.end();
}

string CHANGE(map<string, string> &guide) {
  string region, new_center;
  cin >> region >> new_center;
  string output;
  if (find_region(guide, region))
    output =
        "New region " + region + " with administrative center " + new_center;
  else
    output = "Region " + region +
             " has changed its administrative center from " + guide[region] +
             " to " + new_center;
  guide[region] = new_center;
  return output;
}

string RENAME(map<string, string> &guide) {
  string old_region, new_region;
  cin >> old_region >> new_region;
  if (!find_region(guide, old_region)) {
    guide[new_region] = guide[old_region];
    guide.erase(old_region);
    return old_region + " has been renamed to " + new_region;
  }
  return "There's no " + old_region;
}
string ABOUT(map<string, string> &guide) {
  string region;
  cin >> region;
  if (!find_region(guide, region))
    return region + " has administrative center" + guide[region];
  return "There's no region " + region;
}

string ALL(map<string, string> &guide) {
  string output = "";
  for (auto it = guide.begin(); it != guide.end(); it++) {
    output += it->first + " - " + it->second;
    if (next(it) != guide.end())
      output += '\n';
  }
  return output;
}
