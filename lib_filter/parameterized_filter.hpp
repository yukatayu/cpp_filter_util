#pragma once
#include "filter.hpp"

template<class F> class ParameterizedFilter{
	F filter_func;
	public:
	ParameterizedFilter(F filter_func) : filter_func(filter_func) {}

	template<class ...Args> auto operator()(Args&& ...args){
		return Filter{
			[=](const auto& target){
				return filter_func(target, args...);
			}
		};
	}
};
