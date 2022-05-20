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
		weaponSizeFactor = 1;
		isNormalWeapon = true;
	}

	int Weapon::GetX_LT(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 14 * (int)weaponSizeFactor;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionX + 7 * (int)weaponSizeFactor;
		else
			return -1;
	}

	int Weapon::GetY_LT(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionY + 3 * (int)weaponSizeFactor;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionY + 21 * (int)weaponSizeFactor;
		else
			return -1;
	}

	int Weapon::GetX_RB(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionX + 78 * (int)weaponSizeFactor;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionX + 80 * (int)weaponSizeFactor;
		else
			return -1;
	}

	int Weapon::GetY_RB(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE)
			return weaponPositionY + 79 * (int)weaponSizeFactor;
		else if (runId == DOG_ATTACK_FIRE)
			return weaponPositionY + 65 * (int)weaponSizeFactor;
		else
			return -1;
	}

	void Weapon::Initialize()
	{
		SetPower(0, 0);
		SetPosition(0, 0);
		Cat_Weapon.SetTopLeft(0, 0);
		Dog_Weapon.SetTopLeft(0, 0);
		Cat_PoisionWeapon.SetTopLeft(0, 0);
		Dog_PoisionWeapon.SetTopLeft(0, 0);
		isNormalWeapon = true;
	}

	void Weapon::LoadBitmap()
	{
		Cat_Weapon.LoadBitmap("GamePicture/GameRun/Cat/Weapon.bmp", RGB(180, 0, 255));
		Dog_Weapon.LoadBitmap("GamePicture/GameRun/Dog/Weapon.bmp", RGB(180, 0, 255));
		Cat_PoisionWeapon.LoadBitmap("GamePicture/GameRun/Cat/PoisionWeapon.bmp", RGB(180, 0, 255));
		Dog_PoisionWeapon.LoadBitmap("GamePicture/GameRun/Dog/PoisionWeapon.bmp", RGB(180, 0, 255));
	}

	void Weapon::OnMove(GAME_RUN_ID runId)
	{
		if (runId == CAT_ATTACK_FIRE || runId == DOG_ATTACK_FIRE) {
			SetPower(velocityX, velocityY + 10); // 10 是重力
			SetPosition(weaponPositionX + velocityX, weaponPositionY + velocityY);
		}

		if (isNormalWeapon) {
			// 根據目前的條件改變狀態
			if (runId == CAT_ATTACK_FIRE) {
				Cat_Weapon.SetTopLeft(weaponPositionX, weaponPositionY);
			}
			else if (runId == DOG_ATTACK_FIRE) {
				Dog_Weapon.SetTopLeft(weaponPositionX, weaponPositionY);
			}
		}
		else {
			if (runId == CAT_ATTACK_FIRE) {
				Cat_PoisionWeapon.SetTopLeft(weaponPositionX, weaponPositionY);
			}
			else if (runId == DOG_ATTACK_FIRE) {
				Dog_PoisionWeapon.SetTopLeft(weaponPositionX, weaponPositionY);
			}
		}

	}

	void Weapon::OnShow(GAME_RUN_ID runId)
	{
		if (isNormalWeapon) {
			// 根據狀態顯示貓或狗的武器
			if (runId == CAT_ATTACK_FIRE) {
				Cat_Weapon.ShowBitmap(weaponSizeFactor);
			}
			else if (runId == DOG_ATTACK_FIRE) {
				Dog_Weapon.ShowBitmap(weaponSizeFactor);
			}
		}
		else {
			if (runId == CAT_ATTACK_FIRE) {
				Cat_PoisionWeapon.ShowBitmap(weaponSizeFactor);
			}
			else if (runId == DOG_ATTACK_FIRE) {
				Dog_PoisionWeapon.ShowBitmap(weaponSizeFactor);
			}
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
		return weaponPositionY > 814 || GetX_LT(CAT_ATTACK_FIRE) > 1333 || GetX_RB(DOG_ATTACK_FIRE) < 0;
	}

	int Weapon::isHitCat()
	{
		// -1:too far, 0:miss, 1:lightly attacked, 2:heavly attacked]
		// 判斷武器是不是飛到一半
		if (GetX_LT(DOG_ATTACK_FIRE) < 1333 / 2 && GetY_RB(DOG_ATTACK_FIRE) > 586) {
			// 判斷武器是不是完全在重擊區或擦傷區或是miss
			if (GetX_LT(DOG_ATTACK_FIRE) > 74 && GetX_RB(DOG_ATTACK_FIRE) < 200)
				return 2;
			else if (GetX_LT(DOG_ATTACK_FIRE) > 24 && GetX_RB(DOG_ATTACK_FIRE) < 250)
				return 1;
			else
				return 0;
		}
		else
			return -1;
	}

	int Weapon::isHitDog()
	{
		// -1:too far, 0:miss, 1:lightly attacked, 2:heavly attacked]
		// 判斷武器是不是飛到一半
		if (GetX_LT(CAT_ATTACK_FIRE) > 1333 / 2 && GetY_RB(CAT_ATTACK_FIRE) > 677) {
			// 判斷武器是不是完全在重擊區或擦傷區或是miss
			if (GetX_LT(CAT_ATTACK_FIRE) > 1092 && GetX_RB(CAT_ATTACK_FIRE) < 1238)
				return 2;
			else if (GetX_LT(CAT_ATTACK_FIRE) > 1042 && GetX_RB(CAT_ATTACK_FIRE) < 1288)
				return 1;
			else
				return 0;
		}
		else
			return -1;
	}

	void Weapon::setSize(double factor)
	{
		weaponSizeFactor = factor;
	}

	void Weapon::setNormalWeapon(bool normal)
	{
		isNormalWeapon = normal;
	}
}