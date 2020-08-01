#include <azule/core/Reflection.h>
#include <azule/graphics/BoxSelectionComponent.h>
#include <azule/graphics/DatabaseTexture.h>
#include <azule/graphics/DrawableComponent.h>
#include <azule/export.hxx>
#include <azule/graphics/ProgressBarComponent.h>
#include <azule/graphics/RenderSystem.h>
#include <azule/graphics/SpriteComponent.h>
#include <azule/graphics/TileMapSystem.h>
#include <azule/graphics/Window.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule;
using namespace azule;

STATIC_INVOKE
{
	Reflection::Instance().add<TileMapSystem>("TileMapSystem").addBase<azule::System>();
	Reflection::Instance().add<RenderSystem>("RenderSystem").addBase<azule::System>();

	Reflection::Instance().add<DatabaseTexture>("DatabaseTexture").addBase<azule::Object>();

	Reflection::Instance().add<Window>("Window");

	Reflection::Instance()
		.add<DrawableComponent>("DrawableComponent")
		.addBase<azule::Component>()
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
