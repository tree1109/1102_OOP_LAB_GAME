#pragma once

namespace game_framework {

	class Cat
	{
	public:
		Cat();
		void OnMove(GAME_RUN_ID runId);				// 根據目前的條件改變狀態
		void OnShow(PICTURE_STATUS pictureStatus);	// 根據目前的狀態貼上貓貓圖片
		void Initialize();							// 初始化設定
		void LoadBitmap();

	protected:
		int CatPositionX;
		int CatPositionY;

		// 貓貓的圖片
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