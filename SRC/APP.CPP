#include "APP.H"
#include "RENDERER.H"
#include "UI.H"
#include "KEYBRD.H"
#include "GOL.H"

App::App() {
    renderer = new Renderer();

    gol = new GOL();

    isRunning = 1;
}

App::~App() {
    delete renderer;

    delete gol;
}

void App::loop(void) {
    while (isRunning) {
        update();
        render();
    }
}

void App::update(void) {
    gol->update();
}

void App::render(void) {
    renderer->clear(BLACK);

    gol->draw(renderer);

    renderer->updateBuffer();
}