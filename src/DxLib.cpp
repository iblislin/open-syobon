#include "DxLib.h"

//Main screen
SDL_Surface *screen;

//Fonts
byte fontsize = 0;
TTF_Font *font[FONT_MAX] = {0};

SDL_Joystick* joystick;

bool keysHeld[SDLK_LAST] = {0};
void deinit();

int DxLib_Init(GameConfig* conf)
{
    atexit(deinit);
    setlocale(LC_CTYPE, "ja_JP.UTF-8");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr <<  "Unable to init SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // init screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                              SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (!screen)
        return -1;

    SDL_WM_SetCaption("Syobon Action (しょぼんのアクション)", NULL);
    SDL_ShowCursor(SDL_DISABLE);

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Unable to init SDL_img: " << IMG_GetError() << std::endl;
        return -1;
    }

    //Initialize font
    if (TTF_Init() == -1) {
        std::cerr << "Unable to init SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }
    SetFontSize(16);

    //Audio Rate, Audio Format, Audio Channels, Audio Buffers
    if (conf->sound && Mix_OpenAudio(22050, AUDIO_S16SYS, AUDIO_CHANNELS, 1024)) {
        std::cerr << "Unable to init SDL_mixer: " << Mix_GetError() << std::endl;
        conf->sound = false;
    }

    //Try to get a joystick
    joystick = SDL_JoystickOpen(0);

    srand(time(NULL));

    return 0;
}


//Strings
void SetFontSize(byte size)
{
    ::fontsize = size;

    if (font[size] == NULL) {
        font[size] = TTF_OpenFont("res/sazanami-gothic.ttf", size);

        if (font[size] == NULL) {
            std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
            exit(1);
        }
    }
}

byte fontType = DX_FONTTYPE_NORMAL;
void ChangeFontType(byte type)
{
    fontType = type;
}

void DrawString(int a, int b, const char *x, Uint32 c)
{
    SDL_Color color = {
        static_cast<Uint8>(c >> 16),
        static_cast<Uint8>(c >> 8),
        static_cast<Uint8>(c)
    };
    SDL_Surface *rendered = TTF_RenderUTF8_Solid(font[fontsize], x, color);
    if (fontType == DX_FONTTYPE_EDGE) {
	SDL_Color blk = { 0, 0, 0 };
	SDL_Surface *shadow = TTF_RenderUTF8_Solid(font[fontsize], x, blk);
	DrawGraphZ(a - 1, b - 1, shadow);
	DrawGraphZ(a, b - 1, shadow);
	DrawGraphZ(a + 1, b - 1, shadow);
	DrawGraphZ(a - 1, b, shadow);
	DrawGraphZ(a + 1, b, shadow);
	DrawGraphZ(a - 1, b + 1, shadow);
	DrawGraphZ(a, b + 1, shadow);
	DrawGraphZ(a + 1, b + 1, shadow);
	SDL_FreeSurface(shadow);
    }
    DrawGraphZ(a, b, rendered);
    SDL_FreeSurface(rendered);
}

void DrawFormatString(int a, int b, Uint32 color, const char* str, ...)
{
    va_list args;
    char *newstr = new char[strlen(str) + 16];

    va_start(args, str);
    vsprintf(newstr, str, args);
    va_end(args);

    DrawString(a, b, newstr, color);
    delete[] newstr;
}


void UpdateKeys()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                keysHeld[event.key.keysym.sym] = true;
                break;

            case SDL_KEYUP:
                keysHeld[event.key.keysym.sym] = false;
                break;

            case SDL_JOYAXISMOTION:
                if(event.jaxis.which == 0)
                {
                    if(event.jaxis.axis == JOYSTICK_XAXIS)
                    {
                        if(event.jaxis.value < 0)
                            keysHeld[SDLK_LEFT] = true;
                        else if(event.jaxis.value > 0)
                            keysHeld[SDLK_RIGHT] = true;
                        else {
                            keysHeld[SDLK_LEFT] = false;
                            keysHeld[SDLK_RIGHT] = false;
                        }
                    }
                    else if(event.jaxis.axis == JOYSTICK_YAXIS)
                    {
                        if(event.jaxis.value < 0)
                            keysHeld[SDLK_UP] = true;
                        else if(event.jaxis.value > 0)
                            keysHeld[SDLK_DOWN] = true;
                        else {
                            keysHeld[SDLK_UP] = false;
                            keysHeld[SDLK_DOWN] = false;
                        }
                    }
                }
                break;

            case SDL_QUIT:
                exit(0);
                break;
        }
    }
}

byte CheckHitKey(int key)
{
    if(key == SDLK_z && keysHeld[SDLK_SEMICOLON])
        return true;
    return keysHeld[key];
}

byte WaitKey()
{
    SDL_Event event;
    while (true) {
	while (SDL_PollEvent(&event))
	    if (event.type == SDL_KEYDOWN)
		return event.key.keysym.sym;
    }
}

void DrawGraphZ(int x, int y, SDL_Surface * surface)
{
    if (NULL == surface)
        return;

    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(surface, NULL, screen, &offset);
}

void DrawTurnGraphZ(int a, int b, SDL_Surface * mx)
{
    if (NULL == mx)
        return;

    SDL_Rect offset;
    offset.x = a;
    offset.y = b;

    SDL_Surface *flipped = zoomSurface(mx, -1, 1, 0);
    SDL_SetColorKey(flipped, SDL_SRCCOLORKEY,
                    SDL_MapRGB(flipped->format, 9 * 16 + 9, 255, 255));
    SDL_BlitSurface(flipped, NULL, screen, &offset);
    SDL_FreeSurface(flipped);
}

void DrawVertTurnGraph(int a, int b, SDL_Surface * mx)
{
    if(mx)
    {
        SDL_Rect offset;
        offset.x = a - mx->w / 2;
        offset.y = b - mx->h / 2;

        SDL_Surface *flipped = rotozoomSurface(mx, 180, 1, 0);
        SDL_SetColorKey(flipped, SDL_SRCCOLORKEY,
                SDL_MapRGB(flipped->format, 9 * 16 + 9, 255, 255));
        SDL_BlitSurface(flipped, NULL, screen, &offset);
        SDL_FreeSurface(flipped);
    }
}

SDL_Surface* DerivationGraph(int srcx, int srcy, int width, int height,
                             SDL_Surface * src)
{
    SDL_Surface *img = SDL_CreateRGBSurface(
        SDL_SWSURFACE, width, height,
        screen->format->BitsPerPixel,
        src->format->Rmask, src->format->Bmask,
        src->format->Gmask, src->format->Amask);

    SDL_Rect offset;
    offset.x = srcx;
    offset.y = srcy;
    offset.w = width;
    offset.h = height;

    SDL_BlitSurface(src, &offset, img, NULL);
    SDL_SetColorKey(img, SDL_SRCCOLORKEY,
                    SDL_MapRGB(img->format, 9 * 16 + 9, 255, 255));
    return img;
}

// Noticably different than the original
// NULL will be returned on error
SDL_Surface* LoadGraph(const char *filename)
{
    SDL_Surface *image = IMG_Load(filename);

    if (!image)
        std::cerr << "Error: Unable to load" << filename
                  << ": " << IMG_GetError() << std::endl;

    return image;
}

void PlaySoundMem(Mix_Chunk* s, int l)
{
    Mix_PlayChannel(-1, s, l);
}

Mix_Chunk* LoadSoundMem(const char* f)
{
    Mix_Chunk* s = Mix_LoadWAV(f);
    if (s)
        return s;

    std::cerr << "Error: Unable to load sound " << f << ": "
              << Mix_GetError() << std::endl;
    return NULL;
}

Mix_Music* LoadMusicMem(const char* f)
{
    Mix_Music* m = Mix_LoadMUS(f);
    if (m)
        return m;

    std::cerr << "Error: Unable to load music " << f << ": "
              << Mix_GetError() << std::endl;
    return NULL;
}
