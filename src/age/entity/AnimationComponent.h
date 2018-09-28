#pragma once

#include <age/entity/Animation.h>
#include <age/entity/Export.h>
#include <deque>

namespace age
{
	namespace entity
	{
		///
		///	\class AnimationComponent
		///
		///	\brief An entity component used for applying interpolated values to a given animation channel's function.
		///
		///	\date September 27, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_ENTITY_EXPORT AnimationComponent
		{
		public:
			AnimationComponent();
			~AnimationComponent();

			AnimationComponent(const AnimationComponent&) = delete;
			AnimationComponent& operator=(const AnimationComponent&) = delete;

			///
			///	\brief Set the component to a play state.
			///	While the component is in the play state, animation keys will be interpolated.
			///
			void play();

			///
			///	\brief Set the component to a stop state.
			///	While the component is in the stop state, no animation keys will be interpolated.
			///
			void stop();

			///
			///	\brief Reset the elapted time back to zero and interpolate keys.
			///
			void reset();

			///
			///	\brief Get the playing state of this component.
			///
			///	\return bool True if the component is in a playing state.
			///
			bool getIsPlaying() const;

			///
			///	\brief Set the amount of time that has elapsed since the start of the animation.
			///
			///	\param x The elapsed time since the start of the animation.
			///
			void setElapsed(std::chrono::microseconds x);

			///
			///	\brief Get the amount of elapsed time since the start of the simulation.
			///
			std::chrono::microseconds getElapsed() const;

			///
			///	\brief Set the speed at which to animate the animation.
			///
			///	\param x The speed multiplier for controlling the animation speed.
			///
			void setSpeed(double x);

			///
			///	\brief Get the animation speed multiplier.
			///
			///	\return double The animation speed multiplier.
			///
			double getSpeed() const;

			///
			///	\brief Set the animation duration length.
			///
			///	The length determines when to stop the simulation or loop the animation back to time 0.
			///
			///	\param x The animation length.
			///
			void setLength(std::chrono::microseconds x);

			///
			///	\brief Get the animation length.
			///
			///	\return std::chrono::microseconds The animation length.
			///
			std::chrono::microseconds getLength() const;

			///
			///	\brief Set the current animation of this component.
			///
			///	While this component can maintain multiple animations. Only one animation can be playing at once.
			///
			///	\param x The animation to be set as current.
			///
			void setCurrentAnimation(Animation* x);

			///
			///	\brief Get the current animation.
			///
			///	\return Animation* A pointer to the current animation.
			///
			Animation* getCurrentAnimation() const;

			///
			///	\brief Add an animation to this component.
			///
			///	\return Animation* A pointer to a newly added animation.
			///
			Animation* create();

		private:
			// Use deque in order to create pointers to the animation without losing
			// their reference due to container resize that would occur with vector.
			std::deque<Animation> animations;
			Animation* currentAnimation;
			std::chrono::microseconds elapsed;
			std::chrono::microseconds length;
			double speed;
			bool isPlaying;
		};
	}
}
