/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	// Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//


	// ��l�ƹC�����A
	CurrentPage = START_BUTTON_PAGE_NO_HOVER;

	// �[���C���}�l�e���Ϥ�
	// �C���}�l�e��
	StartButton_noHover.LoadBitmap("GamePicture/GameInit/StartButton_noHover.bmp");
	StartButton_hover.LoadBitmap("GamePicture/GameInit/StartButton_hover.bmp");

	// �C���j���e��
	FleabagVsMutt_noHover.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_noHover.bmp");
	FleabagVsMutt_hoverHowToPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverHowToPlay.bmp");
	FleabagVsMutt_hoverLetsPlay.LoadBitmap("GamePicture/GameInit/FleabagVsMutt_hoverLetsPlay.bmp");

	// �C�������e��
	HowToPlay_noHover.LoadBitmap("GamePicture/GameInit/HowToPlay_noHover.bmp");
	HowToPlay_hover.LoadBitmap("GamePicture/GameInit/HowToPlay_hover.bmp");

	// ��ܹC�����׭���
	SelectYourLevel_noHover.LoadBitmap("GamePicture/GameInit/SelectYourLevel_noHover.bmp");
	SelectYourLevel_hoverBeginner.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBeginner.bmp");
	SelectYourLevel_hoverAverage.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverAverage.bmp");
	SelectYourLevel_hoverBringItOn.LoadBitmap("GamePicture/GameInit/SelectYourLevel_hoverBringItOn.bmp");

	// ��l�ƩҦ��Ϥ���m�A�]�����O��ӵe���ҥH�]�m�b(0, 0)��m
	StartButton_noHover.SetTopLeft(0, 0);
	StartButton_hover.SetTopLeft(0, 0);
	FleabagVsMutt_noHover.SetTopLeft(0, 0);
	FleabagVsMutt_hoverHowToPlay.SetTopLeft(0, 0);
	FleabagVsMutt_hoverLetsPlay.SetTopLeft(0, 0);
	HowToPlay_noHover.SetTopLeft(0, 0);
	HowToPlay_hover.SetTopLeft(0, 0);
	SelectYourLevel_noHover.SetTopLeft(0, 0);
	SelectYourLevel_hoverBeginner.SetTopLeft(0, 0);
	SelectYourLevel_hoverAverage.SetTopLeft(0, 0);
	SelectYourLevel_hoverBringItOn.SetTopLeft(0, 0);

	// �Ҧ����s��CPoint ���W�P�k�U
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
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{

	if (CurrentPage == START_BUTTON_PAGE_NO_HOVER || CurrentPage == START_BUTTON_PAGE_HOVER) {
		if (point.x > StartPage_StartButtonLT.x && point.x < StartPage_StartButtonRB.x && point.y > StartPage_StartButtonLT.y && point.y < StartPage_StartButtonRB.y)
			CurrentPage = START_BUTTON_PAGE_HOVER;
		else
			CurrentPage = START_BUTTON_PAGE_NO_HOVER;
	}

}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (CurrentPage == START_BUTTON_PAGE_HOVER)
		CurrentPage = FLEABAG_VS_MUTT_PAGE_NO_HOVER;
	// GotoGameState(GAME_STATE_RUN);
}

void CGameStateInit::OnMove()
{

}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC




	if (CurrentPage == START_BUTTON_PAGE_NO_HOVER) {
		StartButton_noHover.ShowBitmap();
	}
	else if (CurrentPage == START_BUTTON_PAGE_HOVER) {
		StartButton_hover.ShowBitmap();
	}
	else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_NO_HOVER) {
		FleabagVsMutt_noHover.ShowBitmap();
	}
	else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_HOW_TO_PLAY) {
		FleabagVsMutt_hoverHowToPlay.ShowBitmap();
	}
	else if (CurrentPage == FLEABAG_VS_MUTT_PAGE_HOVER_LETS_PLAY) {
		FleabagVsMutt_hoverLetsPlay.ShowBitmap();
	}
	else if (CurrentPage == HOW_TO_PLAY_PAGE_NO_HOVER) {
		HowToPlay_noHover.ShowBitmap();
	}
	else if (CurrentPage == HOW_TO_PLAY_PAGE_HOVER) {
		HowToPlay_hover.ShowBitmap();
	}
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
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
	for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// ���ʲy
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// �������l
	//
	eraser.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// ���ʼu�����y
	//
	bball.OnMove();
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	eraser.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// �K�W��i���y
	bball.OnShow();						// �K�W�u�����y
	eraser.OnShow();					// �K�W���l
	//
	//  �K�W���W�Υk�U��������
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();
}
}