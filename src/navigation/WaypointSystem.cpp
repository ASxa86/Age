#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/navigation/WaypointComponent.h>
#include <azule/navigation/WaypointSystem.h>
#include <azule/physics/KinematicComponent.h>

using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule;

WaypointSystem::WaypointSystem() : System()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

WaypointSystem::~WaypointSystem()
{
}

void WaypointSystem::frame(std::chrono::microseconds)
{
	const auto manager = this->getEntityDatabase();

	if(manager != nullptr)
	{
		for(auto entity : manager->getChildren<Entity>())
		{
			auto w = entity->getChild<WaypointComponent>();
			auto t = entity->getChild<TransformComponent>();
			auto k = entity->getChild<KinematicComponent>();

			if(w != nullptr && t != nullptr && k != nullptr)
			{
				auto waypoints = w->getChildren<Waypoint>();

				if(waypoints.empty() == false && w->CurrentWaypoint >= 0 && w->CurrentWaypoint < waypoints.size())
				{
					auto& currentWaypoint = waypoints[w->CurrentWaypoint];
					const auto currentPosition = t->Position;

					if(currentWaypoint->Active == true)
					{
						// We've reached the waypoint when the line created by
						// the player's starting position and current position
						// intersects the waypoint's position.

						// Set a 1 unit tolerance to determine when to switch to next waypoint.
						// I suspect a more refined test will be needed here for higher velocities
						// but this tolerance check currently seems to work->
						constexpr auto tolerance = 1.0;

						if(glm::length(currentPosition - currentWaypoint->Position) < tolerance)
						{
							// Deactivate the current waypoint only if we can progress to the next waypoint.
							// This will prevent calculating a new velocity if we've reached the last waypoint.
							// If we are not looping and the last waypoint has been reached, then that is the active waypoint.
							if(w->CurrentWaypoint + 1 < waypoints.size())
							{
								++w->CurrentWaypoint;
								currentWaypoint->Active = false;
							}
							else if(w->CurrentWaypoint + 1 >= waypoints.size() && w->Loop == true)
							{
								w->CurrentWaypoint = 0;
								currentWaypoint->Active = false;
							}

							currentWaypoint = waypoints[w->CurrentWaypoint];
						}
					}

					if(currentWaypoint->Active == false)
					{
						currentWaypoint->Active = true;

						const auto& velocity = k->LinearVelocity;
						const auto totalVelocity = glm::length(velocity);

						auto direction = (currentWaypoint->Position - currentPosition);
						direction = glm::normalize(direction);
						const auto newVelocity = direction * totalVelocity;
						k->LinearVelocity = newVelocity;
					}
				}
			}
		}
	}
}
