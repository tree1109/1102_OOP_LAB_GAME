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

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Cat.h"
#include "Dog.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	// �w�q�e�������A
	enum GAME_PAGE_ID {
		START_BUTTON_PAGE_NO_HOVER,
		START_BUTTON_PAGE_HOVER,
		FLEABAG_VS_MUTT_PAGE_NO_HOVER,
		FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY,
		FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY,
		HOW_TO_PLAY_PAGE_NO_HOVER,
		HOW_TO_PLAY_PAGE_HOVER,
		CHOOSE_GAME_PAGE_NO_HOVER,
		CHOOSE_GAME_PAGE_HOVER_1PLAYER,
		CHOOSE_GAME_PAGE_HOVER_2PLAYER,
		SELECT_YOUR_LEVEL_PAGE_NO_HOVER,
		SELECT_YOUR_LEVEL_PAGE_HOVER_BEGINNER,
		SELECT_YOUR_LEVEL_PAGE_HOVER_AVERAGE,
		SELECT_YOUR_LEVEL_PAGE_HOVER_BRING_IT_ON
	};

	// �w�q�C�����A�{�b�O���٬O�����������A
	enum GAME_RUN_ID {
		DOG_PREPARE,
		DOG_ATTACK_BEGIN,
		DOG_ATTACK_CHARGE,
		DOG_ATTACK_FIRE,
		CAT_PREPARE,
		CAT_ATTACK_BEGIN,
		CAT_ATTACK_CHARGE,
		CAT_ATTACK_FIRE
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// �P�_�n��ܪ��e��
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo


		// �C���}�l�e��
		CMovingBitmap StartButton_noHover;
		CMovingBitmap StartButton_hover;

		// �C���j���e��
		CMovingBitmap FleabagVsMutt_noHover;
		CMovingBitmap FleabagVsMutt_hoverHowToPlay;
		CMovingBitmap FleabagVsMutt_hoverLetsPlay;

		// �C�������e��
		CMovingBitmap HowToPlay_noHover;
		CMovingBitmap HowToPlay_hover;

		// ���a�H�ƿ�ܵe��
		CMovingBitmap ChooseGame_noHover;
		CMovingBitmap ChooseGame_hover1P;
		CMovingBitmap ChooseGame_hover2P;

		// ��ܹC�����׭���
		CMovingBitmap SelectYourLevel_noHover;
		CMovingBitmap SelectYourLevel_hoverBeginner;
		CMovingBitmap SelectYourLevel_hoverAverage;
		CMovingBitmap SelectYourLevel_hoverBringItOn;

		// �{�b���e�����A
		GAME_PAGE_ID CurrentPage;

		// �Ҧ����s��CPoint ���W�P�k�U
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
		CGameStateRun(CGame *g);
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
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y


		// �԰���
		CMovingBitmap Background;

		// ���� �߿�
		Dog	DogObject;
		Cat	CatObject;

	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}