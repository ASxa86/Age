#pragma once

#include <azule/export.hxx>
#include <azule/reflection/Properties.h>
#include <azule/utilities/Signal.h>
#include <functional>
#include <string>
#include <vector>

namespace azule
{
	///
	///	\class Object
	///
	///	\brief Base class for all objects of azule. Designed using the composite pattern from the GoF.
	///
	///	\date April 22, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT Object : public Properties, public std::enable_shared_from_this<Object>
	{
	public:
		enum class FindOption : int
		{
			Direct,
			Recursive
		};

		Object();
		virtual ~Object();

		///
		///	Set an identifier for this object.
		///
		void setID(const std::string& x);

		///
		///	Get this object's identifier.
		///
		std::string getID() const;

	private:
		std::string id;
	};
}
