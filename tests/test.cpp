#include <iostream>
#include <vector>

#include <lib_filter/filter.hpp>

using namespace std;

int main(){
	// preparing filter

	// (int, int) -> vector<int>
	Filter range {[](std::pair<int, int> min_max) -> vector<int>{
		vector<int> res;
		for(int i=min_max.first; i < min_max.second; ++i)
			res.push_back(i);
		return res;
	}};

	// vector<int> -> vector<unsigned>
	Filter abs_num {[](vector<int> list) -> vector<unsigned>{
		vector<unsigned> res;
		res.reserve(list.size());
		for(int i : list)
			res.push_back(i<0 ? -i : i);
		return res;
	}};

	// vector<unsigned> -> int
	Filter max_num {[](vector<unsigned> list) -> int{
		int max = -1;
		for(auto u : list)
			if(max < static_cast<int>(u))
				max = u;
		return max;
	}};

	// int -> int
	Filter square {[](int n){
		return n*n;
	}};

// --------------------

	// synthesize filter

	// vector<int> -> (vector<unsigned>) -> int
	auto abs_max_num = abs_num | max_num;

// --------------------

	// apply filter

	std::cout
		// (4, 8) -> {-4, -3, .. , 7} -> {4, 3, .. , 0, .. , 7} -> 7 -> 49
		// (int, int) -> (vector<int> -> vector<unsigned> -> int) -> int
		<< ( make_pair(-4, 8) | range | abs_max_num | square )
		<< std::endl;
}

