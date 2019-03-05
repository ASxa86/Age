#include <tools/editor/Application.h>
#include <tools/editor/MainWindow.h>

#include <tools/editor/ComponentFactory.h>

#include <age/entity/AnimationComponent.h>
#include <age/entity/TransformComponent.h>
#include <age/navigation/WaypointComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/EdgeCollisionComponent.h>
#include <age/physics/KinematicComponent.h>

int main(int argc, char** argv)
{
	age::Application app(argc, argv);

	age::ComponentFactory::Instance().registerComponent<age::entity::AnimationComponent>();
	age::ComponentFactory::Instance().registerComponent<age::entity::TransformComponent>();
	age::ComponentFactory::Instance().registerComponent<age::navigation::WaypointComponent>();
	age::ComponentFactory::Instance().registerComponent<age::physics::BoxCollisionComponent>();
	age::ComponentFactory::Instance().registerComponent<age::physics::CircleCollisionComponent>();
	age::ComponentFactory::Instance().registerComponent<age::physics::EdgeCollisionComponent>();
	age::ComponentFactory::Instance().registerComponent<age::physics::KinematicComponent>();

	age::MainWindow window;
	window.show();
	return app.exec();
}
