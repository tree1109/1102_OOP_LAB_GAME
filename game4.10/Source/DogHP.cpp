#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "GAMEID.h"
#include "DogHP.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// DogHP: DogHP class
	/////////////////////////////////////////////////////////////////////////////

	DogHP::DogHP()
	{
		HealthPoint = 100;
	}

	void DogHP::Initialize()
	{
		HealthPoint = 100;
		for (int i = 0; i < 464; i++) {
			DogHealthPointPicture[i].SetTopLeft(766 + i, 56);
		}
	}

	void DogHP::LoadBitmap()
	{
		for (int i = 0; i < 464; i++) {
			DogHealthPointPicture[i].LoadBitmap("GamePicture/GameRun/Dog/HP_semicircle.bmp", RGB(180, 0, 255));
		}
	}

	void DogHP::OnShow()
	{
		for (int i = 0; i < (HealthPoint/100) * 464; i++) {
			DogHealthPointPicture[i].ShowBitmap();
		}
	}

	void DogHP::AddHP(int hp)
	{
		HealthPoint += hp;
		if (HealthPoint > 100) {
			HealthPoint = 100;
		}
	}

	void DogHP::SubHP(int hp)
	{
		HealthPoint -= hp;
		if (HealthPoint < 0) {
			HealthPoint = 0;
		}
	}

	bool DogHP::isDead()
	{
		return HealthPoint == 0;
	}

}