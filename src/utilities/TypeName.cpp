#include <azule/utilities/TypeName.h>

std::string azule::TypeName(const std::type_info& x)
{
	std::string name = x.name();
	name = name.substr(name.find_first_of(' ') + 1);
	return name;
}
