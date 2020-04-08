#pragma once

#include <age/graphics/DrawableComponent.h>
#include <age/graphics/export.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

namespace age
{
	namespace graphics
	{
		///
		///	\class SpriteComponent
		///
		///	\brief An entity component for managing sprites and spritesheets.
		///
		///	\date September 29, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT SpriteComponent : public age::graphics::DrawableComponent
		{
		public:
			SpriteComponent();
			~SpriteComponent();

			///
			///	\brief Load a sprite or spriesheet file.
			///
			///	\param x The path to the sprite or spritesheet.
			///
			void loadFile(const std::filesystem::path& x);
			const std::filesystem::path& getFile() const;

			///
			///	\brief Set the current frame of the sprite or spritesheet.
			///
			///	\param x The frame number of the sprite or spritesheet.
			///
			void setFrame(unsigned int x);

			///
			///	\brief Get the current frame number of the sprite or spritesheet.
			///
			///	\return unsigned int The frame number of the sprite or spritesheet.
			///
			unsigned int getFrame() const;

			///
			///	\brief Set the number of vertical frames for the sprite or spritesheet.
			///
			///	Vertical frames define the number of "rows" for the sprite or spritesheet.
			///
			///	\param x The number of vertical frames.
			///
			void setVFrames(unsigned int x);

			///
			///	\brief Get the number of vertical frames.
			///
			///	\return unsigned int The number of vertical frames.
			///
			unsigned int getVFrames() const;

			///
			///	\brief Set the number of horizontal frames for the sprite or spritesheet.
			///
			///	Horizontal frames define the number of "columns" for the sprite or spritesheet.
			///
			///	\param x The number of horizontal frames.
			///
			void setHFrames(unsigned int x);

			///
			///	\brief Get the number of horizontal frames.
			///
			///	\return unsigned int The number of horizontal frames.
			///
			unsigned int getHFrames() const;

			///
			///	\brief Get the total number of frames as defined by vertical and horitonal frames.
			///
			///	\return unsigned int The total number of frames.
			///
			unsigned int getFrameCount() const;

			///
			///	\brief Get the internal sprite data.
			///
			///	\return sf::Sprite& The reference to the internal sprite data.
			///
			virtual sf::Drawable& getDrawable() override;

			/// Rotate the sprite with the given angle in degrees.
			double Rotation{};

		protected:
			virtual void onStartup() override;

			///
			///	\brief Update the internal rectangle for the internal sprite data.
			///
			void updateTextureRect();

		private:
			sf::Sprite sprite;
			std::filesystem::path file;
			unsigned int frame;
			unsigned int vFrames;
			unsigned int hFrames;
		};
	}
}
