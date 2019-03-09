#include <tools/editor/Properties.h>

#include <age/entity/AnimationComponent.h>
#include <age/entity/Entity.h>
#include <age/entity/TransformComponent.h>
#include <age/navigation/WaypointComponent.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/physics/CircleCollisionComponent.h>
#include <age/physics/EdgeCollisionComponent.h>
#include <age/physics/KinematicComponent.h>
#include <sstream>
#include <unordered_map>

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <rttr/method.h>
#include <rttr/property.h>

#ifdef WIN32
#pragma warning(pop)
#endif

using namespace age;
using namespace age::entity;
using namespace age::physics;
using namespace rttr;

namespace
{
	template <typename T>
	T* add(Entity& e)
	{
		return &e.addComponent<T>();
	}

	template <typename T>
	void remove(Entity& e)
	{
		e.removeComponent<T>();
	}
}

std::unordered_map<std::type_index, std::string> Property::Alias;

RTTR_REGISTRATION
{
	Property::Alias[typeid(TransformComponent)] = "TransformComponent";
	Property::Alias[typeid(TransformComponent*)] = "TransformComponent";
	registration::class_<TransformComponent>("TransformComponent")
		.constructor<>(add<TransformComponent>)
		.property("Position", &TransformComponent::Position)
		.property("Rotation", &TransformComponent::Rotation)
		.method("Remove", remove<TransformComponent>);

	type::register_converter_func<std::function<std::string(age::math::Vector&, bool&)>>([](age::math::Vector& x, auto) {
		std::stringstream ss;
		ss << "{" << x.X << ", " << x.Y << "}";
		return ss.str();
	});

	Property::Alias[typeid(KinematicComponent)] = "KinematicComponent";
	Property::Alias[typeid(KinematicComponent*)] = "KinematicComponent";
	registration::class_<KinematicComponent>("KinematicComponent")
		.constructor<>(add<KinematicComponent>)
		.property("BodyType", &KinematicComponent::BodyType)
		.property("LinearVelocity", &KinematicComponent::LinearVelocity)
		.property("CalculateHeading", &KinematicComponent::CalculateHeading)
		.method("Remove", remove<KinematicComponent>);

	Property::Alias[typeid(KinematicComponent::Type)] = "BodyType";
	registration::enumeration<KinematicComponent::Type>("BodyType")(value("Static", KinematicComponent::Type::Static),
																	value("Kinematic", KinematicComponent::Type::Kinematic),
																	value("Dynamic", KinematicComponent::Type::Dynamic));

	Property::Alias[typeid(BoxCollisionComponent)] = "BoxCollisionComponent";
	Property::Alias[typeid(BoxCollisionComponent*)] = "BoxCollisionComponent";
	registration::class_<BoxCollisionComponent>("BoxCollisionComponent")
		.constructor<>(add<BoxCollisionComponent>)
		.property("Density", &BoxCollisionComponent::Density)
		.property("Friction", &BoxCollisionComponent::Friction)
		.property("Restitution", &BoxCollisionComponent::Restitution)
		.property("IsSensor", &BoxCollisionComponent::IsSensor)
		.property("Height", &BoxCollisionComponent::Height)
		.property("Width", &BoxCollisionComponent::Width)
		.method("Remove", remove<BoxCollisionComponent>);

	Property::Alias[typeid(CircleCollisionComponent)] = "CircleCollisionComponent";
	Property::Alias[typeid(CircleCollisionComponent*)] = "CircleCollisionComponent";
	registration::class_<CircleCollisionComponent>("CircleCollisionComponent")
		.constructor<>(add<CircleCollisionComponent>)
		.property("Density", &CircleCollisionComponent::Density)
		.property("Friction", &CircleCollisionComponent::Friction)
		.property("Restitution", &CircleCollisionComponent::Restitution)
		.property("IsSensor", &CircleCollisionComponent::IsSensor)
		.property("Radius", &CircleCollisionComponent::Radius)
		.method("Remove", remove<CircleCollisionComponent>);

	Property::Alias[typeid(EdgeCollisionComponent)] = "EdgeCollisionComponent";
	Property::Alias[typeid(EdgeCollisionComponent*)] = "EdgeCollisionComponent";
	registration::class_<EdgeCollisionComponent>("EdgeCollisionComponent")
		.constructor<>(add<EdgeCollisionComponent>)
		.property("Density", &EdgeCollisionComponent::Density)
		.property("Friction", &EdgeCollisionComponent::Friction)
		.property("Restitution", &EdgeCollisionComponent::Restitution)
		.property("IsSensor", &EdgeCollisionComponent::IsSensor)
		.property("Vertex1", &EdgeCollisionComponent::Vertex1)
		.property("Vertex2", &EdgeCollisionComponent::Vertex2)
		.method("Remove", remove<EdgeCollisionComponent>);
}

Property::Property(Entity& x) : components{}, entity{x}
{
}

void Property::addComponent(const std::string& component)
{
	auto type = type::get_by_name(component.c_str());
	this->components[component] = type.create({this->entity});
}

void Property::removeComponent(const std::string& component)
{
	auto type = type::get_by_name(component.c_str());
	auto method = type.get_method("Remove");
	method.invoke(this->components[component], this->entity);
}

void Property::setValue(const std::string& name, const std::string& property, rttr::argument arg)
{
	auto type = type::get_by_name(name.c_str());
	auto p = type.get_property(property.c_str());
	p.set_value(this->components[name], arg);
}

void Property::setValue(const std::type_index& type, const std::string& property, rttr::argument arg)
{
	this->setValue(Alias[type], property, arg);
}

std::string Property::getValue(const std::string& name, const std::string& property)
{
	auto type = type::get_by_name(name.c_str());
	auto p = type.get_property(property.c_str());
	return p.get_value(this->components[name]).to_string();
}

std::string Property::getValue(const std::type_index& type, const std::string& property)
{
	return this->getValue(Alias[type], property);
}
