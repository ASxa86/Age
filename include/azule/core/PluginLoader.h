#pragma once

#include <azule/export.hxx>
#include <boost/dll/shared_library.hpp>
#include <azule/core/ObjectFactory.h>

namespace azule
{
	class AZULE_EXPORT PluginLoader
	{
	public:
		PluginLoader(ObjectFactory& x);
		~PluginLoader();

		PluginLoader(const PluginLoader& x) = delete;
		PluginLoader(PluginLoader&& x) noexcept = delete;
		PluginLoader& operator=(const PluginLoader& x) = delete;
		PluginLoader& operator=(PluginLoader&& x) noexcept = delete;

	private:
		std::vector<boost::dll::shared_library> libraries;
		ObjectFactory& factory;
	};
}
