/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// �P�_�n��ܪ��e��
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		// �C���}�l�e������
		bool gameStartMusicHadNotPlay;

		// �C���}�l�e���I���ʵe
		CAnimation StartButtonBackground;

		// �C���}�l�e��
		CMovingBitmap StartButton_noHover;
		CMovingBitmap StartButton_hover;

		// �C���j���e��
		CMovingBitmap FleabagVsMutt_noHover;
		CMovingBitmap FleabagVsMutt_hoverHowToPlay;
		CMovingBitmap FleabagVsMutt_hoverLetsPlay;
		CAnimation FleabagVsMutt_titleCat;

		// �C�������e��
		CMovingBitmap HowToPlay_noHover;
		CMovingBitmap HowToPlay_hover;

		// ���a�H�ƿ�ܵe��
		CMovingBitmap ChooseGame_noHover;
		CMovingBitmap ChooseGame_hover1P;
		CMovingBitmap ChooseGame_hover2P;

		// ��ܹC�����׭����U���װʵe
		CAnimation SelectYourLevel_hoverBeginnerAnimation;
		CAnimation SelectYourLevel_hoverAverageAnimation;
		CAnimation SelectYourLevel_hoverBringItOnAnimation;

		// ��ܹC�����׭���
		CMovingBitmap SelectYourLevelBackground;
		CMovingBitmap SelectYourLevel_hoverBeginner;
		CMovingBitmap SelectYourLevel_hoverAverage;
		CMovingBitmap SelectYourLevel_hoverBringItOn;

		// �{�b���e�����A
		GAME_PAGE_ID CurrentPage;

		// �Ҧ����s��CPoint ���W(LT)�P�k�U(RB)
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
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		// ����
		bool catAttackIsNotPlaying;
		bool dogAttackIsNotPlaying;
		bool gameRunMusicHadNotPlay;

		// �԰���
		CMovingBitmap Background;

		// ���� �߿�
		Dog	DogObject;
		Cat	CatObject;
		Weapon WeaponObject;

		// �����ˤT��
		CAnimation CatAttackInvertedTriangle;
		CAnimation DogAttackInvertedTriangle;

		// ��q��
		CatHP CatHealthPointBar;
		DogHP DogHealthPointBar;

		GAME_RUN_ID runId;
		int Timer;
		int lastPower;

		// �ޯબ�A
		SKILL_STATUS catSkillDoubleAttackStatus;
		SKILL_STATUS catSkillPowerAttackStatus;
		SKILL_STATUS catSkillPoisonGasStatus;
		SKILL_STATUS catSkillOKBandStatus;
		SKILL_STATUS dogSkillDoubleAttackStatus;
		SKILL_STATUS dogSkillPowerAttackStatus;
		SKILL_STATUS dogSkillPoisonGasStatus;
		SKILL_STATUS dogSkillOKBandStatus;

		// �ޯ���s�Ϥ�
		CMovingBitmap catSkillDoubleAttackButton;
		CMovingBitmap dogSkillDoubleAttackButton;

		// �ޯ���shover�ʵe
		CAnimation catSkillPowerAttackHoverAnimation;
		CAnimation catSkillPoisonGasHoverAnimation;
		CAnimation catSkillOKBandHoverAnimation;
		CAnimation dogSkillPowerAttackHoverAnimation;
		CAnimation dogSkillPoisonGasHoverAnimation;
		CAnimation dogSkillOKBandHoverAnimation;

		// �Ҧ����s��CPoint ���W(LT)�P�k�U(RB)
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
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		bool isHoverReplay;

		// �C���}�l�e������
		bool gameOverMusicHadNotPlay;

		// �߿�Ĺ�F
		CMovingBitmap CatWin_background;
		CMovingBitmap CatWin_replayHover;
		CAnimation CatWin_titleAnimation;
		CAnimation CatWin_catAnimation;
		CAnimation CatWin_dogAnimation;
		
		// ����Ĺ�F
		CMovingBitmap DogWin_background;
		CMovingBitmap DogWin_replayHover;
		CAnimation DogWin_catAnimation;
		CAnimation DogWin_dogAnimation;

		// replay���s��CPoint ���W(LT)�P�k�U(RB)
		CPoint CatWin_ReplayButtonLT;
		CPoint CatWin_ReplayButtonRB;
		CPoint DogWin_ReplayButtonLT;
		CPoint DogWin_ReplayButtonRB;
	};

}