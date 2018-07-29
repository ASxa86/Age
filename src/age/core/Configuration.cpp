#include <age/core/Configuration.h>

#include <age/core/PimplImpl.h>
#include <mutex>

#ifdef WIN32
#include <Windows.h>
#else
#include <limits.h>
#include <unitstd.h>
#endif

using namespace age::core;

struct Configuration::Impl
{
	std::filesystem::path dataPath;
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
		readlink("/proc/self/exe", filename.data(), filename.size());
#endif

		auto currentPath = std::filesystem::path(filename).parent_path();

		while(std::filesystem::exists(currentPath / "data") == false && currentPath.has_parent_path() == true)
		{
			currentPath = currentPath.parent_path();
		}

		singleton.pimpl->dataPath = currentPath / "data";
	});

	return singleton;
}

Configuration::Configuration() : pimpl{}
{
}

std::filesystem::path Configuration::getDataPath() const
{
	return this->pimpl->dataPath;
}

void Configuration::setPixelsPerMeter(unsigned int x)
{
	this->pimpl->pixelsPerMeter = x;
}

unsigned int Configuration::getPixelsPerMeter() const
{
	return this->pimpl->pixelsPerMeter;
}
