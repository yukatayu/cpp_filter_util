#include <iostream>
#include <vector>

#include <lib_filter/filter.hpp>
#include <lib_filter/parameterized_filter.hpp>

using namespace std;

int main(){
	// preparing filter

	// (int, int) -> vector<int>
	auto range = Filter ([](std::pair<int, int> min_max) -> vector<int>{
		vector<int> res;
		for(int i=min_max.first; i < min_max.second; ++i)
			res.push_back(i);
		return res;
	});

	// vector<int> -> vector<unsigned>
	auto abs_num = Filter ([](vector<int> list) -> vector<unsigned>{
		vector<unsigned> res;
		res.reserve(list.size());
		for(int i : list)
			res.push_back(i<0 ? -i : i);
		return res;
	});

	auto limit_num = ParameterizedFilter ([](vector<unsigned> list, unsigned limit) -> vector<unsigned>{
			vector<unsigned> res;
			for(auto i : list)
				if(i <= limit)
					res.push_back(i);
			return res;
	});

	// vector<unsigned> -> int
	auto max_num = Filter([](vector<unsigned> list) -> int{
		int max = -1;
		for(auto u : list)
			if(max < static_cast<int>(u))
				max = u;
		return max;
	});

	// int -> int
	Filter square {[](int n){
		return n*n;
	}};

// --------------------

	// synthesize filter

	// vector<int> -> (vector<unsigned>) -> (vector<unsigned>) -> int
	auto abs_limit_max_num = abs_num | limit_num(5) | max_num;

// --------------------

	// apply filter

	std::cout
		// (4, 8) -> {-4, -3, .. , 7} -> {4, 3, .. , 0, .. , 5} -> 5 -> 25
		// (int, int) -> (vector<int> -> vector<unsigned> -> int) -> int
		<< ( make_pair(-4, 8) | range | abs_limit_max_num | square )
		<< std::endl;
}

