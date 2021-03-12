#pragma once


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GROUND 500

/*===== 列挙体 =====*/
/*----- メイン用 -----*/
typedef enum {
	TitleLeady,
	Title,
	RuleLeady,
	Rule,
	GamePlay,
	ResaltLeady,
	Resalt,
	EndLeady,
	End,
}eScene;

/*----- ゲーム用 -----*/
typedef enum {
	Exit,
	GameLeady,
	Game,
}eGame;


/*===== 変数 =====*/
/*----- シーン変換用 -----*/
extern int Scene;
extern int GameScene;

/*----- 色 -----*/
extern int White;
extern int Black;

/*----- ゲーム関数処理用 -----*/
extern int EnemyX, EnemyY, EnemyW, EnemyH, EnemyMuki;
extern int PlayerX, PlayerY, PlayerW, PlayerH;
extern bool PlayerDamageFlag;
extern int PlayerDamageCounter;
extern int PlayerMoveW, EnemyMoveW;
extern int JumpPower, JumpPoint;
extern int HitPoint;
extern bool winflag;

/*----- 画像用 -----*/
extern int Player[2];
extern int Enemy[2];


/*===== 関数 =====*/
void GameMain();
void Graph();
int SetJumpPoint(int ex, int ew);
bool HitCheck(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh);