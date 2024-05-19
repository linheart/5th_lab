#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;
using windows = vector<pair<vector<string>, int>>;
using functions = map<string, function<void(windows &)>>;

string gen_ticket();
void ENQUEUE(windows &);
void DISTRIBUTE(windows &);
int find_min_time(windows &queue);

int main() {
  functions commands = {{"ENQUEUE", ENQUEUE}, {"DISTRIBUTE", DISTRIBUTE}};
  int n;
  cout << "Enter the number of windows: ";
  cin >> n;
  windows queue(n);
  string command = "";
  while (command != "DISTRIBUTE") {
    cin >> command;
    if (commands.find(command) != commands.end())
      commands[command](queue);
    else
      cout << "Invalid input" << endl;
  }
  return 0;
}

string gen_ticket() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(100, 999);
  return "T" + to_string(dis(gen));
}

int find_min_time(windows &queue) {
  int min_time_index = 0;
  for (size_t i = 0; i < queue.size(); i++)
    if (queue[i].second < queue[min_time_index].second)
      min_time_index = i;

  return min_time_index;
}

void ENQUEUE(windows &queue) {
  int time;
  cin >> time;
  string ticket = gen_ticket();
  cout << ticket << endl;
  int index = find_min_time(queue);
  queue[index].first.push_back(ticket);
  queue[index].second += time;
}

void DISTRIBUTE(windows &queue) {
  for (size_t i = 0; i < queue.size(); i++) {
    cout << i + 1 << " window " << '(' << queue[i].second << " minutes): ";
    for (auto ticket : queue[i].first)
      cout << ticket << ' ';
    cout << endl;
  }
}
