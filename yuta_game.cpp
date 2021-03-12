#include "DxLib.h"
#include "yuta_game.h"


/*----- 移動幅設定 -----*/
int PlayerMoveW = SCREEN_WIDTH / 320;
int EnemyMoveW = SCREEN_WIDTH / 320;


void GameMain() {

	switch (GameScene) {

	case Exit: {
		break;
	}

	case GameLeady: {
		/*----- 画像サイズを取得 -----*/
		// プレイヤー
		GetGraphSize(Player[0], &PlayerW, &PlayerH);
		// エネミー
		GetGraphSize(Enemy[0], &EnemyW, &EnemyH);

		/*----- 表示座標セット -----*/
		// プレイヤー
		PlayerX = 300, PlayerY = (GROUND - PlayerH);
		// エネミー
		EnemyX = 0, EnemyY = 50;

		/*----- 処理変数を初期化 -----*/
		// プレイヤーの表示グラをノーマルに設定
		PlayerDamageFlag = false;
		// エネミーの移動方向をセット
		EnemyMuki = 1;
		// 加速度リセット
		JumpPower = 0;
		// ジャンプ位置リセット
		JumpPoint = 64;
		// 体力をリセット
		HitPoint = 2;
		// 勝利フラグリセット
		winflag = false;


		GameScene = Game;
		break;
	}

	case Game: {
		/*===== 背景関連 =====*/
		/*----- 地面描画 -----*/
		// 草
		DrawBox(0, GROUND, SCREEN_WIDTH, GROUND + 32, GetColor(37, 188, 0), TRUE);
		// 土
		DrawBox(0, GROUND + 32, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(162, 87, 32), TRUE);

		/*===== プレイヤー関連 =====*/
		/*----- 操作可能範囲設定 -----*/
		if (PlayerX < 0) {
			PlayerX = 0;
		}
		if (PlayerX > SCREEN_WIDTH - PlayerW) {
			PlayerX = SCREEN_WIDTH - PlayerW;
		}

		/*----- ダメージ処理 -----*/
		// ダメージ時
		if (PlayerDamageFlag) {
			// グラ表示
			DrawGraph(PlayerX, PlayerY, Player[1], TRUE);
			// 時間をカウント
			PlayerDamageCounter++;
			// 時間経過後
			if (PlayerDamageCounter == 30){
				// ダメージフラグをオフ
				PlayerDamageFlag = false;
				// 時間リセット
				PlayerDamageCounter = 0;
				// HP減少
				HitPoint--;
			}
		}
		// 通常時
		else {
			// グラ表示
			DrawGraph(PlayerX, PlayerY, Player[0], TRUE);
			// 操作ルーチン
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				PlayerX -= PlayerMoveW;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
				PlayerX += PlayerMoveW;
			}
		}


		/*===== エネミー関連 =====*/
		// 方向フラグにより挙動変化
		if (EnemyMuki == 1) {
			if (EnemyY < (GROUND - PlayerH)) {
				DrawGraph(EnemyX, EnemyY, Enemy[1], TRUE);
			}
			else {
				DrawGraph(EnemyX, EnemyY, Enemy[0], TRUE);
			}
			EnemyX += EnemyMoveW;
		}
		else if (EnemyMuki == 0) {
			if (EnemyY < (GROUND - PlayerH)) {
				DrawTurnGraph(EnemyX, EnemyY, Enemy[1], TRUE);
			}
			else {
				DrawTurnGraph(EnemyX, EnemyY, Enemy[0], TRUE);
			}
			EnemyX -= EnemyMoveW;
		}

		/*----- ジャンプ制御 -----*/
		// 落下加速度追加
		JumpPower -= 2;
		// 落下処理
		EnemyY -= JumpPower;
		// 地面にめり込んだ時に加速度を消す
		if (EnemyY > (GROUND - EnemyH)){
			EnemyY = (GROUND - EnemyH);
			JumpPower = 0;
			JumpPoint = SetJumpPoint(EnemyX, EnemyW);
		}
		// ジャンプポイントで地面についていたらジャンプ
		if ((EnemyX % JumpPoint == 0) && (EnemyY == (GROUND - PlayerH))){
			JumpPower = 40;
		}

		/*----- 動作範囲制御 -----*/
		if (EnemyX > SCREEN_WIDTH - EnemyW){
			EnemyX = SCREEN_WIDTH - EnemyW;
			EnemyMuki = 0;
		}
		if (EnemyX < 0){
			EnemyX = 0;
			EnemyMuki = 1;
		}


		/*===== 当たり判定 =====*/
		if (HitCheck(PlayerX, PlayerY, PlayerW, PlayerH, EnemyX, EnemyY, EnemyW, EnemyH)) {
			// 上から踏まれたとき
			if (JumpPower < 0) {
				PlayerDamageFlag = true;
				PlayerDamageCounter = 0;
				JumpPower = 30;
			}
			// 横からの時
			else if(!PlayerDamageFlag){
				winflag = true;
				Scene = ResaltLeady;
			}
		}


		/*===== 終了判定 =====*/
		if (HitPoint == 0) {
			winflag = false;
			Scene = ResaltLeady;
		}

		break;
	}

	}

}

void Graph() {
	Player[0] = LoadGraph("Graph/Player_Normal.png");
	Player[1] = LoadGraph("Graph/Player_Angry.png");
	Enemy[0] = LoadGraph("Graph/Enemy_Normal.png");
	Enemy[1] = LoadGraph("Graph/Enemy_Jump.png");
}


int SetJumpPoint(int ex, int ew) {
	int jp = ex + (GetRand(20) * EnemyMoveW);
	if (SCREEN_WIDTH <= jp) {
		return (2 * SCREEN_WIDTH - jp);
	}
	else {
		return jp;
	}
}


bool HitCheck(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh) {
	if (((px <= (ex + ew)) && (ex <= (px + pw))) && ((py <= (ey + eh)) && (ey <= (py + ph)))) {
		return true;
	}
	else {
		return false;
	}
}