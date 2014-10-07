#include "Widget.h"
#include <QApplication>

#include "Board.h"
#include "GameEngine.h"

using namespace Chess;
using namespace Chess::GameLogic::GameComponents;

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    GameEngine engine;
    engine.run();

    MovementFlags flag = POWERMOVE_FLAG | CASTLING_FLAG;

    switch ( flag )
    {
    case POWERMOVE_FLAG:
        qDebug() << "Power move";
        break;
    case CASTLING_FLAG:
        qDebug() << "Castling";
        break;
    case POWERMOVE_FLAG | CASTLING_FLAG:
        qDebug() << "Power castling";
        break;
    case CHECK_FLAG:
        qDebug() << "Check";
    }

    return a.exec();
}

// do not expand
/*
              .,-:;//;:=,
          . :H@@@MM@M#H/.,+%;,
       ,/X+ +M@@M@MM%=,-%HMMM@X/,
     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-
    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.
  ,%MM@@MH ,@%=             .---=-=:=,.
  =@#@@@MX.,                -%HX$$%%%:;
 =-./@M@M$                   .;@MMMM@MM:
 X@/ -$MM/                    . +MM@@@M$
,@M@H: :@:                    . =X#@@@@-
,@@@MMX, .                    /H- ;@M@M=
.H@@@@M@+,                    %MM+..%#$.
 /MMMM@MMH/.                  XM@MH; =;
  /%+%$XHH@$=              , .H@@@@MX,
   .=--------.           -%H.,@@@@@MX,
   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
       =%@M@M#@$-.=$@MM@@@M; %M%=
         ,:+$+-,/H#MMMMMMM@= =,
               =++%%%%+/:-.
*/
