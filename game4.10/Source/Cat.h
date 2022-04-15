#pragma once

namespace game_framework {

	class Cat
	{
	public:
		Cat();
		void OnMove(GAME_RUN_ID runId);				// �ھڥثe��������ܪ��A
		void OnShow(PICTURE_STATUS pictureStatus);	// �ھڥثe�����A�K�W�߿߹Ϥ�
		void Initialize();							// ��l�Ƴ]�w
		void LoadBitmap();

	protected:
		int CatPositionX;
		int CatPositionY;

		// �߿ߪ��Ϥ�
		CMovingBitmap Cat_Normal;
		CMovingBitmap Cat_Normal_BadlyHurt;
		CMovingBitmap Cat_Attack_1;
		CMovingBitmap Cat_Attack_2;
		CMovingBitmap Cat_Attack_3;
		CMovingBitmap Cat_Attack_4;
		CMovingBitmap Cat_BeingAttacked_Big;
		CMovingBitmap Cat_BeingAttacked_Little;
		CMovingBitmap Cat_BeingAttacked_Miss;
	};
}