#pragma once

#include <azule/export.hxx>
#include <string_view>
#include <typeinfo>

namespace azule
{
	template <typename T>
	constexpr std::string_view TypeName()
	{
		constexpr std::string_view signature = __FUNCSIG__;
		constexpr std::string_view removeLeft = signature.substr(signature.find_last_of('<') + 1);
		constexpr std::string_view removeRight = removeLeft.substr(0, removeLeft.find_first_of('>'));
		constexpr std::string_view removeSpace = removeRight.substr(removeRight.find_first_of(' ') + 1);
		return removeSpace;
	}

	AZULE_EXPORT std::string TypeName(const std::type_info& x);
}