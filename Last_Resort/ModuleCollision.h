#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 700

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_PLAYER2,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_PLAYER_SHOT2,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,
	COLLIDER_HOU,
	COLLIDER_CAR,
	COLLIDER_PLAYER_LASERBEAM_SHOT,
	COLLIDER_PLAYER_LASERBEAM_AREA_SHOT,
	COLLIDER_PLAYER_LASERBEAM_SHOT2,
	COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2,
	COLLIDER_BOSS_SHOOT,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;

	void changeCollider(COLLIDER_TYPE type_) {
		type = type_;
	}
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;


	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();
	

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__
