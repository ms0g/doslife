#include "APP.H"
#include "RENDERER.H"
#include "LIFESIM.H"

App::App() {
    renderer = new Renderer();

    lifesim = new LifeSimulator();

    isRunning = 1;
}

App::~App() {
    delete renderer;

    delete lifesim;
}

void App::loop(void) {
    while (isRunning) {
        update();
        render();
    }
}

void App::update(void) {
    lifesim->update();
}

void App::render(void) {
    renderer->clear(BLACK);

    lifesim->draw(renderer);

    renderer->updateBuffer();
}