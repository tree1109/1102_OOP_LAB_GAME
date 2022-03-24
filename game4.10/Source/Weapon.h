#pragma once

namespace game_framework {

	class Weapon
	{
	public:
		Weapon();
		int  GetX1();					// ���Y�����W�� x �y��
		int  GetY1();					// ���Y�����W�� y �y��
		void Initialize();				// �]�w
		void OnMove(GAME_RUN_ID runId);					// �ھڥثe��������ܪ��A
		void OnShow(GAME_RUN_ID runId);					// �ھڥثe�����A�K�W�߿߹Ϥ�
		void LoadBitmap();
		void SetPower(int powerX, int powerY);
		void SetPosition(int x, int y);
		void DogFire(int timer);
		void CatFire(int timer);
		bool isHitGround();

	protected:
		// �Z�����Y���y��
		int weaponPositionX;
		int weaponPositionY;

		int velocityX;
		int velocityY;

		CMovingBitmap Cat_Weapon;
		CMovingBitmap Dog_Weapon;
	};
}