#pragma once

namespace game_framework {

	class Weapon
	{
	public:
		Weapon();
		int  GetX1();					// 投擲物左上角 x 座標
		int  GetY1();					// 投擲物左上角 y 座標
		void Initialize();				// 設定
		void OnMove(GAME_RUN_ID runId);					// 根據目前的條件改變狀態
		void OnShow(GAME_RUN_ID runId);					// 根據目前的狀態貼上貓貓圖片
		void LoadBitmap();

	protected:
		// 武器投擲物座標
		int weaponPositionX;
		int weaponPositionY;

		CMovingBitmap Cat_Weapon;
		CMovingBitmap Dog_Weapon;
	};
}