#include <age/core/Factory.h>

#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <atomic>
#include <boost/dll/import.hpp>
#include <map>

using namespace age::core;

CreatorBase::~CreatorBase()
{
}

std::shared_ptr<Object> CreatorBase::create() const
{
	return nullptr;
}

struct Factory::Impl
{
	std::map<std::string, std::shared_ptr<CreatorBase>> factoryMap;
	std::vector<boost::dll::shared_library> loadedLibraries;
	std::atomic<bool> initialized{false};
};

Factory::Factory() : pimpl{}
{
}

Factory::~Factory()
{
}

Factory& Factory::Instance()
{
	static Factory singleton;

	if(singleton.pimpl->initialized == false)
	{
		// Prevent re-entering this block of code to prevent calls to factoryRegister() from
		// causing a recursive loop.
		singleton.pimpl->initialized = true;

		const auto plugins = Configuration::Instance().getPathPlugins();

		if(std::filesystem::exists(plugins) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(plugins))
			{
				const auto ext = it.path().extension();
				if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
				{
					boost::dll::shared_library library(it.path().string());
					const auto factoryRegister = library.get<void()>("FactoryRegister");

					if(factoryRegister != nullptr)
					{
						factoryRegister();
					}

					// Keep track of loaded libraries in order to keep them loaded in memory.
					singleton.pimpl->loadedLibraries.push_back(library);
				}
			}
		}
	}

	return singleton;
}

std::shared_ptr<Object> Factory::create(const std::string& x) const
{
	const auto foundIt = this->pimpl->factoryMap.find(x);

	if(foundIt != std::end(this->pimpl->factoryMap))
	{
		const auto ptr = foundIt->second;
		return ptr->create();
	}

	return nullptr;
}

void Factory::registerType(const std::string& id, std::shared_ptr<CreatorBase> creator)
{
	this->pimpl->factoryMap[id] = creator;
}
