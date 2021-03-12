#pragma once


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GROUND 500

/*===== �񋓑� =====*/
/*----- ���C���p -----*/
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

/*----- �Q�[���p -----*/
typedef enum {
	Exit,
	GameLeady,
	Game,
}eGame;


/*===== �ϐ� =====*/
/*----- �V�[���ϊ��p -----*/
extern int Scene;
extern int GameScene;

/*----- �F -----*/
extern int White;
extern int Black;

/*----- �Q�[���֐������p -----*/
extern int EnemyX, EnemyY, EnemyW, EnemyH, EnemyMuki;
extern int PlayerX, PlayerY, PlayerW, PlayerH;
extern bool PlayerDamageFlag;
extern int PlayerDamageCounter;
extern int PlayerMoveW, EnemyMoveW;
extern int JumpPower, JumpPoint;
extern int HitPoint;
extern bool winflag;

/*----- �摜�p -----*/
extern int Player[2];
extern int Enemy[2];


/*===== �֐� =====*/
void GameMain();
void Graph();
int SetJumpPoint(int ex, int ew);
bool HitCheck(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh);