//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *playField;
        TImage *head;
        TImage *tail;
        TImage *fruit;
        TTimer *left;
        TTimer *right;
        TTimer *up;
        TTimer *down;
        TLabel *Label1;
        void __fastcall downTimer(TObject *Sender);
        void __fastcall leftTimer(TObject *Sender);
        void __fastcall rightTimer(TObject *Sender);
        void __fastcall upTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
