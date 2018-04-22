#ifndef MODULEFONTS_H
#define MODULEFONTS_H

#include "Module.h"
#include "SDL/include/SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font {

	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

class ModuleFonts : public Module {

public:
	ModuleFonts();
	~ModuleFonts();

	int Load(const char* texture_path, const char *characters, uint rows = 1);
	void UnLoad(int font_id);

	void BlitText(int x, int y, int bmp_font_id, const char *text) const;
	
	uint TopScore(uint Score1, uint Score2, uint TopScore);
	uint TopScoreP1(uint Score1, uint TopScore);

	uint SP1 = 0;
	uint SP2 = 0;

private:

	Font fonts[MAX_FONTS];
};

#endif