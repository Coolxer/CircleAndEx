#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/////const infos////////////////
const int width = 600;
const int height = 600;
const int fps = 60;

sf::RenderWindow *window; //window here

sf::Text text;
sf::Text text2;
sf::Text text3;
sf::Font font;//main font of the project

//grid sprite & texture declaration
sf::Sprite gridSprite;
sf::Texture gridTexture;

// decleration of table elements[9] and textures
sf::Sprite elements[9];

sf::Texture texture_X;
sf::Texture texture_O;
sf::Texture transparent;

int whoNow;//random who is play this turn(and first who starts?)
int steps = 0;//it helps to keep check() function

sf::Vector2f position;//position mouse of the window

/////////////////////////////////////    MANAGEMENT FUNCTIONS()   /////////////////////////

void input();
void draw();

////////////////////////////////////     OTHERS FUNCTIONS()      /////////////////////////

void check()//this function() checks for the scores
{
    if(steps >= 5)
    {
        //win X
        if(elements[0].getTexture() == &texture_X && elements[1].getTexture() == &texture_X && elements[2].getTexture() == &texture_X  )text.setString("WON X!");
        else if(elements[3].getTexture() == &texture_X && elements[4].getTexture() == &texture_X && elements[5].getTexture() == &texture_X )text.setString("WON X!");
        else if(elements[6].getTexture() == &texture_X && elements[7].getTexture() == &texture_X && elements[8].getTexture() == &texture_X )text.setString("WON X!");

        else if(elements[0].getTexture() == &texture_X && elements[3].getTexture() == &texture_X && elements[6].getTexture() == &texture_X )text.setString("WON X!");
        else if(elements[1].getTexture() == &texture_X && elements[4].getTexture() == &texture_X && elements[7].getTexture() == &texture_X )text.setString("WON X!");
        else if(elements[2].getTexture() == &texture_X && elements[5].getTexture() == &texture_X && elements[8].getTexture() == &texture_X )text.setString("WON X!");

        else if(elements[0].getTexture() == &texture_X && elements[4].getTexture() == &texture_X && elements[8].getTexture() == &texture_X )text.setString("WON X!");
        else if(elements[2].getTexture() == &texture_X && elements[4].getTexture() == &texture_X && elements[6].getTexture() == &texture_X )text.setString("WON X!");

        //win O

        else if(elements[0].getTexture() == &texture_O && elements[1].getTexture() == &texture_O && elements[2].getTexture() == &texture_O )text.setString("WON O!");
        else if(elements[3].getTexture() == &texture_O && elements[4].getTexture() == &texture_O && elements[5].getTexture() == &texture_O )text.setString("WON O!");
        else if(elements[6].getTexture() == &texture_O && elements[7].getTexture() == &texture_O && elements[8].getTexture() == &texture_O )text.setString("WON O!");

        else if(elements[0].getTexture() == &texture_O && elements[3].getTexture() == &texture_O && elements[6].getTexture() == &texture_O )text.setString("WON O!");
        else if(elements[1].getTexture() == &texture_O && elements[4].getTexture() == &texture_O && elements[7].getTexture() == &texture_O )text.setString("WON O!");
        else if(elements[2].getTexture() == &texture_O && elements[5].getTexture() == &texture_O && elements[8].getTexture() == &texture_O )text.setString("WON O!");

        else if(elements[0].getTexture() == &texture_O && elements[4].getTexture() == &texture_O && elements[8].getTexture() == &texture_O )text.setString("WON O!");
        else if(elements[2].getTexture() == &texture_O && elements[4].getTexture() == &texture_O && elements[6].getTexture() == &texture_O )text.setString("WON O!");

        //draw
        else if(steps == 9) text.setString("DRAW!");

    }

}

////////////////////////////////////     INT MAIN() FUNCTION     /////////////////////////

int main()
{
    sf::Clock clock;

    srand(time(NULL));

    window = new sf::RenderWindow(sf::VideoMode(width,height,32), "tetris");
    window->setFramerateLimit(fps);

    whoNow = (rand()%2)+1;

    //loading textures...
    if(!gridTexture.loadFromFile("grid.png")) cout<<"Error.Not found grid texture!";

    if(!texture_X.loadFromFile("x.png")) cout<<"Error.Not found x texture!";

    if(!texture_O.loadFromFile("o.png")) cout<<"Error.Not found o texture!";

    if(!transparent.loadFromFile("transparent.png")) cout<<"Error.Not found transparent texture!";

    if(!font.loadFromFile("arial.ttf")) cout<<"Error. Not found font!";

    gridSprite.setTexture(gridTexture);
    gridSprite.setPosition(sf::Vector2f(100,100));

    text.setFont(font);
    text.setCharacterSize(150);
    text.setPosition(sf::Vector2f(30,200));

    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setPosition(sf::Vector2f(140,40));

    text3.setFont(font);
    text3.setCharacterSize(50);
    text3.setPosition(sf::Vector2f(140,40));

    if(whoNow == 1) text3.setString("Turn Player: X");
    else text3.setString("Turn Player: O");

    while(window->isOpen())
    {
        input();
        if(clock.getElapsedTime().asSeconds()>=1.0f/fps)
        {
            draw();
            check();
            clock.restart();
        }
    }
    delete window;
    return 0;
}

////////////////////////////////////     END OF  MAIN() FUNCTION     /////////////////////////

void input()
{
    sf::Event event;
    int x,y; //the variables of vector2f position(x,y)

    while(window->pollEvent(event))
    {
           if((event.type == sf::Event::Closed) ||
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window->close();

           if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                  x=0;y=0;

                  //reset
                  if(text.getString() == "DRAW!" || text.getString() == "WON X!" || text.getString() == "WON O!")
                  {
                      steps = 0;
                      text.setString("");
                      for(int i=0; i<9; i++)
                      {
                          elements[i].setPosition(x,y);
                          elements[i].setTexture(transparent);
                      }
                  }

                  position = sf::Vector2f(sf::Mouse::getPosition(*window));
                  x = position.x;
                  y = position.y;

                  /////////first row
                  if((x>143 && x<250) && (y>143 && y<250))
                  {
                      x=170; y=170;

                      if(whoNow == 1 && elements[0].getTexture() != &texture_X && elements[0].getTexture() != &texture_O )
                      {
                          elements[0].setPosition(x,y);
                          elements[0].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[0].getTexture() != &texture_X && elements[0].getTexture() != &texture_O )
                      {
                          elements[0].setPosition(x,y);
                          elements[0].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>250 && x<350) && (y>143 && y<250))
                  {
                      x=270; y=170;

                      if(whoNow == 1 && elements[1].getTexture() != &texture_X && elements[1].getTexture() != &texture_O )
                      {
                          elements[1].setPosition(x,y);
                          elements[1].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[1].getTexture() != &texture_X && elements[1].getTexture() != &texture_O )
                      {
                          elements[1].setPosition(x,y);
                          elements[1].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>350 && x<457) && (y>143 && y<250))
                  {
                      x=370; y=170;

                      if(whoNow == 1 && elements[2].getTexture() != &texture_X && elements[2].getTexture() != &texture_O )
                      {
                          elements[2].setPosition(x,y);
                          elements[2].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[2].getTexture() != &texture_X && elements[2].getTexture() != &texture_O )
                      {
                          elements[2].setPosition(x,y);
                          elements[2].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  //////////second row

                  else if((x>143 && x<250) && (y>250 && y<350))
                  {
                      x=170; y=270;

                      if(whoNow == 1 && elements[3].getTexture() != &texture_X && elements[3].getTexture() != &texture_O )
                      {
                          elements[3].setPosition(x,y);
                          elements[3].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[3].getTexture() != &texture_X && elements[3].getTexture() != &texture_O )
                      {
                          elements[3].setPosition(x,y);
                          elements[3].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>250 && x<350) && (y>250 && y<350))
                  {
                      x=270; y=270;

                     if(whoNow == 1 && elements[4].getTexture() != &texture_X && elements[4].getTexture() != &texture_O )
                      {
                          elements[4].setPosition(x,y);
                          elements[4].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[4].getTexture() != &texture_X && elements[4].getTexture() != &texture_O )
                      {
                          elements[4].setPosition(x,y);
                          elements[4].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>350 && x<457) && (y>250 && y<350))
                  {
                      x=370; y=270;

                      if(whoNow == 1 && elements[5].getTexture() != &texture_X && elements[5].getTexture() != &texture_O )
                      {
                          elements[5].setPosition(x,y);
                          elements[5].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[5].getTexture() != &texture_X && elements[5].getTexture() != &texture_O )
                      {
                          elements[5].setPosition(x,y);
                          elements[5].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  //////////third row

                  else if((x>143 && x<250) && (y>350 && y<457))
                  {
                      x=170;y=370;

                      if(whoNow == 1 && elements[6].getTexture() != &texture_X && elements[6].getTexture() != &texture_O )
                      {
                          elements[6].setPosition(x,y);
                          elements[6].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[6].getTexture() != &texture_X && elements[6].getTexture() != &texture_O )
                      {
                          elements[6].setPosition(x,y);
                          elements[6].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>250 && x<350) && (y>350 && y<457))
                  {
                      x=270;y=370;

                      if(whoNow == 1 && elements[7].getTexture() != &texture_X && elements[7].getTexture() != &texture_O )
                      {
                          elements[7].setPosition(x,y);
                          elements[7].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[7].getTexture() != &texture_X && elements[7].getTexture() != &texture_O )
                      {
                          elements[7].setPosition(x,y);
                          elements[7].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else if((x>350 && x<457) && (y>350 && y<457))
                  {
                      x=370; y=370;

                      if(whoNow == 1 && elements[8].getTexture() != &texture_X && elements[8].getTexture() != &texture_O )
                      {
                          elements[8].setPosition(x,y);
                          elements[8].setTexture(texture_X);
                          steps++;
                          text2.setString("Turn Player: O");
                          text3.setString("");
                          whoNow++;
                      }
                      else if(whoNow == 2 && elements[8].getTexture() != &texture_X && elements[8].getTexture() != &texture_O )
                      {
                          elements[8].setPosition(x,y);
                          elements[8].setTexture(texture_O);
                          steps++;
                          text2.setString("Turn Player: X");
                          text3.setString("");
                          whoNow--;
                      }
                  }

                  else //clicked over the map
                  {
                      cout<<"You are outside the map!"<<endl;
                  }
            }
    }
}

void draw()
{
    window->clear(sf::Color::Black);
    window->draw(gridSprite);

    for(int i=0; i<9; i++)
    {
        window->draw(elements[i]);
    }

    window->draw(text);
    window->draw(text2);
    window->draw(text3);

    //draw something
    window->display();
}
