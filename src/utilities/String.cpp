#include <azule/utilities/String.h>
#include <boost/spirit/include/karma.hpp>

// AMS // 10/6/2019 // Unsupported by gcc v9.0.1
// std::string age::core::ToString(float x, int precision, std::chars_format fmt)
// {
// 	// Defined a buffer size that can support std::numeric_limits<float>::max() with max precision std::numeric_limits<float>::maxdigits10.
// 	std::array<char, 64> buffer{};
//
// 	auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x, fmt, precision);
//
// 	if(ec == std::errc())
// 	{
// 		return std::string(buffer.data(), static_cast<size_t>(p - buffer.data()));
// 	}
//
// 	return {};
// }

// AMS // 10/6/2019 // Unsupported by gcc v9.0.1
// std::string age::core::ToString(double x, int precision, std::chars_format fmt)
// {
// 	// Defined a buffer size that can support std::numeric_limits<double>::max() with max precision std::numeric_limits<double>::maxdigits10.
// 	std::array<char, 512> buffer{};
//
// 	auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x, fmt, precision);
//
// 	if(ec == std::errc())
// 	{
// 		return std::string(buffer.data(), static_cast<size_t>(p - buffer.data()));
// 	}
//
// 	return {};
// }

namespace
{
	///
	/// http://stackoverflow.com/questions/42255919/using-boost-karma-to-replace-stdstringstream-for-double-to-stdstring-convers
	///
	struct precision_policy_double : boost::spirit::karma::real_policies<double>
	{
		precision_policy_double(int prec) : precision_(prec)
		{
		}

		int precision(double) const
		{
			return precision_;
		}
		int precision_;
	};

	struct precision_policy_float : boost::spirit::karma::real_policies<float>
	{
		precision_policy_float(int prec) : precision_(prec)
		{
		}

		int precision(float) const
		{
			return precision_;
		}
		int precision_;
	};
}

std::string azule::ToString(float x, int precision)
{
	using boost::spirit::ascii::space;
	using boost::spirit::karma::generate;
	using boost::spirit::karma::real_generator;

	real_generator<float, precision_policy_float> value(precision);

	std::string s;
	std::back_insert_iterator<std::string> sink(s);
	generate(sink, value, x);
	return s;
}

std::string azule::ToString(double x, int precision)
{
	using boost::spirit::ascii::space;
	using boost::spirit::karma::generate;
	using boost::spirit::karma::real_generator;

	real_generator<double, precision_policy_double> value(precision);

	std::string s;
	std::back_insert_iterator<std::string> sink(s);
	generate(sink, value, x);
	return s;
}
