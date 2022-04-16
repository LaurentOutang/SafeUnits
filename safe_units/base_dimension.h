#pragma once

namespace su
{
	template<typename T>
	struct base_dimension
	{
		using inner = T;
	};

	class length_b {};
	class mass_b {};
	class time_b {};
	class electrical_current_b {};
	class temperature_b {};
	class amount_of_substance_b {};
	class luminous_intesity_b {};

	template<typename ...base_dimensions>
	class order {};

	template<typename base_dim, typename ...base_dimensions>
	struct order<base_dim, base_dimensions...>
	{
		using first = base_dim;
		using sub_order = order<base_dimensions...>;
	};

	using ordered_base_dimensions = order<length_b, mass_b, time_b, electrical_current_b,
		temperature_b, amount_of_substance_b, luminous_intesity_b>;

	template<typename T, typename U, typename O = ordered_base_dimensions>
	struct first_in_order
	{
		using result = std::conditional_t<std::is_same_v<T, typename O::first>, T, std::conditional_t<std::is_same_v<U, typename O::first>, U, typename first_in_order<T, U, typename O::sub_order>::result>>;
	};

	template<typename T, typename U>
	struct first_in_order<T, U, order<>>
	{
		using result = void;
	};
}