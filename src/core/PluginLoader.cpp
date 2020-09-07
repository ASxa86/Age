#include <azule/core/PluginLoader.h>

#include <azule/core/Configuration.h>
#include <filesystem>
#include <iostream>

using namespace azule;

#ifdef WIN32
constexpr std::string_view LibraryName{"azule-plugins-"};
constexpr std::string_view LibraryExt{".dll"};
#else
constexpr std::string_view LibraryName{"libazule-plugins-"};
constexpr std::string_view LibraryExt{".so"};
#endif

PluginLoader::PluginLoader(ObjectFactory& x) : factory{x}
{
	const auto pathBin = Configuration::Instance().getPathBin();
	if(std::filesystem::exists(pathBin) == true)
	{
		for(const auto& it : std::filesystem::directory_iterator(pathBin))
		{
			if(std::filesystem::is_regular_file(it) == true && it.path().extension() == LibraryExt)
			{
				const auto filepath = it.path();
				const auto filename = filepath.filename().string();

				if(filename.compare(0, LibraryName.size(), LibraryName) == 0)
				{
					boost::dll::shared_library library(filepath.string());

					if(library.is_loaded() == true && library.has("OnPluginLoad") == true)
					{
						const auto onPluginLoad = library.get<void(ObjectFactory*)>("OnPluginLoad");
						onPluginLoad(&this->factory);

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
	for(auto& library : this->libraries)
	{
		if(library.has("OnPluginUnload") == true)
		{
			const auto onPluginUnload = library.get<void(ObjectFactory*)>("OnPluginUnload");
			onPluginUnload(&this->factory);
		}
	}

	this->libraries.clear();
}
