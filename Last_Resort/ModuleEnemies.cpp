#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleSound.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "EnemyRhino.h"
#include "EnemyBee.h"
#include "EnemyWasp.h"
#include "EnemyZicZac.h"
#include "EnemyLamella.h"
#include "CarsToFast.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer2.h"
#include "ModulePowerUp.h"
#include "ModuleUI.h"
#include "Enemy_Tears.h"
#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies() {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}

ModuleEnemies::~ModuleEnemies() {}

bool ModuleEnemies::Start() {
	carSprites= App->textures->Load("Images/General/Car_Sprites.png");
	sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");
	LOG("Starting Module Enemies");
	return true;
}

bool ModuleEnemies::CleanUp() {

	LOG("Cleaning Up Enemies Module");

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		queue[i].type = NO_TYPE;
		queue[i].x = 0;
		queue[i].y = 0;

		if (enemies[i] != nullptr) {
			App->textures->Unload(enemies[i]->sprites);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleEnemies::PreUpdate() {

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (queue[i].type != ENEMY_TYPES::NO_TYPE) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {
		
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}
	
	return UPDATE_CONTINUE;
}
update_status ModuleEnemies::Update() {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(enemies[i]->sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate() {

	//Check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		
		if (enemies[i] != nullptr) {
			
			if ((enemies[i]->position.x * SCREEN_SIZE) < (App->render->camera.x - 200) || (enemies[i]->position.x * SCREEN_SIZE) > (App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN + 20)) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
			
				App->textures->Unload(enemies[i]->sprites);
				//AddParticle(EnemyExplosion, active[i]->Position.x - 80, active[i]->Position.y + 3, COLLIDER_NONE, 200);
				delete enemies[i];
				enemies[i] = nullptr;
			}
			else if (enemies[i]->reached == true) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				App->textures->Unload(enemies[i]->sprites);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, bool PowerUp ) {

	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (queue[i].type == ENEMY_TYPES::NO_TYPE) {

			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].PowerUp=PowerUp;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::ENEMY_RHINO:
		enemies[i] = new Enemy_Rhino(info.x, info.y,info.PowerUp);
		break;
		
		case ENEMY_TYPES::ENEMY_WASP:
	  	enemies[i] = new EnemyWasp(info.x, info.y,info.PowerUp);
	  	break;
		
		case ENEMY_TYPES::ENEMY_ZICZAC:
		enemies[i] = new EnemyZicZac(info.x, info.y,info.PowerUp);
		break;
		
		case ENEMY_TYPES::ENEMY_LAMELLA:
		enemies[i] = new EnemyLamella(info.x, info.y,info.PowerUp);
		break;
		
		case ENEMY_TYPES::CARS:
		enemies[i] = new CarsToFast(info.x, info.y,info.type);
		break;

		case ENEMY_TYPES::ENEMY_BEE:
		enemies[i] = new Enemy_Bee(info.x, info.y,info.PowerUp);
		break;

		case ENEMY_TYPES::BOSS_TEARS:
		enemies[i] = new Enemy_BossTears(info.x, info.y, info.PowerUp);
		break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider *c1, Collider *c2) {
		
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		
		 if (enemies[i] != nullptr && (enemies[i]->GetCollider() == c1 || enemies[i]->GetCollider() == c2)) {

			 --(enemies[i]->life);

			if (enemies[i]->life <= 0) {

				

				if (enemies[i]->PowerUp == true) {

					if(App->scene1background->randomPositionCars==1)
						App->powerup->AddPowerUp(POWERUP_TYPES::LASER,enemies[i]->position.x,enemies[i]->position.y);
					else if (App->scene1background->randomColorCars == 2) {
						App->powerup->AddPowerUp(POWERUP_TYPES::MISILES, enemies[i]->position.x, enemies[i]->position.y);
					}
				}

				if(c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
					App->fonts->ScoreP1 += enemies[i]->score;
				else if (c1->type == COLLIDER_PLAYER_SHOT2 || c2->type == COLLIDER_PLAYER_SHOT2)
					App->fonts->ScoreP2 += enemies[i]->score;

				if (enemies[i]->type != ENEMY_TYPES::CARS) {
					App->particles->AddParticle(App->particles->EnemyExplosion, enemies[i]->position.x + 8, enemies[i]->position.y - 2, COLLIDER_NONE, 200);
					//App->particles->AddParticle(App->particles->EnemyExplosion, enemies[i]->position.x - 8, enemies[i]->position.y + 3, COLLIDER_NONE, 200);
				}
				App->textures->Unload(enemies[i]->sprites);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		} 
	}
}