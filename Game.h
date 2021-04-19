// ---------------------------------------------------------------------------
// ������ GameH
#ifndef GameH
#define GameH
// ���������� ������� �����
#include "Main.h"
// ---------------------------------------------------------------------------

// ����� ������� ������� (����� ���� ������� ��� ���� ������� ��������, �� ���� �� ���� ����������� ������ PlayerCar, CarOpponent, Bonus)
class GameObject {
	// protected ������, �� ���� ���������� ������, ������ ����� ������� ������������
protected:
	// �������� ��������
	// TImage* im;
	// ������ ���������� ����� � ���������
	AnsiString path;

	// private ������, �� ���� �������� ������, � ��� ����� ���������� ������ ������ ������ GAMEOBJECT
private:
	// ���������� ���������� �������� (���� ������)
	int xLeft; // ����� x
	int xRight; // ������ x
	int yTop; // ������� y
	int yBottom; // ������ y

	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	TImage* im;
	int typeBonus;
	// ���������� ��� �������� ��������
	int newCoord;

	// ����������� ������ �� ���������!!!!
	GameObject() {
		// ����������� ��������� �������� �����������
		typeBonus = 0; // ��� ������
		newCoord = 0;
		// ����� ����������, ��� �����, ������, ������� ���������� - ��� �������� ����, ��� ������ - ����, �����
		xLeft = 0; // ����� x
		xRight = 0; // ������ x
		yTop = 0; // ������� y
		yBottom = 0; // ������ y
	}

	// ����������� ������ ������� ��� ���������, ������ ��� ����������
	~GameObject() {
		// ������� ��������� �� �������� (��������)
		delete im;
	}
	// ������� ������, ����� ������� ������ ��������� ������� (��������� ��� �� �������� - �������� � �� ��������)
	// int/ void - ��� ������������ �������� �������
	// ������� ���������� ����� ����� (������ � ����������)
	int GetRightX();
	// ������� ���������� ����� ����� (����� � ����������)
	int GetLeftX();
	// ������� ���������� ����� ����� (������� Y ����������)
	int GetTopY();
	// ������� ���������� ����� ����� (������ Y ����������)
	int GetBottomY();
	// void - ������ �� ����������!!!
	// ������� � ����������, ������� ������������� ����� ���������
	void SetLeftX(int xLeft);
	void SetRightX(int xRight);
	void SetTopY(int yTop);
	void SetBottomY(int yBottom);

	// ����������� �������(�������, ������� ����������� � �� ����� ��������������)
	// ������� ��������� ��������
	virtual void DrawObj(int newXLeft) {
	}
};

// ����� ������� ������, ����������� �� �������� ������ GameObject
class PlayerCar : public GameObject {
	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	// ����������� ������
	PlayerCar() {
		// ������������� ���� ��������
		path = "D:\\�������\\Win32\\Debug\\Car1.png";
		// ������� ����� ��������, � ��������� �������� ������������, �� ���� �����, ��� ����� ������������ ��������!!!
		im = new TImage(GameForm);
		im->Width = 75; // ������ ��������
		im->Height = 100; // ������ ��������
		im->Left = 255; // ����� ���������� �� ����
		im->Top = 800; // ���������� ����� ��������
		im->Picture->LoadFromFile(path);
		// ��������� ���� �������� � ����� ���������� ����
		SetLeftX(im->Left); // ������������� ����� ���
		SetRightX(im->Left + im->Width); // ������������� ������ ���
		SetTopY(im->Top); // ������������� ������� Y
		SetBottomY(im->Top + im->Height); // ������������� ������ �
		im->Parent = GameForm;
		// ����� �� ������� ����� �������� (�������� ��������)
	}
	// ���������������� ������� ��������� ������� � ���������� ����� ���������� �������� (��������)
	void DrawObj(int newXLeft);
};

// ����� ������, ����������� �� �������� GameObject
class Road : public GameObject {
	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	// ����������� ������
	Road(int TopY) {
		// ������������� ���� ��������
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		path = "D:\\�������\\Win32\\Debug\\Road.png";
		im = new TImage(GameForm); // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Width = 508;
		im->Height = 408;
		im->Left = 200; // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Top = TopY;
		im->Stretch = true;
		// im->Proportional = true;
		im->Picture->LoadFromFile(path);
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top); // ������ ������� 70, ��� ��� ��� ��!!!!!
		SetBottomY(im->Top + im->Height);
		im->Parent = GameForm;
		// ������ ������� 70, ��� ��� ��� ��!!!!!
	}
	// ���������������� ������� ��������� ������ � ���������� ����� ���������� �������� (��������)
	void DrawObj(int newTopY);
};

// ����� ������� �����������, ����������� �� �������� ������ GameObject
class OpponentCar : public GameObject {
	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	// ����������� ������
	OpponentCar(int LeftX, int TopY, int typeCar) {
		// ������������� ���� ��������
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		path = "D:\\�������\\Win32\\Debug\\Car";
		path += typeCar;
		path += ".png";
		im = new TImage(GameForm); // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Width = 75;
		im->Height = 100;
		im->Left = LeftX; // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Top = TopY;
		im->Picture->LoadFromFile(path);
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top);
		SetBottomY(im->Top + im->Height);
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Parent = GameForm; // ������ ������� 70, ��� ��� ��� ��!!!!!
	}
	// ���������������� ������� ��������� ������� �������� � ���������� ����� ���������� �������� (��������)
	void DrawObj(int newTopY);
};

// ����� �����, ����������� �� �������� ������ GameObject
class Bonus : public GameObject {
	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	// ��� ������, �� �������� ����� ���������� ��� ������ � ��� ��������
	// int typeBonus;
	// ����������� ������ � �����������
	Bonus(int LeftX, int TopY, int typeBonus_) {
		typeBonus = typeBonus_;
		path = "D:\\�������\\Win32\\Debug\\Bonus";
		path += typeBonus;
		path += ".png";
		im = new TImage(GameForm); // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Width = 50;
		im->Height = 50;
		im->Left = LeftX; // ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Top = TopY;
		im->Stretch = true;
		// LeftOpponentCar = LeftX;
		// im->Proportional = true;
		im->Picture->LoadFromFile(path);
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top);
		SetBottomY(im->Top + im->Height);
		// ������ ������� 70, ��� ��� ��� ��!!!!!
		im->Parent = GameForm; // ������ ������� 70, ��� ��� ��� ��!!!!!
	}
	// ���������������� ������� ��������� ������ � ���������� ����� ���������� �������� (��������)
	void DrawObj(int newTopY);
};

// �����, ������� ����� ������������ ��� ������� ����
class Game {
	// public ������, �� ���� � ���� ����������/�������� ������� ������ �����, � ����� �������
public:
	bool game_;
	bool immortality;
	// ������ GameObject
	GameObject* gameObject[12];

	// ����������� ������ �� ���������, ������� �������
	Game() {
		game_ = false;
		immortality = false;
		// �������� ������ ��� ������ ������
		// ������ ��� 1 ����� ������
		gameObject[1] = new Road(-100);
		// ������ ��� 2 ����� ������
		gameObject[2] = new Road(300);
		// ������ ��� 3 ����� ������
		gameObject[3] = new Road(700);
		// // ������ ��� 4 ����� ������
		gameObject[4] = new Road(800);
		// ������ ��� ������� ������
		gameObject[0] = new PlayerCar();
		// ������ ��� ������� ����������
		gameObject[5] = new OpponentCar(300, -100, 1);
		// ������ ��� ������� ����������
		gameObject[6] = new OpponentCar(300, -100, 1);
		// ������ ��� ������� ����������
		gameObject[7] = new OpponentCar(300, -100, 1);
		// ������ ��� �����
		gameObject[8] = new Bonus(300, 100, 1);
	}

	// ����������� ������, ������� ��������� �� ������� �������
	~Game() {
		// ������� � ����� ���� ��������
		for (int i = 0; i < 9; i++) {
			// �������� �� �������
			if (gameObject[i] != NULL) {
				// ������� ������� �������
				delete gameObject[i];
			}
		}
	}
	// ��� ������� �������, � ���������� -  int speedcar - ��������
	void GamePlay(int speedCar);
	// �������� ������
	void BonusActive();
};

#endif
