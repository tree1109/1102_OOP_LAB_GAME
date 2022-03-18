#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "GAMEID.h"
#include "Dog.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Dog: Dog class
	/////////////////////////////////////////////////////////////////////////////

	Dog::Dog()
	{
		DogPositionX = 1032;
		DogPositionY = 634;
	}

	void Dog::Initialize()
	{
		LoadBitmap();

		Dog_Normal.SetTopLeft(DogPositionX, DogPositionY);
		Dog_Normal_BadlyHurt.SetTopLeft(DogPositionX, DogPositionY);
		Dog_Attack_1.SetTopLeft(DogPositionX, DogPositionY);
		Dog_Attack_2.SetTopLeft(DogPositionX, DogPositionY);
		Dog_Attack_3.SetTopLeft(DogPositionX, DogPositionY);
		Dog_Attack_4.SetTopLeft(DogPositionX, DogPositionY);
		Dog_BeingAttacked_Big.SetTopLeft(DogPositionX, DogPositionY);
		Dog_BeingAttacked_Little.SetTopLeft(DogPositionX, DogPositionY);
		Dog_BeingAttacked_Miss.SetTopLeft(DogPositionX, DogPositionY);
	}

	void Dog::LoadBitmap()
	{
		Dog_Normal.LoadBitmap("GamePicture/GameRun/Dog/Normal.bmp");
		Dog_Normal_BadlyHurt.LoadBitmap("GamePicture/GameRun/Dog/Normal_BadlyHurt.bmp");
		Dog_Attack_1.LoadBitmap("GamePicture/GameRun/Dog/Attack_1.bmp");
		Dog_Attack_2.LoadBitmap("GamePicture/GameRun/Dog/Attack_2.bmp");
		Dog_Attack_3.LoadBitmap("GamePicture/GameRun/Dog/Attack_3.bmp");
		Dog_Attack_4.LoadBitmap("GamePicture/GameRun/Dog/Attack_4.bmp");
		Dog_BeingAttacked_Big.LoadBitmap("GamePicture/GameRun/Dog/BeingAttacked_Big.bmp");
		Dog_BeingAttacked_Little.LoadBitmap("GamePicture/GameRun/Dog/BeingAttacked_Little.bmp");
		Dog_BeingAttacked_Miss.LoadBitmap("GamePicture/GameRun/Dog/BeingAttacked_Miss.bmp");
	}

	void Dog::OnMove(GAME_RUN_ID runId)
	{
		// 根據目前的條件改變狀態
	}

	void Dog::OnShow(PICTURE_STATUS pictureStatus)
	{
		switch (pictureStatus)
		{
		case Normal:
			Dog_Normal.ShowBitmap();
			break;
		case Normal_BadlyHurt:
			Dog_Normal_BadlyHurt.ShowBitmap();
			break;
		case Attack_1:
			Dog_Attack_1.ShowBitmap();
			break;
		case Attack_2:
			Dog_Attack_2.ShowBitmap();
			break;
		case Attack_3:
			Dog_Attack_3.ShowBitmap();
			break;
		case Attack_4:
			Dog_Attack_4.ShowBitmap();
			break;
		case BeingAttacked_Big:
			Dog_BeingAttacked_Big.ShowBitmap();
			break;
		case BeingAttacked_Little:
			Dog_BeingAttacked_Little.ShowBitmap();
			break;
		case BeingAttacked_Miss:
			Dog_BeingAttacked_Miss.ShowBitmap();
			break;
		default:
			break;
		}
	}
}