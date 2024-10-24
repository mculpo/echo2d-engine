#ifndef MAIN_ECHOMAPAEDITOR2D
#define MAIN_ECHOMAPAEDITOR2D
#include "Core/Core.h"
#include "MapaEditor/MapaEditor.h"

int main(int argc, char* argv[]) {

    MapaEditor *mMapEditor = new MapaEditor();
    mMapEditor->Run();

    return 0;
}

#endif