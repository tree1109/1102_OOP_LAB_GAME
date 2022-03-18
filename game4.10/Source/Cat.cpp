#include "stdafx.h"
#include "Resource.h"
#include <ddraw.h>
#include "gamelib.h"
#include "Cat.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
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
		Cat_Weapon.LoadBitmap("GamePicture/GameRun/Cat/Weapon.bmp", RGB(180, 0, 255));
		
	}

	void Cat::OnMove()
	{
		// 根據目前的條件改變狀態
	}

	void Cat::OnShow()
	{
		// 根據目前的狀態貼上貓貓圖片
	}
}