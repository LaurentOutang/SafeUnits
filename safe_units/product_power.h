#pragma once
#include "power.h"

namespace su
{
	template<typename power1, typename power2>
	struct product_power
	{
		using ratio_sum = std::ratio_add<typename power1::exponent, typename power2::exponent>;
		using result = power<typename power1::base_dim, std::ratio<ratio_sum::num, ratio_sum::den>>;
	};
}
