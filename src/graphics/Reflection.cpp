#include <age/core/Reflection.h>
#include <age/graphics/BoxSelectionComponent.h>
#include <age/graphics/DatabaseTexture.h>
#include <age/graphics/DrawableComponent.h>
#include <age/graphics/DrawableSystem.h>
#include <age/graphics/Export.h>
#include <age/graphics/HealthBarSystem.h>
#include <age/graphics/RenderSystem.h>
#include <age/graphics/SpriteComponent.h>
#include <age/graphics/TileMapSystem.h>
#include <age/graphics/Window.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::graphics;

STATIC_INVOKE
{
	Reflection::Instance().add<TileMapSystem>("TileMapSystem").addBase<age::entity::System>();
	Reflection::Instance().add<DrawableSystem>("DrawableSystem").addBase<age::entity::System>();
	Reflection::Instance().add<RenderSystem>("RenderSystem").addBase<age::entity::System>();

	Reflection::Instance().add<DatabaseTexture>("DatabaseTexture").addBase<age::core::Object>();

	Reflection::Instance()
		.add<HealthBarSystem>("HealthBarSystem")
		.addBase<age::entity::System>()
		.addProperty("Color", &HealthBarSystem::Color)
		.addProperty("Offset", &HealthBarSystem::Offset)
		.addProperty("Size", &HealthBarSystem::Size);

	Reflection::Instance().add<Window>("Window");

	Reflection::Instance()
		.add<BoxSelectionComponent>("BoxSelectionComponent")
		.addBase<age::entity::Component>()
		.addProperty("Size", &BoxSelectionComponent::Size)
		.addProperty("FillColor", &BoxSelectionComponent::FillColor)
		.addProperty("OutlineColor", &BoxSelectionComponent::OutlineColor)
		.addProperty("OutlineThickness", &BoxSelectionComponent::OutlineThickness)
		.addProperty("Selected", &BoxSelectionComponent::Selected);

	Reflection::Instance()
		.add<SpriteComponent>("SpriteComponent")
		.addBase<age::entity::Component>()
		.addMethod("Frame", &SpriteComponent::setFrame, &SpriteComponent::getFrame)
		.addMethod("VFrames", &SpriteComponent::setVFrames, &SpriteComponent::getVFrames)
		.addMethod("HFrames", &SpriteComponent::setHFrames, &SpriteComponent::getHFrames)
		.addProperty("Rotation", &SpriteComponent::Rotation)
		.addMethod("File", &SpriteComponent::loadFile, &SpriteComponent::getFile);
}
