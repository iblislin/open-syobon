#include "DxLib.h"

extern int ma, t, tt;
extern SDL_Surface *grap[161][8];
extern SDL_Surface *titleGraph;
int x1;
extern Mix_Music *otom[6];
extern Mix_Chunk *oto[19];

extern int anx[160], any[160];  /* x, y of enemy on graph */
extern int ne[40], nf[40]; /* x, y of background */

void loadSound(GameConfig* conf);

int loadg(GameConfig* conf)  /* load graph from res/ */
{
    std::map<std::string, SDL_Surface*> srcGraph;
    //プレイヤー
    srcGraph["player"] = LoadGraph("res/player.png");
    //ブロック
    srcGraph["block"] = LoadGraph("res/brock.png");
    //アイテム
    srcGraph["item"] = LoadGraph("res/item.png");
    //敵
    srcGraph["teki"] = LoadGraph("res/teki.png");
    //背景 background
    srcGraph["haikei"] = LoadGraph("res/haikei.png");
    //ブロック2
    srcGraph["block2"] = LoadGraph("res/brock2.png");
    //おまけ
    srcGraph["omake"] = LoadGraph("res/omake.png");
    //おまけ2
    srcGraph["omake2"] = LoadGraph("res/omake2.png");

    for (auto i=srcGraph.begin(); i!=srcGraph.end(); ++i)
        if (!(*i).second)
            return -1;  // graph failed to load

    //タイトル
    ::titleGraph  = LoadGraph("res/title.png");
    if (!titleGraph)
        return -1;

    //プレイヤー読み込み
    // player
    grap[40][0] = DerivationGraph(0, 0, 30, 36, srcGraph["player"]);
    grap[0][0]  = DerivationGraph(31 * 4, 0, 30, 36, srcGraph["player"]);
    grap[1][0]  = DerivationGraph(31 * 1, 0, 30, 36, srcGraph["player"]);
    grap[2][0]  = DerivationGraph(31 * 2, 0, 30, 36, srcGraph["player"]);
    grap[3][0]  = DerivationGraph(31 * 3, 0, 30, 36, srcGraph["player"]);
    grap[41][0] = DerivationGraph(50, 0, 51, 73, srcGraph["omake"]);

    // block
    //ブロック読み込み
    for (auto i=0; i<=6; i++)
    {
        grap[i][1]      = DerivationGraph(33 * i,  0, 30, 30, srcGraph["block"]);
        grap[i + 30][1] = DerivationGraph(33 * i, 33, 30, 30, srcGraph["block"]);
        grap[i + 60][1] = DerivationGraph(33 * i, 66, 30, 30, srcGraph["block"]);
        grap[i + 90][1] = DerivationGraph(33 * i, 99, 30, 30, srcGraph["block"]);
    }
    grap[8]  [1] = DerivationGraph(33 * 7,  0, 30, 30, srcGraph["block"]);
    grap[16] [1] = DerivationGraph(33 * 6,  0, 24, 27, srcGraph["item"]);
    grap[10] [1] = DerivationGraph(33 * 9,  0, 30, 30, srcGraph["block"]);
    grap[40] [1] = DerivationGraph(33 * 9, 33, 30, 30, srcGraph["block"]);
    grap[70] [1] = DerivationGraph(33 * 9, 66, 30, 30, srcGraph["block"]);
    grap[100][1] = DerivationGraph(33 * 9, 99, 30, 30, srcGraph["block"]);

    // block2
    //ブロック読み込み2
    for (auto i=0; i<=6; i++)
        grap[i][5] = DerivationGraph(33 * i, 0, 30, 30, srcGraph["block2"]);

    grap[10][5] = DerivationGraph(33 * 1, 33, 30, 30, srcGraph["block2"]);
    grap[11][5] = DerivationGraph(33 * 2, 33, 30, 30, srcGraph["block2"]);
    grap[12][5] = DerivationGraph(33 * 0, 66, 30, 30, srcGraph["block2"]);
    grap[13][5] = DerivationGraph(33 * 1, 66, 30, 30, srcGraph["block2"]);
    grap[14][5] = DerivationGraph(33 * 2, 66, 30, 30, srcGraph["block2"]);

    // item
    //アイテム読み込み
    for (auto i= 0; i<= 5; i++)
        grap[i][2] = DerivationGraph(33 * i, 0, 30, 30, srcGraph["item"]);

    // teki
    //敵キャラ読み込み
    grap[0]  [3] = DerivationGraph(33 * 0, 0, 30, 30, srcGraph["teki"]);
    grap[1]  [3] = DerivationGraph(33 * 1, 0, 30, 43, srcGraph["teki"]);
    grap[2]  [3] = DerivationGraph(33 * 2, 0, 30, 30, srcGraph["teki"]);
    grap[3]  [3] = DerivationGraph(33 * 3, 0, 30, 44, srcGraph["teki"]);
    grap[4]  [3] = DerivationGraph(33 * 4, 0, 33, 35, srcGraph["teki"]);
    grap[5]  [3] = DerivationGraph(0, 0, 37, 55, srcGraph["omake2"]);
    grap[6]  [3] = DerivationGraph(38 * 2, 0, 36, 50, srcGraph["omake2"]);
    grap[150][3] = DerivationGraph(38 * 2 + 37 * 2, 0, 36, 50, srcGraph["omake2"]);
    grap[7]  [3] = DerivationGraph(33 * 6 + 1, 0, 32, 32, srcGraph["teki"]);
    grap[8]  [3] = DerivationGraph(38 * 2 + 37 * 3, 0, 37, 47, srcGraph["omake2"]);
    grap[151][3] = DerivationGraph(38 * 3 + 37 * 3, 0, 37, 47, srcGraph["omake2"]);
    grap[9]  [3] = DerivationGraph(33 * 7 + 1, 0, 26, 30, srcGraph["teki"]);
    grap[10] [3] = DerivationGraph(214, 0, 46, 16, srcGraph["omake"]);

    //モララー
    grap[30][3] = DerivationGraph(0, 56, 30, 36, srcGraph["omake2"]);
    grap[155][3] = DerivationGraph(31 * 3, 56, 30, 36, srcGraph["omake2"]);
    grap[31][3] = DerivationGraph(50, 74, 49, 79, srcGraph["omake"]);

    grap[80][3] = DerivationGraph(151, 31, 70, 40, srcGraph["haikei"]);
    grap[81][3] = DerivationGraph(151, 72, 70, 40, srcGraph["haikei"]);
    grap[130][3] = DerivationGraph(151 + 71, 72, 70, 40, srcGraph["haikei"]);
    grap[82][3] = DerivationGraph(33 * 1, 0, 30, 30, srcGraph["block2"]);
    grap[83][3] = DerivationGraph(0, 0, 49, 48, srcGraph["omake"]);
    grap[84][3] = DerivationGraph(33 * 5 + 1, 0, 30, 30, srcGraph["teki"]);
    grap[86][3] = DerivationGraph(102, 66, 49, 59, srcGraph["omake"]);
    grap[152][3] = DerivationGraph(152, 66, 49, 59, srcGraph["omake"]);

    grap[90][3] = DerivationGraph(102, 0, 64, 63, srcGraph["omake"]);

    grap[100][3] = DerivationGraph(33 * 1, 0, 30, 30, srcGraph["item"]);
    grap[101][3] = DerivationGraph(33 * 7, 0, 30, 30, srcGraph["item"]);
    grap[102][3] = DerivationGraph(33 * 3, 0, 30, 30, srcGraph["item"]);

    grap[105][3] = DerivationGraph(33 * 5, 0, 30, 30, srcGraph["item"]);
    grap[110][3] = DerivationGraph(33 * 4, 0, 30, 30, srcGraph["item"]);


    //背景読み込み
    grap[0][4] = DerivationGraph(0, 0, 150, 90, srcGraph["haikei"]);
    grap[1][4] = DerivationGraph(151, 0, 65, 29, srcGraph["haikei"]);
    grap[2][4] = DerivationGraph(151, 31, 70, 40, srcGraph["haikei"]);
    grap[3][4] = DerivationGraph(0, 91, 100, 90, srcGraph["haikei"]);
    grap[4][4] = DerivationGraph(151, 113, 51, 29, srcGraph["haikei"]);
    grap[5][4] = DerivationGraph(222, 0, 28, 60, srcGraph["haikei"]);
    grap[6][4] = DerivationGraph(151, 143, 90, 40, srcGraph["haikei"]);
    grap[30][4] = DerivationGraph(293, 0, 149, 90, srcGraph["haikei"]);
    grap[31][4] = DerivationGraph(293, 92, 64, 29, srcGraph["haikei"]);

    //中間フラグ
    grap[20][4] = DerivationGraph(40, 182, 40, 60, srcGraph["haikei"]);

    //グラ
    grap[0][5] = DerivationGraph(167, 0, 45, 45, srcGraph["omake"]);

    // release srcGraph
    for (auto i=srcGraph.begin(); i!=srcGraph.end(); ++i)
        SDL_FreeSurface((*i).second);


    //敵サイズ収得
    for (auto i=0; i<=140; i++) {
        if (!grap[i][3])
            continue;

        anx[i] = grap[i][3]->w;
        any[i] = grap[i][3]->h;
        anx[i] *= 100;
        any[i] *= 100;
    }
    anx[79] = 120 * 100;
    any[79] = 15 * 100;
    anx[85] = 25 * 100;
    any[85] = 30 * 10 * 100;

    //背景サイズ収得
    for (auto t=0; t<40; t++) {
        if (!grap[t][4])
            continue;

        ne[t] = grap[t][4]->w;
        nf[t] = grap[t][4]->h;
    }

    loadSound(conf);

    return 0;
}

void loadSound(GameConfig* conf)
{
    if (!conf->sound)
        return;

    //ogg読み込み
    otom[1] = LoadMusicMem("bgm/field.ogg"); // volume: 50%
    otom[2] = LoadMusicMem("bgm/dungeon.ogg"); // volume: 40%
    otom[3] = LoadMusicMem("bgm/star4.ogg"); // volume: 50%
    otom[4] = LoadMusicMem("bgm/castle.ogg"); // volume: 50%
    otom[5] = LoadMusicMem("bgm/puyo.ogg"); // volume: 50%

    oto[1]  = LoadSoundMem("se/jump.ogg");
    oto[2]  = LoadSoundMem("se/brockcoin.ogg");
    oto[3]  = LoadSoundMem("se/brockbreak.ogg");
    oto[4]  = LoadSoundMem("se/coin.ogg");
    oto[5]  = LoadSoundMem("se/humi.ogg");
    oto[6]  = LoadSoundMem("se/koura.ogg");
    oto[7]  = LoadSoundMem("se/dokan.ogg");
    oto[8]  = LoadSoundMem("se/brockkinoko.ogg");
    oto[9]  = LoadSoundMem("se/powerup.ogg");
    oto[10] = LoadSoundMem("se/kirra.ogg");
    oto[11] = LoadSoundMem("se/goal.ogg");
    oto[12] = LoadSoundMem("se/death.ogg");
    oto[13] = LoadSoundMem("se/Pswitch.ogg");
    oto[14] = LoadSoundMem("se/jumpBlock.ogg");
    oto[15] = LoadSoundMem("se/hintBlock.ogg");
    oto[16] = LoadSoundMem("se/4-clear.ogg");
    oto[17] = LoadSoundMem("se/allclear.ogg");
    oto[18] = LoadSoundMem("se/tekifire.ogg");
}
