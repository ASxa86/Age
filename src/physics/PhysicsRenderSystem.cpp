#include <azule/core/Configuration.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/physics/BoxCollisionComponent.h>
#include <azule/physics/CircleCollisionComponent.h>
#include <azule/physics/EdgeCollisionComponent.h>
#include <azule/physics/PhysicsRenderSystem.h>
#include <SFML/Graphics.hpp>

using namespace azule;
using namespace azule;
using namespace azule;

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
	const auto manager = this->getEntityDatabase();

	for(auto e : manager->getChildren<Entity>())
	{
		if(e->getChild<BoxCollisionComponent>() != nullptr)
		{
			auto box = e->getChild<BoxCollisionComponent>();

			sf::RectangleShape rect;
			rect.setSize({static_cast<float>(box->Width), static_cast<float>(box->Height)});
			rect.setOutlineColor(sf::Color::Green);
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(0.1f);
			rect.setOrigin({rect.getSize().x / 2.0f, rect.getSize().y / 2.0f});

			if(e->getChild<TransformComponent>() != nullptr)
			{
				const auto& t = e->getChild<TransformComponent>();
				rect.setPosition({static_cast<float>(t->Position.x), static_cast<float>(t->Position.y)});
			}

			target.draw(rect, this->pimpl->state);
		}

		if(e->getChild<CircleCollisionComponent>() != nullptr)
		{
			auto c = e->getChild<CircleCollisionComponent>();

			sf::CircleShape circle;
			circle.setRadius(static_cast<float>(c->Radius));
			circle.setOutlineColor(sf::Color::Blue);
			auto blue = sf::Color::Blue;
			blue.a = 100;
			circle.setFillColor(blue);
			circle.setOutlineThickness(1.0f);
			circle.setOrigin(circle.getRadius(), circle.getRadius());

			if(e->getChild<TransformComponent>() != nullptr)
			{
				const auto& t = e->getChild<TransformComponent>();
				circle.setPosition({static_cast<float>(t->Position.x), static_cast<float>(t->Position.y)});
			}

			//target.draw(circle, this->pimpl->state);
			target.draw(circle);
		}

		if(e->getChild<EdgeCollisionComponent>() != nullptr)
		{
			auto edge = e->getChild<EdgeCollisionComponent>();

			sf::VertexArray array;
			array.setPrimitiveType(sf::PrimitiveType::Lines);

			array.append(sf::Vertex({static_cast<float>(edge->Vertex1.x), static_cast<float>(edge->Vertex1.y)}, sf::Color::Green));
			array.append(sf::Vertex({static_cast<float>(edge->Vertex2.x), static_cast<float>(edge->Vertex2.y)}, sf::Color::Green));
			target.draw(array, this->pimpl->state);
		}
	}
}
