#pragma once

#include "main_lib.h"
#include "game.h"

#include "assets.h"

//virtual significa que essas funções podem ser substituídas nas subclasses (polimorfismo).

//= 0 torna essas funções puras virtuais, ou seja, a Scene é uma classe/interface abstrata, não pode ser instanciada diretamente.

//Todas as cenas específicas devem implementar essas funções.

//O destrutor virtual garante que, ao deletar um ponteiro Scene* para uma cena derivada, o destrutor correto será chamado (evita vazamento de memória).

struct Scene
{
    virtual ~Scene(){}                     // Destrutor virtual para liberar corretamente
    virtual void init() = 0;               // Inicialização da cena
    virtual void update(float dt) = 0;     // Atualização lógica
    virtual void render(float interp) = 0; // Renderização
    virtual void cleanup() = 0;            // Limpeza / desalocação
};

struct SceneMenu : public Scene
{
    void init() override;
    void update(float dt) override;
    void render(float interp) override;
    void cleanup() override;
};

struct SceneGame : public Scene
{
    void init() override;
    void update(float dt) override;
    void render(float interp) override;
    void cleanup() override;
};