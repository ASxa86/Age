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
	const std::vector<std::pair<int64_t, uint64_t>> ProblemSpace{
		{{10, 1'000'000}, {100, 100'000}, {1'000, 10'000}, {10'000, 1'000}, {100'000, 100}, {1'000'000, 10}}};
	constexpr double Time{0.01};

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

		virtual std::vector<std::pair<int64_t, uint64_t>> getExperimentValues() const override
		{
			return ProblemSpace;
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(int64_t experimentValue) override
		{
			pos.clear();
			vel.clear();
			pos.reserve(experimentValue);
			vel.reserve(experimentValue);

			for(auto i = 0; i < experimentValue; i++)
			{
				pos.push_back({});
				vel.push_back({});
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

		virtual std::vector<std::pair<int64_t, uint64_t>> getExperimentValues() const override
		{
			return ProblemSpace;
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(int64_t experimentValue) override
		{
			// Clear the previous entities
			em = std::make_unique<age::entity::EntityManager>(experimentValue);

			for(auto i = 0; i < experimentValue; ++i)
			{
				auto e = em->create();
				e.addComponent<Pos>();
				e.addComponent<Vel>();
			}
		}

		std::unique_ptr<age::entity::EntityManager> em;
	};

	struct EntityXF : public celero::TestFixture
	{
		EntityXF()
		{
		}

		virtual std::vector<std::pair<int64_t, uint64_t>> getExperimentValues() const override
		{
			return ProblemSpace;
		}

		virtual void setUp(int64_t experimentValue) override
		{
			// Clear the previous entities
			em = std::make_unique<entityx::EntityManager>(this->evtManager);

			for(auto i = 0; i < experimentValue; ++i)
			{
				auto e = em->create();
				e.assign<Pos>();
				e.assign<Vel>();
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

		virtual std::vector<std::pair<int64_t, uint64_t>> getExperimentValues() const override
		{
			return ProblemSpace;
		}

		virtual void setUp(int64_t experimentValue) override
		{
			// Clear the previous entities
			em = std::make_unique<age::benchmark::Object>();

			for(auto i = 0; i < experimentValue; ++i)
			{
				auto e = std::make_unique<age::benchmark::Object>();
				e->addChild(std::make_unique<PosF>());
				e->addChild(std::make_unique<VelF>());
				em->addChild(std::move(e));
			}
		}

		std::unique_ptr<age::benchmark::Object> em;
	};
}

BASELINE_F(Iteration, Baseline, EntityArrayF, 10, 1)
{
	for(auto i = 0; i < this->pos.size(); ++i)
	{
		auto& p = this->pos[i];
		auto& v = this->vel[i];

		p.x += v.x * Time;
		p.y += v.y * Time;
	}
}

BENCHMARK_F(Iteration, AgeEntity, AgeEntityF, 10, 1)
{
	this->em->each<Pos, Vel>([this](age::entity::Entity, Pos& p, Vel& v) {
		p.x += v.x * Time;
		p.y += v.y * Time;
	});
}

BENCHMARK_F(Iteration, EntityX, EntityXF, 10, 1)
{
	this->em->each<Pos, Vel>([this](entityx::Entity, Pos& p, Vel& v) {
		p.x += v.x * Time;
		p.y += v.y * Time;
	});
}

BENCHMARK_F(Iteration, Object, ObjectF, 10, 1)
{
	const auto& entities = this->em->getChildren();

	for(const auto& entity : entities)
	{
		const auto p = entity->getChild<ObjectF::PosF>();
		const auto v = entity->getChild<ObjectF::VelF>();

		p->x += v->x * Time;
		p->y += v->y * Time;
	}
}
