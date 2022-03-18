#pragma once

namespace game_framework {

	class Dog
	{
	public:
		Dog();
		void OnMove(GAME_RUN_ID runId);			// �ھڥثe��������ܪ��A
		void OnShow(PICTURE_STATUS pictureStatus);	// �ھڥثe�����A�K�W���ĹϤ�
		void Initialize();				// ��l�Ƴ]�w
		void LoadBitmap();

	protected:
		int DogPositionX;
		int DogPositionY;

		// �߿ߪ��Ϥ�
		CMovingBitmap Dog_Normal;
		CMovingBitmap Dog_Normal_BadlyHurt;
		CMovingBitmap Dog_Attack_1;
		CMovingBitmap Dog_Attack_2;
		CMovingBitmap Dog_Attack_3;
		CMovingBitmap Dog_Attack_4;
		CMovingBitmap Dog_BeingAttacked_Big;
		CMovingBitmap Dog_BeingAttacked_Little;
		CMovingBitmap Dog_BeingAttacked_Miss;
	};
}