#include <azule/core/PluginLoader.h>

#include <azule/core/Configuration.h>
#include <filesystem>
#include <iostream>

using namespace azule;

PluginLoader::PluginLoader()
{
	const auto pathBin = Configuration::Instance().getPathBin();
	if(std::filesystem::exists(pathBin) == true)
	{
		for(const auto& it : std::filesystem::directory_iterator(pathBin))
		{
			if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
			{
				const auto filepath = it.path();
				const auto filename = filepath.filename().string();

				const std::string plugin = "azule-plugins-";
				if(filename.compare(0, plugin.size(), plugin) == 0)
				{
					boost::dll::shared_library library(filepath.string());

					if(library.is_loaded() == true)
					{
						// Keep track of loaded libraries in order to keep them loaded in memory.
						this->libraries.push_back(library);
					}
					else
					{
						std::cerr << "Failed to load: " << filepath << "\n";
					}
				}
			}
		}
	}
}

PluginLoader::~PluginLoader()
{
	this->libraries.clear();
}

PluginLoader::PluginLoader(const PluginLoader& x) : libraries{x.libraries}
{
}

PluginLoader::PluginLoader(PluginLoader&& x) noexcept : libraries{std::move(x.libraries)}
{
}

PluginLoader& PluginLoader::operator=(const PluginLoader& x)
{
	this->libraries = x.libraries;
	return *this;
}

PluginLoader& PluginLoader::operator=(PluginLoader&& x) noexcept
{
	this->libraries = std::move(x.libraries);
	return *this;
}
