// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Game.h"
#include "ctime.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// ���������� ���������� - ����� ������� ��������� � ����� ������� ���� ����� �����, ������ �����!!!!
TGameForm *GameForm; // ��������� �� �����
Game* game; // ��������� �� ����� Game
bool game_ = false; // ��������� ���� / true -  ������ / false - �� ������
// ����������, ������� ����������, ����� ���������� �������
bool nextCar = false;
bool lookBonus = false; // ����������, ��� ���������� - ���������� �� �������� ������ �� �����
int time_spown[2] = {0, 0}; // ����� ������ �������, ������, ������ ������� ����� ��� 2, ������ ��� 1 �������
int state[2] = {0, 0}; // ��������� ������������ �������, 0 - �����, 1 - ������
int bonusSpown = 0; // ������� ������ ������
int speedCar = 15; // �������� ������� � ������
int score = 0; // ���� ������
int countCarWin = 0;
// ���������� �����, ������� �������� (����� 2 ������, ������� �� ����)
int defaultScore = 0;
// ��������������� ���������� ��� ������ �����, ������� ��������
int distanceByCar = 225; // ���������� ����� ��������
int countPlusSpeed = 50;

// ---------------------------------------------------------------------------
// ����������� ������ TFORM
__fastcall TGameForm::TGameForm(TComponent* Owner) : TForm(Owner) {
	// �������� ������
	srand(time(NULL));
	// �������� ������
	randomize();
}

// ---------------------------------------------------------------------------
// ������� ������
void __fastcall TGameForm::VisibleMainMenu()
{
	// ��������� ��������� 3 ������
	BtnPlay->Visible = true; // ������
	BtnDocument->Visible = true; // ������������
	BtnRegulations->Visible = true; // �������
}
// ---------------------------------------------------------------------------
void __fastcall TGameForm::VisibleGameComponent()
{
	// ��������� ��������� �����
	Image3->Visible = true;
	Label1->Visible = true;
	Label2->Visible = true;
	Label3->Visible = true;
}
// ������� ������
void __fastcall TGameForm::NOVisibleGameComponent()
{
	// ��������� ��������� �����
	Image3->Visible = false;
	Image5->Visible = false;
	Label1->Visible = false;
	Label2->Visible = false;
	Label3->Visible = false;
}

// ������� ������
void _fastcall TGameForm::VisibleGameOverMenu() {
	// ��������� ��������� 3 ������
	BtnPlay->Visible = false; // ������
	BtnDocument->Visible = false; // ������������
	BtnRegulations->Visible = false; // �������
}

// ---------------------------------------------------------------------------
// ������, ���������� �������, �������� 10 ����������
void __fastcall TGameForm::Timer1Timer(TObject *Sender) {
	// ��������, ���� ����, ��...
	if (game->game_)
	{
		// ����������, �������� ���� �������� � ������ ���������� ����� ���������
		// �������, ���� �������� 50 �������, ���� �������� �� ��� �����, �� ����� ������ ����, � ��������,
		// ����� ��������� ������ ���� ��� ��� ��� ������ �������
		if (countCarWin % countPlusSpeed == 0 && countCarWin / countPlusSpeed >=
			0 && countCarWin != defaultScore)
		{
			// �������� ������� �� 1 ������
			speedCar++;
			// ��������� ���������� ����� ���������
			distanceByCar-=25;
			// ���������� ���������� ���������� � �������������� ����������
			defaultScore = countCarWin;
		}
		// ��������� ������� ������� ������ �������
		time_spown[0]++;
		// ���� ������� ������ ������� ������ 75, ��������� ����� �������
		if (time_spown[0] > 75) {
			// ��������� ��������� ������� ������ �������
			nextCar = true;
		}
		// ���� ����� ����� �������, ��������� ������� �� ������
		if (nextCar) {
			// ��������� ������� ������ ����� �������
			time_spown[1]++;
		}
		// �������� �� ������������ � ��������� �����
		// ������������ � ����� ��������
		if (game->gameObject[0]->GetLeftX() < 205)
		{
			// ������������� �� ������� �� 1 ������
			game->gameObject[0]->newCoord = 1;
		}
		//  ������������ � ������ ��������
		if (game->gameObject[0]->GetLeftX() > 595)
		{
			// ������������� �� ������� ����� �� 1
			game->gameObject[0]->newCoord = -1;
		}
		// ���� ������� ����� ������� ������ 150
		if (time_spown[1] > 150) {
			// ������� ��������� ����������
			int randomCoord = (rand() % 495) + 205;
			// ���� ���������� ������ 495
			if (randomCoord > 495) {
				// �������� ���������� ����� ����, ������� ����� � ����
				randomCoord = 595;
			}
			// �������� ������� �������
			delete game->gameObject[7];
			// �������� ����� �������, � ������ �����������
			game->gameObject[7] = new OpponentCar(randomCoord, 0, 1);//� ��������� ��������� ������������, 0 - ��� ���������� �����
			// �������� ���� �������, ������� ���������������� (���� 1)
			countCarWin++;
			// ���� + 1
			score++;
			// �������� ����� ������ � ����
			time_spown[1] = 0;
		}
		// ���� ����� ������ > 150
		if (time_spown[0] > 150) {
			// ������� ������ ������ ���� 1
			bonusSpown++;
			// ������� ��������� ���������� �� 205 � 495
			int randomCoord = (rand() % 495) + 205;
			// ���� ���������� ������ 49
			if (randomCoord > 495) {
			// �������� ���������� ����� ����, ������� ����� � ����
				randomCoord = 595;
			}
			// ������� ������ �������
			delete game->gameObject[5];
			// ������� ����� �������
			game->gameObject[5] = new OpponentCar(randomCoord, 0, 2);//� ��������� ��������� ������������, 0 - ��� ���������� �����
			// �������� ���� �������, ������� ���������������� (���� 1)
			countCarWin++;
			// ���� + 1
			score++;
			// �������� ������ ��� ������ �� 1 � 2
			int randBonus = 1 + rand() % 2;
			// ���� ����� ���������� ������� ������ 400, ������ ������� ����� �����
			if (game->gameObject[5]->GetLeftX() > 400) {
				// ������� ������� ������
				delete game->gameObject[6];
				//� ��������� ��������� ������������, 0 - ��� ���������� �����
				game->gameObject[6] = new OpponentCar(randomCoord - distanceByCar, 0, 4);
				// ���� ������� ������ = 3
				if (bonusSpown == 5) {
					// ������� �����
					delete game->gameObject[8];
					// ������� ����� �����
					game->gameObject[8] = new Bonus(randomCoord - 82, 0, randBonus);
					// ����� ����� ������� = 0
					bonusSpown = 0;
				}
			}
		   // ���� ����� ���������� ������� ������ 400, ������ ������� ����� �����
			else {
				// ������� �������
				delete game->gameObject[6];
				// ������� ������� �����
				//� ��������� ��������� ������������, 0 - ��� ���������� �����, 3 - ��� �������(��������)
				game->gameObject[6] = new OpponentCar(randomCoord + distanceByCar, 0, 3);
				// ���� ������� ������ ������ = 3
				if (bonusSpown == 5) {
					// ������� �����
					delete game->gameObject[8];
					// ������� ����� �����
					game->gameObject[8] = new Bonus(randomCoord + 122, 0, randBonus);
					// ������� �����  ������ � 0
					bonusSpown = 0;
				}
			}
			// ������� ������� ������ ������� � 0
			time_spown[0] = 0;
		}
		// ��������� ������� ������� ����, �������� - speedCar - �������� ������� � ������
		game->GamePlay(speedCar);
		// Label1->Caption = IntToStr(score);
		// ���� ������ ������ A
		if (state[0] == 1) {
			// ����� ������� ������ ����� �� 6
			game->gameObject[0]->newCoord = -6;
		}
			// ���� ������ ������ D
		if (state[1] == 1) {
		// ����� ������� ������ ������ �� 6
			game->gameObject[0]->newCoord = 6;
		}
		// ���� �� ������, �������� = 0
		if (state[0] == 0 && state[1] == 0) {
			game->gameObject[0]->newCoord = 0;
		}
	}
	// ���� ���������
	else {
		NOVisibleGameComponent();
		// ������� ����
		delete game;
		// ������ ������ �� �����
		MediaPlayer1->Pause();
		// ��������� ������
		Timer1->Enabled = false;
		// ��������� ��������� �������� ����
		Image2->Visible = false;
		// �������� �������� ����
		Image1->Visible = true;
	}
	// ����� ����� �� �����
	Label2->Caption = IntToStr(score);
	// ���� ���������� ��������� ������ = true
	if (lookBonus)
	{
		// �������� ��������� �������� ������
		Image5->Visible = true;
	}
	// �����
	else
	{   // ��������� ��������� �������� ������
		Image5->Visible = false;
    }
}
// ---------------------------------------------------------------------------
// ��� �������� �����
void __fastcall TGameForm::FormCreate(TObject *Sender) {
	// ������ �������� ��������
	DoubleBuffered = true;
	// ��������� ���� � �������, ������� ����� ����� .exe
	MediaPlayer1->FileName = ExtractFileDir(Application->ExeName) +
		"\\phonkgame.wav";
	// ��������� ����� ������
	MediaPlayer1->Open();
	NOVisibleGameComponent();
}
// ---------------------------------------------------------------------------
// ������� ��������
void __fastcall TGameForm::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	// ���� ������� �
	if (Key == 65) {
		// ������� ��������� �������� �����
		state[0] = 1;
	}
	// ���� ������� D
	if (Key == 68) {
		// ������� ��������� �������� �����
		state[1] = 1;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	// ���� ������� �
	if (Key == 65) {
	// �� ������� ��������� �������� �����
		state[0] = 0;
	}
	// ���� ������� D
	if (Key == 68) {
	// �� ������� ��������� �������� ������
		state[1] = 0;
	}
}
// ---------------------------------------------------------------------------
// ������ ������   ������ ����
void __fastcall TGameForm::BtnPlayClick(TObject *Sender)
{
	VisibleGameComponent();
	// �������� �������� 2
	Image2->Visible = true;
	// �������� ������� � 0
	time_spown[0] = 0;
	time_spown[1] = 0;
	// ���� ������� ����, FALSE
	nextCar = false;
	// ���� 0
	score = 0;
	// ������� ��������
	speedCar = 8;
	// ������� ����� ����
	game = new Game();
	// ������������� ���������� ����
	game->game_ = true;
	// �������� �������� ������ �����
	Label1->Visible = true;
	// Label2->Visible = true;
	// ��������� ������
	MediaPlayer1->Play();
	// ������ �������� �������
	Timer1->Interval = 10;
	// �������� ������
	Timer1->Enabled = true;
}
// ---------------------------------------------------------------------------



