#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSceneLvl1.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

enum Shoots
{
	BASICSHOOT,
	LASERSHOOT,
	MISSILES
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider *c1, Collider *c2);
	
	bool AppearAnim;
	bool Dead;
	bool Spawned;

	bool GOD = false;
	bool ToBeDeleted = false;
	bool TimeCounter = true;
	uint AppearTime;
	uint current_time=SDL_GetTicks();

public:
	SDL_Rect Ship;
	SDL_Rect UI_ship;
	

	SDL_Texture* graphicsp1 = nullptr;
	SDL_Texture*UI_Main_Menu = nullptr;

	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	Animation DestroyShip;

	Animation* current_animation = nullptr;
	
	iPoint position;

	Collider *Ship1Collider;


	//Font id
	int font = -1;
	int disappeartext = -1;

	//P1 Score
	char score_text[10];
	uint ScoreP1;

	//Top Score
	char top_score[10];
	uint TopScore;

	//P1 Life
	char life_text[10];

public:
	
	bool startAnim = true;
	bool shooted = false;
	
	Mix_Chunk*Shot_Sound=nullptr;

public:

	SDL_Rect setFirePos() {

		SDL_Rect FirePos;
		
		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

		return FirePos;
	}

		void resetPosition() {
			position.x = App->scene1background->position_min_limit + 20;
		    position.y = SCREEN_HEIGHT / 2;

	}
		void Reset_limits(){
			int position_max_limit = SCREEN_WIDTH;
			int position_min_limit = 0;
		}
public:
	//shoot selector here
	int WeaponType = 0;

	void ShootSelector(uint shoot) {
		if (shoot == BASICSHOOT) {
			WeaponType = 1;
		}
		else if (shoot == LASERSHOOT) {
			WeaponType = 2;
		}
	};
};

#endif