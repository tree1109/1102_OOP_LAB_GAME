#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "GAMEID.h"
#include "CatHP.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CatHP: CatHP class
	/////////////////////////////////////////////////////////////////////////////

	CatHP::CatHP()
	{
		HealthPoint = 100;
	}

	void CatHP::Initialize()
	{
		HealthPoint = 100;
		for (int i = 0; i < 464; i++) {
			CatHealthPointPicture[i].SetTopLeft(561 - i, 57);
		}
	}

	void CatHP::LoadBitmap()
	{
		for (int i = 0; i < 464; i++) {
			CatHealthPointPicture[i].LoadBitmap("GamePicture/GameRun/Cat/HP_semicircle.bmp", RGB(180, 0, 255));
		}
	}

	void CatHP::OnShow()
	{
		for (int i = 0; i < (HealthPoint/100) * 464; i++) {
			CatHealthPointPicture[i].ShowBitmap();
		}
	}

	void CatHP::AddHP(int hp)
	{
		HealthPoint += hp;
		if (HealthPoint > 100) {
			HealthPoint = 100;
		}
	}

	void CatHP::SubHP(int hp)
	{
		HealthPoint -= hp;
		if (HealthPoint < 0) {
			HealthPoint = 0;
		}
	}

	bool CatHP::isDead()
	{
		return HealthPoint == 0;
	}

}