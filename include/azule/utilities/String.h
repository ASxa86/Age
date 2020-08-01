#pragma once

#include <azule/utilities/TypeTraits.h>
#include <array>
#include <azule/export.hxx>
#include <charconv>
#include <filesystem>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace azule
{
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
	AZULE_EXPORT std::string ToString(float x, int precision = std::numeric_limits<float>::max_digits10);

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
	AZULE_EXPORT std::string ToString(double x, int precision = std::numeric_limits<double>::max_digits10);

	///
	///	\brief Generic type conversion/serialization to a std::string.
	///
	///	Complex types such as containers and classes will be serialized as json strings.
	///
	template <typename T>
	std::string ToString([[maybe_unused]] const T& x)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		if constexpr(azule::is_duration<TNoRef>::value == true)
		{
			return ToString(x.count());
		}
		else if constexpr(std::is_same<bool, TNoRef>::value == true)
		{
			return x ? "true" : "false";
		}
		else if constexpr(std::is_same<std::filesystem::path, TNoRef>::value == true)
		{
			return x.string();
		}
		else if constexpr(std::is_arithmetic<TNoRef>::value == true)
		{
			std::array<char, 100> buffer{};
			const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x);

			if(ec == std::errc())
			{
				return std::string(buffer.data(), p - buffer.data());
			}

			return {};
		}
		else if constexpr(std::is_enum<TNoRef>::value == true)
		{
			return std::string(magic_enum::enum_name(x));
		}
		else if constexpr(std::is_convertible<TNoRef, std::string>::value == true)
		{
			return static_cast<std::string>(x);
		}
		else if constexpr(std::is_same<std::string, TNoRef>::value == true)
		{
			return x;
		}
		else if constexpr(std::is_class<TNoRef>::value == true)
		{
			nlohmann::json j = x;
			return j.dump();
		}
	}

	template <typename T>
	typename std::remove_reference<T>::type StringTo(std::string_view x);

	template <typename T>
	void StringTo([[maybe_unused]] std::string_view x, T& t)
	{
		if constexpr(azule::is_duration<T>::value == true)
		{
			t = T{StringTo<typename T::rep>(x)};
		}
		else if constexpr(std::is_same<bool, T>::value == true)
		{
			t = (x == "true") ? true : false;
		}
		else if constexpr(std::is_same<std::filesystem::path, std::remove_reference<T>::type>::value == true)
		{
			t = x;
		}
		// AMS // 10/6/2019 // gcc v9.0.1 doesn't support charconv for floating point types.
		else if constexpr(std::is_floating_point<T>::value == true)
		{
			if constexpr(std::is_same<T, float>::value == true)
			{
				try
				{
					t = std::stof(std::string(x));
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
					t = std::stod(std::string(x));
				}
				catch(...)
				{
					t = std::numeric_limits<double>::quiet_NaN();
				}
			}
		}
		else if constexpr(std::is_arithmetic<std::remove_reference<T>::type>::value == true)
		{
			std::from_chars(x.data(), x.data() + x.size(), t);
		}
		else if constexpr(std::is_enum<std::remove_reference<T>::type>::value == true)
		{
			t = magic_enum::enum_cast<T>(x).value_or(t);
		}
		else if constexpr(std::is_same<std::string, std::remove_reference<T>::type>::value == true)
		{
			t = x;
		}
		else if constexpr(std::is_class<T>::value == true)
		{
			nlohmann::json j = nlohmann::json::parse(x);
			j.get_to(t);
		}
	}

	template <typename T>
	typename std::remove_reference<T>::type StringTo(std::string_view x)
	{
		using TNoRef = typename std::remove_const<typename std::remove_reference<T>::type>::type;

		TNoRef t{};
		StringTo(x, t);
		return t;
	}
}
