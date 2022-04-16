#pragma once
#include <type_traits>

namespace su
{
	template<typename dim, typename u, typename rep>
	struct quantity
	{
		rep raw;
	};

	template<typename dim1, typename dim2, typename u1, typename u2, typename rep1, typename rep2>
	constexpr auto operator*(quantity<dim1, u1, rep1> const& q1, quantity<dim2, u2, rep2> const& q2) -> decltype(auto)
	{
		return quantity<typename product_dimension<dim1, dim2>::result, 
			typename product_unit<u1, u2>::result, 
			decltype(std::declval<rep1>()* std::declval<rep2>())>
		{  };
	}
}