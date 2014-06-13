#ifndef STATES_H
#define STATES_H

namespace stg
{
	class States
	{
		protected:
			States(){}
		public:
			//Initialize the state's resources.
			virtual void start(Danmaku *game) = 0;
			//End a state and free its resources.
			virtual void stop(Danmaku *game) = 0;
			//Resume a state.
			virtual void play(Danmaku *game) = 0;
			//Pause the current state.
			virtual void pause(Danmaku *game) = 0;
			//Handle the events of this state.
			virtual void controller(Danmaku *game) = 0;
			//Handle events and game logic of this state.
			virtual void update(Danmaku *game) = 0;
			//Handles rendering routines.
			virtual void render(Danmaku *game) = 0;
	};
}

#endif

/* Copyleft 2013, Anonymous */
