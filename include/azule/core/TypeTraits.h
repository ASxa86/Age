#pragma once

#include <array>
#include <type_traits>

namespace azule
{
	namespace core
	{
		/// https://stackoverflow.com/questions/40924276/why-does-stdis-array-return-false-for-stdarray
		template <class T>
		struct is_array : std::is_array<T>
		{
		};

		template <class T, std::size_t N>
		struct is_array<std::array<T, N>> : std::true_type
		{
		};
	}
}
