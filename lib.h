#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>
#include <fstream>
#include <omp.h>


using namespace std;

const unsigned int  WINDOW_GORISONTAL_SIZE = 1800;
const unsigned int  WINDOW_VERTICAL_SIZE = 1000;
const unsigned int  GAME_SIZE = 90;
const unsigned int  CELL_SIZE = 15;
const unsigned int  CELL_BORDER_SIZE = 2;

const sf::Vector2i CELL_NEIGHBOURS[8] = {sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, 1), sf::Vector2i(-1, 1), sf::Vector2i(-1, 0), sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(1, -1)};

const float DELAY = 0.2;

enum Cell_state{
    dead, alive
};

void swap_flag(int* );
void HandleClose(sf::RenderWindow&, sf::Event&);

class CellPicture : public sf::RectangleShape
{
    public:
    CellPicture();
    ~CellPicture();
};

class Cell
{
    int x, y; //coordinates relative to other cells, NOT in pixels!
    Cell_state state;
    CellPicture picture;
public:    
    Cell();
    Cell(int x, int y);
    Cell(int x, int y, Cell_state state);
    ~Cell();   
    void SetPicture();
    void set_x(int _x);
    void set_y(int _y);
    void set_state(Cell_state);
    void swap_state();
    int get_x();
    int get_y();
    Cell_state get_state();
    CellPicture get_picture();
};

class GameField
{
    vector<Cell> arrCells;
    int CountAlive(int x0, int y0);
public:
    GameField();
    ~GameField();
    vector<Cell> get_arrCells();
    Cell* iterate();
    void ArrangeField(sf::Event& event, int Cell_On_Mouse);
    void draw(sf::RenderWindow& window, int size);
    void Load(std::ifstream& myfile);
};

class Button{
    int x, y;
    int xsize, ysize;
    sf::RectangleShape picture;
    sf::Text label;
    bool pressedStatus;
public:
    Button();
    ~Button();
    Button(int x, int y, int xsize, int ysize, sf::Font& font, string name);
    bool HandlePressed(sf::Event event, int MouseX, int MouseY);
    bool get_pressedStatus();
    void setStatus(bool status);
    sf::RectangleShape get_picture();
    sf::Text get_label();
    void setLabel(string& s);
};

#include "cells.inl"
#include "interface.inl"