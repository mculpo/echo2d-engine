#ifndef MAIN_ECHO2D_H
#define MAIN_ECHO2D_H
#include "Game/EchoGame.h"

int main(int argc, char* argv[]) {

    EchoGame mEchoGame;

    mEchoGame.Initialize();
    mEchoGame.Run();
    mEchoGame.Destroy();

    return 0;
}

#endif