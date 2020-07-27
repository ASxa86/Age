#pragma once

// https://stackoverflow.com/questions/19666142/why-is-a-level-of-indirection-needed-for-this-concatenation-macro
#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define STATIC_INVOKE                                                   \
	static void StaticInvoke();                                         \
	namespace                                                           \
	{                                                                   \
		struct StaticInvokeClass                                        \
		{                                                               \
			StaticInvokeClass()                                         \
			{                                                           \
				StaticInvoke();                                         \
			}                                                           \
		};                                                              \
	}                                                                   \
	static const StaticInvokeClass CONCAT(StaticRegister, __COUNTER__); \
	static void StaticInvoke()
