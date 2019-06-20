#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <celero/Celero.h>
#include "Object.h"

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <entityx/entityx.h>

#ifdef WIN32
#pragma warning(pop)
#endif

// The first thing we do in this code is to define a BASELINE test case.This template takes four arguments :
//
// BASELINE(GroupName, BaselineName, Samples, Operations)
// GroupName - The name of the benchmark group.This is used to batch together runs and results with their corresponding baseline measurement.
// BaselineName - The name of this baseline for reporting purposes.
// Samples - The total number of times you want to execute the given number of operations on the test code.
// Operations - The total number of times you want to execute the test code per sample.

namespace
{
	constexpr int Samples{100};
	constexpr int Iterations{1000000};

	struct IntF : public celero::TestFixture
	{
		int value{0};
		int copy{0};
		int& ref{value};
	};

	// struct AgeEntityF : public celero::TestFixture
	//{
	//	age::entity::EntityDatabase em;
	//	age::entity::Entity value{*em.addEntity()};
	//	age::entity::Entity copy{value};
	//	age::entity::Entity& ref{value};
	//};

	struct EntityXF : public celero::TestFixture
	{
		entityx::EventManager evtManager;
		entityx::EntityManager em{evtManager};
		entityx::Entity value{em.create()};
		entityx::Entity copy{em.create()};
		entityx::Entity ref{value};
	};

	struct ObjectF : public celero::TestFixture
	{
		std::shared_ptr<age::benchmark::Object> value{std::make_shared<age::benchmark::Object>()};
		std::shared_ptr<age::benchmark::Object> copy{std::make_shared<age::benchmark::Object>()};
		std::shared_ptr<age::benchmark::Object>& ref{value};
	};
}

BASELINE_F(Copy, Baseline, IntF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->copy = this->value);
}

BENCHMARK_F(Copy, BaselineR, IntF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->ref = this->value);
}

// BENCHMARK_F(Copy, AgeEntity, AgeEntityF, Samples, Iterations)
//{
//	celero::DoNotOptimizeAway(this->copy = this->value);
//}
//
// BENCHMARK_F(Copy, AgeEntityR, AgeEntityF, Samples, Iterations)
//{
//	celero::DoNotOptimizeAway(this->ref = this->value);
//}

BENCHMARK_F(Copy, EntityX, EntityXF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->copy = this->value);
}

BENCHMARK_F(Copy, EntityXR, EntityXF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->ref = this->value);
}

BENCHMARK_F(Copy, Object, ObjectF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->copy = this->value);
}

BENCHMARK_F(Copy, ObjectR, ObjectF, Samples, Iterations)
{
	celero::DoNotOptimizeAway(this->ref = this->value);
}
