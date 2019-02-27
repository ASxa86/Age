#include <age/physics/PhysicsRenderSystem.h>

#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/EdgeCollisionComponent.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::physics;

struct PhysicsRenderSystem::Impl
{
	sf::RenderStates state;
};

PhysicsRenderSystem::PhysicsRenderSystem()
{
	const auto factor = static_cast<float>(Configuration::Instance().getPixelsPerMeter());
	this->pimpl->state.transform.scale(factor, factor);
}

PhysicsRenderSystem::~PhysicsRenderSystem()
{
}

void PhysicsRenderSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityManager();

	manager->each([&target, this](Entity& e) {
		if(e.hasComponent<BoxCollisionComponent>() == true)
		{
			auto& box = e.getComponent<BoxCollisionComponent>();

			sf::RectangleShape rect;
			rect.setSize({static_cast<float>(box.Width), static_cast<float>(box.Height)});
			rect.setOutlineColor(sf::Color::Green);
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(0.1f);
			rect.setOrigin({rect.getSize().x / 2.0f, rect.getSize().y / 2.0f});

			if(e.hasComponent<TransformComponent>() == true)
			{
				const auto& t = e.getComponent<TransformComponent>();
				rect.setPosition({static_cast<float>(t.Position.X), static_cast<float>(t.Position.Y)});
			}

			target.draw(rect, this->pimpl->state);
		}

		if(e.hasComponent<CircleCollisionComponent>() == true)
		{
			auto& c = e.getComponent<CircleCollisionComponent>();

			sf::CircleShape circle;
			circle.setRadius(static_cast<float>(c.Radius));
			circle.setOutlineColor(sf::Color::Green);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineThickness(0.1f);
			circle.setOrigin(circle.getRadius(), circle.getRadius());

			if(e.hasComponent<TransformComponent>() == true)
			{
				const auto& t = e.getComponent<TransformComponent>();
				circle.setPosition({static_cast<float>(t.Position.X), static_cast<float>(t.Position.Y)});
			}

			target.draw(circle, this->pimpl->state);
		}

		if(e.hasComponent<EdgeCollisionComponent>() == true)
		{
			auto& edge = e.getComponent<EdgeCollisionComponent>();

			sf::VertexArray array;
			array.setPrimitiveType(sf::PrimitiveType::Lines);

			array.append(sf::Vertex({static_cast<float>(edge.Vertex1.X), static_cast<float>(edge.Vertex1.Y)}, sf::Color::Green));
			array.append(sf::Vertex({static_cast<float>(edge.Vertex2.X), static_cast<float>(edge.Vertex2.Y)}, sf::Color::Green));
			target.draw(array, this->pimpl->state);
		}
	});
}
