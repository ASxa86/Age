#include <celero/Celero.h>

#include <age/entity/EntityManager.h>
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
	constexpr size_t IterationCount{10'000};

	struct Pos
	{
		double x{};
		double y{};
	};

	struct Vel
	{
		double x{1.0};
		double y{2.0};
	};

	struct EntityArrayF : public celero::TestFixture
	{
		EntityArrayF()
		{
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(const celero::TestFixture::ExperimentValue&) override
		{
			pos.clear();
			vel.clear();
			pos.reserve(IterationCount);
			vel.reserve(IterationCount);

			for(auto i = 0; i < IterationCount; ++i)
			{
				this->vel.push_back({});
				this->pos.push_back({});
			}
		}

		std::vector<Pos> pos;
		std::vector<Vel> vel;
	};

	struct AgeEntityF : public celero::TestFixture
	{
		AgeEntityF()
		{
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(const celero::TestFixture::ExperimentValue&) override
		{
			// Clear the previous entities
			this->em = std::make_unique<age::entity::EntityManager>();

			for(auto i = 0; i < IterationCount; ++i)
			{
				celero::DoNotOptimizeAway(this->em->create());
			}
		}

		std::unique_ptr<age::entity::EntityManager> em;
	};

	struct EntityXF : public celero::TestFixture
	{
		EntityXF()
		{
		}

		virtual void setUp(const celero::TestFixture::ExperimentValue&) override
		{
			// Clear the previous entities
			this->em = std::make_unique<entityx::EntityManager>(this->evtManager);

			for(auto i = 0; i < IterationCount; ++i)
			{
				celero::DoNotOptimizeAway(this->em->create());
			}
		}

		entityx::EventManager evtManager;
		std::unique_ptr<entityx::EntityManager> em;
	};

	struct ObjectF : public celero::TestFixture
	{
		struct PosF : public age::benchmark::Object, public Pos
		{
		};

		struct VelF : public age::benchmark::Object, public Vel
		{
		};

		ObjectF()
		{
		}

		virtual void setUp(const celero::TestFixture::ExperimentValue&) override
		{
			// Clear the previous entities
			this->em = std::make_unique<age::benchmark::Object>();

			for(auto i = 0; i < IterationCount; ++i)
			{
				this->em->addChild(std::make_unique<age::benchmark::Object>());
			}
		}

		std::unique_ptr<age::benchmark::Object> em;
	};
}

BASELINE_F(Destroy, Baseline, EntityArrayF, 10, 100)
{
	for(auto i = 0; i < IterationCount; ++i)
	{
		this->vel.pop_back();
		this->pos.pop_back();
	}
}

BENCHMARK_F(Destroy, AgeEntity, AgeEntityF, 10, 100)
{
	const auto& entities = this->em->getEntities();

	for(auto& e : entities)
	{
		e.destroy();
	}
}

BENCHMARK_F(Destroy, EntityX, EntityXF, 10, 100)
{
	for(auto i = 0; i < IterationCount; ++i)
	{
		this->em->destroy(entityx::Entity::Id(i));
	}
}

BENCHMARK_F(Destroy, Object, ObjectF, 10, 100)
{
	const auto entities = this->em->getChildren();

	for(const auto& entity : entities)
	{
		this->em->removeChild(entity);
	}
}
