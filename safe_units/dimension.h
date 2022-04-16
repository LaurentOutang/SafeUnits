#pragma once
#include "power.h"

namespace su
{
	template<typename ...powers>
	struct dimension
	{

	};

	template<typename power, typename ...powers>
	struct dimension<power, powers...>
	{
		using first = power;
		using sub_dim = dimension<powers...>;
	};

	template<typename T>
	struct is_dimension
	{
		template<typename ...args>
		static std::true_type dimension_test(dimension<args...> const&);

		template<typename ...args>
		static std::false_type dimension_test(...);

		static constexpr bool value = decltype(dimension_test(std::declval<T>()))::value;
	};

	template<typename T>
	static constexpr bool is_dimension_v = is_dimension<T>::value;
}