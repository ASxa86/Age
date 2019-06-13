#include <age/navigation/WaypointSystem.h>

#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <age/navigation/WaypointComponent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::entity;
using namespace age::math;
using namespace age::navigation;
using namespace age::physics;

struct WaypointSystem::Impl
{
};

WaypointSystem::WaypointSystem() : System(), pimpl()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

WaypointSystem::~WaypointSystem()
{
}

void WaypointSystem::frame(std::chrono::microseconds)
{
	const auto manager = this->getEntityManager();

	manager->each<WaypointComponent, TransformComponent, KinematicComponent>(
		[this](auto&, WaypointComponent& w, TransformComponent& t, KinematicComponent& k) {
			if(w.Waypoints.empty() == false && w.CurrentWaypoint >= 0 && w.CurrentWaypoint < w.Waypoints.size())
			{
				auto& currentWaypoint = w.Waypoints[w.CurrentWaypoint];
				const auto currentPosition = t.Position;

				if(currentWaypoint.Active == true)
				{
					// We've reached the waypoint when the line created by
					// the player's starting position and current position
					// intersects the waypoint's position.

					// Set a 1 unit tolerance to determine when to switch to next waypoint.
					// I suspect a more refined test will be needed here for higher velocities
					// but this tolerance check currently seems to work.
					constexpr auto tolerance = 1.0;

					if((currentPosition - currentWaypoint.Position).magnitude() < tolerance)
					{
						// Deactivate the current waypoint only if we can progress to the next waypoint.
						// This will prevent calculating a new velocity if we've reached the last waypoint.
						// If we are not looping and the last waypoint has been reached, then that is the active waypoint.
						if(w.CurrentWaypoint + 1 < w.Waypoints.size())
						{
							++w.CurrentWaypoint;
							currentWaypoint.Active = false;
						}
						else if(w.CurrentWaypoint + 1 >= w.Waypoints.size() && w.Loop == true)
						{
							w.CurrentWaypoint = 0;
							currentWaypoint.Active = false;
						}

						currentWaypoint = w.Waypoints[w.CurrentWaypoint];
					}
				}

				if(currentWaypoint.Active == false)
				{
					currentWaypoint.Active = true;

					const auto& velocity = k.LinearVelocity;
					const auto totalVelocity = velocity.magnitude();

					auto direction = (currentWaypoint.Position - currentPosition);
					direction.normalize();
					const auto newVelocity = direction * totalVelocity;
					k.LinearVelocity = newVelocity;
				}
			}
		});
}
