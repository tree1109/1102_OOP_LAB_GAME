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

	protected:
		int HealthPoint;

		// �߫}��q���Ϥ�
		CMovingBitmap DogHealthPointPicture[467];
	};
}