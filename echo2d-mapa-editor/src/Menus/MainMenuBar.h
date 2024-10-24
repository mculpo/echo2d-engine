#ifndef MAINMENUBAR_ECHO2D_H
#define MAINMENUBAR_ECHO2D_H
#include "../Core/Core.h"
void Menu_MainMenu(SDL_Window *pWindows, SDL_Renderer *pRenderer) {
    // Criar a Barra de Menu Superior
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) { /* L�gica para novo arquivo */ }
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* L�gica para abrir arquivo */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* L�gica para salvar arquivo */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* L�gica para desfazer */ }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* L�gica para refazer */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Solution Explorer")) { /* Alternar Painel */ }
            if (ImGui::MenuItem("Output")) { /* Alternar Painel */ }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Obter o tamanho da janela principal
    int windowWidth, windowHeight;
    SDL_GetWindowSize(pWindows, &windowWidth, &windowHeight);

    // Definir a posi��o e o tamanho do painel esquerdo (fixo)
    ImGui::SetNextWindowPos(ImVec2(0, 30)); // Posi��o (x=0, y=20 para espa�o para a barra superior)
    ImGui::SetNextWindowSize(ImVec2(300, windowHeight - 20)); // Tamanho fixo (largura=300, altura igual � janela menos a barra)
    ImGui::Begin("Painel Esquerdo", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Este � o painel esquerdo fixo.");
    ImGui::End();

    // Definir a posi��o e o tamanho do painel inferior (fixo)
    ImGui::SetNextWindowPos(ImVec2(300, windowHeight - 140)); // Posi��o (acima da borda inferior)
    ImGui::SetNextWindowSize(ImVec2(windowWidth - 300, 150)); // Largura ajustada e altura fixa
    ImGui::Begin("Painel Inferior", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Este � o painel inferior fixo.");
    ImGui::End();

    // Definir a posi��o e o tamanho da �rea principal (ajust�vel)
    ImGui::SetNextWindowPos(ImVec2(300, 30)); // Posi��o ap�s o painel esquerdo e abaixo da barra de menu
    ImGui::SetNextWindowSize(ImVec2(windowWidth - 300, windowHeight - 170)); // Largura e altura ajust�veis
    ImGui::Begin("�rea Principal", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Esta � a �rea principal ajust�vel.");
    ImGui::End();
}

#endif // !MAINMENUBAR_ECHO2D_H



