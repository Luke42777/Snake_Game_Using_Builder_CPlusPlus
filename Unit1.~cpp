//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int xFruit = 0;
int yFruit = 0;
int score = 0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool isFruitBeingEaten()
 {
     if( Form1->head->Left + Form1->head->Width >= Form1->fruit->Left
       && Form1->head->Left  <= Form1->fruit->Left + Form1->fruit->Width
       && Form1->head->Top + Form1->head->Height  >= Form1->fruit->Top
       && Form1->head->Top  <= Form1->fruit->Top + Form1->fruit->Height)
        {
           return true;
        }
      else
        {
           return false;
        }
 }
//-----------------------------------------------------------------------
void resetTimers()
 {
    Form1->left->Enabled = false;
    Form1->right->Enabled = false;
    Form1->up->Enabled = false;
    Form1->down->Enabled = false;

 }
 //----------------------------------------------------------------------------
 void setFruitLocation()
 {
    //randomly choosing fruit place on the field
        randomize();
        xFruit = random(400);
        yFruit = random(400);

    //prevent placing fruit on middle of the game field where will be snake at the beginning of the game
        if((xFruit > 180 && xFruit < 220) && (yFruit > 180 && yFruit < 220) )
          {
                xFruit == 100;
          }
    //locatiing fruit on the field
        Form1->fruit->Left = xFruit;
        Form1->fruit->Top =  yFruit;
 }
//---------------------------------------------------------------------------
 void setGame()
{
        setFruitLocation();
        Form1->head->Left = 200;
        Form1->head->Top = 200;

        score = 0;

        //play intro sound
        sndPlaySound("snd/intro.wav",SND_ASYNC);
        resetTimers();
        //initial label caption
        Form1->Label1->Caption = "Score: " + IntToStr(score);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::downTimer(TObject *Sender)
{

    head->Top += 6;
    if((head->Top + head->Height) >= playField->Height)
    {
      head->Top = 0;
    }

     if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;



    }
    Form1->Label1->Caption = "Score: " + IntToStr(score);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftTimer(TObject *Sender)
{

    head->Left -= 6;
    if((head->Left) <= 0)
    {
      head->Left = playField->Width - 10;
    }

    if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;



    }
    Form1->Label1->Caption = "Score: " + IntToStr(score);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightTimer(TObject *Sender)
{
   head->Left += 6;
   if((head->Left + head->Width) > playField->Width)
    {
      head->Left = 0;
    }
      if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;



    }
    Form1->Label1->Caption = "Score: " + IntToStr(score);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::upTimer(TObject *Sender)
{
     head->Top -= 6;
   if(head->Top + 10  <= 0)
    {
      head->Top = playField->Height - head->Height;
    }
      if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;



    }
    Form1->Label1->Caption = "Score: " + IntToStr(score);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        setGame();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_UP && up->Enabled == false) //(up->Enabled == false)to prevent stopping head when holding key
  {
        head->Picture->LoadFromFile("img/leb.bmp");
        resetTimers();
        up->Enabled = true;

   }
  if(Key == VK_LEFT && left->Enabled == false)
  {
        head->Picture->LoadFromFile("img/lebWlewo.bmp");
        resetTimers();
        left->Enabled = true;
   }

  if(Key == VK_DOWN && down->Enabled == false)
 {
        head->Picture->LoadFromFile("img/lebWdol.bmp");
        resetTimers();
        down->Enabled = true;
 }
 if(Key == VK_RIGHT && right->Enabled == false   )
 {
       head->Picture->LoadFromFile("img/lebWprawo.bmp");
       resetTimers();
       right->Enabled = true;
 }


}
//---------------------------------------------------------------------------

