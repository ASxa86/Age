#include <age/entity/ComponentFactory.h>
#include <age/graphics/Export.h>
#include <age/graphics/InputComponent.h>
#include <age/graphics/SpriteComponent.h>
#include <age/graphics/TileMapComponent.h>

using namespace age::entity;
using namespace age::graphics;

AGE_GRAPHICS_EXPORT_C void ComponentFactoryRegister()
{
	ComponentFactory::RegisterType<SpriteComponent>("SpriteComponent");
	ComponentFactory::RegisterType<InputComponent>("InputComponent");
	ComponentFactory::RegisterType<TileMapComponent>("TileMapComponent");
}
