/**
Swaraj Ketan Santra  ~ v2
**/
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Pair
{
private:
	int _A;
	int _B;
public:
	Pair(int a, int b) : 
		_A(a), _B(b) {
	}
	Pair() {

	}
	~Pair() {
	}
public:
	int A() const { return _A; };
	int B() const { return _B; };
	bool AreSame(Pair* pair) {
		return (A() == pair->A() && B() == pair->B()) || (A() == pair->B() && B() == pair->A());
	}
};

vector<int> CheckIfFormsTriangle(Pair* x, Pair* y, Pair* z) {

	vector<int> distinctAngles;
	if (x->AreSame(y) || y->AreSame(z) || z->AreSame(x))
		return distinctAngles;

	int lines[6] = { x->A(), x->B(), y->A(), y->B(), z->A(), z->B() };
	for (int i : lines) {
		bool found = false;
		for (int da : distinctAngles) {
			if (i == da) {
				found = true; break;
			}
		}
		if (!found)
			distinctAngles.push_back(i);
	}
	std::sort(std::begin(distinctAngles), std::end(distinctAngles)); // sort
	return distinctAngles;
}

int main()
{	//////////////////////////////////////////////////////INPUT/////////////////////////////
	int count = 6; // Input 1
	int angles[] = {-20,20,0,50,50,50}; // Input 2	
	////////////////////////////////////////////////////////////////////////////////////////

	int cuts = 0; // Number of cut points
	vector<Pair> pairs; // all the cut Pairs
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (angles[i] != angles[j]) // Same angled lines are parallel. They wont cut each other
			{
				cuts += 1;
				int a, b;
				if (angles[i] > angles[j]){
					a = angles[j]; b = angles[i];
				}
				else {
					a = angles[i]; b = angles[j];
				}

				Pair pair(a, b);
				pairs.push_back(pair);
			}
		}
	}
	
	/*
	Pairs : (-20,0) , (-20,20) , (-20,50), (-20,50), (-20,50), (0,20) , (0, 50), (0,50), (20,50), (20,50)
	One triagnle will be formed by : (-20,0) -> (0,20) -> (20,-20)
	Thus there will  be 7 triangles
	*/
	vector<vector<int>> combinations; // triangles
	for(Pair p : pairs) {

		for (Pair pi : pairs) {

			if (p.AreSame(&pi)) // Same item skip
				continue;

			for (Pair pii : pairs) {

				if (pi.AreSame(&pii) || p.AreSame(&pii))  // Same item skip
					continue;

				auto result = CheckIfFormsTriangle(&p, &pi, &pii);

				if (result.size() == 3) {					
					bool exists = false;
					for (vector<int> t : combinations) {
						if (t[0] == result[0] && t[1] == result[1] && t[2] == result[2])
							exists = true;
					}
					if (!exists) {
						combinations.push_back(result);
   				    }

				}

			}
		
		}
	}

	int trianglesCount = combinations.size();

	// Handle duplicate angles(Parallel lines) seperately
	vector<int> distinctAngles;

	for (int i : angles) {
		int c = 0;
		for (int di : distinctAngles) {
			if (i == di) {
				c += 1;
			}
		}
		if (c == 0) { distinctAngles.push_back(i); }
		else if (c > 0) {
			trianglesCount += (distinctAngles.size() - 1);
		}
	}
	std::cout << "Triangles count : " << trianglesCount << endl;

    return EXIT_SUCCESS;
}



