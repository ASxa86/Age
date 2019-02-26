#include <age/physics/PhysicsRenderSystem.h>

#include <Box2D/Box2D.h>
#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/physics/BoxCollisionComponent.h>
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

			if(e.hasComponent<TransformComponent>() == true)
			{
				const auto& t = e.getComponent<TransformComponent>();
				const auto pos = t.getPosition();
				rect.setPosition({static_cast<float>(pos.getX()), static_cast<float>(pos.getY())});
			}

			target.draw(rect);
		}

		// case b2Shape::Type::e_circle:
		//{
		//	sf::CircleShape circle;
		//	circle.setRadius(f->GetShape()->m_radius);
		//	circle.setOutlineColor(sf::Color::Green);
		//	circle.setFillColor(sf::Color::Transparent);
		//	circle.setOutlineThickness(0.1f);
		//	circle.setPosition(b.Body->GetPosition().x, b.Body->GetPosition().y);
		//	circle.setOrigin(circle.getRadius(), circle.getRadius());
		//	target.draw(circle, this->pimpl->state);
		//	break;
		//}
		// case b2Shape::Type::e_edge:
		//{
		//	sf::VertexArray array;
		//	array.setPrimitiveType(sf::PrimitiveType::Lines);

		//	const auto pos = b.Body->GetPosition();
		//	const auto b2Edge = static_cast<b2EdgeShape*>(f->GetShape());
		//	array.append(sf::Vertex({b2Edge->m_vertex1.x, b2Edge->m_vertex1.y}, sf::Color::Green));
		//	array.append(sf::Vertex({b2Edge->m_vertex2.x, b2Edge->m_vertex2.y}, sf::Color::Green));
		//	target.draw(array, this->pimpl->state);
		//	break;
		//}

		// case b2Shape::Type::e_polygon:
		//{
		//	sf::VertexArray array;
		//	array.setPrimitiveType(sf::PrimitiveType::LineStrip);

		//	const auto pos = b.Body->GetPosition();
		//	const auto b2Rect = static_cast<b2PolygonShape*>(f->GetShape());
		//	for(auto i = 0; i < b2Rect->m_count; ++i)
		//	{
		//		const auto& vert = b2Rect->m_vertices[i];
		//		array.append(sf::Vertex({vert.x + pos.x, vert.y + pos.y}, sf::Color::Green));
		//	}

		//	array.append(array[0]);
		//	target.draw(array, this->pimpl->state);
		//	break;
	});
}
