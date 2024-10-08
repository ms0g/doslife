#ifndef APP_H
#define APP_H

class Renderer;
class LifeSimulator;
class App {
public:
    App();
    
    ~App();

    void loop(void);

private:
    void update(void);

    void render(void);

    Renderer* renderer;
    
    LifeSimulator* lifesim;

    int isRunning;
};
#endif