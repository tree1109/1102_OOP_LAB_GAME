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
		// �ھڥثe��������ܪ��A
		if (runId == CAT_ATTACK_FIRE) {
			
		}
		else if (runId == DOG_ATTACK_FIRE) {
			SetPower(velocityX, velocityY + 1); // 10 �O���O
			SetPosition(weaponPositionX + velocityX, weaponPositionY + velocityY);
		}
	}

	void Weapon::OnShow(GAME_RUN_ID runId)
	{
		// �ھڪ��A��ܿߩΪ����Z��
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
		int power = 100;
		SetPosition(1088, 693);		// ���Y�_�l�o�g��m
		SetPower(-power, -power);	// �����W���o�g

	}

	bool Weapon::isHitGround()
	{
		// Y�Ȥj��888�ɥN���a
		return weaponPositionY > 888;
	}
}