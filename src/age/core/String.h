#pragma once

#include <age/core/Export.h>
#include <array>
#include <charconv>
#include <string>

namespace age
{
	namespace core
	{
		template <typename T>
		std::string ToString([[maybe_unused]] const T& x)
		{
			if constexpr(std::is_arithmetic<T>::value == true)
			{
				std::array<char, 100> buffer{};
				const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x);

				if(ec == std::errc())
				{
					return std::string(buffer.data(), p - buffer.data());
				}
			}

			return {};
		}

		template <typename T>
		T StringTo([[maybe_unused]] const std::string& x)
		{
			if constexpr(std::is_arithmetic<T>::value == true)
			{
				T t{};
				const auto [p, ec] = std::from_chars(x.data(), x.data() + x.size(), t);

				if(ec == std::errc())
				{
					return t;
				}
			}

			return {};
		}
	}
}
