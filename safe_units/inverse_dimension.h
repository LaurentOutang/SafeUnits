#pragma once
#include "dimension.h"
#include "inverse_power.h"

namespace su
{
	namespace 
	{
		template<typename dim, typename ...already_computed_powers>
		struct compute_inverse_dimension
		{
			using result = typename compute_inverse_dimension<typename dim::sub_dim, already_computed_powers..., typename inverse_power<typename dim::first>::result>::result;
		};

		template<typename ...already_computed_powers>
		struct compute_inverse_dimension<dimension<>, already_computed_powers...>
		{
			using result = dimension<already_computed_powers...>;
		};
	}

	template<typename dim>
	struct inverse_dimension_t
	{
		using result = typename compute_inverse_dimension<dim>::result;
	};

	template<typename dim>
	using inverse_dimension = typename inverse_dimension_t<dim>::result;
}
