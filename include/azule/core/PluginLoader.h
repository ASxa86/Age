#pragma once

#include <azule/export.hxx>
#include <boost/dll/shared_library.hpp>

namespace azule
{
	class AZULE_EXPORT PluginLoader
	{
	public:
		PluginLoader();
		~PluginLoader();

		PluginLoader(const PluginLoader& x);
		PluginLoader(PluginLoader&& x) noexcept;
		PluginLoader& operator=(const PluginLoader& x);
		PluginLoader& operator=(PluginLoader&& x) noexcept;

	private:
		std::vector<boost::dll::shared_library> libraries;
	};
}
