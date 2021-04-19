// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Game.h"
#include "ctime.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// ÃËÎÁÀËÜÍÛÅ ÏÅÐÅÌÅÍÍÛÅ - ÈÌÅÞÒ ÎÁËÀÑÒÜ ÂÈÄÈÌÎÑÒÈ Â ËÞÁÎÉ ÑÒÐÎ×ÊÅ ÊÎÄÀ ÝÒÎÃÎ ÔÀÉËÀ, ÒÎËÜÊÎ ÝÒÎÃÎ!!!!
TGameForm *GameForm; // óêàçàòåëü íà ôîðìó
Game* game; // óêàçàòåëü íà êëàññ Game
bool game_ = false; // ñîñòîÿíèå èãðû / true -  èãðàåì / false - íå èãðàåì
// ïåðåìåííàÿ, êîòîðàÿ ïîêàçûâàåò, êîãäà ñïàâíèòüñÿ ìàøèíêå
bool nextCar = false;
bool lookBonus = false; // Ïåðåìåííàÿ, ÷òî ïîêàçûâàåò - ÏÎÊÀÇÛÂÀÒÜ ËÈ ÊÀÐÒÈÍÊÓ ÁÎÍÓÑÀ ÍÀ ÝÊÐÀÍ
int time_spown[2] = {0, 0}; // âðåìÿ ñïàâíà ìàøèíêè, ÌÀÑÑÈÂ, ïåðâûé ýëåìåíò ñïàâí äëÿ 2, âòîðîé äëÿ 1 ìàøèíêè
int state[2] = {0, 0}; // ñîñòîÿíèÿ ïåðåäâèæåíèÿ ìàøèíêè, 0 - âëåâî, 1 - âïðàâî
int bonusSpown = 0; // ñ÷åò÷èê ñïàâíà áîíóñà
int speedCar = 15; // ñêîðîñòü ìàøèíîê è áîíóñà
int score = 0; // î÷êè èãðîêà
int countCarWin = 0;
// êîëè÷åñòâî ìàøèí, êîòîðûé ïðîåõàëè (êîãäà 2 âìåñòå, ñ÷èòàåì çà îäíó)
int defaultScore = 0;
// âñïîìîãàòåëüíàÿ ïåðåìåííàÿ äëÿ çàïèñè ìàøèí, êîòîðûé ïðîåõàëè
int distanceByCar = 225; // ðàññòîÿíèå ìåæäó ìàøèíàìè
int countPlusSpeed = 50;

// ---------------------------------------------------------------------------
// ÊÎÍÑÒÐÓÊÒÎÐ ÊËÀÑÑÀ TFORM
__fastcall TGameForm::TGameForm(TComponent* Owner) : TForm(Owner) {
	// ÂÊËÞ×ÀÅÌ ÐÀÍÄÎÌ
	srand(time(NULL));
	// ÂÊËÞ×ÀÅÌ ÐÀÍÄÎÌ
	randomize();
}

// ---------------------------------------------------------------------------
// ÔÓÍÊÖÈß ÊËÀÑÑÀ
void __fastcall TGameForm::VisibleMainMenu()
{
	// ÎÒÊÐÛÂÀÅÌ ÂÈÄÈÌÎÑÒÜ 3 êíîïîê
	BtnPlay->Visible = true; // ÈÃÐÀÒÜ
	BtnDocument->Visible = true; // ÄÎÊÓÌÅÍÒÀÖÈß
	BtnRegulations->Visible = true; // ÏÐÀÂÈËÀ
}
// ---------------------------------------------------------------------------
void __fastcall TGameForm::VisibleGameComponent()
{
	// ÎÒÊÐÛÂÀÅÌ Âèäèìîñòü î÷êîâ
	Image3->Visible = true;
	Label1->Visible = true;
	Label2->Visible = true;
	Label3->Visible = true;
}
// ÔÓÍÊÖÈß ÊËÀÑÑÀ
void __fastcall TGameForm::NOVisibleGameComponent()
{
	// ÇÀÊÐÛÂÀÅÌ Âèäèìîñòü î÷êîâ
	Image3->Visible = false;
	Image5->Visible = false;
	Label1->Visible = false;
	Label2->Visible = false;
	Label3->Visible = false;
}

// ÔÓÍÊÖÈß ÊËÀÑÑÀ
void _fastcall TGameForm::VisibleGameOverMenu() {
	// ÇÀÊÐÛÂÀÅÌ ÂÈÄÈÌÎÑÒÜ 3 êíîïîê
	BtnPlay->Visible = false; // ÈÃÐÀÒÜ
	BtnDocument->Visible = false; // ÄÎÊÓÌÅÍÒÀÖÈß
	BtnRegulations->Visible = false; // ÏÐÀÂÈËÀ
}

// ---------------------------------------------------------------------------
// ÒÀÉÌÅÐ, ÏÎÂÒÎÐÅÍÈÅ ÑÎÁÛÒÈÉ, ÈÍÒÅÐÂÀË 10 ìèëèñåêóíä
void __fastcall TGameForm::Timer1Timer(TObject *Sender) {
	// Ïðîâåðêà, åñëè èãðà, òî...
	if (game->game_)
	{
		// ÓÑËÎÆÍÅÍÈÅ, ÄÅËÀÅÒÑß ÂÛØÅ ÑÊÎÐÎÑÒÜ È ÌÅÍÜØÅ ÐÀÑÑÒÎßÍÈÅ ÌÅÆÄÓ ÌÀØÈÍÊÀÌÈ
		// Óñëîâèå, åñëè ïðîåõàëè 50 ìàøèíîê, åñëè ïîäåëèòü íà ýòî ÷èñëî, íå áóäåò ìåíüøå íóëÿ, È ïðîâåðêà,
		// ÷òîáû ñðàáîòàëî òîëüêî îäèí ðàç òàê êàê Òàéìåð ÁÛÑÒÐÛÉ
		if (countCarWin % countPlusSpeed == 0 && countCarWin / countPlusSpeed >=
			0 && countCarWin != defaultScore)
		{
			// ñêîðîñòü ìàøèíîê íà 1 áîëüøå
			speedCar++;
			// óìåíüøàåì ðàññòîÿíèå ìåæäó ìàøèíêàìè
			distanceByCar-=25;
			// çàïèñûâàåì êîëè÷åñòâî ïðîåõâàøèõ â ñïîìîãàòåëüíóþ ïåðåìåííóþ
			defaultScore = countCarWin;
		}
		// çàïóñêàåì ñ÷åò÷èê âðåìåíè ñïàóíà ìàøèíîê
		time_spown[0]++;
		// åñëè ñ÷åò÷èê ìïàâíà ìàøèíîê áîëüøå 75, çàïóñêàåì íîâóþ ìàøèíêó
		if (time_spown[0] > 75) {
			// ðàçðåøàåì çàïóñòèòü ñ÷åò÷èê âòîðîé ìàøèíêè
			nextCar = true;
		}
		// åñëè ìîæíî íîâóþ ìàøèíêó, çàïóñêàåì ñ÷åò÷èê åå ñïàóíà
		if (nextCar) {
			// çàïóñêàåì ñ÷åò÷èê ñïàâíà íîâîé ìàøèíêè
			time_spown[1]++;
		}
		// ÏÐÎÂÅÐÊÀ ÍÀ ÑÒÎËÊÍÎÂÅÍÈÅ Ñ ÃÐÀÍÈÖÀÌÈ ÊÀÐÒÛ
		// ÑÒÎËÊÍÎÂÅÍÈÅ Ñ ËÅÂÎÉ ÃÐÀÍÈÖÅÉ
		if (game->gameObject[0]->GetLeftX() < 205)
		{
			// ÎÒÒÎËÊÍÎÂÅÍÈÅ ÎÒ ÃÐÀÍÈÖÛ ÍÀ 1 âïðàâî
			game->gameObject[0]->newCoord = 1;
		}
		//  ÑÒÎËÊÍÎÂÅÍÈÅ Ñ ÏÐÀÂÎÉ ÃÐÀÍÈÖÅÉ
		if (game->gameObject[0]->GetLeftX() > 595)
		{
			// ÎÒÒÎËÊÍÎÂÅÍÈÅ ÎÒ ÃÐÀÍÈÖÛ ÂËÅÂÎ ÍÀ 1
			game->gameObject[0]->newCoord = -1;
		}
		// ÅÑËÈ Ñ×ÅÒ×ÈÊ ÍÎÂÛÕ ÌÀØÈÍÎÊ ÁÎËÜØÅ 150
		if (time_spown[1] > 150) {
			// ñîçäàåì ðàíäîìíóþ êîîðäèíàòó
			int randomCoord = (rand() % 495) + 205;
			// åñëè êîîðäèíàòà áîëüøå 495
			if (randomCoord > 495) {
				// ïðèñâîèì êîîðäèíàòå ñàìûé êðàé, ÌÀØÈÍÊÀ ÁÓÄÅÒ Â ÊÐÀÞ
				randomCoord = 595;
			}
			// óäàëåíèå îáúåêòà ìàøèíêè
			delete game->gameObject[7];
			// ñîçäàíèå íîâîé ìàøèíêè, ñ íîâûìè êîîäèíàòàìè
			game->gameObject[7] = new OpponentCar(randomCoord, 0, 1);//Â ÑÊÎÁÎ×ÊÀÕ ÏÀÐÀÌÅÒÐÛ ÊÎÍÑÒÐÓÊÒÎÐÀ, 0 - ýòî Êîîðäèíàòà Âåðõà
			// ÏÐÎÅÕÀËÈ ÎÄÍÓ ÌÀØÈÍÊÓ, Ñ×ÅÒ×ÈÊ ÈÍÊÐÅÌÅÍÒÈÐÓÅÒÑß (ïëþñ 1)
			countCarWin++;
			// Î×ÊÈ + 1
			score++;
			// ÍÀ×ÈÍÀÅÌ ÂÐÅÌß ÑÏÀÂÍÀ Ñ ÍÓËß
			time_spown[1] = 0;
		}
		// ÅÑËÈ ÂÐÅÌß ÑÏÀÓÍÀ > 150
		if (time_spown[0] > 150) {
			// Ñ×ÅÒ×ÈÊ ÑÏÀÂÍÀ ÁÎÍÓÑÀ ÏËÞÑ 1
			bonusSpown++;
			// ÑÎÇÄÀÅÌ ÐÀÍÄÎÌÍÓÞ ÊÎÎÐÄÈÍÀÒÓ ÎÒ 205 ê 495
			int randomCoord = (rand() % 495) + 205;
			// åñëè êîîðäèíàòà áîëüøå 49
			if (randomCoord > 495) {
			// ïðèñâîèì êîîðäèíàòå ñàìûé êðàé, ÌÀØÈÍÊÀ ÁÓÄÅÒ Â ÊÐÀÞ
				randomCoord = 595;
			}
			// óäàëÿåì îáúåêò ìàøèíêó
			delete game->gameObject[5];
			// ÑÎÇÄÀÅÌ ÍÎÂÓÞ ÌÀØÈÍÊÓ
			game->gameObject[5] = new OpponentCar(randomCoord, 0, 2);//Â ÑÊÎÁÎ×ÊÀÕ ÏÀÐÀÌÅÒÐÛ ÊÎÍÑÒÐÓÊÒÎÐÀ, 0 - ýòî Êîîðäèíàòà Âåðõà
			// ÏÐÎÅÕÀËÈ ÎÄÍÓ ÌÀØÈÍÊÓ, Ñ×ÅÒ×ÈÊ ÈÍÊÐÅÌÅÍÒÈÐÓÅÒÑß (ïëþñ 1)
			countCarWin++;
			// Î×ÊÈ + 1
			score++;
			// ÐÀÍÄÎÌÍÎ ÓÇÍÀÅÌ ÒÈÏ ÁÎÍÓÑÀ ÎÒ 1 ê 2
			int randBonus = 1 + rand() % 2;
			// ÅÑËÈ ËÅÂÀß ÊÎÎÐÄÈÍÀÒÀ ÌÀØÈÍÊÈ ÁÎËÜØÅ 400, ÂÒÎÐÀß ÌÀØÈÍÊÀ ÁÓÄÅÒ ÑËÅÂÀ
			if (game->gameObject[5]->GetLeftX() > 400) {
				// óäàëÿåì ìàøèíêó âòîðóþ
				delete game->gameObject[6];
				//Â ÑÊÎÁÎ×ÊÀÕ ÏÀÐÀÌÅÒÐÛ ÊÎÍÑÒÐÓÊÒÎÐÀ, 0 - ýòî Êîîðäèíàòà Âåðõà
				game->gameObject[6] = new OpponentCar(randomCoord - distanceByCar, 0, 4);
				// ÅÑËÈ Ñ×ÅÒ×ÈÊ ÑÏÀÂÍÀ = 3
				if (bonusSpown == 5) {
					// óäàëÿåì áîíóñ
					delete game->gameObject[8];
					// ñîçäàåì íîâûé áîíóñ
					game->gameObject[8] = new Bonus(randomCoord - 82, 0, randBonus);
					// ÁÎÍÓÑ ÑÏÀÂÍ Ñ×ÅÒ×ÈÊ = 0
					bonusSpown = 0;
				}
			}
		   // ÅÑËÈ ËÅÂÀß ÊÎÎÐÄÈÍÀÒÀ ÌÀØÈÍÊÈ ÁÎËÜØÅ 400, ÂÒÎÐÀß ÌÀØÈÍÊÀ ÁÓÄÅÒ ÑËÅÂÀ
			else {
				// óäàëÿåì ìàøèíêó
				delete game->gameObject[6];
				// ñîçäàåì ìàøèíêó íîâóþ
				//Â ÑÊÎÁÎ×ÊÀÕ ÏÀÐÀÌÅÒÐÛ ÊÎÍÑÒÐÓÊÒÎÐÀ, 0 - ýòî Êîîðäèíàòà Âåðõà, 3 - òèï ìàøèíêè(êàðòèíêà)
				game->gameObject[6] = new OpponentCar(randomCoord + distanceByCar, 0, 3);
				// ÅÑËÈ Ñ×ÅÒ×ÈÊ ÑÏÀÂÍÀ ÁÎÍÓÑÀ = 3
				if (bonusSpown == 5) {
					// óäàëèòü áîíóñ
					delete game->gameObject[8];
					// ñîçäàòü íîâûé áîíóñ
					game->gameObject[8] = new Bonus(randomCoord + 122, 0, randBonus);
					// Ñ÷åò÷èê ñïâíà  áîíóñà â 0
					bonusSpown = 0;
				}
			}
			// ñ÷åò÷èê âðåìåíè ñïàâíà ìàøèíîê â 0
			time_spown[0] = 0;
		}
		// ÇÀÏÓÑÊÀÅÌ ÎÑÍÎÍÓÞ ÔÓÍÊÖÈÞ ÈÃÐÛ, ÏÀÐÀÌÅÒÐ - speedCar - ñìåùåíèå ìàøèíîê è áîíóñà
		game->GamePlay(speedCar);
		// Label1->Caption = IntToStr(score);
		// åñëè íàæàòà êíîïêà A
		if (state[0] == 1) {
			// ÑÄÂÈÃ ÌÀØÈÍÊÈ ÈÃÐÎÊÀ ÂËÅÂÎ íà 6
			game->gameObject[0]->newCoord = -6;
		}
			// åñëè íàæàòà êíîïêà D
		if (state[1] == 1) {
		// ÑÄÂÈÃ ÌÀØÈÍÊÈ ÈÃÐÎÊÀ ÂÏðàÂÎ íà 6
			game->gameObject[0]->newCoord = 6;
		}
		// Åñëè íå íàæàòû, ñìåùåíèå = 0
		if (state[0] == 0 && state[1] == 0) {
			game->gameObject[0]->newCoord = 0;
		}
	}
	// ÅÑëè ÏÐÎÈÃÐÀËÈ
	else {
		NOVisibleGameComponent();
		// óäëàÿåì èãðó
		delete game;
		// ÑÒÀÂÈÌ ÌÓÇÛÊÓ ÍÀ ÏÀÓÇÓ
		MediaPlayer1->Pause();
		// ÂÛÊËÞ×ÀÅÌ ÒÀÖÌÅÐ
		Timer1->Enabled = false;
		// ÂÛÊËÞ×ÀÅÌ ÂÈÄÈÌÎÑÒÜ ÊÀÐÒÈÍÊÈ ÈÃÐÛ
		Image2->Visible = false;
		// ÂÊËÞ×ÀÅÌ ÊÀÐÒÈÍÊÈ ÌÅÍÞ
		Image1->Visible = true;
	}
	// ÂÛÂÎÄ Î×ÊÎÂ ÍÀ ÝÊÐÀÍ
	Label2->Caption = IntToStr(score);
	// Åñëè ïåðåìåííàÿ âèäèìîñòè áîíóñà = true
	if (lookBonus)
	{
		// âêëþ÷àåì âèäèìîñòü êàðòèíêè áîíóñà
		Image5->Visible = true;
	}
	// ÈÍÀ×Å
	else
	{   // âûêëþ÷àåì âèäèìîñòü êàðòèíêè áîíóñà
		Image5->Visible = false;
    }
}
// ---------------------------------------------------------------------------
// ÏÐÈ ÑÎÇÄÀÍÈÈ ÔÎÐÌÛ
void __fastcall TGameForm::FormCreate(TObject *Sender) {
	// óáðàòü ìåðöàíèå êàðòèíîê
	DoubleBuffered = true;
	// ÎÒÊÐÛÂÀÅÌ ÔÀÉË Ñ ÌÓÇÛÊÎÉ, êîòîðûé ëåæèò âîçëå .exe
	MediaPlayer1->FileName = ExtractFileDir(Application->ExeName) +
		"\\phonkgame.wav";
	// îòêðûâàåì ìåäèà ïëåéåð
	MediaPlayer1->Open();
	NOVisibleGameComponent();
}
// ---------------------------------------------------------------------------
// íàæàòèÿ êëàâòóðû
void __fastcall TGameForm::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	// Åñëè êëàâèøà À
	if (Key == 65) {
		// àêòèâíî ñîñòîÿíèÿ ñìåùåíèÿ âëåâî
		state[0] = 1;
	}
	// Åñëè êëàâèøà D
	if (Key == 68) {
		// àêòèâíî ñîñòîÿíèÿ ñìåùåíèÿ âïàâî
		state[1] = 1;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	// Åñëè êëàâèøà À
	if (Key == 65) {
	// ÍÅ àêòèâíî ñîñòîÿíèÿ ñìåùåíèÿ âëåâî
		state[0] = 0;
	}
	// Åñëè êëàâèøà D
	if (Key == 68) {
	// ÍÅ àêòèâíî ñîñòîÿíèÿ ñìåùåíèÿ âïðàâî
		state[1] = 0;
	}
}
// ---------------------------------------------------------------------------
// ÊÍÎÏÊÀ ÈÃÐÀÒÜ   ÍÀ×ÀËÎ ÈÃÐÛ
void __fastcall TGameForm::BtnPlayClick(TObject *Sender)
{
	VisibleGameComponent();
	// ÂÊËÞ×ÀÅÌ ÊÀÐÒÈÍÊÓ 2
	Image2->Visible = true;
	// Ñ÷åò÷èêè âðåìåíè â 0
	time_spown[0] = 0;
	time_spown[1] = 0;
	// Ñëåä ìàøèíêà íèçÿ, FALSE
	nextCar = false;
	// Î÷êè 0
	score = 0;
	// Ñáèâàåì ñêîðîñòü
	speedCar = 8;
	// ñîçäàåì íîâóþ èãðó
	game = new Game();
	// óñòàíàâëèâàåì àêòèâíîñòü èãðû
	game->game_ = true;
	// Âêëþ÷àåì âäèìîñòü âûâîäà î÷êîâ
	Label1->Visible = true;
	// Label2->Visible = true;
	// çàïóñêàåì ìóçûêó
	MediaPlayer1->Play();
	// ñòàâèì èíòåðâàë òàéìåðà
	Timer1->Interval = 10;
	// âêëþ÷àåì òàéìåð
	Timer1->Enabled = true;
}
// ---------------------------------------------------------------------------



