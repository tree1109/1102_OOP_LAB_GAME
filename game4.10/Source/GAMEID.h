#pragma once

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	// 定義畫面的狀態
	enum GAME_PAGE_ID {
		ABOUT_PICTURE,
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

	// 定義遊玩中，現在是貓還是狗攻擊的狀態
	enum GAME_RUN_ID {
		CAT_PREPARE,
		CAT_ATTACK_TAKE,
		CAT_ATTACK_BEGIN,
		CAT_ATTACK_CHARGE,
		CAT_ATTACK_FIRE,
		CAT_BEGIN_ATTACKED_MISS,
		CAT_BEGIN_ATTACKED_LITTLE,
		CAT_BEGIN_ATTACKED_BIG,
		DOG_PREPARE,
		DOG_ATTACK_TAKE,
		DOG_ATTACK_BEGIN,
		DOG_ATTACK_CHARGE,
		DOG_ATTACK_FIRE,
		DOG_BEGIN_ATTACKED_MISS,
		DOG_BEGIN_ATTACKED_LITTLE,
		DOG_BEGIN_ATTACKED_BIG
	};

	enum PICTURE_STATUS {
		Normal,
		Normal_BadlyHurt,
		Attack_1,
		Attack_2,
		Attack_3,
		Attack_4,
		BeingAttacked_Big,
		BeingAttacked_Little,
		BeingAttacked_Miss
	};

	enum class GAME_LEVEL {
		ImaBeginner,
		ImAverage,
		BringItOn
	};

	// 定義技能的狀態
	enum SKILL_STATUS {
		IS_NOT_HOVER,
		IS_HOVER,
		USED,
		USING
	};

	// 定義各種音效的編號 0~15
	enum AUDIO_ID {	
		AUDIO_SINGLE,				// GameInit 開頭按鈕, 單人遊戲
		AUDIO_SINGLE_SHORT,			// GameInit 其他畫面按鈕, GameRun 玩家開始
		AUDIO_DOUBLE,				// GameInit 雙人遊戲, GameOver 重完按鈕
		AUDIO_INIT_MUSIC,			// GameInit 開頭畫面音樂
		AUDIO_OVER_MUSIC,			// GameOver 遊戲結束音樂
		AUDIO_RUNSTART_MUSIC,		// GameRun 遊戲開始音樂
		AUDIO_COM_SKILL_HEAL,		// 共用:	治癒技能
		AUDIO_CAT_SKILL,			// 貓:	技能
		AUDIO_CAT_ATTACK,			//		發射武器
		AUDIO_CAT_ATTACKED_BIG,		//		受到重擊
		AUDIO_CAT_ATTACKED_LITTLE,	//		受到輕擊
		AUDIO_CAT_ATTACKED_MISS,	//		沒有擊中
		AUDIO_DOG_SKILL,			// 狗:	技能
		AUDIO_DOG_ATTACK,			//		發射武器
		AUDIO_DOG_ATTACKED_BIG,		//		受到重擊
		AUDIO_DOG_ATTACKED_LITTLE,	//		受到輕擊
		AUDIO_DOG_ATTACKED_MISS,	//		沒有擊中
	};
}