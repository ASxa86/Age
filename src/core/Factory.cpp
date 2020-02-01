#include <age/core/Configuration.h>
#include <age/core/Factory.h>
#include <age/core/Object.h>
#include <atomic>
#include <boost/dll/import.hpp>
#include <iostream>
#include <map>

using namespace age::core;

CreatorBase::~CreatorBase()
{
}

std::unique_ptr<Object> CreatorBase::create() const
{
	return nullptr;
}

Factory::Type::Type(const std::type_index& type) : TypeIndex{type}
{
}

Factory::Type& Factory::Type::addAlias(std::string_view x)
{
	this->Aliases.insert(std::string(x));
	return *this;
}

bool Factory::Type::valid() const
{
	return this->TypeIndex != typeid(*this);
}

bool Factory::Type::operator==(std::string_view x) const
{
	return this->Name == x || this->NameClean == x || std::find_if(std::begin(this->Aliases), std::end(this->Aliases), [x](const std::string& name) {
														  return name == x;
													  }) != std::end(this->Aliases);
}

bool Factory::Type::operator!=(std::string_view x) const
{
	return !(*this == x);
}

bool Factory::Type::operator==(const Type& x) const
{
	return this->TypeIndex == x.TypeIndex;
}

bool Factory::Type::operator!=(const Type& x) const
{
	return !(*this == x);
}

Factory::Factory()
{
}

Factory::~Factory()
{
}

Factory& Factory::Instance()
{
	static Factory singleton;

	if(singleton.initialized == false)
	{
		// Prevent re-entering this block of code to prevent calls to factoryRegister() from
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

		const auto plugins = Configuration::Instance().getPathPlugins();

		if(std::filesystem::exists(plugins) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(plugins))
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
			const std::string agePlugin = "age";
			if(filename.compare(0, agePlugin.size(), agePlugin) == 0)
			{
				boost::system::error_code ec;
				boost::dll::shared_library library(filepath.string(), ec);

				if(!ec)
				{
					if(library.has("FactoryRegister") == true)
					{
						const auto factoryRegister = library.get<void()>("FactoryRegister");

						if(factoryRegister != nullptr)
						{
							factoryRegister();
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

Factory::Type Factory::getType(std::string_view x)
{
	const auto foundIt = std::find_if(std::begin(this->types), std::end(this->types), [x](Factory::Type& type) { return type == x; });

	if(foundIt != std::end(this->types))
	{
		return *foundIt;
	}

	return Factory::Type();
}

Factory::Type Factory::getType(std::type_index x)
{
	const auto foundIt = std::find_if(std::begin(this->types), std::end(this->types), [x](Factory::Type& type) { return type.TypeIndex == x; });

	if(foundIt != std::end(this->types))
	{
		return *foundIt;
	}

	return Factory::Type();
}

std::vector<Factory::Type> Factory::getTypes() const
{
	return this->types;
}

std::vector<Factory::Type> Factory::getTypesFromBase(std::type_index x)
{
	std::vector<Factory::Type> v;

	for(const auto& type : this->types)
	{
		const auto foundIt =
			std::find_if(std::begin(type.BaseTypes), std::end(type.BaseTypes), [x](const std::type_index& type) { return type == x; });

		if(foundIt != std::end(type.BaseTypes))
		{
			v.push_back(type);
		}
	}

	return v;
}

std::unique_ptr<Object> Factory::create(std::string_view x)
{
	auto type = this->getType(x);

	if(type.valid() == true)
	{
		return type.Creator->create();
	}

	return {};
}

std::unique_ptr<Object> Factory::create(std::type_index x)
{
	auto type = this->getType(x);

	if(type.valid() == true)
	{
		return type.Creator->create();
	}

	return {};
}
