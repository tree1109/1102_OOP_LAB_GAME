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
		int poisoningRound;	// �������r�Ѿl�^�X�ơA0�N��S�����r

		// �߫}��q���Ϥ�
		CMovingBitmap DogHealthPointPicture[467];
	};
}