/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "GAMEID.h"
#include "Cat.h"
#include "Dog.h"
#include "Weapon.h"
#include "GameData.h"
#include "CatHP.h"
#include "DogHP.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 判斷要顯示的畫面
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// 遊戲開始畫面音樂
		bool gameStartMusicHadNotPlay;

		// 遊戲開始畫面背景動畫
		CAnimation StartButtonBackground;

		// 遊戲開始畫面
		CMovingBitmap StartButton_noHover;
		CMovingBitmap StartButton_hover;

		// 遊戲大綱畫面
		CMovingBitmap FleabagVsMutt_noHover;
		CMovingBitmap FleabagVsMutt_hoverHowToPlay;
		CMovingBitmap FleabagVsMutt_hoverLetsPlay;
		CAnimation FleabagVsMutt_titleCat;

		// 遊戲說明畫面
		CMovingBitmap HowToPlay_noHover;
		CMovingBitmap HowToPlay_hover;

		// 玩家人數選擇畫面
		CMovingBitmap ChooseGame_noHover;
		CMovingBitmap ChooseGame_hover1P;
		CMovingBitmap ChooseGame_hover2P;

		// 選擇遊戲難度頁面各難度動畫
		CAnimation SelectYourLevel_hoverBeginnerAnimation;
		CAnimation SelectYourLevel_hoverAverageAnimation;
		CAnimation SelectYourLevel_hoverBringItOnAnimation;

		// 選擇遊戲難度頁面
		CMovingBitmap SelectYourLevelBackground;
		CMovingBitmap SelectYourLevel_hoverBeginner;
		CMovingBitmap SelectYourLevel_hoverAverage;
		CMovingBitmap SelectYourLevel_hoverBringItOn;

		// 現在的畫面狀態
		GAME_PAGE_ID CurrentPage;

		// 所有按鈕的CPoint 左上(LT)與右下(RB)
		CPoint StartPage_StartButtonLT;
		CPoint StartPage_StartButtonRB;
		CPoint FleabagVsMuttPage_HowToPlayButtonLT;
		CPoint FleabagVsMuttPage_HowToPlayButtonRB;
		CPoint FleabagVsMuttPage_LetsPlayButtonLT;
		CPoint FleabagVsMuttPage_LetsPlayButtonRB;
		CPoint HowToPlayPage_LetsPlayButtonLT;
		CPoint HowToPlayPage_LetsPlayButtonRB;
		CPoint ChooseGamePage_1PlayerButtonLT;
		CPoint ChooseGamePage_1PlayerButtonRB;
		CPoint ChooseGamePage_2PlayerButtonLT;
		CPoint ChooseGamePage_2PlayerButtonRB;
		CPoint SelectYourLevelPage_ImBeginnerButtonLT;
		CPoint SelectYourLevelPage_ImBeginnerButtonRB;
		CPoint SelectYourLevelPage_ImAverageButtonLT;
		CPoint SelectYourLevelPage_ImAverageButtonRB;
		CPoint SelectYourLevelPage_BringItOnButtonLT;
		CPoint SelectYourLevelPage_BringItOnButtonRB;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// 音效
		bool catAttackIsNotPlaying;
		bool dogAttackIsNotPlaying;
		bool gameRunMusicHadNotPlay;

		// 戰鬥中
		CMovingBitmap Background;

		// 狗勾 貓貓
		Dog	DogObject;
		Cat	CatObject;
		Weapon WeaponObject;

		// 攻擊倒三角
		CAnimation CatAttackInvertedTriangle;
		CAnimation DogAttackInvertedTriangle;

		// 血量條
		CatHP CatHealthPointBar;
		DogHP DogHealthPointBar;

		GAME_RUN_ID runId;
		int Timer;
		int lastPower;

		// 技能狀態
		SKILL_STATUS catSkillDoubleAttackStatus;
		SKILL_STATUS catSkillPowerAttackStatus;
		SKILL_STATUS catSkillPoisonGasStatus;
		SKILL_STATUS catSkillOKBandStatus;
		SKILL_STATUS dogSkillDoubleAttackStatus;
		SKILL_STATUS dogSkillPowerAttackStatus;
		SKILL_STATUS dogSkillPoisonGasStatus;
		SKILL_STATUS dogSkillOKBandStatus;

		// 技能按鈕圖片
		CMovingBitmap catSkillDoubleAttackButton;
		CMovingBitmap dogSkillDoubleAttackButton;

		// 技能按鈕hover動畫
		CAnimation catSkillPowerAttackHoverAnimation;
		CAnimation catSkillPoisonGasHoverAnimation;
		CAnimation catSkillOKBandHoverAnimation;
		CAnimation dogSkillPowerAttackHoverAnimation;
		CAnimation dogSkillPoisonGasHoverAnimation;
		CAnimation dogSkillOKBandHoverAnimation;

		// 所有按鈕的CPoint 左上(LT)與右下(RB)
		CPoint catSkillDoubleAttackButtonLT;
		CPoint catSkillDoubleAttackButtonRB;
		CPoint catSkillPowerAttackButtonLT;
		CPoint catSkillPowerAttackButtonRB;
		CPoint catSkillPoisonGasButtonLT;
		CPoint catSkillPoisonGasButtonRB;
		CPoint catSkillOKBandButtonLT;
		CPoint catSkillOKBandButtonRB;
		CPoint dogSkillDoubleAttackButtonLT;
		CPoint dogSkillDoubleAttackButtonRB;
		CPoint dogSkillPowerAttackButtonLT;
		CPoint dogSkillPowerAttackButtonRB;
		CPoint dogSkillPoisonGasButtonLT;
		CPoint dogSkillPoisonGasButtonRB;
		CPoint dogSkillOKBandButtonLT;
		CPoint dogSkillOKBandButtonRB;

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		bool isHoverReplay;

		// 遊戲開始畫面音樂
		bool gameOverMusicHadNotPlay;

		// 貓貓贏了
		CMovingBitmap CatWin_background;
		CMovingBitmap CatWin_replayHover;
		CAnimation CatWin_titleAnimation;
		CAnimation CatWin_catAnimation;
		CAnimation CatWin_dogAnimation;
		
		// 狗溝贏了
		CMovingBitmap DogWin_background;
		CMovingBitmap DogWin_replayHover;
		CAnimation DogWin_catAnimation;
		CAnimation DogWin_dogAnimation;

		// replay按鈕的CPoint 左上(LT)與右下(RB)
		CPoint CatWin_ReplayButtonLT;
		CPoint CatWin_ReplayButtonRB;
		CPoint DogWin_ReplayButtonLT;
		CPoint DogWin_ReplayButtonRB;
	};

}