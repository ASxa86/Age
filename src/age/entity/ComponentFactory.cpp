#include <age/entity/ComponentFactory.h>

#include <age/core/Configuration.h>
#include <boost/dll/import.hpp>
#include <iostream>

using namespace age::core;
using namespace age::entity;

ComponentCreatorBase::~ComponentCreatorBase()
{
}

ComponentFactory::ComponentFactory()
{
}

ComponentFactory& ComponentFactory::Instance()
{
	static ComponentFactory singleton;

	if(singleton.initialized == false)
	{
		// Prevent re-entering this block of code to prevent calls to ComponentFactoryRegister() from
		// causing a recursive loop.
		singleton.initialized = true;

		std::vector<std::filesystem::path> ageLibraries;

		const auto agecore = Configuration::Instance().getPathBin();
		if(std::filesystem::exists(agecore) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(agecore))
			{
				if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
				{
					const auto filepath = it.path();
					ageLibraries.push_back(it.path());
				}
			}
		}

		for(const auto& filepath : ageLibraries)
		{
			const auto filename = filepath.filename().string();
			const std::string agePlugin = "Age";
			if(filename.compare(0, agePlugin.size(), agePlugin) == 0)
			{
				boost::system::error_code ec;
				boost::dll::shared_library library(filepath.string(), ec);

				if(!ec)
				{
					if(library.has("ComponentFactoryRegister") == true)
					{
						const auto ComponentFactoryRegister = library.get<void()>("ComponentFactoryRegister");

						if(ComponentFactoryRegister != nullptr)
						{
							ComponentFactoryRegister();
						}

						// Keep track of loaded libraries in order to keep them loaded in memory.
						singleton.loadedLibraries.push_back(library);
					}
				}
				else
				{
					std::cerr << "Failed to load: " << filepath << " error code: " << ec.message() << "\n";
				}
			}
		}
	}

	return singleton;
}

Component* ComponentFactory::create(Entity x, std::string component) const
{
	const auto foundIt = this->FactoryMap.find(component);

	if(foundIt != std::end(this->FactoryMap))
	{
		const auto ptr = foundIt->second.get();
		return ptr->create(x);
	}

	return nullptr;
}

std::string ComponentFactory::alias(const std::type_index& x)
{
	return this->typeAlias[x];
}
