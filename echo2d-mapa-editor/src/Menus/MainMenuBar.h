#ifndef MAINMENUBAR_ECHO2D_H
#define MAINMENUBAR_ECHO2D_H
#include "../Core/Core.h"
void Menu_MainMenu(SDL_Window *pWindows, SDL_Renderer *pRenderer) {
    // Criar a Barra de Menu Superior
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) { /* Lógica para novo arquivo */ }
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Lógica para abrir arquivo */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Lógica para salvar arquivo */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Lógica para desfazer */ }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* Lógica para refazer */ }
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

    // Definir a posição e o tamanho do painel esquerdo (fixo)
    ImGui::SetNextWindowPos(ImVec2(0, 30)); // Posição (x=0, y=20 para espaço para a barra superior)
    ImGui::SetNextWindowSize(ImVec2(300, windowHeight - 20)); // Tamanho fixo (largura=300, altura igual à janela menos a barra)
    ImGui::Begin("Painel Esquerdo", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Este é o painel esquerdo fixo.");
    ImGui::End();

    // Definir a posição e o tamanho do painel inferior (fixo)
    ImGui::SetNextWindowPos(ImVec2(300, windowHeight - 140)); // Posição (acima da borda inferior)
    ImGui::SetNextWindowSize(ImVec2(windowWidth - 300, 150)); // Largura ajustada e altura fixa
    ImGui::Begin("Painel Inferior", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Este é o painel inferior fixo.");
    ImGui::End();

    // Definir a posição e o tamanho da área principal (ajustável)
    ImGui::SetNextWindowPos(ImVec2(300, 30)); // Posição após o painel esquerdo e abaixo da barra de menu
    ImGui::SetNextWindowSize(ImVec2(windowWidth - 300, windowHeight - 170)); // Largura e altura ajustáveis
    ImGui::Begin("Área Principal", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Esta é a área principal ajustável.");
    ImGui::End();
}

#endif // !MAINMENUBAR_ECHO2D_H



