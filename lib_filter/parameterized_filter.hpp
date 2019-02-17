#pragma once
#include "filter.hpp"

static auto ParameterizedFilter = [](auto&& func){
	return [func](auto&& ...args){
		return Filter{
			[=](const auto& target){
				return func(target, args...);
			}
		};
	};
};


