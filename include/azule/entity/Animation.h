#pragma once

#include <azule/entity/AnimationChannel.h>
#include <azule/entity/export.h>
#include <memory>

namespace azule
{
	namespace entity
	{
		///
		///	\class Animation
		///
		///	\brief A single animation that is driven by an arbitrary number of AnimationChannels.
		///
		///	\date September 27, 2018
		///
		///	\author Aaron Shelley
		///
		class AZULE_ENTITY_EXPORT Animation
		{
		public:
			Animation();

			Animation(Animation&&) = default;
			Animation& operator=(Animation&&) = default;

			Animation(const Animation&) = delete;
			Animation& operator=(const Animation&) = delete;

			///
			///	\brief Evaluate all channels for the given elapsed time.
			///
			///	\param x The elapsed time used to evaluate channels against.
			///
			void process(std::chrono::microseconds x) const;

			///
			///	\brief Add a channel that describes the behavior of interpolation when evaluating the given function.
			///
			///	\param shape The interpolation shape of the channel.
			///	\param f The evaluation function that is invoked when a channel is evaluated.
			///
			template <typename T>
			AnimationChannel<T>& addChannel(Channel::Shape shape, const std::function<void(T)>& f)
			{
				auto channel = std::make_unique<AnimationChannel<T>>(shape, f);
				auto p = channel.get();
				this->channels.push_back(std::move(channel));

				return *p;
			}

		private:
			std::vector<std::unique_ptr<Channel>> channels;
		};
	}
}
