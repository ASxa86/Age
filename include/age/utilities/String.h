#pragma once

#include <age/core/TypeTraits.h>
#include <age/utilities/export.h>
#include <age/utilities/MagicEnum.h>
#include <array>
#include <charconv>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace age
{
	namespace utilities
	{
		AGE_UTILITIES_EXPORT std::vector<std::string> Split(std::string x, std::string tokens = " \t\n,", std::array<char, 2> container = {'{', '}'});

		///
		///	\brief Special ToString overload to support floating point precision and format.
		///
		///	\param x The float to convert.
		///	\param precision The decimal precision to output.
		///	\param fmt Specify either scientific or fixed format.
		///

		// AMS // 10/6/2019 // Unsupported by gcc v9.0.1
		// AGE_CORE_EXPORT std::string ToString(float x, int precision = std::numeric_limits<float>::max_digits10,
		// 										  std::chars_format fmt = std::chars_format::fixed);
		AGE_UTILITIES_EXPORT std::string ToString(float x, int precision = std::numeric_limits<float>::max_digits10);

		///
		///	\brief Special ToString overload to support floating point precision and format.
		///
		///	\param x The double to convert.
		///	\param precision The decimal precision to output.
		///	\param fmt Specify either scientific or fixed format.
		///

		// AMS // 10/6/2019 // Unsupported by gcc v9.0.1
		// AGE_CORE_EXPORT std::string ToString(double x, int precision = std::numeric_limits<double>::max_digits10,
		// 										  std::chars_format fmt = std::chars_format::fixed);
		AGE_UTILITIES_EXPORT std::string ToString(double x, int precision = std::numeric_limits<double>::max_digits10);

		template <typename T>
		std::string ToString([[maybe_unused]] const T& x)
		{
			if constexpr(std::is_same<std::chrono::microseconds, T>::value == true || std::is_same<std::chrono::milliseconds, T>::value == true
						 || std::is_same<std::chrono::seconds, T>::value == true || std::is_same<std::chrono::minutes, T>::value == true
						 || std::is_same<std::chrono::hours, T>::value == true)
			{
				return ToString(x.count());
			}
			else if constexpr(std::is_same<bool, T>::value == true)
			{
				return x ? "true" : "false";
			}
			else if constexpr(std::is_same<std::filesystem::path, T>::value == true)
			{
				return x.string();
			}
			else if constexpr(std::is_arithmetic<T>::value == true && std::is_floating_point<T>::value == false)
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
			else if constexpr(std::is_convertible<T, std::string>::value == true)
			{
				return static_cast<std::string>(x);
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
			else if constexpr(std::is_same<const std::string&, T>::value == true)
			{
				return x;
			}
		}

		template <typename T>
		T StringTo([[maybe_unused]] const std::string& x)
		{
			if constexpr(std::is_same<std::chrono::microseconds, T>::value == true || std::is_same<std::chrono::milliseconds, T>::value == true
						 || std::is_same<std::chrono::seconds, T>::value == true || std::is_same<std::chrono::minutes, T>::value == true
						 || std::is_same<std::chrono::hours, T>::value == true)
			{
				return T{StringTo<typename T::rep>(x)};
			}
			else if constexpr(std::is_same<bool, T>::value == true)
			{
				return x == "true" ? true : false;
			}
			else if constexpr(std::is_same<std::filesystem::path, T>::value == true)
			{
				return std::filesystem::path{x};
			}
			// AMS // 10/6/2019 // gcc v9.0.1 doesn't support charconv for floating point types.
			else if constexpr(std::is_floating_point<T>::value == true)
			{
				T t{};

				if constexpr(std::is_same<T, float>::value == true)
				{
					try
					{
						t = std::stof(x);
					}
					catch(...)
					{
						t = std::numeric_limits<float>::quiet_NaN();
					}
				}
				else
				{
					try
					{
						t = std::stod(x);
					}
					catch(...)
					{
						t = std::numeric_limits<double>::quiet_NaN();
					}
				}

				return t;
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
			else if constexpr(std::is_constructible<T, const std::string&>::value == true)
			{
				return T{x};
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
			else if constexpr(std::is_same<const std::string&, T>::value == true)
			{
				return x;
			}
		}
	}
}
