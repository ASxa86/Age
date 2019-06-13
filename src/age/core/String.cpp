#include <age/core/String.h>
#include <boost/algorithm/string.hpp>

std::vector<std::string> age::core::Split(std::string x, std::string tokens, std::array<char, 2> container)
{
	std::vector<std::string> v;

	if(x.size() >= 2)
	{
		if(x.front() == container[0] && x.back() == container[1])
		{
			// Strip the containing braces.
			x = x.substr(1, x.size() - 2);
		}

		boost::algorithm::trim(x);
		boost::algorithm::split(v, x, boost::is_any_of(tokens), boost::algorithm::token_compress_mode_type::token_compress_on);
	}

	return v;
}
