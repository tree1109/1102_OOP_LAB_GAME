namespace game_framework {

	class Dog
	{
	public:
		Dog();
		void OnMove();					// �ھڥثe��������ܪ��A
		void OnShow();					// �ھڥثe�����A�K�W�߿߹Ϥ�
		void Initialize();				// �]�w
		void LoadBitmap();

	protected:

		int DogPositionX;
		int DogPositionY;

		// �߿ߪ��Ϥ�
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