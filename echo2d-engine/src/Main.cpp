#include "Game.h"

int main(int argc, char* argv[]) {

    EchoGame mEchoGame;

    mEchoGame.Initialize();
    mEchoGame.Run();
    mEchoGame.Destroy();

    return 0;
}