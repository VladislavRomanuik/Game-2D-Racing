// ---------------------------------------------------------------------------

#ifndef MainH
#define MainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.MPlayer.hpp>

// ---------------------------------------------------------------------------
class TGameForm : public TForm {
__published: // IDE-managed Components

	TTimer *Timer1;
	TImage *Image1;
	TImage *BtnPlay;
	TImage *BtnDocument;
	TImage *BtnRegulations;
	TImage *Image2;
	TMediaPlayer *MediaPlayer1;
	TImage *Image3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TImage *Image5;

	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnPlayClick(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TGameForm(TComponent* Owner);
	void __fastcall VisibleMainMenu();
	void __fastcall VisibleGameOverMenu();
	void __fastcall VisibleGameComponent();
	void __fastcall NOVisibleGameComponent();
};

// ---------------------------------------------------------------------------
extern PACKAGE TGameForm *GameForm;
// ---------------------------------------------------------------------------
#endif
