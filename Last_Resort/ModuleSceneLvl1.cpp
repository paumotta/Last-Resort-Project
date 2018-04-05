#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLvl2.h"
#include "ModuleMainMenu.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLvl1::ModuleSceneLvl1()
{
	// background1 
	FirstPlaneBackGround.x = 0;
	FirstPlaneBackGround.y = 0;
	FirstPlaneBackGround.w = 4407; //works
	FirstPlaneBackGround.h = 238; //also works
	//background2
	SecondPlaneBackground.x = 0;
	SecondPlaneBackground.y = 0;
	SecondPlaneBackground.w = 1302;
	SecondPlaneBackground.h = 159;
	//background3
	ThirdPlaneBackground.x = 0;
	ThirdPlaneBackground.y = 0;
	ThirdPlaneBackground.w = 802;
	ThirdPlaneBackground.h = 159;
}

ModuleSceneLvl1::~ModuleSceneLvl1()
{
	
}

// Load assets
bool ModuleSceneLvl1::Start()
{
	
	LOG("Loading background assets");

	//order of position in the game
	graphics_Boss_Static_Background = App->textures->Load("Images/Background_Lvl1/Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("Images/Background_Lvl1/ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("Images/Background_Lvl1/SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("Images/Background_Lvl1/FirstPlaneBackGround.png");

	//Music
	Stage1=App->sound->LoadMusic("Audio/Stage1/Jack_to_Metro_Stage1.ogg");
	Mix_PlayMusic(Stage1,-1);
	Mix_Volume(-1, MIX_MAX_VOLUME / 9);

	
	if (App->player->IsEnabled() == false) {

		App->player->Enable();
	}

	if (App->scene1background->IsEnabled() == false) {
		
		App->player->Disable();
	}

	return true;

}

//Unload Assets

bool ModuleSceneLvl1::CleanUp() {

	LOG("Unloading Lvl 1 Scene");
	
	App->textures->Unload(graphics_Boss_Static_Background);
	App->textures->Unload(graphics_Boss_Static_Background);
	App->textures->Unload(graphics_Boss_Static_Background);
	App->textures->Unload(graphics_Boss_Static_Background);

	return true;
}
// Update: draw background
update_status ModuleSceneLvl1::Update()
{

	float Speed_Foreground=3;
	float Speed_Background=1;
	float Speed_Midground=2;

	//background movements!!! HERE---> The images are the ones which move, not the camera.

		FirstPlaneBackGround_position_X -= Speed_Foreground;
	
		SecondPlaneGround_position_X -= Speed_Midground;
	
		ThirdPlaneBackground_position_X -= Speed_Background;
	
	
	// Draw everything --------------------------------------
	App->render->Blit(graphics_ThirdPlaneBackground, (ThirdPlaneBackground_position_X)/3.5, 0, &ThirdPlaneBackground, 1.0f);
	App->render->Blit(graphics_SecondPlaneBackground, (SecondPlaneGround_position_X)/3, 30, &SecondPlaneBackground, 1.0f); //SECOND PLANE BACKGROUND
	App->render->Blit(graphics_FirstPlaneBackGround, (FirstPlaneBackGround_position_X)/2, 0, &FirstPlaneBackGround, 1.0f); // FIRST PLANE BACKGROUND

	if (App->input->keyboard[SDL_SCANCODE_SPACE]==1) {
		App->fade->FadeToBlack(App->scene1background, (Module*)App->scene2background, 2.0f);
	}

	return UPDATE_CONTINUE;
}