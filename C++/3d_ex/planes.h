#ifndef PLANES_H // PLANES_H
#define PLANES_H

#include <set>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

enum class Type {
	CREATE_PLANE,
	PLANES_FOR_TOWN,
	TOWNS_FOR_PLANE,
	PLANES
};

using list = map<string, set<string>>;

void CREATE_PLANE(list &);
void PLANES_FOR_TOWN(list &, string);
void TOWNS_FOR_PLANE(list &);
void PLANES(list);

#endif // PLANES_H
