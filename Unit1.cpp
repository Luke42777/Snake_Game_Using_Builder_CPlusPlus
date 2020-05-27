//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int xFruit = 0;
int yFruit = 0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------
void resetTimers()
 {
    Form1->left->Enabled = false;
    Form1->right->Enabled = false;
    Form1->up->Enabled = false;
    Form1->down->Enabled = false;

 }
//---------------------------------------------------------------------------
 void setGame()
{

    //placing fruit on the field
        randomize();
        xFruit = random(400);
        yFruit = random(400);

        //prevent placing fruit on middle of the game field where will be snake at the beginning of the game
        if((xFruit > 180 && xFruit < 220) && (yFruit > 180 && yFruit < 220) )
          {
                xFruit == 100;
          }
        Form1->fruit->Left = xFruit;
        Form1->fruit->Top =  yFruit;

        Form1->head->Left = 200;
        Form1->head->Top = 200;

        //play intro sound
        ///sndPlaySound("snd/intro.wav",SND_ASYNC);
        //resetTimers();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::downTimer(TObject *Sender)
{
   head->Top += 10;       
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftTimer(TObject *Sender)
{
    head->Left -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightTimer(TObject *Sender)
{
         head->Left += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::upTimer(TObject *Sender)
{
     head->Top -= 10;    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
setGame();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
if(Key == VK_LEFT)
{
 head->Picture->LoadFromFile("img/lebWlewo");
 resetTimers();
 left->Enabled = true;

}
if(Key == VK_DOWN)
{
 head->Picture->LoadFromFile("img/lebWdol");
 resetTimers();
 down->Enabled = true;

}
 if(Key == VK_RIGHT)
{
 head->Picture->LoadFromFile("img/lebWprawo");
 resetTimers();
 right->Enabled = true;

}
if(Key == VK_UP)
{
 head->Picture->LoadFromFile("img/leb");
 resetTimers();
 up->Enabled = true;

}
}
//---------------------------------------------------------------------------
