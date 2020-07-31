#include <azule/utilities/SharedLibrary.h>

#ifdef WIN32
#include <Windows.h>
#endif

using namespace azule;

SharedLibrary::~SharedLibrary()
{
	this->unload();
}

SharedLibrary::SharedLibrary(const std::filesystem::path& x)
{
	this->load(x);
}

SharedLibrary::SharedLibrary(const SharedLibrary& x)
{
	this->load(x.location());
}

SharedLibrary& SharedLibrary::operator=(const SharedLibrary& x)
{
	this->load(x.location());
	return *this;
}

bool SharedLibrary::load(const std::filesystem::path& x)
{
	if(this->loaded() == true && this->loc != x)
	{
		this->unload();
	}

#ifdef WIN32
	this->handle = LoadLibraryA(x.string().c_str());
#else
	// Not yet implemented for linux.
#endif

	if(this->loaded() == true)
	{
		this->loc = x;
	}

	return this->loaded();
}

void SharedLibrary::unload()
{
	if(this->handle != nullptr)
	{
#ifdef WIN32
		FreeLibrary((HMODULE)this->handle);
#else
		// Not yet implemented for linux.
#endif
		this->handle = nullptr;
		this->loc.clear();
	}
}

bool SharedLibrary::loaded() const
{
	return this->handle != nullptr;
}

std::function<void()> SharedLibrary::symbol(const std::string& x) const
{
	if(this->loaded() == true)
	{
#ifdef WIN32
		return GetProcAddress((HMODULE)this->handle, x.c_str());
#else
		// Not yet implemented for linux.
#endif
	}

	return nullptr;
}

std::filesystem::path SharedLibrary::location() const
{
	return this->loc;
}
