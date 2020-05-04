#include <age/core/Reflection.h>
#include <age/graphics/BoxSelectionComponent.h>
#include <age/graphics/DatabaseTexture.h>
#include <age/graphics/DrawableComponent.h>
#include <age/graphics/Export.h>
#include <age/graphics/ProgressBarComponent.h>
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
	Reflection::Instance().add<RenderSystem>("RenderSystem").addBase<age::entity::System>();

	Reflection::Instance().add<DatabaseTexture>("DatabaseTexture").addBase<age::core::Object>();

	Reflection::Instance().add<Window>("Window");

	Reflection::Instance()
		.add<DrawableComponent>("DrawableComponent")
		.addBase<age::entity::Component>()
		.addProperty("UseRotation", &DrawableComponent::UseRotation)
		.addProperty("UsePosition", &DrawableComponent::UsePosition)
		.addProperty("RenderOrder", &DrawableComponent::RenderOrder);

	Reflection::Instance()
		.add<BoxSelectionComponent>("BoxSelectionComponent")
		.addBase<DrawableComponent>()
		.addProperty("Size", &BoxSelectionComponent::Size)
		.addProperty("FillColor", &BoxSelectionComponent::FillColor)
		.addProperty("OutlineColor", &BoxSelectionComponent::OutlineColor)
		.addProperty("OutlineThickness", &BoxSelectionComponent::OutlineThickness)
		.addProperty("Selected", &BoxSelectionComponent::Selected);

	Reflection::Instance()
		.add<SpriteComponent>("SpriteComponent")
		.addBase<DrawableComponent>()
		.addMethod("Frame", &SpriteComponent::setFrame, &SpriteComponent::getFrame)
		.addMethod("VFrames", &SpriteComponent::setVFrames, &SpriteComponent::getVFrames)
		.addMethod("HFrames", &SpriteComponent::setHFrames, &SpriteComponent::getHFrames)
		.addProperty("Rotation", &SpriteComponent::Rotation)
		.addMethod("File", &SpriteComponent::loadFile, &SpriteComponent::getFile);

	Reflection::Instance()
		.add<ProgressBarComponent>("ProgressBarComponent")
		.addBase<DrawableComponent>()
		.addProperty("Value", &ProgressBarComponent::Value)
		.addProperty("ValueMax", &ProgressBarComponent::ValueMax)
		.addProperty("Size", &ProgressBarComponent::Size)
		.addProperty("Color", &ProgressBarComponent::Color)
		.addProperty("Position", &ProgressBarComponent::Position);
}
