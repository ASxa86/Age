#pragma once

#include <age/core/MagicEnum.h>
#include <age/core/TypeTraits.h>
#include <age/core/export.h>
#include <array>
#include <boost/type_traits.hpp>
#include <charconv>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>

namespace age
{
	namespace core
	{
		AGE_CORE_EXPORT std::vector<std::string> Split(std::string x, std::string tokens = " \t\n,", std::array<char, 2> container = {'{', '}'});

		template <typename T>
		std::string ToString([[maybe_unused]] const T& x)
		{
			if constexpr(std::is_same<std::chrono::microseconds, T>::value == true)
			{
				return ToString(x.count());
			}
			else if constexpr(std::is_same<bool, T>::value == true)
			{
				return x ? "true" : "false";
			}
			else if constexpr(std::is_arithmetic<T>::value == true)
			{
				std::array<char, 100> buffer{};
				const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x);

				if(ec == std::errc())
				{
					return std::string(buffer.data(), p - buffer.data());
				}

				return {};
			}
			else if constexpr(std::is_enum<T>::value == true)
			{
				return std::string(magic_enum::enum_name(x));
			}
			else if constexpr(age::core::is_array<T>::value == true)
			{
				std::string s = "{";

				for(const auto& i : x)
				{
					s += ToString(i);
					s += ", ";
				}

				// Remove last ", "
				s.pop_back();
				s.pop_back();

				return s + "}";
			}
			else if constexpr(boost::has_left_shift<std::ostream, T>::value == true)
			{
				std::stringstream ss;
				ss << x;
				return ss.str();
			}
			else if constexpr(std::is_same<const std::string&, T>::value == true)
			{
				return x;
			}
		}

		template <typename T>
		T StringTo([[maybe_unused]] const std::string& x)
		{
			if constexpr(std::is_same<std::chrono::microseconds, T>::value == true)
			{
				return std::chrono::microseconds{StringTo<T::rep>(x)};
			}
			else if constexpr(std::is_same<bool, T>::value == true)
			{
				return x == "true" ? true : false;
			}
			else if constexpr(std::is_arithmetic<T>::value == true)
			{
				T t{};
				const auto [p, ec] = std::from_chars(x.data(), x.data() + x.size(), t);

				if(ec == std::errc())
				{
					return t;
				}

				return t;
			}
			else if constexpr(std::is_enum<T>::value == true)
			{
				return magic_enum::enum_cast<T>(x).value_or(T{});
			}
			else if constexpr(age::core::is_array<T>::value == true)
			{
				T t{};
				const auto tokens = Split(x);
				for(auto i = 0; i < t.size(); i++)
				{
					t[i] = StringTo<T::value_type>(tokens[i]);
				}

				return t;
			}
			else if constexpr(boost::has_right_shift<std::istream, T>::value == true)
			{
				T t{};
				std::istringstream ss{x};
				ss >> t;
				return t;
			}
			else if constexpr(std::is_same<const std::string&, T>::value == true)
			{
				return x;
			}
		}
	}
}
