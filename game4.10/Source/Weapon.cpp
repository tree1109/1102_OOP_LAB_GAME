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

	int Weapon::GetX_LT(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 14;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionX + 7;
	}

	int Weapon::GetY_LT(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 3;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionY + 21;
	}

	int Weapon::GetX_RB(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 78;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionX + 80;
	}

	int Weapon::GetY_RB(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 79;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionY + 65;
	}

	void Weapon::Initialize()
	{
		SetPower(0, 0);
		SetPosition(0, 0);
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
		if (runId == CAT_ATTACK_FIRE || runId == DOG_ATTACK_FIRE) {
			SetPower(velocityX, velocityY + 10); // 10 是重力
			SetPosition(weaponPositionX + velocityX, weaponPositionY + velocityY);
		}

		// 根據目前的條件改變狀態
		if (runId == CAT_ATTACK_FIRE) {
			Cat_Weapon.SetTopLeft(weaponPositionX, weaponPositionY);
		}
		else if (runId == DOG_ATTACK_FIRE) {
			Dog_Weapon.SetTopLeft(weaponPositionX, weaponPositionY);
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

	void Weapon::SetPower(int powerX, int powerY)
	{
		velocityX = powerX;
		velocityY = powerY;
	}

	void Weapon::SetPosition(int x, int y)
	{
		weaponPositionX = x;
		weaponPositionY = y;
	}

	void Weapon::DogFire(int timer)
	{
		int power = timer * 5;
		SetPosition(1088, 693);		// 骨頭起始發射位置
		SetPower(-power * 4 / 5, -power);	// 往左上角發射
	}

	void Weapon::CatFire(int timer)
	{
		int power = timer * 5;
		SetPosition(182, 588);		// 骨頭起始發射位置
		SetPower(power * 4 / 5, -power);	// 往左上角發射
	}

	bool Weapon::isHitGround()
	{
		// Y值大於814時代表落地
		return weaponPositionY > 814;
	}

	int Weapon::isHitCat()
	{
		// 0:miss, 1:lightly attacked, 2:heavly attacked


		return 0;
	}

	int Weapon::isHitDog()
	{
		return 0;
	}
}