#pragma once

#include <age/entity/export.h>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

namespace age
{
	namespace entity
	{
		///
		///	\class Channel
		///
		///	\brief Base channel class for maintaining a Channel's shape and providing a public interface for derived types.
		///
		///	\date September 27, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT Channel
		{
		public:
			enum class Shape : uint8_t
			{
				Step,
				Linear
			};

			Channel() = delete;
			Channel(Shape s);
			virtual ~Channel();

			Shape getShape() const;

			///
			///	\brief Abstract function. Override to handle interpolating a channel's keys.
			///
			virtual void evaluate(std::chrono::microseconds) const = 0;

		private:
			Shape shape;
		};

		///
		///	\class AnimationChannel
		///
		///	\brief Template channel for adding key frames for interpolation of the channel.
		///
		///	\date September 27, 2018
		///
		///	\author Aaron Shelley
		///
		template <typename T>
		class AnimationChannel final : public Channel
		{
		public:
			///
			///	\class Key
			///
			///	\brief A channel's key is a time/value pair representing a key frame.
			///
			struct Key
			{
				std::chrono::microseconds Time{};
				T Value{};
			};

			AnimationChannel() = delete;

			AnimationChannel(Shape shape, const std::function<void(T)>& e) : Channel(shape), evaluator{e}
			{
			}

			AnimationChannel(AnimationChannel&& x) : Channel{x.shape}, evaluator{x.evaluator}
			{
			}

			///
			///	\brief Interpolate keys based on the given elapsed time.
			///
			///	\param x Elapsed time.
			///
			void evaluate(std::chrono::microseconds x) const override
			{
				switch(this->getShape())
				{
					case Channel::Shape::Linear:
					case Channel::Shape::Step:
					default:
						auto foundIt = std::find_if(std::begin(this->keys), std::end(this->keys), [x](const auto& k) { return k.Time >= x; });
						if(foundIt != std::end(this->keys))
						{
							if(foundIt->Time > x)
							{
								foundIt--;
							}

							this->evaluator(foundIt->Value);
						}
						break;
				}
			}

			///
			///	\brief Add a key to the channel.
			///
			///	\param x Key.
			///
			void addKey(const Key& x)
			{
				this->keys.push_back(x);
			}

		private:
			std::vector<Key> keys{};
			std::function<void(T)> evaluator{};
		};
	}
}
