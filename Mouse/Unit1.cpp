//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int CheesPos[10][10];
Graphics::TBitmap*CheesImage[2];
Graphics::TBitmap*Back;
Graphics::TBitmap*MouseImage;
Graphics::TBitmap*CatImage;
TPoint MousePos;
int CatsCol;
TPoint CatsPos[20];  //Положения x,y каждого кота
TPoint CatsSpeed[20];//Скорости dx,dy каждого кота
int Lifes;
int Ochki;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
randomize();
PutCheesInGame();
Back=new Graphics::TBitmap();
Back->Width =300;
Back->Height=300;
MouseImage=new Graphics::TBitmap();
MouseImage->LoadFromFile("Mouse.bmp");
CatImage=new Graphics::TBitmap();
CatImage->LoadFromFile("Cat.bmp");
CatImage->Transparent=true;
for(int i=0;i<2;i++)
        {
        CheesImage[i]=new Graphics::TBitmap();
        CheesImage[i]->LoadFromFile("chees"+IntToStr(i+1)+".bmp");
        }
CatsCol=6;
for(int i=0;i<20;i++)               //Кота будет два
        CatsPos[i]=Point(-100,-100);    //Но всех двадцать помещаем в начальное положение -1, тоесть никуда
Lifes=3;
Ochki=0;
}
//---------------------------------------------------------------------------


TForm1::PutCheesInGame()     //Начальная функция
{
        for(int j=0;j<10;j++)
                for(int i=0;i<10;i++)
                CheesPos[i][j]=random(2);  //Выбираем картинку с сыром 1 или 2
MousePos=Point(5,5);
                                           //случайную
}

TForm1::DrawCheesOnForm()
{
         for(int j=0;j<10;j++)
                for(int i=0;i<10;i++)
                        if(CheesPos[i][j]!=-1)Back->Canvas->Draw(i*30,j*30,CheesImage[CheesPos[i][j]]);
                        else
                        {
                        Back->Canvas->Brush->Color=RGB(192,192,192);
                        Back->Canvas->FillRect(Rect(i*30,j*30,i*30+30,j*30+30));
                        }
}

TForm1::FlipOnForm()
{
        Canvas->Draw(0,0,Back);
}


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if(CheesPos[MousePos.x][MousePos.y]!=-1)
        {
        Ochki++;
        Label2->Caption="Очки:"+IntToStr(Ochki);
        CheesPos[MousePos.x][MousePos.y]=-1;
        }
MoveCats();
DrawCheesOnForm();
Back->Canvas->Draw(MousePos.x*30,MousePos.y*30,MouseImage);
DrawCat();
FlipOnForm();
if(IfTheMouseEatAllChees())
        {
        Timer1->Enabled=false;
        ShowMessage("Урааа!!!!!\nМыша съела весь сыр\nПереход на следующий уровень");
        CatsCol++;
        MousePos=Point(5,5);
        for(int i=0;i<CatsCol;i++)CatsPos[i].x=-100;
        PutCheesInGame();
        Timer1->Enabled=true;
        }
if(TestCatEatMouse())
        {
        Timer1->Enabled=false;
        ShowMessage("Вас сожрали голодные коты");
        if(Lifes>0)
        {
        Lifes--;
        Label1->Caption="Жизней:"+IntToStr(Lifes);
        MousePos=Point(5,5);
        for(int i=0;i<CatsCol;i++)CatsPos[i].x=-100;
        Timer1->Enabled=true;
        }else
                {
                ShowMessage("Вы набрали "+IntToStr(Ochki)+" очков");
                ShowMessage("Вам прийдется начинать сначала");
                Lifes=3;
                Label1->Caption="Жизней:"+IntToStr(Lifes);
                CatsCol=6;
                MousePos=Point(5,5);
                for(int i=0;i<CatsCol;i++)CatsPos[i].x=-100;
                PutCheesInGame();
                Ochki=0;
                Timer1->Enabled=true;
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_LEFT)
        {
        MousePos.x--;
        }
if(Key==VK_RIGHT)
        {
        MousePos.x++;
        }
if(Key==VK_UP)
        {
        MousePos.y--;
        }
if(Key==VK_DOWN)
        {
        MousePos.y++;
        }
if(MousePos.x>9)MousePos.x=9;
if(MousePos.x<0)MousePos.x=0;
if(MousePos.y>9)MousePos.y=9;
if(MousePos.y<0)MousePos.y=0;
}
//---------------------------------------------------------------------------


TForm1::MoveCats()
{
for(int i=0;i<CatsCol;i++)     //Проходимся по всем активным котам
        {
        if(CatsPos[i].x!=-100)
                {
                CatsPos[i].x+=CatsSpeed[i].x;
                CatsPos[i].y+=CatsSpeed[i].y;
                if(CatsPos[i].x>340)CatsPos[i].x=-100;
                if(CatsPos[i].x<-40)CatsPos[i].x=-100;
                if(CatsPos[i].y>340)CatsPos[i].x=-100;
                if(CatsPos[i].y<-40)CatsPos[i].x=-100;
                }
        if(CatsPos[i].x==-100)
                {
                switch(random(4))
                        {
                        case 0:CatsPos[i].x=-30;CatsPos[i].y=random(270);
                             CatsSpeed[i].x=1;CatsSpeed[i].y=random(3)-1;
                             break;

                        case 1:CatsPos[i].x=330;CatsPos[i].y=random(270);
                             CatsSpeed[i].x=-1;CatsSpeed[i].y=random(3)-1;
                             break;

                        case 2:CatsPos[i].y=-30;CatsPos[i].x=random(270);
                             CatsSpeed[i].y=1;CatsSpeed[i].x=random(3)-1;
                             break;

                        case 3:CatsPos[i].y=330;CatsPos[i].x=random(270);
                             CatsSpeed[i].y=-1;CatsSpeed[i].x=random(5)-2;
                             break;
                        }
                }
        }
}

TForm1::DrawCat()
{
       for(int i=0;i<CatsCol;i++)
       {
       if(CatsPos[i].x!=-100)Back->Canvas->Draw(CatsPos[i].x,CatsPos[i].y,CatImage);
       }
}

bool __fastcall TForm1::TestCatEatMouse()
{
for(int j=0;j<CatsCol;j++)
{
RECT Rect1=Rect(MousePos.x*30,MousePos.y*30,MousePos.x*30+30,MousePos.y*30+30);
RECT Rect3=Rect(0,0,0,0);
RECT Rect2=Rect(CatsPos[j].x+5,CatsPos[j].y+5,CatsPos[j].x+25,CatsPos[j].y+25);
if(IntersectRect(&Rect3,&Rect1,&Rect2))
{
return true;
}
}
return false;
}

bool TForm1::IfTheMouseEatAllChees()
{
       for(int j=0;j<10;j++)
               for(int i=0;i<10;i++)
               {
               if(CheesPos[i][j]!=-1)return false;
               }
return true;
}