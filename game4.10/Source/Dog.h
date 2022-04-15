#pragma once

namespace game_framework {

	class Dog
	{
	public:
		Dog();
		void OnMove(GAME_RUN_ID runId);			// 根據目前的條件改變狀態
		void OnShow(PICTURE_STATUS pictureStatus);	// 根據目前的狀態貼上狗勾圖片
		void Initialize();				// 初始化設定
		void LoadBitmap();

	protected:
		int DogPositionX;
		int DogPositionY;

		// 貓貓的圖片
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