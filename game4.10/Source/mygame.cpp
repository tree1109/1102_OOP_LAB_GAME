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
#include <cstdlib>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	// 初始化遊戲難度
	GAME_LEVEL GameData::GameLevel = GAME_LEVEL::ImaBeginner;

	// 初始化狗狗輸贏
	bool GameData::isDogWin = false;

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		char buffer[100];

		// 初始化遊戲狀態
		CurrentPage = START_BUTTON_PAGE_NO_HOVER;

		// 加載遊戲開始畫面圖片
		// 遊戲開始畫面動畫
		StartButtonBackground.SetDelayCount(4);
		for (int i = 1; i <= 8; i++) {
			std::string PicturePath = string("GamePicture/GameInit/StartButton/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			StartButtonBackground.AddBitmap(buffer);
		}

		// 遊戲開始畫面
		StartButton_noHover.LoadBitmap("GamePicture/GameInit/StartButton_noHover.bmp");
		StartButton_hover.LoadBitmap("GamePicture/GameInit/StartButton_hover.bmp");

		// 遊戲大綱畫面
		FleabagVsMutt_noHover.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_noHover.bmp");
		FleabagVsMutt_hoverHowToPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverHowToPlay.bmp");
		FleabagVsMutt_hoverLetsPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverLetsPlay.bmp");
		FleabagVsMutt_titleCat.SetDelayCount(4);
		for (int i = 1; i <= 8; i++) {
			std::string PicturePath = string("GamePicture/GameInit/FleabagVsMutt_titleCat/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			FleabagVsMutt_titleCat.AddBitmap(buffer);
		}

		// 遊戲說明畫面
		HowToPlay_noHover.LoadBitmap("GamePicture/GameInit/HowToPlay_noHover.bmp");
		HowToPlay_hover.LoadBitmap("GamePicture/GameInit/HowToPlay_hover.bmp");

		// 玩家人數選擇畫面
		ChooseGame_noHover.LoadBitmap("GamePicture/GameInit/ChooseGame_noHover.bmp");
		ChooseGame_hover1P.LoadBitmap("GamePicture/GameInit/ChooseGame_hover1P.bmp");
		ChooseGame_hover2P.LoadBitmap("GamePicture/GameInit/ChooseGame_hover2P.bmp");

		// 選擇遊戲難度頁面各難度動畫
		SelectYourLevel_hoverBeginnerAnimation.SetDelayCount(3);
		SelectYourLevel_hoverAverageAnimation.SetDelayCount(3);
		SelectYourLevel_hoverBringItOnAnimation.SetDelayCount(3);
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameInit/SelectYourLevel/1-") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			SelectYourLevel_hoverBeginnerAnimation.AddBitmap(buffer);
			PicturePath = string("GamePicture/GameInit/SelectYourLevel/2-") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			SelectYourLevel_hoverAverageAnimation.AddBitmap(buffer);
		}
		for (int i = 1; i <= 7; i++) {
			std::string PicturePath = string("GamePicture/GameInit/SelectYourLevel/3-") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			SelectYourLevel_hoverBringItOnAnimation.AddBitmap(buffer);
		}

		// 選擇遊戲難度頁面
		SelectYourLevelBackground.LoadBitmap("GamePicture/GameInit/SelectYourLevelBackground.bmp");
		SelectYourLevel_hoverBeginner.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBeginner.bmp");
		SelectYourLevel_hoverAverage.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverAverage.bmp");
		SelectYourLevel_hoverBringItOn.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBringItOn.bmp");

		// 初始化所有圖片位置，因為都是整個畫面所以設置在(0, 0)位置
		StartButtonBackground.SetTopLeft(0, 0);
		StartButton_noHover.SetTopLeft(572, 778);
		StartButton_hover.SetTopLeft(572, 778);
		FleabagVsMutt_noHover.SetTopLeft(0, 0);
		FleabagVsMutt_hoverHowToPlay.SetTopLeft(0, 0);
		FleabagVsMutt_hoverLetsPlay.SetTopLeft(0, 0);
		FleabagVsMutt_titleCat.SetTopLeft(220, 52);
		HowToPlay_noHover.SetTopLeft(0, 0);
		HowToPlay_hover.SetTopLeft(0, 0);
		ChooseGame_noHover.SetTopLeft(0, 0);
		ChooseGame_hover1P.SetTopLeft(0, 0);
		ChooseGame_hover2P.SetTopLeft(0, 0);
		SelectYourLevelBackground.SetTopLeft(0, 0);
		SelectYourLevel_hoverBeginner.SetTopLeft(0, 0);
		SelectYourLevel_hoverAverage.SetTopLeft(0, 0);
		SelectYourLevel_hoverBringItOn.SetTopLeft(0, 0);
		SelectYourLevel_hoverBeginnerAnimation.SetTopLeft(429, 298);
		SelectYourLevel_hoverAverageAnimation.SetTopLeft(423, 418);
		SelectYourLevel_hoverBringItOnAnimation.SetTopLeft(435, 548);

		// 所有按鈕的CPoint 左上(LT)與右下(RB)
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
		switch (CurrentPage)
		{
		case START_BUTTON_PAGE_NO_HOVER:
		case START_BUTTON_PAGE_HOVER:
			if (point.x > StartPage_StartButtonLT.x && point.x < StartPage_StartButtonRB.x && point.y > StartPage_StartButtonLT.y && point.y < StartPage_StartButtonRB.y)
				CurrentPage = START_BUTTON_PAGE_HOVER;
			else
				CurrentPage = START_BUTTON_PAGE_NO_HOVER;
			break;
		case FLEABAG_VS_MUTT_PAGE_NO_HOVER:
		case FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY:
		case FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY:
			if (point.x > FleabagVsMuttPage_HowToPlayButtonLT.x && point.x < FleabagVsMuttPage_HowToPlayButtonRB.x && point.y > FleabagVsMuttPage_HowToPlayButtonLT.y && point.y < FleabagVsMuttPage_HowToPlayButtonRB.y)
				CurrentPage = FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY;
			else if (point.x > FleabagVsMuttPage_LetsPlayButtonLT.x && point.x < FleabagVsMuttPage_LetsPlayButtonRB.x && point.y > FleabagVsMuttPage_LetsPlayButtonLT.y && point.y < FleabagVsMuttPage_LetsPlayButtonRB.y)
				CurrentPage = FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY;
			else
				CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			break;
		case HOW_TO_PLAY_PAGE_NO_HOVER:
		case HOW_TO_PLAY_PAGE_HOVER:
			if (point.x > HowToPlayPage_LetsPlayButtonLT.x && point.x < HowToPlayPage_LetsPlayButtonRB.x && point.y > HowToPlayPage_LetsPlayButtonLT.y && point.y < HowToPlayPage_LetsPlayButtonRB.y)
				CurrentPage = HOW_TO_PLAY_PAGE_HOVER;
			else
				CurrentPage = HOW_TO_PLAY_PAGE_NO_HOVER;
			break;
		case CHOOSE_GAME_PAGE_NO_HOVER:
		case CHOOSE_GAME_PAGE_HOVER_1PLAYER:
		case CHOOSE_GAME_PAGE_HOVER_2PLAYER:
			if (point.x > ChooseGamePage_1PlayerButtonLT.x && point.x < ChooseGamePage_1PlayerButtonRB.x && point.y > ChooseGamePage_1PlayerButtonLT.y && point.y < ChooseGamePage_1PlayerButtonRB.y)
				CurrentPage = CHOOSE_GAME_PAGE_HOVER_1PLAYER;
			else if (point.x > ChooseGamePage_2PlayerButtonLT.x && point.x < ChooseGamePage_2PlayerButtonRB.x && point.y > ChooseGamePage_2PlayerButtonLT.y && point.y < ChooseGamePage_2PlayerButtonRB.y)
				CurrentPage = CHOOSE_GAME_PAGE_HOVER_2PLAYER;
			else
				CurrentPage = CHOOSE_GAME_PAGE_NO_HOVER;
			break;
		case SELECT_YOUR_LEVEL_PAGE_NO_HOVER:
		case SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER:
		case SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE:
		case SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON:
			if (point.x > SelectYourLevelPage_ImBeginnerButtonLT.x && point.x < SelectYourLevelPage_ImBeginnerButtonRB.x && point.y > SelectYourLevelPage_ImBeginnerButtonLT.y && point.y < SelectYourLevelPage_ImBeginnerButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER;
			else if (point.x > SelectYourLevelPage_ImAverageButtonLT.x && point.x < SelectYourLevelPage_ImAverageButtonRB.x && point.y > SelectYourLevelPage_ImAverageButtonLT.y && point.y < SelectYourLevelPage_ImAverageButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE;
			else if (point.x > SelectYourLevelPage_BringItOnButtonLT.x && point.x < SelectYourLevelPage_BringItOnButtonRB.x && point.y > SelectYourLevelPage_BringItOnButtonLT.y && point.y < SelectYourLevelPage_BringItOnButtonRB.y)
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON;
			else
				CurrentPage = SELECT_YOUR_LEVEL_PAGE_NO_HOVER;
			break;
		default:
			break;
		}
	}

	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		switch (CurrentPage)
		{
		case START_BUTTON_PAGE_HOVER:
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			break;
		case FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY:
			CurrentPage = HOW_TO_PLAY_PAGE_NO_HOVER;
			break;
		case FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY:
		case HOW_TO_PLAY_PAGE_HOVER:
			CurrentPage = CHOOSE_GAME_PAGE_NO_HOVER;
			break;
		case CHOOSE_GAME_PAGE_HOVER_1PLAYER:
			CurrentPage = SELECT_YOUR_LEVEL_PAGE_NO_HOVER;
			break;
		case CHOOSE_GAME_PAGE_HOVER_2PLAYER:
			// 重置CurrentPage到FLEABAG_VS_MUTT頁面，遊戲結束按下reply會回到這個頁面。
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			GotoGameState(GAME_STATE_RUN);
			break;
		case SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER:
			// 重置CurrentPage到FLEABAG_VS_MUTT頁面，遊戲結束按下reply會回到這個頁面。
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			// 紀錄難度
			GameData::GameLevel = GAME_LEVEL::ImaBeginner;
			GotoGameState(GAME_STATE_RUN);
			break;
		case SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE:
			// 重置CurrentPage到FLEABAG_VS_MUTT頁面，遊戲結束按下reply會回到這個頁面。
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			// 紀錄難度
			GameData::GameLevel = GAME_LEVEL::ImAverage;
			GotoGameState(GAME_STATE_RUN);
			break;
		case SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON:
			// 重置CurrentPage到FLEABAG_VS_MUTT頁面，遊戲結束按下reply會回到這個頁面。
			CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
			// 紀錄難度
			GameData::GameLevel = GAME_LEVEL::BringItOn;
			GotoGameState(GAME_STATE_RUN);
			break;
		default:
			break;
		}

	}

	void CGameStateInit::OnMove()
	{
		// 遊戲開始畫面動畫
		switch (CurrentPage)
		{
		case game_framework::START_BUTTON_PAGE_NO_HOVER:
		case game_framework::START_BUTTON_PAGE_HOVER:
			StartButtonBackground.OnMove();
			break;
		case game_framework::FLEABAG_VS_MUTT_PAGE_NO_HOVER:
		case game_framework::FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY:
		case game_framework::FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY:
		case game_framework::HOW_TO_PLAY_PAGE_NO_HOVER:
		case game_framework::HOW_TO_PLAY_PAGE_HOVER:
			FleabagVsMutt_titleCat.OnMove();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER:
			SelectYourLevel_hoverBeginnerAnimation.OnMove();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE:
			SelectYourLevel_hoverAverageAnimation.OnMove();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON:
			SelectYourLevel_hoverBringItOnAnimation.OnMove();
			break;
		default:
			break;
		}
	}

	void CGameStateInit::OnShow()
	{
		switch (CurrentPage)
		{
		case game_framework::START_BUTTON_PAGE_NO_HOVER: // 遊戲開始畫面
			StartButtonBackground.OnShow();
			StartButton_noHover.ShowBitmap();
			break;
		case game_framework::START_BUTTON_PAGE_HOVER:
			StartButtonBackground.OnShow();
			StartButton_hover.ShowBitmap();
			break;
		case game_framework::FLEABAG_VS_MUTT_PAGE_NO_HOVER: // 遊戲大綱畫面
			FleabagVsMutt_noHover.ShowBitmap();
			FleabagVsMutt_titleCat.OnShow();
			break;
		case game_framework::FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY:
			FleabagVsMutt_hoverHowToPlay.ShowBitmap();
			FleabagVsMutt_titleCat.OnShow();
			break;
		case game_framework::FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY:
			FleabagVsMutt_hoverLetsPlay.ShowBitmap();
			FleabagVsMutt_titleCat.OnShow();
			break;
		case game_framework::HOW_TO_PLAY_PAGE_NO_HOVER: // 遊戲說明畫面
			HowToPlay_noHover.ShowBitmap();
			FleabagVsMutt_titleCat.OnShow();
			break;
		case game_framework::HOW_TO_PLAY_PAGE_HOVER:
			HowToPlay_hover.ShowBitmap();
			FleabagVsMutt_titleCat.OnShow();
			break;
		case game_framework::CHOOSE_GAME_PAGE_NO_HOVER: // 玩家人數選擇畫面
			ChooseGame_noHover.ShowBitmap();
			break;
		case game_framework::CHOOSE_GAME_PAGE_HOVER_1PLAYER:
			ChooseGame_hover1P.ShowBitmap();
			break;
		case game_framework::CHOOSE_GAME_PAGE_HOVER_2PLAYER:
			ChooseGame_hover2P.ShowBitmap();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_NO_HOVER: // 選擇遊戲難度頁面
			SelectYourLevelBackground.ShowBitmap();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER:
			SelectYourLevel_hoverBeginner.ShowBitmap();
			SelectYourLevel_hoverBeginnerAnimation.OnShow();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE:
			SelectYourLevel_hoverAverage.ShowBitmap();
			SelectYourLevel_hoverAverageAnimation.OnShow();
			break;
		case game_framework::SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON:
			SelectYourLevel_hoverBringItOn.ShowBitmap();
			SelectYourLevel_hoverBringItOnAnimation.OnShow();
			break;
		default:
			break;
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
		if (GameData::isDogWin) {
			DogWin_catAnimation.OnMove();
			DogWin_dogAnimation.OnMove();
		}
		else {
			CatWin_titleAnimation.OnMove();
			CatWin_catAnimation.OnMove();
			CatWin_dogAnimation.OnMove();
		}
	}

	void CGameStateOver::OnBeginState()
	{

	}

	void CGameStateOver::OnInit()
	{
		isHoverReplay = false;
		char buffer[100];

		// 貓咪贏
		CatWin_background.LoadBitmap("GamePicture/GameOver/CatWin/background.bmp");
		CatWin_replayHover.LoadBitmap("GamePicture/GameOver/CatWin/replayHover.bmp");
		// 載入遊戲結束動畫
		CatWin_titleAnimation.SetDelayCount(3);
		CatWin_catAnimation.SetDelayCount(2);
		CatWin_dogAnimation.SetDelayCount(3);
		for (int i = 1; i <= 6; i++) {
			std::string PicturePath = string("GamePicture/GameOver/CatWin/Title/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			CatWin_titleAnimation.AddBitmap(buffer);
		}
		for (int i = 1; i <= 10; i++) {
			std::string PicturePath = string("GamePicture/GameOver/CatWin/Cat/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			CatWin_catAnimation.AddBitmap(buffer);
		}
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameOver/CatWin/Dog/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			CatWin_dogAnimation.AddBitmap(buffer);
		}

		// 狗溝贏
		DogWin_background.LoadBitmap("GamePicture/GameOver/DogWin/background.bmp");
		DogWin_replayHover.LoadBitmap("GamePicture/GameOver/DogWin/replayHover.bmp");
		// 載入遊戲結束動畫
		DogWin_catAnimation.SetDelayCount(3);
		DogWin_dogAnimation.SetDelayCount(4);
		for (int i = 1; i <= 10; i++) {
			std::string PicturePath = string("GamePicture/GameOver/DogWin/Cat/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			DogWin_catAnimation.AddBitmap(buffer);
		}
		for (int i = 1; i <= 6; i++) {
			std::string PicturePath = string("GamePicture/GameOver/DogWin/Dog/") + std::to_string(i) + ".bmp";
			std::sprintf(buffer, "%s", (PicturePath.c_str()));
			DogWin_dogAnimation.AddBitmap(buffer);
		}

		// 初始化所有圖片位置
		CatWin_background.SetTopLeft(0, 0);
		CatWin_replayHover.SetTopLeft(585, 455);
		CatWin_titleAnimation.SetTopLeft(417, 310);
		CatWin_catAnimation.SetTopLeft(0, 501);
		CatWin_dogAnimation.SetTopLeft(999, 669);
		DogWin_background.SetTopLeft(0, 0);
		DogWin_replayHover.SetTopLeft(584, 449);
		DogWin_catAnimation.SetTopLeft(0, 612);
		DogWin_dogAnimation.SetTopLeft(1030, 620);

		// replay按鈕的CPoint 左上與右下
		CatWin_ReplayButtonLT = CPoint(585, 455);
		CatWin_ReplayButtonRB = CPoint(769, 507);
		DogWin_ReplayButtonLT = CPoint(584, 449);
		DogWin_ReplayButtonRB = CPoint(767, 505);
	}

	void CGameStateOver::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (GameData::isDogWin) {
			if (point.x > DogWin_ReplayButtonLT.x && point.x < DogWin_ReplayButtonRB.x && point.y > DogWin_ReplayButtonLT.y && point.y < DogWin_ReplayButtonRB.y)
				isHoverReplay = true;
			else
				isHoverReplay = false;
		}
		else {
			if (point.x > CatWin_ReplayButtonLT.x && point.x < CatWin_ReplayButtonRB.x && point.y > CatWin_ReplayButtonLT.y && point.y < CatWin_ReplayButtonRB.y)
				isHoverReplay = true;
			else
				isHoverReplay = false;
		}
	}

	void CGameStateOver::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if (isHoverReplay)
				GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnShow()
	{
		if (GameData::isDogWin) {
			DogWin_background.ShowBitmap();
			DogWin_catAnimation.OnShow();
			DogWin_dogAnimation.OnShow();
			if (isHoverReplay)
				DogWin_replayHover.ShowBitmap();
		}
		else {
			CatWin_background.ShowBitmap();
			CatWin_titleAnimation.OnShow();
			CatWin_catAnimation.OnShow();
			CatWin_dogAnimation.OnShow();
			if (isHoverReplay)
				CatWin_replayHover.ShowBitmap();
		}
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
		// 每次進到CGameStateRun都會跑一次

		// 初始化貓咪跟狗狗武器物件
		CatObject.Initialize();
		DogObject.Initialize();
		WeaponObject.Initialize();

		// 初始化貓咪跟狗狗血量為100%
		CatHealthPointBar.Initialize();
		DogHealthPointBar.Initialize();

		// 一開始由狗先行攻擊
		runId = DOG_PREPARE;

		// 初始化計時器
		Timer = 0;

		// 初始化技能狀態
		catSkillDoubleAttackStatus = IS_NOT_HOVER;
		catSkillPowerAttackStatus = IS_NOT_HOVER;
		catSkillPoisonGasStatus = IS_NOT_HOVER;
		catSkillOKBandStatus = IS_NOT_HOVER;
		dogSkillDoubleAttackStatus = IS_NOT_HOVER;
		dogSkillPowerAttackStatus = IS_NOT_HOVER;
		dogSkillPoisonGasStatus = IS_NOT_HOVER;
		dogSkillOKBandStatus = IS_NOT_HOVER;
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		switch (runId)
		{
		case CAT_PREPARE:
			Timer++;
			if (Timer >= 30) {
				runId = CAT_ATTACK_TAKE;
				Timer = 0;
			}
			break;
		case CAT_ATTACK_TAKE:
			Timer++;
			if (Timer >= 25) {
				runId = CAT_ATTACK_BEGIN;
				Timer = 0;
			}
			break;
		case CAT_ATTACK_BEGIN:
			Timer ++;
			if (Timer >= 20) {
				runId = CAT_ATTACK_CHARGE;
				Timer = 0;
			}
			break;
		case CAT_ATTACK_CHARGE:
			Timer++;
			if (Timer >= 20) {
				int max = 0;
				int min = 0;

				// 難度每升一級就將攻擊範圍縮小12
				switch (GameData::GameLevel)
				{
				case GAME_LEVEL::ImaBeginner:
					// 命中率 3/25 == 12%
					max = 27;
					min = 3;
					break;
				case GAME_LEVEL::ImAverage:
					// 命中率 3/15 == 20%
					max = 22;
					min = 8;
					break;
				case GAME_LEVEL::BringItOn:
					// 命中率 3/5 == 60%
					max = 17;
					min = 13;
					break;
				default:
					break;
				}
				int rand_power = rand() % (max - min + 1) + min;

				WeaponObject.CatFire(rand_power);
				runId = CAT_ATTACK_FIRE;
				Timer = 0;
			}
			break;
		case CAT_ATTACK_FIRE:
			if (WeaponObject.isHitDog() == 1) {
				runId = DOG_BEGIN_ATTACKED_LITTLE;
				Timer = 0;
				DogHealthPointBar.SubHP(10);
			}
			else if (WeaponObject.isHitDog() == 2) {
				runId = DOG_BEGIN_ATTACKED_BIG;
				Timer = 0;
				DogHealthPointBar.SubHP(25);
			}
			else if (WeaponObject.isHitGround()) {
				runId = DOG_BEGIN_ATTACKED_MISS;
				Timer = 0;
			}

			if (DogHealthPointBar.isDead())
			{
				GameData::isDogWin = false;
				GotoGameState(GAME_STATE_OVER);
			}
			break;
		case CAT_BEGIN_ATTACKED_LITTLE:
		case CAT_BEGIN_ATTACKED_BIG:
		case CAT_BEGIN_ATTACKED_MISS:
			Timer++;
			if (Timer > 30)
			{
				// 連擊
				if (dogSkillDoubleAttackStatus == USING)
				{
					runId = DOG_ATTACK_FIRE;
					WeaponObject.DogFire(lastPower);
					dogSkillDoubleAttackStatus = USED;
				}
				else
					runId = CAT_PREPARE;
				if (dogSkillPowerAttackStatus == USING)
				{
					WeaponObject.setSize(1);
					dogSkillPowerAttackStatus = USED;
				}
			}
			break;
		case DOG_PREPARE:
			Timer++;
			if (Timer >= 30) {
				runId = DOG_ATTACK_TAKE;
				Timer = 0;
			}
			break;
		case DOG_ATTACK_TAKE:
			Timer++;
			if (Timer >= 25) {
				runId = DOG_ATTACK_BEGIN;
			}
			break;
		case DOG_ATTACK_BEGIN:
			AttackInvertedTriangle.OnMove();
			break;
		case DOG_ATTACK_CHARGE:
			Timer++;
			break;
		case DOG_ATTACK_FIRE:
			if (WeaponObject.isHitCat() == 1) {
				runId = CAT_BEGIN_ATTACKED_LITTLE;
				Timer = 0;
				CatHealthPointBar.SubHP(10);
			}
			else if (WeaponObject.isHitCat() == 2) {
				runId = CAT_BEGIN_ATTACKED_BIG;
				Timer = 0;
				CatHealthPointBar.SubHP(25);
			}
			else if (WeaponObject.isHitGround()) {
				runId = CAT_BEGIN_ATTACKED_MISS;
				Timer = 0;
			}
			if (CatHealthPointBar.isDead())
			{
				GameData::isDogWin = true;
				GotoGameState(GAME_STATE_OVER);
			}
			break;
		case DOG_BEGIN_ATTACKED_LITTLE:
		case DOG_BEGIN_ATTACKED_BIG:
		case DOG_BEGIN_ATTACKED_MISS:
			Timer++;
			if (Timer > 30)
			{
				// 連擊
				if (catSkillDoubleAttackStatus == USING)
				{
					runId = CAT_ATTACK_FIRE;
					WeaponObject.CatFire(lastPower);
					catSkillDoubleAttackStatus = USED;
				}
				else
					runId = DOG_PREPARE;
				if (catSkillPowerAttackStatus == USING)
				{
					WeaponObject.setSize(1);
					catSkillPowerAttackStatus = USED;
				}
			}
			break;
		default:
			break;
		}

		// Weapon位移運算
		WeaponObject.OnMove(runId);

		// 技能hover動畫撥放
		if (catSkillPowerAttackStatus == IS_HOVER)
			// 正常播放動畫
			catSkillPowerAttackHoverAnimation.OnMove();
		else if (catSkillPowerAttackStatus == IS_NOT_HOVER)
			// 停止撥放動畫
			catSkillPowerAttackHoverAnimation.Reset();

		// 毒氣
		if (catSkillPoisonGasStatus == IS_HOVER)
			catSkillPoisonGasHoverAnimation.OnMove();
		else if (catSkillPoisonGasStatus == IS_NOT_HOVER)
			catSkillPoisonGasHoverAnimation.Reset();

		// 治癒
		if (catSkillOKBandStatus == IS_HOVER)
			catSkillOKBandHoverAnimation.OnMove();
		else if (catSkillOKBandStatus == IS_NOT_HOVER)
			catSkillOKBandHoverAnimation.Reset();

		// Dog skill
		// 重擊
		if (dogSkillPowerAttackStatus == IS_HOVER)
			dogSkillPowerAttackHoverAnimation.OnMove();
		else if (dogSkillPowerAttackStatus == IS_NOT_HOVER)
			dogSkillPowerAttackHoverAnimation.Reset();

		// 毒氣
		if (dogSkillPoisonGasStatus == IS_HOVER)
			dogSkillPoisonGasHoverAnimation.OnMove();
		else if (dogSkillPoisonGasStatus == IS_NOT_HOVER)
			dogSkillPoisonGasHoverAnimation.Reset();

		// 治癒
		if (dogSkillOKBandStatus == IS_HOVER)
			dogSkillOKBandHoverAnimation.OnMove();
		else if (dogSkillOKBandStatus == IS_NOT_HOVER)
			dogSkillOKBandHoverAnimation.Reset();
	}

	void CGameStateRun::OnInit()
	{
		char num_char[100];

		// 啟動遊戲時進行遊戲圖形載入
		// 狗攻擊時頭上的倒三角形動畫載入
		AttackInvertedTriangle.SetDelayCount(4);
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Dog/AttackInvertedTriangle_") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			AttackInvertedTriangle.AddBitmap(num_char);
		}

		// 載入所有戰鬥中的圖片
		// 背景
		Background.LoadBitmap("GamePicture/GameRun/Background.bmp");
		CatObject.LoadBitmap();
		DogObject.LoadBitmap();
		WeaponObject.LoadBitmap();

		// 血量條
		CatHealthPointBar.LoadBitmap();
		DogHealthPointBar.LoadBitmap();

		// 技能按鈕圖片
		catSkillDoubleAttackButton.LoadBitmap("GamePicture/GameRun/Cat/Skill/DoubleAttack.bmp");
		dogSkillDoubleAttackButton.LoadBitmap("GamePicture/GameRun/Dog/Skill/DoubleAttack.bmp");

		// 技能按鈕hover動畫
		// 貓技能
		catSkillPowerAttackHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 6; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Cat/Skill/PowerAttack-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			catSkillPowerAttackHoverAnimation.AddBitmap(num_char);
		}
		catSkillPoisonGasHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 6; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Cat/Skill/PoisonGas-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			catSkillPoisonGasHoverAnimation.AddBitmap(num_char);
		}
		catSkillOKBandHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Cat/Skill/OKBand-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			catSkillOKBandHoverAnimation.AddBitmap(num_char);
		}
		// 狗技能
		dogSkillPowerAttackHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Dog/Skill/PowerAttack-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			dogSkillPowerAttackHoverAnimation.AddBitmap(num_char);
		}
		dogSkillPoisonGasHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 4; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Dog/Skill/PoisonGas-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			dogSkillPoisonGasHoverAnimation.AddBitmap(num_char);
		}
		dogSkillOKBandHoverAnimation.SetDelayCount(4);
		for (int i = 1; i <= 6; i++) {
			std::string PicturePath = string("GamePicture/GameRun/Dog/Skill/OKBand-") + std::to_string(i) + ".bmp";
			std::sprintf(num_char, "%s", (PicturePath.c_str()));
			dogSkillOKBandHoverAnimation.AddBitmap(num_char);
		}

		// 初始化所有圖片位置
		// 攻擊倒三角
		AttackInvertedTriangle.SetTopLeft(1175, 546);
		// 技能按鈕
		catSkillDoubleAttackButton.SetTopLeft(123, 94);
		catSkillPowerAttackHoverAnimation.SetTopLeft(217, 97);
		catSkillPoisonGasHoverAnimation.SetTopLeft(310, 95);
		catSkillOKBandHoverAnimation.SetTopLeft(401, 95);
		dogSkillDoubleAttackButton.SetTopLeft(846, 97);
		dogSkillPowerAttackHoverAnimation.SetTopLeft(939, 96);
		dogSkillPoisonGasHoverAnimation.SetTopLeft(1033, 96);
		dogSkillOKBandHoverAnimation.SetTopLeft(1122, 97);

		// 所有技能按鈕的CPoint 左上(LT)與右下(RB)
		catSkillDoubleAttackButtonLT = CPoint(123, 94);
		catSkillDoubleAttackButtonRB = CPoint(204, 172);
		catSkillPowerAttackButtonLT = CPoint(217, 97);
		catSkillPowerAttackButtonRB = CPoint(298, 169);
		catSkillPoisonGasButtonLT = CPoint(310, 95);
		catSkillPoisonGasButtonRB = CPoint(388, 170);
		catSkillOKBandButtonLT = CPoint(401, 95);
		catSkillOKBandButtonRB = CPoint(479, 169);
		dogSkillDoubleAttackButtonLT = CPoint(846, 97);
		dogSkillDoubleAttackButtonRB = CPoint(926, 169);
		dogSkillPowerAttackButtonLT = CPoint(939, 96);
		dogSkillPowerAttackButtonRB = CPoint(1021, 170);
		dogSkillPoisonGasButtonLT = CPoint(1033, 96);
		dogSkillPoisonGasButtonRB = CPoint(1114, 173);
		dogSkillOKBandButtonLT = CPoint(1122, 97);
		dogSkillOKBandButtonRB = CPoint(1200, 172);

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{

	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_C = 0x43;
		const char KEY_D = 0x44;

		// debug專用 按C, D可以扣貓狗一滴血，
		if (nChar == KEY_C)
		{
			CatHealthPointBar.SubHP(100);
		}
		if (nChar == KEY_D)
		{
			DogHealthPointBar.SubHP(100);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		// 技能點擊
		if (runId == CAT_ATTACK_BEGIN)
		{
			bool isNotUsingSKill = (catSkillDoubleAttackStatus != USING && catSkillPowerAttackStatus != USING && catSkillPoisonGasStatus != USING && catSkillOKBandStatus != USING);
			// 連擊
			if (catSkillDoubleAttackStatus == IS_HOVER && isNotUsingSKill)
				catSkillDoubleAttackStatus = USING;
			// 重擊
			else if (catSkillPowerAttackStatus == IS_HOVER && isNotUsingSKill)
			{
				WeaponObject.setSize(2);
				catSkillPowerAttackStatus = USING;
			}
			// 毒氣
			else if (catSkillPoisonGasStatus == IS_HOVER && isNotUsingSKill)
				catSkillPoisonGasStatus = USING;
			// 治癒
			else if (catSkillOKBandStatus == IS_HOVER && isNotUsingSKill)
				catSkillOKBandStatus = USING;
		}
		else if (runId == DOG_ATTACK_BEGIN)
		{
			bool isNotUsingSKill = (dogSkillDoubleAttackStatus != USING && dogSkillPowerAttackStatus != USING && dogSkillPoisonGasStatus != USING && dogSkillOKBandStatus != USING);
			// 連擊
			if (dogSkillDoubleAttackStatus == IS_HOVER && isNotUsingSKill)
				dogSkillDoubleAttackStatus = USING;
			// 重擊
			else if (dogSkillPowerAttackStatus == IS_HOVER && isNotUsingSKill)
			{
				WeaponObject.setSize(2);
				dogSkillPowerAttackStatus = USING;
			}
			// 毒氣
			else if (dogSkillPoisonGasStatus == IS_HOVER && isNotUsingSKill)
				dogSkillPoisonGasStatus = USING;
			// 治癒
			else if (dogSkillOKBandStatus == IS_HOVER && isNotUsingSKill)
			{
				DogHealthPointBar.AddHP(30);
				dogSkillOKBandStatus = USED;
				runId = CAT_PREPARE;
			}
			// 正常攻擊蓄力
			else
			{
				runId = DOG_ATTACK_CHARGE;
				Timer = 0;
			}
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		if (runId == DOG_ATTACK_CHARGE) {
			runId = DOG_ATTACK_FIRE;
			WeaponObject.DogFire(Timer);
			if (dogSkillDoubleAttackStatus == USING)
				lastPower = Timer;
		}
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)
	{
		// Cat skill
		// 連擊
		if (catSkillDoubleAttackStatus != USED && catSkillDoubleAttackStatus != USING)
		{
			if (point.x > catSkillDoubleAttackButtonLT.x && point.x < catSkillDoubleAttackButtonRB.x && point.y > catSkillDoubleAttackButtonLT.y && point.y < catSkillDoubleAttackButtonRB.y)
				catSkillDoubleAttackStatus = IS_HOVER;
			else
				catSkillDoubleAttackStatus = IS_NOT_HOVER;
		}
		// 重擊
		if (catSkillPowerAttackStatus != USED && catSkillPowerAttackStatus != USING)
		{
			if (point.x > catSkillPowerAttackButtonLT.x && point.x < catSkillPowerAttackButtonRB.x && point.y > catSkillPowerAttackButtonLT.y && point.y < catSkillPowerAttackButtonRB.y)
				catSkillPowerAttackStatus = IS_HOVER;
			else
				catSkillPowerAttackStatus = IS_NOT_HOVER;
		}
		// 毒氣
		if (catSkillPoisonGasStatus != USED && catSkillPoisonGasStatus != USING)
		{
			if (point.x > catSkillPoisonGasButtonLT.x && point.x < catSkillPoisonGasButtonRB.x && point.y > catSkillPoisonGasButtonLT.y && point.y < catSkillPoisonGasButtonRB.y)
				catSkillPoisonGasStatus = IS_HOVER;
			else
				catSkillPoisonGasStatus = IS_NOT_HOVER;
		}
		// 治癒
		if (catSkillOKBandStatus != USED && catSkillOKBandStatus != USING)
		{
			if (point.x > catSkillOKBandButtonLT.x && point.x < catSkillOKBandButtonRB.x && point.y > catSkillOKBandButtonLT.y && point.y < catSkillOKBandButtonRB.y)
				catSkillOKBandStatus = IS_HOVER;
			else
				catSkillOKBandStatus = IS_NOT_HOVER;
		}
		// Dog skill
		// 連擊
		if (dogSkillDoubleAttackStatus != USED && dogSkillDoubleAttackStatus != USING)
		{
			if (point.x > dogSkillDoubleAttackButtonLT.x && point.x < dogSkillDoubleAttackButtonRB.x && point.y > dogSkillDoubleAttackButtonLT.y && point.y < dogSkillDoubleAttackButtonRB.y)
				dogSkillDoubleAttackStatus = IS_HOVER;
			else
				dogSkillDoubleAttackStatus = IS_NOT_HOVER;
		}
		// 重擊
		if (dogSkillPowerAttackStatus != USED && dogSkillPowerAttackStatus != USING)
		{
			if (point.x > dogSkillPowerAttackButtonLT.x && point.x < dogSkillPowerAttackButtonRB.x && point.y > dogSkillPowerAttackButtonLT.y && point.y < dogSkillPowerAttackButtonRB.y)
				dogSkillPowerAttackStatus = IS_HOVER;
			else
				dogSkillPowerAttackStatus = IS_NOT_HOVER;
		}
		// 毒氣
		if (dogSkillPoisonGasStatus != USED && dogSkillPoisonGasStatus != USING)
		{
			if (point.x > dogSkillPoisonGasButtonLT.x && point.x < dogSkillPoisonGasButtonRB.x && point.y > dogSkillPoisonGasButtonLT.y && point.y < dogSkillPoisonGasButtonRB.y)
				dogSkillPoisonGasStatus = IS_HOVER;
			else
				dogSkillPoisonGasStatus = IS_NOT_HOVER;
		}
		// 治癒
		if (dogSkillOKBandStatus != USED && dogSkillOKBandStatus != USING)
		{
			if (point.x > dogSkillOKBandButtonLT.x && point.x < dogSkillOKBandButtonRB.x && point.y > dogSkillOKBandButtonLT.y && point.y < dogSkillOKBandButtonRB.y)
				dogSkillOKBandStatus = IS_HOVER;
			else
				dogSkillOKBandStatus = IS_NOT_HOVER;
		}
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

		// Cat
		switch (runId)
		{
		case CAT_PREPARE:
			CatObject.OnShow(Normal);
			break;
		case CAT_ATTACK_TAKE:
			CatObject.OnShow(Attack_1);
			break;
		case CAT_ATTACK_BEGIN:
			CatObject.OnShow(Attack_2);
			break;
		case CAT_ATTACK_CHARGE:
			CatObject.OnShow(Attack_3);
			break;
		case CAT_ATTACK_FIRE:
			CatObject.OnShow(Attack_4);
			break;
		case CAT_BEGIN_ATTACKED_LITTLE:
			CatObject.OnShow(BeingAttacked_Little);
			break;
		case CAT_BEGIN_ATTACKED_BIG:
			CatObject.OnShow(BeingAttacked_Big);
			break;
		case CAT_BEGIN_ATTACKED_MISS:
			CatObject.OnShow(BeingAttacked_Miss);
			break;
		default:
			CatObject.OnShow(Normal);
			break;
		}

		// Dog
		switch (runId)
		{
		case DOG_PREPARE:
			DogObject.OnShow(Normal);
			break;
		case DOG_ATTACK_TAKE:
			DogObject.OnShow(Attack_1);
			break;
		case DOG_ATTACK_BEGIN:
			DogObject.OnShow(Attack_2);
			break;
		case DOG_ATTACK_CHARGE:
			DogObject.OnShow(Attack_3);
			break;
		case DOG_ATTACK_FIRE:
			DogObject.OnShow(Attack_4);
			break;
		case DOG_BEGIN_ATTACKED_LITTLE:
			DogObject.OnShow(BeingAttacked_Little);
			break;
		case DOG_BEGIN_ATTACKED_BIG:
			DogObject.OnShow(BeingAttacked_Big);
			break;
		case DOG_BEGIN_ATTACKED_MISS:
			DogObject.OnShow(BeingAttacked_Miss);
			break;
		default:
			DogObject.OnShow(Normal);
			break;
		}

		// 血量條
		CatHealthPointBar.OnShow();
		DogHealthPointBar.OnShow();

		// Weapon
		WeaponObject.OnShow(runId);

		// 技能hover動畫撥放
		// 二連擊
		if (catSkillDoubleAttackStatus != USED && catSkillDoubleAttackStatus != USING)
			catSkillDoubleAttackButton.ShowBitmap();
		// 重擊
		if (catSkillPowerAttackStatus != USED && catSkillPowerAttackStatus != USING)
			catSkillPowerAttackHoverAnimation.OnShow();
		// 毒氣
		if (catSkillPoisonGasStatus != USED && catSkillPoisonGasStatus != USING)
			catSkillPoisonGasHoverAnimation.OnShow();
		// 治癒
		if (catSkillOKBandStatus != USED && catSkillOKBandStatus != USING)
			catSkillOKBandHoverAnimation.OnShow();
		// Dog skill
		// 二連擊
		if (dogSkillDoubleAttackStatus != USED && dogSkillDoubleAttackStatus != USING)
			dogSkillDoubleAttackButton.ShowBitmap();
		// 重擊
		if (dogSkillPowerAttackStatus != USED && dogSkillPowerAttackStatus != USING)
			dogSkillPowerAttackHoverAnimation.OnShow();
		// 毒氣
		if (dogSkillPoisonGasStatus != USED && dogSkillPoisonGasStatus != USING)
			dogSkillPoisonGasHoverAnimation.OnShow();
		// 治癒
		if (dogSkillOKBandStatus != USED && dogSkillOKBandStatus != USING)
			dogSkillOKBandHoverAnimation.OnShow();
	}
}