#pragma once
#include "power.h"

namespace su
{
	template<typename p>
	struct inverse_power
	{
		static constexpr std::intmax_t neg_num = - p::exponent::num;
		using neg_p = std::ratio<neg_num, p::exponent::den>;
		using result = power<typename p::base_dim, neg_p>;
	};
}