#include "DxLib.h"
#include "yuta_game.h"


/*----- �ړ����ݒ� -----*/
int PlayerMoveW = SCREEN_WIDTH / 320;
int EnemyMoveW = SCREEN_WIDTH / 320;


void GameMain() {

	switch (GameScene) {

	case Exit: {
		break;
	}

	case GameLeady: {
		/*----- �摜�T�C�Y���擾 -----*/
		// �v���C���[
		GetGraphSize(Player[0], &PlayerW, &PlayerH);
		// �G�l�~�[
		GetGraphSize(Enemy[0], &EnemyW, &EnemyH);

		/*----- �\�����W�Z�b�g -----*/
		// �v���C���[
		PlayerX = 300, PlayerY = (GROUND - PlayerH);
		// �G�l�~�[
		EnemyX = 0, EnemyY = 50;

		/*----- �����ϐ��������� -----*/
		// �v���C���[�̕\���O�����m�[�}���ɐݒ�
		PlayerDamageFlag = false;
		// �G�l�~�[�̈ړ��������Z�b�g
		EnemyMuki = 1;
		// �����x���Z�b�g
		JumpPower = 0;
		// �W�����v�ʒu���Z�b�g
		JumpPoint = 64;
		// �̗͂����Z�b�g
		HitPoint = 2;
		// �����t���O���Z�b�g
		winflag = false;


		GameScene = Game;
		break;
	}

	case Game: {
		/*===== �w�i�֘A =====*/
		/*----- �n�ʕ`�� -----*/
		// ��
		DrawBox(0, GROUND, SCREEN_WIDTH, GROUND + 32, GetColor(37, 188, 0), TRUE);
		// �y
		DrawBox(0, GROUND + 32, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(162, 87, 32), TRUE);

		/*===== �v���C���[�֘A =====*/
		/*----- ����\�͈͐ݒ� -----*/
		if (PlayerX < 0) {
			PlayerX = 0;
		}
		if (PlayerX > SCREEN_WIDTH - PlayerW) {
			PlayerX = SCREEN_WIDTH - PlayerW;
		}

		/*----- �_���[�W���� -----*/
		// �_���[�W��
		if (PlayerDamageFlag) {
			// �O���\��
			DrawGraph(PlayerX, PlayerY, Player[1], TRUE);
			// ���Ԃ��J�E���g
			PlayerDamageCounter++;
			// ���Ԍo�ߌ�
			if (PlayerDamageCounter == 30){
				// �_���[�W�t���O���I�t
				PlayerDamageFlag = false;
				// ���ԃ��Z�b�g
				PlayerDamageCounter = 0;
				// HP����
				HitPoint--;
			}
		}
		// �ʏ펞
		else {
			// �O���\��
			DrawGraph(PlayerX, PlayerY, Player[0], TRUE);
			// ���샋�[�`��
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				PlayerX -= PlayerMoveW;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
				PlayerX += PlayerMoveW;
			}
		}


		/*===== �G�l�~�[�֘A =====*/
		// �����t���O�ɂ�苓���ω�
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

		/*----- �W�����v���� -----*/
		// ���������x�ǉ�
		JumpPower -= 2;
		// ��������
		EnemyY -= JumpPower;
		// �n�ʂɂ߂荞�񂾎��ɉ����x������
		if (EnemyY > (GROUND - EnemyH)){
			EnemyY = (GROUND - EnemyH);
			JumpPower = 0;
			JumpPoint = SetJumpPoint(EnemyX, EnemyW);
		}
		// �W�����v�|�C���g�Œn�ʂɂ��Ă�����W�����v
		if ((EnemyX % JumpPoint == 0) && (EnemyY == (GROUND - PlayerH))){
			JumpPower = 40;
		}

		/*----- ����͈͐��� -----*/
		if (EnemyX > SCREEN_WIDTH - EnemyW){
			EnemyX = SCREEN_WIDTH - EnemyW;
			EnemyMuki = 0;
		}
		if (EnemyX < 0){
			EnemyX = 0;
			EnemyMuki = 1;
		}


		/*===== �����蔻�� =====*/
		if (HitCheck(PlayerX, PlayerY, PlayerW, PlayerH, EnemyX, EnemyY, EnemyW, EnemyH)) {
			// �ォ�瓥�܂ꂽ�Ƃ�
			if (JumpPower < 0) {
				PlayerDamageFlag = true;
				PlayerDamageCounter = 0;
				JumpPower = 30;
			}
			// ������̎�
			else if(!PlayerDamageFlag){
				winflag = true;
				Scene = ResaltLeady;
			}
		}


		/*===== �I������ =====*/
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