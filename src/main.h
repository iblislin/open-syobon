#include "GameConfig.h"
#include "DxLib.h"
#include "erl_ai.h"

using namespace std;


int loadg(GameConfig* conf);
void parseArgs(int argc, char* argv[], GameConfig* conf);

//プログラム中
//main-10
//タイトル-100

//: This is unexcusable. How could someone in their right mind define
//: a variable called 'main'!?
//: The new define is after the main method
int maintm = 0;

//ステージ
int stagecolor = 1;

// クイック
// quick
int fast = 1;

//トラップ表示
int trap = 1;

//中間ゲート
int tyuukan = 0;


//ステージ読み込みループ(いじらない)
int stagerr, stagepoint;

//ステージスイッチ
int stageonoff = 0;


//メインプログラム
void Mainprogram(GameConfig* conf);
void renderMain(GameConfig* conf);

void renderLivePanel(GameConfig* conf);
void renderStaffRoll(GameConfig* conf);
void renderStage(GameConfig* conf);
void renderTitle(GameConfig* conf);


// helper functions
int get_fps();


//サブクラス
//(ウエイト系
void wait(Uint32 stime, Uint32 etime, int frame_time);
int rand(int Rand);
#define end() exit(0)

//描画
Uint32 color;
Uint32 gfxcolor;
void setfont(int a);
void setcolor(int red, int green, int blue);
void setc0();
void setc1();
void drawpixel(int a, int b);
void drawline(int a, int b, int c, int d);
void drawrect(int a, int b, int c, int d);
void fillrect(int a, int b, int c, int d);
void drawarc(int a, int b, int c, int d);
void fillarc(int a, int b, int c, int d);
void FillScreen();
SDL_Surface *grap[161][8] = {};
SDL_Surface *titleGraph;
int mirror;
void drawimage(SDL_Surface * mx, int a, int b);
void drawimage(SDL_Surface * mx, int a, int b, int c, int d, int e, int f);
void setre();
void setre2();
void setno();
Mix_Music *otom[6] = {};
Mix_Chunk *oto[19] = {};
void ot(Mix_Chunk * x, bool enableFlag);
void chBgm(Mix_Music* music, int volume=50);

//文字
void str(string c, int a, int b);


//)

void stagecls();
void stage(GameConfig* conf);
void stagep(GameConfig* conf);
void enterLivePanel(GameConfig* conf);
void enterStaffRoll(GameConfig* conf);
void enterStage(GameConfig* conf);
void enterTitle(GameConfig* conf);


//ループ
int t, tt, t1, t2, t3, t4;

//キーコンフィグ
int key, keytm;

//三角関数
double pai = 3.1415926535;


//地面
#define smax 31
int sx, sco;
int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax],
    sr[smax];
int sgtype[smax];



//プレイヤー
int mainmsgtype;
int ma, mb; // player location on the screen (ma, mb) is (x, y)
int mnobia, mnobib;
int mhp; // player hp, mhp > 0 denote alive
int mc, md; // the acceleration of player (a_x, a_y)
int macttype, atkon, atktm, mactsok, msstar, mactp, mact;

int mtype, mxtype, mtm, mzz;
int mzimen, mrzimen, mkasok, mmuki, mmukitm, mjumptm, mkeytm, mcleartm;
int mmutekitm, mmutekion;
int mztm, mztype;
int actaon[7];
//メッセージ
int mmsgtm, mmsgtype;

int mascrollmax = 21000;	//9000




//ブロック
void tyobi(int x, int y, int type);
void brockbreak(int t);
#define tmax 641
int tco;
int ta[tmax], tb[tmax], tc[tmax], td[tmax], thp[tmax], ttype[tmax];
int titem[tmax], txtype[tmax];

//メッセージブロック
int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;
void ttmsg();
void txmsg(string x, int a);
void setfont(int x, int y);

//効果を持たないグラ
void eyobi(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia,
	   int xnobib, int xgtype, int xtm);
#define emax 201
int eco;
int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
int ee[emax], ef[emax], etm[emax];
int egtype[emax];



//敵キャラ
void ayobi(GameConfig* conf, int xa, int xb, int xc, int xd, int xnotm, int xtype,
	   int xxtype);
void tekizimen(GameConfig*);
#define amax 24
int aco;
int aa[amax], ab[amax], anobia[amax], anobib[amax], ac[amax], ad[amax];
int ae[amax], af[amax], abrocktm[amax];
int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
int atype[amax], axtype[amax], amuki[amax], ahp[amax];
int anotm[amax], anx[160] = {} /* enemy x on graph */, any[160] = {};
int atm[amax], a2tm[amax];
int amsgtm[amax], amsgtype[amax];

//敵出現
#define bmax 81
int bco;
int ba[bmax], bb[bmax], btm[bmax];
int btype[bmax], bxtype[bmax], bz[bmax];


//背景
#define nmax 41
int nxxmax, nco;
int na[nmax], nb[nmax], nc[nmax], nd[nmax], ntype[nmax];
int ne[nmax] = {},
    nf[nmax] = {},
    ng[nmax], nx[nmax];


//リフト
#define srmax 21
int srco;
int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
int srmuki[srmax], sron[srmax], sree[srmax];
int srsok[srmax], srmovep[srmax], srmove[srmax];





//スクロール範囲
int fx = 0, fy = 0, fzx, fzy, scrollx, scrolly;
//全体のポイント

//: "fma" already exists, so call it something else and add a define
int fmaZ = 0, fmb = 0;
#define fma fmaZ

//強制スクロール
int kscroll = 0;
//画面サイズ(ファミコンサイズ×2)(256-224)
int fxmax = 48000, fymax = 42000;



//ステージ
byte stagedate[17][2001];

//画面黒
int blacktm = 1, blackx = 0;



//自由な値
int xx[91];
double xd[11];
string xs[31];


// function prototypes
void deinit();
