#include <iostream>
#include "product_dimension.h"
#include "inverse_dimension.h"

using Length = su::dimension<su::power<su::base_dimension<su::length_b>, std::ratio<1,1>>>;
using Time = su::dimension<su::power<su::base_dimension<su::time_b>, std::ratio<1, 1>>>;

using Frequency = su::inverse_dimension_t<Time>::result;
using Speed = su::product_dimension<Length, Frequency>::result;
/*using Speed = decltype(std::declval<Length>()* std::declval<invTime>());

using Length2 = decltype(std::declval<Time>() * std::declval<Speed>());
using Length3 = decltype(std::declval<Speed>() * std::declval<Time>());

using test_somme = decltype(std::declval<Length2>() + std::declval<Length>());*/

int main()
{
	//std::cout << typeid(Length).name() << typeid(Length2).name() << typeid(Length3).name() << std::endl;
	return 0;
}