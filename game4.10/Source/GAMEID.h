#pragma once

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

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
}