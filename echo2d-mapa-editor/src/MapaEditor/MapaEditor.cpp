#include "MapaEditor.h"
#include "../Menus/MainMenuBar.h"

MapaEditor::MapaEditor() : mRenderer(nullptr), mWindow(nullptr), mIsRunning(true){}

MapaEditor::~MapaEditor()
{
}

void MapaEditor::Initialize()
{
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    // Criar uma janela SDL e Renderer
    mWindow = SDL_CreateWindow("Editor De Mapas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mWindow || !mRenderer)
    {
        printf("Erro ao criar janela ou renderer SDL: %s\n", SDL_GetError());
        return;
    }
}

void MapaEditor::Run()
{
    Initialize();
    Setup();
    while (mIsRunning) {
        ProcessingInput();
        Update();
        Render();
    }
}

void MapaEditor::ProcessingInput()
{
    // Processar eventos SDL
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            mIsRunning = false;
    }
}

void MapaEditor::Setup()
{
    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Configurar estilo do ImGui
    ImGui::StyleColorsDark();

    io.Fonts->AddFontDefault()->FontSize = 20.0f;

    // Inicializar implementações de SDL2 e SDL_Renderer para ImGui
    ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer2_Init(mRenderer);

    io.Fonts->Build();

    // Personalizar padding do menu
    ImGuiStyle& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(10.0f, 10.0f);    // Padding dentro dos itens do menu
    style.ItemSpacing = ImVec2(20.0f, 10.0f);     // Espaçamento entre os itens do menu
    style.WindowPadding = ImVec2(15.0f, 15.0f);   // Padding da janela em geral
}

void MapaEditor::Update()
{
#ifdef _DEBUG
    // Iniciar novo frame ImGui
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    Menu_MainMenu(mWindow, mRenderer);

    // Renderizar interface
    ImGui::Render();
#endif
}

void MapaEditor::Render()
{
    // Renderizar SDL e ImGui
    SDL_SetRenderDrawColor(mRenderer, 114, 144, 154, 255);
    SDL_RenderClear(mRenderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);

    SDL_RenderPresent(mRenderer);
}

void MapaEditor::Destroy()
{

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
