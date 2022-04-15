#pragma once

namespace game_framework {

	class CatHP
	{
	public:
		CatHP();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void AddHP(int hp);
		void SubHP(int hp);
		bool isDead();

	protected:
		int HealthPoint;

		// 貓咪血量條圖片
		CMovingBitmap CatHealthPointPicture[469];
	};
}