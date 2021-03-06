#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleGameOver.h"
#include "ModuleParticles.h"
#include "ModuleStageClear.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"
#include "ModuleBossLvl1.h"
#include "ModuleTank.h"
#include "ModuleGameControllers.h"
#include "Iron_Craw.h"
#include "Module_Hou_Player1.h"
#include "Module_Hou_Player2.h"
#include "ModuleHighScore.h"

#include <time.h>

Application::Application()
{
	srand(time(NULL));

	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = controllers = new ModuleGameControllers();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = sound = new ModuleSound();
	modules[i++] = menu = new ModuleMainMenu();
	modules[i++] = scene1background = new ModuleSceneLvl1();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = gameover = new ModuleGameOver();
	modules[i++] = stageclear = new ModuleStageClear();
	modules[i++] = HOU_Player2 = new ModuleHouPlayer2();
	modules[i++] = HOU_Player1 = new ModuleHouPlayer1();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
    modules[i++] = MiniBoss = new Iron_Craw();
	modules[i++] = powerup = new ModulePowerUp();
	modules[i++] = BossTank = new ModuleTank();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = HighScore = new ModuleHighScore();
	modules[i++] = fonts = new ModuleUI();
	modules[i++] = Boss = new ModuleBossLvl1();
	modules[i++] = fade = new ModuleFadeToBlack();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	//Disable the map that you do not start with

	player->Disable();
	scene1background->Disable();
	gameover->Disable();
	stageclear->Disable();
	collision->Disable();
	particles->Disable();
	enemies->Disable();
	powerup->Disable();
	player2->Disable();
	App->Boss->Disable();
	MiniBoss->Disable();
	App->fonts->Enable();
	App->BossTank->Disable();
	App->HighScore->Disable();


	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}// 138