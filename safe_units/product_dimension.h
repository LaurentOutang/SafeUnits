#pragma once
#include <type_traits>
#include "dimension.h"
#include "product_power.h"

namespace su
{
	template<typename dim, typename ...powers>
	struct concat_powers_right
	{
		using next_dim = typename dim::sub_dim;
		using power = typename dim::first;
		using result = typename concat_powers_right<next_dim, powers..., power>::result;
	};

	template<typename ...powers>
	struct concat_powers_right<dimension<>, powers...>
	{
		using result = dimension<powers...>;
	};

	template<typename dim1, typename dim2, typename ...already_computed_powers>
	struct compute_product_dimension
	{
		//Same dim case
		static constexpr bool first_power_has_same_base_dimension = std::is_same_v<typename dim1::first::base_dim::inner, typename dim2::first::base_dim::inner>;
		using first_power_prod_assuming_same_dim = typename product_power<typename dim1::first, typename dim2::first>::result;
		static constexpr bool power_has_zero_exponent = typename first_power_prod_assuming_same_dim::exponent::num == 0;
		using result_same_dimension = std::conditional_t<power_has_zero_exponent,
			typename compute_product_dimension<typename dim1::sub_dim, typename dim2::sub_dim, already_computed_powers...>::result,
			typename compute_product_dimension<typename dim1::sub_dim, typename dim2::sub_dim, already_computed_powers..., first_power_prod_assuming_same_dim>::result>;

		//Diff dim case (assuming that if dim1 has not priority then dim2 has, i.e. both contained in the defined order)
		using first_inner_dim_result = typename first_in_order<typename dim1::first::base_dim::inner, typename dim2::first::base_dim::inner>::result;
		static constexpr bool dim1_has_priority = std::is_same_v<first_inner_dim_result, typename dim1::first::base_dim::inner>;
		using first_power_assuming_diff_dim = std::conditional_t<dim1_has_priority, typename dim1::first, typename dim2::first>;
		using next_dim1_result = std::conditional_t<dim1_has_priority, typename dim1::sub_dim, dim1>;
		using next_dim2_result = std::conditional_t<dim1_has_priority, dim2, typename dim2::sub_dim>;
		using result_diff_dimension = typename compute_product_dimension<next_dim1_result, next_dim2_result, already_computed_powers..., first_power_assuming_diff_dim>::result;

		using result = std::conditional_t<first_power_has_same_base_dimension, result_same_dimension, result_diff_dimension>;
	};

	template<typename dim2, typename ...already_computed_powers>
	struct compute_product_dimension<dimension<>, dim2, already_computed_powers...>
	{
		using result = typename concat_powers_right<dim2, already_computed_powers...>::result;
	};

	template<typename dim1, typename ...already_computed_powers>
	struct compute_product_dimension<dim1, dimension<>, already_computed_powers...>
	{
		using result = typename concat_powers_right<dim1, already_computed_powers...>::result;
	};

	template<typename ...already_computed_powers>
	struct compute_product_dimension<dimension<>, dimension<>, already_computed_powers...>
	{
		using result = dimension<already_computed_powers...>;
	};

	template<typename dim1, typename dim2>
	struct product_dimension
	{
		using result = typename compute_product_dimension<dim1, dim2>::result;
	};
}
