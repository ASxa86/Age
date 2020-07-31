#include  <azule/qt/WidgetPropertyFactory.h>

#include <azule/core/Configuration.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/SharedLibrary.h>
#include <QtWidgets/QWidget>
#include <atomic>
#include <iostream>
#include <map>

using namespace azule::core::qt;
using namespace azule::utilities;

CreatorBase::~CreatorBase()
{
}

WidgetProperty* CreatorBase::create(QWidget*) const
{
	return nullptr;
}

struct WidgetPropertyFactory::Impl
{
	std::map<std::type_index, std::unique_ptr<CreatorBase>> factoryMap;
	std::vector<SharedLibrary> loadedLibraries;
	std::atomic<bool> initialized{false};
};

WidgetPropertyFactory::WidgetPropertyFactory() /* : pimpl{}*/
{
}

WidgetPropertyFactory::~WidgetPropertyFactory()
{
}

WidgetPropertyFactory& WidgetPropertyFactory::Instance()
{
	static WidgetPropertyFactory singleton;

	if(singleton.pimpl->initialized == false)
	{
		// Prevent re-entering this block of code to prevent calls to factoryRegister() from
		// causing a recursive loop.
		singleton.pimpl->initialized = true;

		const auto plugins = Configuration::Instance().getPathBin();

		if(std::filesystem::exists(plugins) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(plugins))
			{
				if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
				{
					const auto filepath = it.path();
					const auto filename = filepath.filename().string();
					if(filename.find("qt") != std::string::npos)
					{
						SharedLibrary library(filepath);

						if(library.loaded() == true)
						{
							const auto factoryRegister = library.symbol("FactoryRegisterQt");

							if(factoryRegister != nullptr)
							{
								factoryRegister();
							}

							// Keep track of loaded libraries in order to keep them loaded in memory.
							singleton.pimpl->loadedLibraries.push_back(library);
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

	return singleton;
}

WidgetProperty* WidgetPropertyFactory::create(const std::type_index& x, QWidget* parent) const
{
	// const auto foundIt = this->pimpl->factoryMap.find(x);

	// if(foundIt != std::end(this->pimpl->factoryMap))
	//{
	//	const auto ptr = foundIt->second.get();
	//	return ptr->create(parent);
	//}

	return nullptr;
}

void WidgetPropertyFactory::registerType(const std::type_index& x, std::unique_ptr<CreatorBase> creator)
{
	// this->pimpl->factoryMap[x] = std::move(creator);
}
