#include <SFML/Graphics.hpp>
#include "lib.h"
#include <iostream>
#include "TextField.h"
#include <string>
#include <fstream>


using namespace sf;

int main()
{
    RenderWindow window(VideoMode(WINDOW_GORISONTAL_SIZE, WINDOW_VERTICAL_SIZE), "Game of Life 1"); //main window    
    GameField field;
    int size_to_draw = 50; 
    
    float timer = 0;
    float delay = 1;
    Clock clock;

    sf::Font font;
    if (!font.loadFromFile("20339.ttf"))
    {
        std::cout << "error";
    }    
    
    TextField textField;
    textField.setFont(font); //font
    textField.setLength(20);
    textField.setPlaceholder("Enter file name"); 
    textField.setPosition(sf::Vector2f(WINDOW_GORISONTAL_SIZE - 260,150)); //координаты для ввода

    Button RunButton(WINDOW_GORISONTAL_SIZE - 125, 25, 100, 40, font, "Run/Stop");
    Button SaveButton(WINDOW_GORISONTAL_SIZE - 125, 75, 100, 40, font, "Save");
    Button LoadButton(WINDOW_GORISONTAL_SIZE - 125, 200, 100, 40, font, "Load");
    Button NextButton(WINDOW_GORISONTAL_SIZE - 125, 275, 100, 40, font, "Next Step");
    Button SpeedUpButton(WINDOW_GORISONTAL_SIZE - 125, 325, 100, 40, font, "SpeedUp");
    Button SpeedDownButton(WINDOW_GORISONTAL_SIZE - 125, 375, 175, 40, font, "SpeedDown");
    Button SpeedValue(WINDOW_GORISONTAL_SIZE - 125, 425, 100, 40, font, "");


    while (window.isOpen())
    {   
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //getting mouse position
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / (CELL_SIZE + CELL_BORDER_SIZE);
        int y = pos.y / (CELL_SIZE + CELL_BORDER_SIZE);
        int Cell_On_Mouse = x * GAME_SIZE + y;        

        Event event;
        while (window.pollEvent(event))
        {
            HandleClose(window, event);                     
            field.ArrangeField(event, Cell_On_Mouse);
            RunButton.HandlePressed(event, pos.x, pos.y);
            SaveButton.HandlePressed(event, pos.x, pos.y);
            LoadButton.HandlePressed(event, pos.x, pos.y);
            //NextButton.HandlePressed(event, pos.x, pos.y);
            textField.input(event);            
            if (NextButton.HandlePressed(event, pos.x, pos.y)) field.iterate();
            if (SpeedUpButton.HandlePressed(event, pos.x, pos.y)) 
            {
                delay = delay - 0.1;
            }
            if (SpeedDownButton.HandlePressed(event, pos.x, pos.y)) 
            {
                delay = delay + 0.1;
            }
        }  

        if (SaveButton.get_pressedStatus())
        {
            
            string path;
            string one = "1";
            string zero = "0";
            path = textField.getText();           
           
            std::ofstream myfile;
            myfile.open(path.c_str());
            

            vector<Cell> Cells = field.get_arrCells();
            for (int i = 0; i < GAME_SIZE; i++)
            {
                for (int j = 0; j < GAME_SIZE; j++)
                {
                    int number = i * GAME_SIZE + j;
                    if (Cells[number].get_state() == alive)
                    {
                        myfile << one << endl;                        
                    } else {
                        myfile << zero << endl;
                    }

                }        
            }            
            //SaveButton.setStatus();
            myfile.close();
            
        }


        if (LoadButton.get_pressedStatus())
        {
            string path;            
            path = textField.getText();                    
           
            std::ifstream myfile;
            myfile.open(path.c_str());
            

            //vector<Cell> Cells = field.get_arrCells();
            field.Load(myfile);
            
            //LoadButton.setStatus(false);
            myfile.close();
            
        }        

        window.clear(sf::Color::White);  //setting the color of main window
        
        //std::string value = std::to_string(delay);
        
        
        if ((timer > delay) && RunButton.get_pressedStatus()) 
        {
            field.iterate(); //iterate if the time for iteration has come  &&  RunButton is in "run state"      
            timer = 0;
        }
        field.draw(window, size_to_draw);//drawing the Game in the window

        window.draw(RunButton.get_picture()); //drawing the RunButton
        window.draw(RunButton.get_label());
        window.draw(SaveButton.get_picture()); //drawing the RunButton
        window.draw(SaveButton.get_label());        
        window.draw(LoadButton.get_picture()); //drawing the RunButton
        window.draw(LoadButton.get_label());
        window.draw(NextButton.get_picture()); 
        window.draw(NextButton.get_label());
        window.draw(SpeedUpButton.get_picture()); 
        window.draw(SpeedUpButton.get_label());
        window.draw(SpeedDownButton.get_picture()); 
        window.draw(SpeedDownButton.get_label());    
        textField.render(window);
        //speedField.render(window);

        window.display();
    }
    return 0;
}

