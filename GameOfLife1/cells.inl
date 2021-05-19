#include <SFML/Graphics.hpp>

CellPicture::CellPicture(){
    setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    setOutlineThickness(CELL_BORDER_SIZE);
    setOutlineColor(sf::Color::Black);
}

CellPicture::~CellPicture(){

}

//CONSTRUCTORS of Class Cell
Cell::Cell(){
    x = 1;
    y = 1;
    state = dead;
}

Cell::Cell(int x, int y){
    this -> x = x;
    this -> y = y;
}

Cell::Cell(int x, int y, Cell_state state){
    this -> x = x;
    this -> y = y;
    this -> state = state;
}

///////////////////////////////////////////////////////////////////////////
Cell::~Cell(){

}

//Methods
void Cell::set_x(int x){
    this -> x = x;
}

void Cell::set_y(int y){
    this -> y = y;
}

void Cell::set_state(Cell_state state){
    this -> state = state;
}

void Cell::swap_state(){
    if (state == dead){
        state = alive;
    } else {
        state = dead;
    }
}

int Cell::get_x(){
    return x;
}

int Cell::get_y(){
    return y;
}

Cell_state Cell::get_state(){
    return state;
}


void Cell::SetPicture(){
    picture.setPosition((x - 1) * (CELL_SIZE + CELL_BORDER_SIZE) + CELL_BORDER_SIZE, (y - 1) * (CELL_SIZE + CELL_BORDER_SIZE) + CELL_BORDER_SIZE);
}

CellPicture Cell::get_picture(){
    if (state == alive) {
        picture.setFillColor(sf::Color::Green);
    } else {
        picture.setFillColor(sf::Color::White);
    }
    return picture;
} 

//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField
//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField//class GameField
GameField::GameField(){
    arrCells.resize(arrCells.size() + GAME_SIZE * GAME_SIZE);
    for (int i = 0; i < GAME_SIZE; i++){
        for (int j = 0; j < GAME_SIZE; j++){
            int number = i * GAME_SIZE + j;
            arrCells[number].set_x(i + 1);
            arrCells[number].set_y(j + 1);
            arrCells[number].set_state(dead);
            arrCells[number].SetPicture();
        }        
    } 
}

GameField::~GameField(){

}

vector<Cell> GameField::get_arrCells(){
    return arrCells;
}

int GameField::CountAlive(int x0, int y0){
    int count = 0;
    if ((x0 != 1) && (y0 != 1) && (x0 != GAME_SIZE) && (y0 != GAME_SIZE)){
        for (int i = 0; i <= 7; i++){
            int number = (x0 + CELL_NEIGHBOURS[i].x - 1) * GAME_SIZE + y0 + CELL_NEIGHBOURS[i].y - 1;
            if (arrCells[number].get_state() == alive) count++;  
        } 
        return count;
    }

    return 0; 
}

Cell* GameField::iterate(){
    Cell_state NextStepStates[GAME_SIZE * GAME_SIZE];
    #pragma omp parallel for  
    for (int i = 0; i < GAME_SIZE; i++ ){
        for(int j = 0; j < GAME_SIZE; j++){
            int CNumber = i * GAME_SIZE + j;
            int count = CountAlive(arrCells[CNumber].get_x(), arrCells[CNumber].get_y());
            NextStepStates[CNumber] = arrCells[CNumber].get_state();
            if ((arrCells[CNumber].get_state() == alive) && (count < 2)) NextStepStates[CNumber] = dead;
            if ((arrCells[CNumber].get_state() == alive) && (count > 3)) NextStepStates[CNumber] = dead;
            if ((arrCells[CNumber].get_state() == dead) && (count == 3)) NextStepStates[CNumber] = alive;
        }
    }

    #pragma omp parallel for  
    for (int i = 0; i < GAME_SIZE; i++){
        for (int j = 0; j < GAME_SIZE; j++){
            int CNumber = i * GAME_SIZE + j;
            arrCells[CNumber].set_state(NextStepStates[CNumber]);
        }        
    } 
}

void GameField::ArrangeField(sf::Event& event, int Cell_On_Mouse){
    if ((event.type == sf::Event::MouseButtonPressed) && (Cell_On_Mouse < GAME_SIZE * GAME_SIZE ))
        arrCells[Cell_On_Mouse].swap_state();
}

void GameField::draw(sf::RenderWindow& window, int size){
    #pragma omp parallel for  
    for (int i = 0; i < GAME_SIZE; i++){
        for (int j = 0; j < GAME_SIZE; j++){
            int Cell_Number = i * GAME_SIZE + j;
            window.draw(arrCells[Cell_Number].get_picture());
        }        
    } 
}

void GameField:: Load(std::ifstream& myfile)
{
    string one = "1";
    string zero = "0";
    string real;
    for (int i = 0; i < GAME_SIZE; i++)
            {
                for (int j = 0; j < GAME_SIZE; j++)
                {
                    int number = i * GAME_SIZE + j;
                    myfile >> real;
                    if (real == one)
                    {
                        arrCells[number].set_state(alive);                        
                    } else {
                        arrCells[number].set_state(dead);
                    }

                }        
            }            
}


