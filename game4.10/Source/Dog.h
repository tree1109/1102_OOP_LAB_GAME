namespace game_framework {

	class Dog
	{
	public:
		Dog();
		void OnMove();					// 根據目前的條件改變狀態
		void OnShow();					// 根據目前的狀態貼上貓貓圖片
		void Initialize();				// 設定
		void LoadBitmap();

	protected:

		int DogPositionX;
		int DogPositionY;

		// 貓貓的圖片
		CMovingBitmap Dog_Normal;
		CMovingBitmap Dog_Normal_BadlyHurt;
		CMovingBitmap Dog_Attack_1;
		CMovingBitmap Dog_Attack_2;
		CMovingBitmap Dog_Attack_3;
		CMovingBitmap Dog_Attack_4;
		CMovingBitmap Dog_BeingAttacked_Big;
		CMovingBitmap Dog_BeingAttacked_Little;
		CMovingBitmap Dog_BeingAttacked_Miss;
		CMovingBitmap Dog_Weapon;
	};
}