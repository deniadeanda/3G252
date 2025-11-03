#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>

#include <Dibujo.hpp>
#include <GestorDibujos.hpp>
#include <Corral.hpp>

using namespace ftxui;

static std::vector<std::u32string> Conejo1 = {
    U" (\\_/)",
    U" ( •_•)",
    U" /   \\"
};

static std::vector<std::u32string> ConejoCome = {
    U" (\\_/)",
    U" ( •ᴗ•) munch",
    U" /   \\"
};

static std::vector<std::u32string> Zanahoria = {
    U"  \\|/",
    U"   V",
    U"  / \\",
    U"  \\_/"
};

static std::vector<std::u32string> Arbol = {
    U"   &&& &&  & &&",
    U"  && &\\/&\\|& ()|",
    U"  &\\/(/&/&||/& /_/)_&",
    U"&() &\\/&|()|/&\\/ '%\" &",
    U"&_\\/_\\\\|& |&&/&__%_/_&",
    U"  &&   \\|||",
    U"       \\|||",
    U"        |||",
    U"        |||"
};

static std::vector<std::u32string> Flor = {
    U"  _(_)_  ",
    U" (_)@(_) ",
    U"   / \\   ",
    U"  /___\\  ",
    U"   \\_/   "
};

static std::vector<std::u32string> Sol = {
    U"  \\ | / ",
    U" -- o --",
    U"  / | \\ "
};

int main() {
    auto screen = Screen::Create(Dimension::Fixed(100), Dimension::Fixed(32));

    GestorDibujos gestor;

    gestor.Agregar(Dibujo(82, 3, Sol, Color::Yellow));

    gestor.Agregar(Dibujo(12, 14, Arbol, Color::Green));
    gestor.Agregar(Dibujo(44, 14, Arbol, Color::Green));
    gestor.Agregar(Dibujo(76, 14, Arbol, Color::Green));

    gestor.Agregar(Dibujo(6,  24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(20, 24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(34, 24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(48, 24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(62, 24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(76, 24, Flor, Color::GreenLight));
    gestor.Agregar(Dibujo(90, 24, Flor, Color::GreenLight));

    std::vector<int> pos_z = {24, 40, 56, 72, 88, 32, 64};
    int zi = 0;
    Dibujo zan( pos_z[zi], 22, Zanahoria, Color::Orange1 );

    Dibujo conejo(4, 22, Conejo1, Color::White);

    Corral corral(2, 2, 36, 10, Color::White);
    corral.AgregarAnimal(Dibujo(4, 4, Conejo1, Color::White));

    int dir = 1;
    int t = 0;
    int comer_t = 0;

    while (true) {
        screen.Clear();

        for (int i = 0; i < 7; ++i) {
            int base = 6 + i*14;
            gestor.dibujos[3 + i].x = base; 
        }

        gestor.dibujos[0].y = 3 + (int)(std::sin(t * 0.1) * 1.5);

        if (comer_t > 0) {
            conejo.figura = ConejoCome;
            comer_t--;
        } else {
            conejo.figura = Conejo1;
        }

        conejo.x += dir;
        int W = screen.dimx();
        if (conejo.x >= W - 16) dir = -1;
        if (conejo.x <= 2)      dir = 1;

        if (std::abs((conejo.x + 5) - zan.x) <= 3 && std::abs((conejo.y + 1) - zan.y) <= 3 && comer_t == 0) {
            comer_t = 12;
            zi = (zi + 1) % (int)pos_z.size();
            zan.x = pos_z[zi];
        }

        gestor.DibujarTodos(screen);
        zan.Dibujar(screen);
        conejo.Dibujar(screen);

        corral.Dibujar(screen);

        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        t++;
    }

    return 0;
}
