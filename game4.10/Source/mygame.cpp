/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		// 初始化遊戲狀態
		CurrentPage = START_BUTTON_PAGE_NO_HOVER;

		// 加載遊戲開始畫面圖片
		// 遊戲開始畫面
		StartButton_noHover.LoadBitmap("GamePicture/GameInit/StartButton_noHover.bmp");
		StartButton_hover.LoadBitmap("GamePicture/GameInit/StartButton_hover.bmp");

		// 遊戲大綱畫面
		FleabagVsMutt_noHover.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_noHover.bmp");
		FleabagVsMutt_hoverHowToPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverHowToPlay.bmp");
		FleabagVsMutt_hoverLetsPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverLetsPlay.bmp");

		// 遊戲說明畫面
		HowToPlay_noHover.LoadBitmap("GamePicture/GameInit/HowToPlay_noHover.bmp");
		HowToPlay_hover.LoadBitmap("GamePicture/GameInit/HowToPlay_hover.bmp");

		// 玩家人數選擇畫面
		ChooseGame_noHover.LoadBitmap("GamePicture/GameInit/ChooseGame_noHover.bmp");;
		ChooseGame_hover1P.LoadBitmap("GamePicture/GameInit/ChooseGame_hover1P.bmp");;
		ChooseGame_hover2P.LoadBitmap("GamePicture/GameInit/ChooseGame_hover2P.bmp");;

		// 選擇遊戲難度頁面
		SelectYourLevel_noHover.LoadBitmap("GamePicture/GameInit/SelectYourLevel_noHover.bmp");
		SelectYourLevel_hoverBeginner.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBeginner.bmp");
		SelectYourLevel_hoverAverage.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverAverage.bmp");
		SelectYourLevel_hoverBringItOn.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBringItOn.bmp");

		// 初始化所有圖片位置，因為都是整個畫面所以設置在(0, 0)位置
		StartButton_noHover.SetTopLeft(0, 0);
		StartButton_hover.SetTopLeft(0, 0);
		FleabagVsMutt_noHover.SetTopLeft(0, 0);
		FleabagVsMutt_hoverHowToPlay.SetTopLeft(0, 0);
		FleabagVsMutt_hoverLetsPlay.SetTopLeft(0, 0);
		HowToPlay_noHover.SetTopLeft(0, 0);
		HowToPlay_hover.SetTopLeft(0, 0);
		ChooseGame_noHover.SetTopLeft(0, 0);
		ChooseGame_hover1P.SetTopLeft(0, 0);
		ChooseGame_hover2P.SetTopLeft(0, 0);
		SelectYourLevel_noHover.SetTopLeft(0, 0);
		SelectYourLevel_hoverBeginner.SetTopLeft(0, 0);
		SelectYourLevel_hoverAverage.SetTopLeft(0, 0);
		SelectYourLevel_hoverBringItOn.SetTopLeft(0, 0);

		// 所有按鈕的CPoint 左上與右下
		StartPage_StartButtonLT = CPoint(436, 771);
		StartPage_StartButtonRB = CPoint(912, 839);
		FleabagVsMuttPage_HowToPlayButtonLT = CPoint(403, 559);
		FleabagVsMuttPage_HowToPlayButtonRB = CPoint(915, 635);
		FleabagVsMuttPage_LetsPlayButtonLT = CPoint(400, 709);
		FleabagVsMuttPage_LetsPlayButtonRB = CPoint(911, 788);
		HowToPlayPage_LetsPlayButtonLT = CPoint(400, 788);
		HowToPlayPage_LetsPlayButtonRB = CPoint(912, 866);
		ChooseGamePage_1PlayerButtonLT = CPoint(398, 350);
		ChooseGamePage_1PlayerButtonRB = CPoint(597, 563);
		ChooseGamePage_2PlayerButtonLT = CPoint(678, 364);
		ChooseGamePage_2PlayerButtonRB = CPoint(912, 563);
		SelectYourLevelPage_ImBeginnerButtonLT = CPoint(429, 305);
		SelectYourLevelPage_ImBeginnerButtonRB = CPoint(929, 409);
		SelectYourLevelPage_ImAverageButtonLT = CPoint(433, 426);
		SelectYourLevelPage_ImAverageButtonRB = CPoint(893, 539);
		SelectYourLevelPage_BringItOnButtonLT = CPoint(436, 555);
		SelectYourLevelPage_BringItOnButtonRB = CPoint(896, 647);
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{

		if (CurrentPage == START_BUTTON_PAGE_NO_HOVER || CurrentPage == START_BUTTON_PAGE_HOVER) {
			if (point.x > StartPage_StartButtonLT.x && point.x < StartPage_StartButtonRB.x && point.y > StartPage_StartButtonLT.y && point.y < StartPage_StartButtonRB.y)
				CurrentPage = START_BUTTON_PAGE_HOVER;
			else
				CurrentPage = START_BUTTON_PAGE_NO_HOVER;
		}
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_NO_HOVER || CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY || CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY) {
			if (point.x > FleabagVsMuttPage_HowToPlayButtonLT.x && point.x < FleabagVsMuttPage_HowToPlayButtonRB.x && point.y > FleabagVsMuttPage_HowToPlayButtonLT.y && point.y < FleabagVsMuttPage_HowToPlayButtonRB.y)
				CurrentPage = FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY;
			else if (point.x > FleabagVsMuttPage_LetsPlayButtonLT.x && point.x < FleabagVsMuttPage_LetsPlayButtonRB.x && point.y > FleabagVsMuttPage_LetsPlayButtonLT.y && point.y < FleabagVsMuttPage_LetsPlayButtonRB.y)
				CurrentPage = FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY;
			else
				CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
		}
		else if (CurrentPage == HOW_TO_PLAY_PAGE_NO_HOVER || CurrentPage == HOW_TO_PLAY_PAGE_HOVER) {
			if (point.x > HowToPlayPage_LetsPlayButtonLT.x && point.x < HowToPlayPage_LetsPlayButtonRB.x && point.y > HowToPlayPage_LetsPlayButtonLT.y && point.y < HowToPlayPage_LetsPlayButtonRB.y)
				CurrentPage = HOW_TO_PLAY_PAGE_HOVER;
			else
				CurrentPage = HOW_TO_PLAY_PAGE_NO_HOVER;
		}
		else if (CurrentPage == CHOOSE_GAME_PAGE_NO_HOVER || CurrentPage == CHOOSE_GAME_PAGE_HOVER_1PLAYER || CurrentPage == CHOOSE_GAME_PAGE_HOVER_2PLAYER) {
			if (point.x > ChooseGamePage_1PlayerButtonLT.x && point.x < ChooseGamePage_1PlayerButtonRB.x && point.y > ChooseGamePage_1PlayerButtonLT.y && point.y < ChooseGamePage_1PlayerButtonRB.y)
				CurrentPage = CHOOSE_GAME_PAGE_HOVER_1PLAYER;
			else if (point.x > ChooseGamePage_2PlayerButtonLT.x && point.x < ChooseGamePage_2PlayerButtonRB.x && point.y > ChooseGamePage_2PlayerButtonLT.y && point.y < ChooseGamePage_2PlayerButtonRB.y)
				CurrentPage = CHOOSE_GAME_PAGE_HOVER_2PLAYER;
			else
				CurrentPage = CHOOSE_GAME_PAGE_NO_HOVER;
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_NO_HOVER || CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER || CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE || CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON) {
			if (point.x > SelectYourLevelPage_ImBeginnerButtonLT.x && point.x < SelectYourLevelPage_ImBeginnerButtonRB.x && point.y > SelectYourLevelPage_ImBeginnerButtonLT.y && point.y < SelectYourLevelPage_ImBeginnerButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER;
			else if (point.x > SelectYourLevelPage_ImAverageButtonLT.x && point.x < SelectYourLevelPage_ImAverageButtonRB.x && point.y > SelectYourLevelPage_ImAverageButtonLT.y && point.y < SelectYourLevelPage_ImAverageButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE;
			else if (point.x > SelectYourLevelPage_BringItOnButtonLT.x && point.x < SelectYourLevelPage_BringItOnButtonRB.x && point.y > SelectYourLevelPage_BringItOnButtonLT.y && point.y < SelectYourLevelPage_BringItOnButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON;
			else
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_NO_HOVER;
		}

	}

	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if (CurrentPage == START_BUTTON_PAGE_HOVER) {
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
		}
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY) {
			CurrentPage = HOW_TO_PLAY_PAGE_NO_HOVER;
		}
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY || CurrentPage == HOW_TO_PLAY_PAGE_HOVER) {
			CurrentPage = CHOOSE_GAME_PAGE_NO_HOVER;
		}
		else if (CurrentPage == CHOOSE_GAME_PAGE_HOVER_1PLAYER) {
			CurrentPage = SELECT_YOUR_LEVEL_PAGE_NO_HOVER;
		}
		else if (CurrentPage == CHOOSE_GAME_PAGE_HOVER_2PLAYER) {
			GotoGameState(GAME_STATE_RUN);
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER) {
			// 紀錄難度
			GotoGameState(GAME_STATE_RUN);
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE) {
			// 紀錄難度
			GotoGameState(GAME_STATE_RUN);
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON) {
			// 紀錄難度
			GotoGameState(GAME_STATE_RUN);
		}
	}

	void CGameStateInit::OnMove()
	{

	}

	void CGameStateInit::OnShow()
	{
		// 遊戲開始畫面
		if (CurrentPage == START_BUTTON_PAGE_NO_HOVER) {
			StartButton_noHover.ShowBitmap();
		}
		else if (CurrentPage == START_BUTTON_PAGE_HOVER) {
			StartButton_hover.ShowBitmap();
		}
		// 遊戲大綱畫面
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_NO_HOVER) {
			FleabagVsMutt_noHover.ShowBitmap();
		}
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY) {
			FleabagVsMutt_hoverHowToPlay.ShowBitmap();
		}
		else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY) {
			FleabagVsMutt_hoverLetsPlay.ShowBitmap();
		}
		// 遊戲說明畫面
		else if (CurrentPage == HOW_TO_PLAY_PAGE_NO_HOVER) {
			HowToPlay_noHover.ShowBitmap();
		}
		else if (CurrentPage == HOW_TO_PLAY_PAGE_HOVER) {
			HowToPlay_hover.ShowBitmap();
		}
		// 玩家人數選擇畫面
		else if (CurrentPage == CHOOSE_GAME_PAGE_NO_HOVER) {
			ChooseGame_noHover.ShowBitmap();
		}
		else if (CurrentPage == CHOOSE_GAME_PAGE_HOVER_1PLAYER) {
			ChooseGame_hover1P.ShowBitmap();
		}
		else if (CurrentPage == CHOOSE_GAME_PAGE_HOVER_2PLAYER) {
			ChooseGame_hover2P.ShowBitmap();
		}
		// 選擇遊戲難度頁面
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_NO_HOVER) {
			SelectYourLevel_noHover.ShowBitmap();
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER) {
			SelectYourLevel_hoverBeginner.ShowBitmap();
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE) {
			SelectYourLevel_hoverAverage.ShowBitmap();
		}
		else if (CurrentPage == SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON) {
			SelectYourLevel_hoverBringItOn.ShowBitmap();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{

	}

	void CGameStateOver::OnShow()
	{

	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{

	}

	CGameStateRun::~CGameStateRun()
	{

	}

	void CGameStateRun::OnBeginState()
	{
		// 初始化貓咪跟狗狗物件
		CatObject.Initialize();
		DogObject.Initialize();

		// 一開始由狗先行攻擊
		runId = DOG_PREPARE;
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		if (runId == CAT_PREPARE) {
			Timer++;
			if (Timer >= 30) {
				runId = CAT_ATTACK_TAKE;
				Timer = 0;
			}
		}
		else if (runId == CAT_ATTACK_TAKE) {
			Timer++;
			if (Timer >= 25) {
				runId = CAT_ATTACK_BEGIN;
				Timer = 0;
			}
		}
		else if (runId == CAT_ATTACK_BEGIN) {
			runId = CAT_ATTACK_CHARGE;
		}
		else if (runId == CAT_ATTACK_CHARGE) {
			runId = CAT_ATTACK_FIRE;
		}
		else if (runId == CAT_ATTACK_FIRE) {
			runId = DOG_PREPARE;
		}
		else if (runId == DOG_PREPARE) {
			Timer++;
			if (Timer >= 30) {
				runId = DOG_ATTACK_TAKE;
				Timer = 0;
			}
		}
		else if (runId == DOG_ATTACK_TAKE) {
			Timer++;
			if (Timer >= 25) {
				runId = DOG_ATTACK_BEGIN;
				Timer = 0;
			}
		}
		else if (runId == DOG_ATTACK_BEGIN) {
			// runId = DOG_ATTACK_CHARGE;
		}
		else if (runId == DOG_ATTACK_CHARGE) {
			Timer++;
			// runId = DOG_ATTACK_FIRE;
		}
		else if (runId == DOG_ATTACK_FIRE) {
			runId = CAT_PREPARE;
			Timer = 0;
		}

	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		// 載入所有戰鬥中的圖片
		// 背景
		Background.LoadBitmap("GamePicture/GameRun/Background.bmp");

		// 初始化計時器
		Timer = 0;
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		if (runId == DOG_ATTACK_BEGIN) {
			runId = DOG_ATTACK_CHARGE;
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		if (runId == DOG_ATTACK_CHARGE) {
			runId = DOG_ATTACK_FIRE;
		}
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//

		// 顯示背景
		Background.ShowBitmap();


		// 顯示武器
		// Dog_Weapon.ShowBitmap();
		// Cat_Weapon.ShowBitmap();

		// 顯示貓貓狗狗
		// CatObject.OnShow(runId);
		// DogObject.OnShow(runId);

		// Cat
		if (runId == CAT_PREPARE) {
			CatObject.OnShow(Normal);
		}
		else if (runId == CAT_ATTACK_TAKE) {
			CatObject.OnShow(Attack_1);
		}
		else if (runId == CAT_ATTACK_BEGIN) {
			CatObject.OnShow(Attack_2);
		}
		else if (runId == CAT_ATTACK_CHARGE) {
			CatObject.OnShow(Attack_3);
		}
		else if (runId == CAT_ATTACK_FIRE) {
			CatObject.OnShow(Attack_4);
		}
		else {
			CatObject.OnShow(Normal);
		}

		// Dog
		if (runId == DOG_PREPARE) {
			DogObject.OnShow(Normal);
		}
		else if (runId == DOG_ATTACK_TAKE) {
			DogObject.OnShow(Attack_1);
		}
		else if (runId == DOG_ATTACK_BEGIN) {
			DogObject.OnShow(Attack_2);
		}
		else if (runId == DOG_ATTACK_CHARGE) {
			DogObject.OnShow(Attack_3);
		}
		else if (runId == DOG_ATTACK_FIRE) {
			DogObject.OnShow(Attack_4);
		}
		else {
			DogObject.OnShow(Normal);
		}

	}
}