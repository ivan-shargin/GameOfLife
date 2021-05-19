
void swap_flag(bool* pflag){
    if (*pflag){
        *pflag = false;
    } else {
        *pflag = true;
    }
}

void HandleClose(sf::RenderWindow& window, sf::Event& event){
    //if exit button was pressed
    if (event.type == sf::Event::Closed)
        //then close the main window
        window.close();
}

//CONSTRUCTORS
Button::Button()
{
    x = 0;
    y = 0;
    xsize = 10;
    ysize = 10;
    
}

Button::Button(int x, int y, int xsize, int ysize, sf::Font& font, string name){
    this -> x = x;
    this -> y = y;
    this -> xsize = xsize;
    this -> ysize = ysize;
    pressedStatus = false;
    picture.setSize(sf::Vector2f(xsize, ysize));
    picture.setFillColor(sf::Color::Red);
    picture.setOutlineThickness(2);
    picture.setOutlineColor(sf::Color::Black);
    picture.setPosition(x, y);

    label.setFont(font);    
    label.setColor(sf::Color::Black);
    label.setPosition(x, y);
    label.setString(name);
    label.setCharacterSize(20);
}

///////////////////////////////////////////////////////////////////////////
Button::~Button(){

}
///////////////////////////////////////////////////////////////////////////

bool Button::HandlePressed(sf::Event event, int MouseX, int MouseY){
    if (event.type == sf::Event::MouseButtonPressed){
        if ((MouseX >= x) && (MouseY >= y) && (MouseX <= (x + xsize)) && (MouseY <= (y + ysize))) {
            pressedStatus = !pressedStatus;
            if (pressedStatus){
                picture.setFillColor(sf::Color::White);
            } else {
                picture.setFillColor(sf::Color::Red);
            }
            return true;
        }
    }
    return false;
}

bool Button::get_pressedStatus(){
    return pressedStatus;
}

sf::RectangleShape Button::get_picture(){
    if (pressedStatus){
                picture.setFillColor(sf::Color::White);
            } else {
                picture.setFillColor(sf::Color::Red);
            }
    return picture;
}

sf::Text Button::get_label(){
    return label;
}

void Button::setStatus(bool status){
    pressedStatus = status;
}

void Button::setLabel(string& s)
{
    label.setString(s);
}

