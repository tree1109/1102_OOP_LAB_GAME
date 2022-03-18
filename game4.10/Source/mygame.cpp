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

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	// Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//


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
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
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
	//
	// 貼上logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC



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

CGameStateOver::CGameStateOver(CGame *g)
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
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI


	// 初始化貓咪跟狗狗物件
	CatObject.Initialize();
	DogObject.Initialize();

	// 一開始由狗先行攻擊
	runId = DOG_PREPARE;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// 移動擦子
	//
	eraser.OnMove();
	//
	// 判斷擦子是否碰到球
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// 移動彈跳的球
	//
	bball.OnMove();
		


	if (runId == CAT_PREPARE) {
		runId = CAT_ATTACK_BEGIN;
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
		runId = DOG_ATTACK_BEGIN;
	}
	else if (runId == DOG_ATTACK_BEGIN) {
		runId = DOG_ATTACK_CHARGE;
	}
	else if (runId == DOG_ATTACK_CHARGE) {
		runId = DOG_ATTACK_FIRE;
	}
	else if (runId == DOG_ATTACK_FIRE) {
		runId = CAT_PREPARE;
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();								// 載入第i個球的圖形
	eraser.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//


	// 載入所有戰鬥中的圖片
	// 背景
	Background.LoadBitmap("GamePicture/GameRun/Background.bmp");
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	background.ShowBitmap();			// 貼上背景圖
	help.ShowBitmap();					// 貼上說明圖
	hits_left.ShowBitmap();
	for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// 貼上第i號球
	bball.OnShow();						// 貼上彈跳的球
	eraser.OnShow();					// 貼上擦子
	//
	//  貼上左上及右下角落的圖
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();


	// 顯示背景
	Background.ShowBitmap();


	// 顯示武器
	// Dog_Weapon.ShowBitmap();
	// Cat_Weapon.ShowBitmap();

	// 顯示貓貓狗狗
	// CatObject.OnShow(runId);
	// DogObject.OnShow(runId);

	// 根據狀態
	if (runId == CAT_PREPARE) {
		CatObject.OnShow(Normal);
		Sleep(1000);
	}
	else if (runId == CAT_ATTACK_BEGIN) {
		CatObject.OnShow(Attack_1);
		Sleep(2000);
		CatObject.OnShow(Attack_2);
		Sleep(800);
	}
	else if (runId == CAT_ATTACK_CHARGE) {
		CatObject.OnShow(Attack_3);
		Sleep(2000);
	}
	else if (runId == CAT_ATTACK_FIRE) {
		CatObject.OnShow(Attack_4);
		Sleep(2000);
	}
	else {
		CatObject.OnShow(Normal);
	}


	if (runId == DOG_PREPARE) {
		DogObject.OnShow(Normal);
		Sleep(1000);
	}
	else if (runId == DOG_ATTACK_BEGIN) {
		DogObject.OnShow(Attack_1);
		Sleep(800);
		DogObject.OnShow(Attack_2);
		Sleep(800);
	}
	else if (runId == DOG_ATTACK_CHARGE) {
		DogObject.OnShow(Attack_3);
		Sleep(2000);
	}
	else if (runId == DOG_ATTACK_FIRE) {
		DogObject.OnShow(Attack_4);
		Sleep(2000);
	}
	else {
		DogObject.OnShow(Normal);
	}

}
}