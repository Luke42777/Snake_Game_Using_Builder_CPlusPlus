   //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "mmsystem.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//////////////////////////////////////////////////////////////////////////////
struct TheadPath
{
 short int x,y;

 TheadPath(int a, int b): x(a), y(b) {}
};
///////////////////////////////////////////////////////////////////////////////
std::vector<TheadPath> path;
TImage* pTail[80]; // array of pointers to the TImage objects(our tails)

const int playGroundWidth = 450;
const int playGroundHeight = 450;
int xFruit = 0;
int yFruit = 0;
int score = 0;
bool isGamePaused = false;

bool isFruitBeingEaten();
bool isGameOver();
void setFruitLocation();
void resetTimers();
void setGame();
void createArrayOfTailsSetValues();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//--------------------------------------------------------------------------
void __fastcall TForm1::downTimer(TObject *Sender)
{
  path.push_back(TheadPath(head->Left,head->Top));

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
       pTail[score - 1]->Visible = true;
    }// isFruitBeingEaten()

    for(int i = 0; i < score; i++)
    {
       pTail[i]->Left = path[path.size() - (i + 1)].x;
       pTail[i]->Top  = path[path.size() - (i + 1)].y - 5; // (- 5) to make clearance between objects
    }
    Label1->Caption = "Score: " + IntToStr(score);

    //game over
     if(isGameOver())
    {
       resetTimers();
       sndPlaySound("snd/koniec.wav",SND_ASYNC);
       path.clear(); //empty vector

       if(Application->MessageBox("would you like to play again?", "Confirm",
       MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          setGame();
        }

       else
        {
          Application->Terminate();
        }
    }
    path.erase(path.begin(), path.end() - score);
  //free memeory, we just need to track movement of head that much we have tail elements(score),
  //before that we ignore

}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftTimer(TObject *Sender)
{
    path.push_back(TheadPath(head->Left,head->Top));



    head->Left -= 20;

    if((head->Left) < 0)
    {
      head->Left = playField->Width - head->Width;
    }

    if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       pTail[score - 1]->Visible = true;
     }

       for(int i = 0; i < score; i++)
    {
        pTail[i]->Left = path[path.size() - (i + 1)].x + 5;
        pTail[i]->Top  = path[path.size() - (i + 1)].y;
    }

    Label1->Caption = "Score: " + IntToStr(score);

    //game over
    if(isGameOver())
    {
       resetTimers();
       sndPlaySound("snd/koniec.wav",SND_ASYNC);
       path.clear(); //empty vector

       if(Application->MessageBox("would you like to play again?", "Confirm",
       MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          setGame();
        }

       else
        {
          Application->Terminate();
        }
    }
     path.erase(path.begin(), path.end() - score);
    //free memeory, we just need to track movement of head that much we have tail elements(score),
    //before that we ignore
}

//---------------------------------------------------------------------------
void __fastcall TForm1::rightTimer(TObject *Sender)
{
   path.push_back(TheadPath(head->Left,head->Top));


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
       pTail[score - 1]->Visible = true;
    }
     for(int i = 0; i < score; i++)
    {
      pTail[i]->Left = path[path.size() - (i + 1)].x - 5;
      pTail[i]->Top  = path[path.size() - (i + 1)].y;
    }
    Label1->Caption = "Score: " + IntToStr(score);

    //game over
    if(isGameOver())
    {
       resetTimers();
       sndPlaySound("snd/koniec.wav",SND_ASYNC);
       path.clear(); //clear all elemnts of vector

       if(Application->MessageBox("would you like to play again?", "Confirm",
       MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          setGame();
        }

       else
        {
          Application->Terminate();
        }
    }
     path.erase(path.begin(), path.end() - score);
   //free memeory, we just need to track movement of head that much we have tail elements(score),
   //before that we ignore

}
//---------------------------------------------------------------------------
void __fastcall TForm1::upTimer(TObject *Sender)
{
    path.push_back(TheadPath(head->Left,head->Top));



    head->Top -= 20;

   if(head->Top + 10  <= 0)
    {
      head->Top = playField->Height - head->Height - 5;
    }

   if(isFruitBeingEaten() == true)
    {
       sndPlaySound("snd/eating.wav",SND_ASYNC);
       setFruitLocation();
       score++;
       pTail[score - 1]->Visible = true;
    }

     for(int i = 0; i < score; i++)
    {
      pTail[i]->Left = path[path.size() - (i + 1)].x;
      pTail[i]->Top  = path[path.size() - (i + 1)].y + 5;
    }

    Label1->Caption = "Score: " + IntToStr(score);

    //game over
    if(isGameOver())
    {
       resetTimers();
       sndPlaySound("snd/koniec.wav",SND_ASYNC);
       path.clear();

       if(Application->MessageBox("Would you like to play again?", "Confirm",
       MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
          setGame();
        }

       else
        {
          Application->Terminate();
        }
    }
    path.erase(path.begin(), path.end() - score);
    //free memeory, we just need to track movement of head that much we have tail elements(score),
    //before that we ignore

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
  //pausing the game
  if(Key == VK_SPACE )
   {
        resetTimers();
   }
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
//***************************************************************************
//***************************************************************************
//**************************GLOBAL FUNCTIONS*********************************
//***************************************************************************
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
//******************************************************************************
bool isGameOver()
{
       for(int i = 0; i < score;i++)
       {
        if( Form1->head->Left + Form1->head->Width - 11  > pTail[i]->Left
            && Form1->head->Left +11  < pTail[i]->Left + pTail[i]->Width
            && Form1->head->Top + Form1->head->Height  -11   > pTail[i]->Top
            && Form1->head->Top + 11  < pTail[i]->Top + pTail[i]->Height)
          {
             return true;
          }

        }//for


            return false;

}
//******************************************************************************
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
//****************************************************************************
void resetTimers()
 {
    Form1->left->Enabled  = false;
    Form1->right->Enabled = false;
    Form1->up->Enabled    = false;
    Form1->down->Enabled  = false;
 }
 //*****************************************************************************

 void setGame()
{
        setFruitLocation();
        createArrayOfTailsSetValues();
        Form1->head->Left = playGroundWidth / 2; //middle of play ground
        Form1->head->Top = playGroundHeight / 2 ;

        //make all tail elements unvisible if there is second or more game
        for(int i = 0 ; i < score;i++)
        {
           pTail[i]->Visible = false;
        }
        score = 0;
        sndPlaySound("snd/intro.wav",SND_ASYNC); //play intro sound
        resetTimers();

        Form1->Label1->Caption = "Score: " + IntToStr(score);//initial label caption

}

//************************************************************************************

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
pTail[51] = Form1->Image51;
pTail[52] = Form1->Image52;
pTail[53] = Form1->Image53;
pTail[54] = Form1->Image54;
pTail[55] = Form1->Image55;
pTail[56] = Form1->Image56;
pTail[57] = Form1->Image57;
pTail[58] = Form1->Image58;
pTail[59] = Form1->Image59;
pTail[60] = Form1->Image60;
pTail[61] = Form1->Image61;
pTail[62] = Form1->Image62;
pTail[63] = Form1->Image63;
pTail[64] = Form1->Image64;
pTail[65] = Form1->Image65;
pTail[66] = Form1->Image66;
pTail[67] = Form1->Image67;
pTail[68] = Form1->Image68;
pTail[69] = Form1->Image69;
pTail[70] = Form1->Image70;
pTail[71] = Form1->Image71;
pTail[72] = Form1->Image72;
pTail[73] = Form1->Image73;
pTail[74] = Form1->Image74;
pTail[75] = Form1->Image75;
pTail[76] = Form1->Image76;
pTail[77] = Form1->Image77;
pTail[78] = Form1->Image78;
pTail[79] = Form1->Image79;
pTail[80] = Form1->Image80;
}

void __fastcall TForm1::QR1Click(TObject *Sender)
{
        Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VisitprojectGitHubrepository1Click(TObject *Sender)
{
  ShellExecute(NULL,"open","https://github.com/Luke42777/Snake_Game_Using_Builder_CPlusPlus.git",NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

