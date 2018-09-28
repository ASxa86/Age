#pragma once

#include <age/graphics/Export.h>
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
		class AGE_GRAPHICS_EXPORT SpriteComponent
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
			sf::Sprite& getSprite();

		protected:
			///
			///	\brief Update the internal rectangle for the internal sprite data.
			///
			void updateTextureRect();

		private:
			sf::Texture texture;
			sf::Sprite sprite;
			unsigned int frame;
			unsigned int vFrames;
			unsigned int hFrames;
		};
	}
}
