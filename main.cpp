#include "DxLib.h"
#include "yuta_game.h"


/*===== 変数 =====*/
/*----- キー入力用 -----*/
int cflag = 0;
int rflag = 0;

/*----- シーン変換用 -----*/
int Scene = TitleLeady;
int GameScene = Exit;

/*----- 色 -----*/
int White = GetColor(255, 255, 255);
int Black = GetColor(0, 0, 0);

/*----- タイトル用 -----*/
int c_count = 0;

/*----- ゲーム関数処理用 -----*/
int EnemyX, EnemyY, EnemyW, EnemyH, EnemyMuki;
int PlayerX, PlayerY, PlayerW, PlayerH, PlayerMuki;
bool PlayerDamageFlag;
int PlayerDamageCounter;
int JumpPower, JumpPoint;
int HitPoint;
bool winflag;

/*----- 画像用 -----*/
int Player[2];
int Enemy[2];


/*===== メイン =====*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK), SetBackgroundColor(255, 255, 255);

	/*----- 動作処理用変数 -----*/
	int eflag = 0; //エンドフラグ

	Graph();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !eflag && !CheckHitKey(KEY_INPUT_ESCAPE)) {

		switch (Scene) {

		case TitleLeady: {
			c_count = 0;
			cflag = 0;

			Scene = Title;
			break;
		}

		case Title: {
			DrawFormatString(100, 100, Black, "Kuribo ga Mario kara nigeru Game");
			DrawFormatString(1180, 520, Black, "Hajimari");
			DrawFormatString(1180, 620, Black, "Owari");
			DrawFormatString(1170, 520+(100*c_count), Black, ">");

			if ((CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) && (cflag == 0)) {
				c_count = (c_count + 1) % 2;
				cflag = 1;
			}
			else if(!CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && (cflag == 1)) {
				cflag = 0;
			}

			if (CheckHitKey(KEY_INPUT_RETURN) && (rflag == 0)) {
				rflag = 1;
			}
			else if (!CheckHitKey(KEY_INPUT_RETURN) && (rflag == 1)) {
				switch (c_count) {
				case 0: {
					Scene = RuleLeady;
					break;
				}
				case 1: {
					Scene = EndLeady;
					break;
				}
				default: {
					eflag = 1;
					break;
				}
				}
				rflag = 0;
			}

			break;
		}

		case RuleLeady: {
			cflag = 0;
			Scene = Rule;
			break;
		}

		case Rule: {
			DrawFormatString(100, 100, Black, "Kuribo wo sousa suruyo!");
			DrawFormatString(100, 150, Black, "Jamp suru Mario kara gannbatte nigetene");
			DrawFormatString(100, 200, Black, "Mario ni taiatari suruto Win!");
			DrawFormatString(100, 250, Black, "2 kai Mario ni fumaretara Lose dayo");
			DrawFormatString(100, 620, Black, "Press Enter to start");

			if (CheckHitKey(KEY_INPUT_RETURN) && (rflag == 0)) {
				rflag = 1;
			}
			else if (!CheckHitKey(KEY_INPUT_RETURN) && (rflag == 1)) {
				Scene = GamePlay;
				GameScene = GameLeady;
				rflag = 0;
			}

			break;
		}

		case GamePlay: {
			GameMain();
			break;
		}

		case ResaltLeady: {
			Scene = Resalt;
			break;
		}

		case Resalt: {
			if (winflag) {
				DrawFormatString(100, 100, Black, "You are winner!");
			}
			else {
				DrawFormatString(100, 100, Black, "GameOver");
			}
			DrawFormatString(1080, 520, Black, "Mouikkai");
			DrawFormatString(1080, 620, Black, "Back To Title");
			DrawFormatString(1070, 520 + (100 * c_count), Black, ">");

			if ((CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) && (cflag == 0)) {
				c_count = (c_count + 1) % 2;
				cflag = 1;
			}
			else if (!CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && (cflag == 1)) {
				cflag = 0;
			}

			if (CheckHitKey(KEY_INPUT_RETURN) && (rflag == 0)) {
				rflag = 1;
			}
			else if (!CheckHitKey(KEY_INPUT_RETURN) && (rflag == 1)) {
				switch (c_count) {
				case 0: {
					Scene = RuleLeady;
					break;
				}
				case 1: {
					Scene = TitleLeady;
					break;
				}
				default: {
					eflag = 1;
					break;
				}
				}
				rflag = 0;
			}

			break;
		}

		case EndLeady: {
			Scene = End;
			break;
		}

		case End: {
			eflag = 1;
			break;
		}

		}

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;

}