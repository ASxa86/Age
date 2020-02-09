#include <age/core/Configuration.h>

#include <age/utilities/PimplImpl.h>
#include <mutex>

#ifdef WIN32
#include <Windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

using namespace age::core;

const std::string Configuration::PathDataAlias = "$AGE_DATA";
const std::string Configuration::PathMapsAlias = "$AGE_MAPS";
const std::string Configuration::PathBinAlias = "$AGE_BIN";
const std::string Configuration::PathRootAlias = "$AGE_ROOT";

struct Configuration::Impl
{
	std::filesystem::path pathRoot;
	std::filesystem::path pathData;
	std::filesystem::path pathMaps;
	std::filesystem::path pathBin;
	std::filesystem::path pathPlugins;
	std::once_flag onceFlag;
	unsigned int pixelsPerMeter{32};
};

const Configuration& age::core::Configuration::Instance()
{
	static Configuration singleton;

	std::call_once(singleton.pimpl->onceFlag, [] {
		std::string filename;

#ifdef WIN32
		filename.resize(MAX_PATH);
		GetModuleFileNameA(nullptr, filename.data(), static_cast<DWORD>(filename.size()));
#else
		filename.resize(PATH_MAX);
		const auto result = readlink("/proc/self/exe", filename.data(), filename.size());
		(void)result;
#endif

		auto currentPath = std::filesystem::path(filename).parent_path();
		singleton.pimpl->pathBin = currentPath;
		singleton.pimpl->pathPlugins = currentPath / "plugins";

		while(std::filesystem::exists(currentPath / "data") == false && currentPath.has_parent_path() == true)
		{
			currentPath = currentPath.parent_path();
		}

		singleton.pimpl->pathData = currentPath / "data";
		singleton.pimpl->pathMaps = currentPath / "data" / "maps";
		singleton.pimpl->pathRoot = singleton.pimpl->pathData.parent_path();
	});

	return singleton;
}

Configuration::Configuration() : pimpl{}
{
}

Configuration::~Configuration()
{
}

std::filesystem::path Configuration::getPathRoot() const
{
	return this->pimpl->pathRoot;
}

std::filesystem::path Configuration::getPathData() const
{
	return this->pimpl->pathData;
}

std::filesystem::path Configuration::getPathMaps() const
{
	return this->pimpl->pathMaps;
}

std::filesystem::path Configuration::getPathBin() const
{
	return this->pimpl->pathBin;
}

std::filesystem::path Configuration::getPathPlugins() const
{
	return this->pimpl->pathPlugins;
}

std::filesystem::path Configuration::getPath(std::string_view x) const
{
	if(x == Configuration::PathDataAlias)
	{
		return this->pimpl->pathData;
	}
	else if(x == Configuration::PathMapsAlias)
	{
		return this->pimpl->pathMaps;
	}
	else if(x == Configuration::PathBinAlias)
	{
		return this->pimpl->pathBin;
	}
	else if(x == Configuration::PathRootAlias)
	{
		return this->pimpl->pathRoot;
	}

	return {};
}

void Configuration::setPixelsPerMeter(unsigned int x)
{
	this->pimpl->pixelsPerMeter = x;
}

unsigned int Configuration::getPixelsPerMeter() const
{
	return this->pimpl->pixelsPerMeter;
}
