#include <age/entity/Component.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <celero/Celero.h>
#include "Object.h"

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <entt/entt.hpp>
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
	const std::vector<celero::TestFixture::ExperimentValue> ProblemSpace{
		{{100, 100'000}, {1'000, 10'000}, {10'000, 1'000}, {100'000, 100}}};
	constexpr double Time{0.01};

	struct Pos : public age::entity::Component
	{
		Pos()
		{
		}

		Pos(const Pos&)
		{
		}

		Pos(Pos&&)
		{
		}

		Pos& operator=(const Pos&)
		{
			return *this;
		}

		Pos& operator=(Pos&&)
		{
			return *this;
		}

		double x{};
		double y{};
	};

	struct Vel : public age::entity::Component
	{
		Vel()
		{
		}

		Vel(const Vel&)
		{
		}

		Vel(Vel&&)
		{
		}

		Vel& operator=(const Vel&)
		{
			return *this;
		}

		Vel& operator=(Vel&&)
		{
			return *this;
		}

		double x{1.0};
		double y{2.0};
	};

	struct EntityArrayF : public celero::TestFixture
	{
		EntityArrayF()
		{
		}

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			pos.clear();
			vel.clear();
			pos.reserve(x.Value);
			vel.reserve(x.Value);

			for(auto i = 0; i < x.Value; i++)
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

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			// Clear the previous entities
			em = std::make_unique<age::entity::EntityDatabase>();

			for(auto i = 0; i < x.Value; ++i)
			{
				auto e = em->addEntity();
				e->addComponent<Pos>();
				e->addComponent<Vel>();
			}
		}

		std::unique_ptr<age::entity::EntityDatabase> em;
	};

	struct EnTTF : public celero::TestFixture
	{
		EnTTF()
		{
		}

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		/// Before each run, build a vector of random integers.
		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			// Clear the previous entities
			em = std::make_unique<entt::registry>();

			for(auto i = 0; i < x.Value; ++i)
			{
				auto e = em->create();
				em->assign<Pos>(e);
				em->assign<Vel>(e);
			}
		}

		std::unique_ptr<entt::registry> em;
	};

	struct EntityXF : public celero::TestFixture
	{
		EntityXF()
		{
		}

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			// Clear the previous entities
			em = std::make_unique<entityx::EntityManager>(this->evtManager);

			for(auto i = 0; i < x.Value; ++i)
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

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			// Clear the previous entities
			em = std::make_unique<age::benchmark::Object>();

			for(auto i = 0; i < x.Value; ++i)
			{
				auto e = std::make_unique<age::benchmark::Object>();
				e->addChild(std::make_unique<PosF>());
				e->addChild(std::make_unique<VelF>());
				em->addChild(std::move(e));
			}
		}

		std::unique_ptr<age::benchmark::Object> em;
	};

	struct ObjectF2 : public celero::TestFixture
	{
		struct PosF : public age::benchmark::Object, public Pos
		{
			virtual void update(double z) override
			{
				this->x += 1.0 * z;
				this->y += 1.0 * z;
			}
		};

		struct VelF : public age::benchmark::Object, public Vel
		{
			virtual void update(double z) override
			{
				this->x += 1.0 * z;
				this->y += 1.0 * z;
			}
		};

		ObjectF2()
		{
		}

		virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const
		{
			return ProblemSpace;
		}

		virtual void setUp(const celero::TestFixture::ExperimentValue& x) override
		{
			// Clear the previous entities
			em = std::make_unique<age::benchmark::Object>();

			for(auto i = 0; i < x.Value; ++i)
			{
				auto e = std::make_unique<age::benchmark::Object>();
				e->addChild(std::make_unique<ObjectF::PosF>());
				e->addChild(std::make_unique<ObjectF::VelF>());
				em->addChild(std::move(e));
			}
		}

		std::unique_ptr<age::benchmark::Object> em;
	};
}

BASELINE_F(Iteration, Baseline, EntityArrayF, 30, 1)
{
	for(auto i = 0; i < this->pos.size(); ++i)
	{
		auto& p = this->pos[i];
		auto& v = this->vel[i];

		p.x += v.x * Time;
		p.y += v.y * Time;
	}
}

 BENCHMARK_F(Iteration, AgeEntity, AgeEntityF, 30, 1)
 {
 	for(auto e : this->em->getChildren<age::entity::Entity>())
 	{
 		auto p = e->getChild<Pos>();
 		auto v = e->getChild<Vel>();
 
 		if(p != nullptr && e != nullptr)
 		{
 			p->x += v->x * Time;
 			p->y += v->y * Time;
 		}
 	}
 }

BENCHMARK_F(Iteration, EnTT, EnTTF, 30, 1)
{
	this->em->view<Pos, Vel>().each([this](auto, Pos& p, Vel& v) {
		p.x += v.x * Time;
		p.y += v.y * Time;
	});
}

BENCHMARK_F(Iteration, EntityX, EntityXF, 30, 1)
{
	this->em->each<Pos, Vel>([this](entityx::Entity, Pos& p, Vel& v) {
		p.x += v.x * Time;
		p.y += v.y * Time;
	});
}

BENCHMARK_F(Iteration, Object, ObjectF, 30, 1)
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

BENCHMARK_F(Iteration, Object2, ObjectF2, 30, 1)
{
	const auto& entities = this->em->getChildren();

	for(const auto& entity : entities)
	{
		const auto p = entity->getChild2<ObjectF::PosF>();
		const auto v = entity->getChild2<ObjectF::VelF>();

		p->x += v->x * Time;
		p->y += v->y * Time;
	}
}
