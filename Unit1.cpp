   //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;



const int playGroundWidth = 450;
const int playGroundHeight = 450;

int xFruit = 0;
int yFruit = 0;
int score = 0;

int xToFollow = 0;
int yToFollow = 0;

int xPreviousHead;
int yPreviousHead;


TImage* pTail[80];
int numberElements = 0;// for pTail[tailElement]
void createArrayOfTailsSetValues(); // prototype
bool moveTailElements = true;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool isFruitBeingEaten()
 {
     if( Form1->head->Left + Form1->head->Width - 5 > Form1->fruit->Left
       && Form1->head->Left + 5  < Form1->fruit->Left + Form1->fruit->Width
       && Form1->head->Top + Form1->head->Height  - 5   > Form1->fruit->Top
       && Form1->head->Top + 5  < Form1->fruit->Top + Form1->fruit->Height)
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
        xFruit = random(playGroundWidth - 30);
        yFruit = random(playGroundHeight - 30);

    //prevent placing fruit on middle of the game field where will be snake at the beginning of the game
        if((xFruit > 180 && xFruit < 220) && (yFruit > 180 && yFruit < 220) )
          {
                xFruit == 100;
          }
    //locating fruit on the field
        Form1->fruit->Left = xFruit;
        Form1->fruit->Top =  yFruit;
 }
//---------------------------------------------------------------------------
 void setGame()
{
        setFruitLocation();
        createArrayOfTailsSetValues();

        Form1->head->Left = playGroundWidth / 2; //middle of play ground
        Form1->head->Top = playGroundHeight / 2 ;

        score = 0;

        //play intro sound
        //sndPlaySound("snd/intro.wav",SND_ASYNC);
        resetTimers();
        //initial label caption
        Form1->Label1->Caption = "Score: " + IntToStr(score);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::downTimer(TObject *Sender)
{

   head->Top += 20;


    if((head->Top + head->Height) >= playField->Height)
    {
      head->Top = 0;
    }

    if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       numberElements++;

       //placing tail elements
       if( numberElements == 1)
        {
          pTail[0]->Left = xPreviousHead;
          pTail[0]->Top  = yPreviousHead;
          pTail[0]->Visible = true;
          moveTailElements = false;
        }
       if( numberElements > 1)
        {
         for(int i = score - 1; i < numberElements; i++)
          {
            pTail[i]->Left =  pTail[i -1]->Top;
            pTail[i]->Top  =  pTail[i-1]->Top;
            pTail[i]->Visible = true;
          }
         moveTailElements = false;
        }

    }// isFruitBeingEaten()

    if(moveTailElements == true)
      {
        for(int i = 0; i < numberElements;i++)
        {
         pTail[i]->Top += 20;

        }
      }


    Label1->Caption = "Score: " + IntToStr(score);

    xPreviousHead = head->Left;
    yPreviousHead = head->Top;
    moveTailElements = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftTimer(TObject *Sender)
{
    head->Left -= 20;
    if((head->Left) <= 0)
    {
      head->Left = playField->Width - 10;
    }

    if(isFruitBeingEaten() == true)
    {

       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       numberElements++;

         //placing tail elements
       if( numberElements == 1)
        {
          pTail[0]->Left = xPreviousHead;
          pTail[0]->Top  = yPreviousHead;
          pTail[0]->Visible = true;
          moveTailElements = false;
        }
       if( numberElements > 1)
        {
         for(int i = score - 1; i < numberElements; i++)
          {
            pTail[i]->Left =  pTail[i -1]->Top;
            pTail[i]->Top  =  pTail[i-1]->Top;
            pTail[i]->Visible = true;
          }
         moveTailElements = false;
        }


    }
      if(moveTailElements == true)
      {
        for(int i = 0; i < numberElements;i++)
        {
         pTail[i]->Left -= 20;

        }
      }

    Label1->Caption = "Score: " + IntToStr(score);
     xPreviousHead = head->Left;
     yPreviousHead = head->Top;
      moveTailElements = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightTimer(TObject *Sender)
{

      head->Left += 20;
   if((head->Left + head->Width) > playField->Width)
    {
      head->Left = 0;
    }
      if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       numberElements++;

        //placing tail elements
       if( numberElements == 1)
        {
          pTail[0]->Left = xPreviousHead;
          pTail[0]->Top  = yPreviousHead;
          pTail[0]->Visible = true;
          moveTailElements = false;
        }
       if( numberElements > 1)
        {
         for(int i = score - 1; i < numberElements; i++)
          {
            pTail[i]->Left =  pTail[i -1]->Top;
            pTail[i]->Top  =  pTail[i-1]->Top;
            pTail[i]->Visible = true;
          }
          moveTailElements = false;
        }


    }
     if(moveTailElements == true)
      {
        for(int i = 0; i < numberElements;i++)
        {
         pTail[i]->Left += 20;
        }
      }

    Label1->Caption = "Score: " + IntToStr(score);

    xPreviousHead = head->Left;
    yPreviousHead = head->Top;
     moveTailElements = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::upTimer(TObject *Sender)
{

    head->Top -= 20;

   if(head->Top + 10  <= 0)
    {
      head->Top = playField->Height + head->Height + 2;

    }

   if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       numberElements++;

       //placing tail elements
       if( numberElements == 1)
        {
          pTail[0]->Left = xPreviousHead;
          pTail[0]->Top  = yPreviousHead;
          pTail[0]->Visible = true;
          moveTailElements = false;
        }
       if( numberElements > 1)
        {
         for(int i = score - 1; i < numberElements; i++)
          {
            pTail[i]->Left =  pTail[i - 1]->Top;
            pTail[i]->Top  =  pTail[i- 1]->Top;
            pTail[i]->Visible = true;
          }
           moveTailElements = false;
        }

    }

     if(moveTailElements == true)
      {
        for(int i = 0; i < numberElements;i++)
        {
         pTail[i]->Top -= 20;

        }
      }


    Label1->Caption = "Score: " + IntToStr(score);
    xPreviousHead = head->Left;
    yPreviousHead = head->Top;
    moveTailElements = true;
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
void  createArrayOfTailsSetValues()
{
pTail[0] = Form1->Image0;
pTail[1] = Form1->Image1;
pTail[2] = Form1->Image2;
pTail[3] = Form1->Image3;
pTail[4] = Form1->Image4;
pTail[5] = Form1->Image5;
pTail[6] = Form1->Image6;
pTail[7] = Form1->Image7;
pTail[8] = Form1->Image8;
pTail[9] = Form1->Image9;
pTail[10] = Form1->Image10;
pTail[11] = Form1->Image11;
pTail[12] = Form1->Image12;
pTail[13] = Form1->Image13;
pTail[14] = Form1->Image14;
pTail[15] = Form1->Image15;
pTail[16] = Form1->Image16;
pTail[17] = Form1->Image17;
pTail[18] = Form1->Image18;
pTail[19] = Form1->Image19;
pTail[20] = Form1->Image20;
pTail[21] = Form1->Image21;
pTail[22] = Form1->Image22;
pTail[23] = Form1->Image23;
pTail[24] = Form1->Image24;
pTail[25] = Form1->Image25;
pTail[26] = Form1->Image26;
pTail[27] = Form1->Image27;
pTail[28] = Form1->Image28;
pTail[29] = Form1->Image29;
pTail[30] = Form1->Image30;
pTail[31] = Form1->Image31;
pTail[32] = Form1->Image32;
pTail[33] = Form1->Image33;
pTail[34] = Form1->Image34;
pTail[35] = Form1->Image35;
pTail[36] = Form1->Image36;
pTail[37] = Form1->Image37;
pTail[38] = Form1->Image38;
pTail[39] = Form1->Image39;
pTail[40] = Form1->Image40;
pTail[41] = Form1->Image41;
pTail[42] = Form1->Image42;
pTail[43] = Form1->Image43;
pTail[44] = Form1->Image44;
pTail[45] = Form1->Image45;
pTail[46] = Form1->Image46;
pTail[47] = Form1->Image47;
pTail[48] = Form1->Image48;
pTail[49] = Form1->Image49;
pTail[50] = Form1->Image50;



}

