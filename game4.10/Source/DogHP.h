#pragma once

namespace game_framework {

	class DogHP
	{
	public:
		DogHP();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void AddHP(int hp);
		void SubHP(int hp);
		bool isDead();
		void Poisoning();
		void SetPoisoning();

	protected:
		int HealthPoint;
		int poisoningRound;	// 紀錄中毒剩餘回合數，0代表沒有中毒

		// 貓咪血量條圖片
		CMovingBitmap DogHealthPointPicture[467];
	};
}