#pragma once

namespace game_framework {

	class Weapon
	{
	public:
		Weapon();
		int  GetX_LT(GAME_RUN_ID runId);					// ���Y�����W�� x �y��
		int  GetY_LT(GAME_RUN_ID runId);					// ���Y�����W�� y �y��
		int  GetX_RB(GAME_RUN_ID runId);					// ���Y���k�U�� x �y��
		int  GetY_RB(GAME_RUN_ID runId);					// ���Y���k�U�� y �y��
		void Initialize();				// �]�w
		void OnMove(GAME_RUN_ID runId);					// �ھڥثe��������ܪ��A
		void OnShow(GAME_RUN_ID runId);					// �ھڥثe�����A�K�W�߿߹Ϥ�
		void LoadBitmap();
		void SetPower(int powerX, int powerY);
		void SetPosition(int x, int y);
		void DogFire(int timer);
		void CatFire(int timer);
		bool isHitGround();
		int isHitCat();
		int isHitDog();
		void setSize(double);

	protected:
		// �Z�����Y���y��
		int weaponPositionX;
		int weaponPositionY;

		int velocityX;
		int velocityY;

		CMovingBitmap Cat_Weapon;
		CMovingBitmap Dog_Weapon;

		bool weaponSizeFactor;
	};
}