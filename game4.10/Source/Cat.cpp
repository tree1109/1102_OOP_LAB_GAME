#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "GAMEID.h"
#include "Cat.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Cat: Cat class
	/////////////////////////////////////////////////////////////////////////////

	Cat::Cat()
	{
		CatPositionX = 0;
		CatPositionY = 559;
	}

	void Cat::Initialize()
	{
		LoadBitmap();

		Cat_Normal.SetTopLeft(CatPositionX, CatPositionY);
		Cat_Normal_BadlyHurt.SetTopLeft(CatPositionX, CatPositionY);
		Cat_Attack_1.SetTopLeft(CatPositionX, CatPositionY);
		Cat_Attack_2.SetTopLeft(CatPositionX, CatPositionY);
		Cat_Attack_3.SetTopLeft(CatPositionX, CatPositionY);
		Cat_Attack_4.SetTopLeft(CatPositionX, CatPositionY);
		Cat_BeingAttacked_Big.SetTopLeft(CatPositionX, CatPositionY);
		Cat_BeingAttacked_Little.SetTopLeft(CatPositionX, CatPositionY);
		Cat_BeingAttacked_Miss.SetTopLeft(CatPositionX, CatPositionY);
	}

	void Cat::LoadBitmap()
	{
		Cat_Normal.LoadBitmap("GamePicture/GameRun/Cat/Normal.bmp");
		Cat_Normal_BadlyHurt.LoadBitmap("GamePicture/GameRun/Cat/Normal_BadlyHurt.bmp");
		Cat_Attack_1.LoadBitmap("GamePicture/GameRun/Cat/Attack_1.bmp");
		Cat_Attack_2.LoadBitmap("GamePicture/GameRun/Cat/Attack_2.bmp");
		Cat_Attack_3.LoadBitmap("GamePicture/GameRun/Cat/Attack_3.bmp");
		Cat_Attack_4.LoadBitmap("GamePicture/GameRun/Cat/Attack_4.bmp");
		Cat_BeingAttacked_Big.LoadBitmap("GamePicture/GameRun/Cat/BeingAttacked_Big.bmp");
		Cat_BeingAttacked_Little.LoadBitmap("GamePicture/GameRun/Cat/BeingAttacked_Little.bmp");
		Cat_BeingAttacked_Miss.LoadBitmap("GamePicture/GameRun/Cat/BeingAttacked_Miss.bmp");
	}

	void Cat::OnMove(GAME_RUN_ID runId)
	{
		// 根據目前的條件改變狀態
	}

	void Cat::OnShow(PICTURE_STATUS pictureStatus)
	{
		switch (pictureStatus)
		{
		case Normal:
			Cat_Normal.ShowBitmap();
			break;
		case Normal_BadlyHurt:
			Cat_Normal_BadlyHurt.ShowBitmap();
			break;
		case Attack_1:
			Cat_Attack_1.ShowBitmap();
			break;
		case Attack_2:
			Cat_Attack_2.ShowBitmap();
			break;
		case Attack_3:
			Cat_Attack_3.ShowBitmap();
			break;
		case Attack_4:
			Cat_Attack_4.ShowBitmap();
			break;
		case BeingAttacked_Big:
			Cat_BeingAttacked_Big.ShowBitmap();
			break;
		case BeingAttacked_Little:
			Cat_BeingAttacked_Little.ShowBitmap();
			break;
		case BeingAttacked_Miss:
			Cat_BeingAttacked_Miss.ShowBitmap();
			break;
		default:
			break;
		}
	}
}