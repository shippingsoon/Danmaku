#ifndef STAGE_H
#define STAGE_H
#include "main.h"

//#include "enemy.h"
//#include "path.h"

namespace stg
{
	//class Enemy;
	
	class Stage : public States
	{
		private:
			float timeline;
			std::string msg;
			sf::RenderTexture buffer_layer, canvas_layer, paint_layer[2];
			sf::Texture background_texture, canvas_texture;
			sf::Sprite background_sprite, canvas_sprite, buffer_sprite, paint_sprite[2];
			sf::Vector2f canvas_position, m_position[2], b_position, t_position, paint_position[2], bullet_position[20];
			sf::CircleShape m_circle[2], b_circle, k_circle, t_circle, bullet[20];
			sf::Color bullet_color[20];
			float bullet_speed[20];
			float rote, ro;
			float radians, degrees, radius, angle, step_size, bullet_radius[20], bullet_angle[20];
			bool is_odd_layer;
			int layer_index;
			void tmp(Danmaku *game);
			static Stage stage;
			bool action = true;
			std::vector<sf::Vector2f> paths;
			Enemy enemy[1];
		protected:
			Stage(){};
		public:
			void start(Danmaku *game);
			void stop(Danmaku *game);
			void play(Danmaku *game);
			void pause(Danmaku *game);
			void controller(Danmaku *game);
			void update(Danmaku *game);
			void render(Danmaku *game);
			static Stage *instance()
			{
				return &stage;
			}
	};
}

#endif

/* Copyleft 2013, Anonymous */
