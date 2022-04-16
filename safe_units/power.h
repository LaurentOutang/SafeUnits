#pragma once
#include <ratio>
#include "base_dimension.h"

namespace su
{
	template<typename dim, typename exp>
	struct power
	{
		using base_dim = dim;
		using exponent = exp;
	};
}
