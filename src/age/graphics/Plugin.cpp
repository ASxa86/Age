#include <age/core/Factory.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/Export.h>
#include <age/graphics/SpriteComponent.h>
#include <age/graphics/TileMapSystem.h>
#include <age/graphics/Window.h>

AGE_GRAPHICS_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::graphics::SpriteComponent).addBaseType<age::entity::Component>();
	AgeFactoryRegister(age::graphics::Window);
	AgeFactoryRegister(age::graphics::TileMapSystem).addBaseType<age::entity::System>();
	AgeFactoryRegister(age::graphics::DrawableSystem).addBaseType<age::entity::System>();
}
