#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "GAMEID.h"
#include "Weapon.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Weapon: Weapon class
	/////////////////////////////////////////////////////////////////////////////

	Weapon::Weapon()
	{
		weaponPositionX = 0;
		weaponPositionY = 559;
	}

	int Weapon::GetX1()
	{
		return weaponPositionX;
	}

	int Weapon::GetY1()
	{
		return weaponPositionY;
	}

	void Weapon::Initialize()
	{
		LoadBitmap();

		Cat_Weapon.SetTopLeft(0, 0);
		Dog_Weapon.SetTopLeft(0, 0);
	}

	void Weapon::LoadBitmap()
	{
		Cat_Weapon.LoadBitmap("GamePicture/GameRun/Cat/Weapon.bmp", RGB(180, 0, 255));
		Dog_Weapon.LoadBitmap("GamePicture/GameRun/Dog/Weapon.bmp", RGB(180, 0, 255));
		
	}

	void Weapon::OnMove(GAME_RUN_ID runId)
	{
		// 根據目前的條件改變狀態
		if (runId == CAT_ATTACK_FIRE) {
			
		}
		else if (runId == DOG_ATTACK_FIRE) {
			
		}
	}

	void Weapon::OnShow(GAME_RUN_ID runId)
	{
		// 根據狀態顯示貓或狗的武器
		if (runId == CAT_ATTACK_FIRE) {
			Cat_Weapon.ShowBitmap();
		}
		else if (runId == DOG_ATTACK_FIRE) {
			Dog_Weapon.ShowBitmap();
		}
	}

	void Weapon::SetPower(int power)
	{
		velocityX = power;
		velocityY = 0-power;
	}

	void Weapon::SetPosition(int x, int y)
	{
		weaponPositionX = x;
		weaponPositionY = y;
	}
}