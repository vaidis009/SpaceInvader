//Vaidas Siupienius
//30.11.16
//space invader game
#include <SFML/Graphics.hpp>
#include <iostream>
#include "InvadersCl.h"

int rightMoves=0;
bool rightSide=true, leftSide=false;
int main()
{

    //create Window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Invader Game");
    // setup any shapes or variables.
    sf::RectangleShape player(sf::Vector2f(40, 20));
    // my code
    //sf::RectangleShape invader(sf::Vector2f(20, 20));

    // Invaders positions
    float invaderX = 0;
    float invaderY = 0;
    float invaderSpeed = 1.0f;
// array of invaders
    InvadersCl invaders[55];
    int invaderNum=0;
    for (int i=0;i<55;i++){
        //moving line when is 11 invaders
        if (invaderNum!=0 && invaderNum!=1 && invaderNum%11==0){
            invaderY+=25;
            invaderX=0;
        }
        invaders[invaderNum]=InvadersCl();
        invaders[invaderNum].invader.setPosition(sf::Vector2f(invaderX,invaderY));
        invaderX+=35;
        invaderNum++;
    }


    float playerX = 1;
    float playerY = 379;
    float playerSpeed = 1.0f;
    player.setFillColor(sf::Color::Red);
    player.setPosition(playerX, playerY);
    // set timepeFrame to 1 60th of a second. 60 frames per second
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // the clock object keeps the time.
    sf::Clock clock;
    clock.restart();
    invaderX = 0;
    invaderY = 0;
    bool reachEnd=true, reachBegining= false;
    int movesCounter;


    while (window.isOpen())
    {

        invaderNum=0;
        invaderX=0;
        // check if the close window button is clicked on.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //get the time since last update and restart the clock
        timeSinceLastUpdate += clock.restart();
        //update every 60th of a second
        //only when the time since last update is greate than 1/60 update the world.
        if (timeSinceLastUpdate > timePerFrame) {
            // get keyboard input.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerX = playerX - playerSpeed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerX = playerX + playerSpeed;
            }

//my code for moving invaders************************************************
        if(rightSide) {
            invaderX = invaderX + invaderSpeed;
            for (int i = 0; i < 55; i++) {
                invaders[invaderNum].invader.move(invaderX, invaderY);
                invaderNum++;
            }
            rightMoves++;
            if (rightMoves == 220) {
                rightSide = false;
                leftSide = true;
                invaderNum = 0;
                for (int i = 0; i < 55; i++) {
                    sf::Vector2f position =invaders[i].invader.getPosition();
                    std::cout<<invaderNum;
                    invaders[i].invader.setPosition(sf::Vector2f(position.x,position.y+10));
                }
            }
        }
            if(leftSide){
                invaderX= invaderX-invaderSpeed;
                for (int i = 0; i < 55; i++) {
                    invaders[invaderNum].invader.move(invaderX, invaderY);
                    invaderNum++;

                }
                rightMoves--;
                if(rightMoves==0){
                    rightSide=true;
                    leftSide=false;
                    for (int i = 0; i < 55; i++) {
                        sf::Vector2f position =invaders[i].invader.getPosition();
                        std::cout<<invaderNum;
                        invaders[i].invader.setPosition(sf::Vector2f(position.x,position.y+10));
                    }

                }
            }
//**********end of moving invaders ******************************************************

            // update any variables..
            player.setPosition(playerX, playerY);

            // clear the screen and draw all the shapes
            window.clear();
            window.draw(player);
            for (int i=0;i<55;i++){
                window.draw(invaders[i].invader);
            }



            window.display();
            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;
        }






        //my code
        if (playerX==0){
            playerX=559;
        }
        else if(playerX==560){
            playerX=1;
        }

    }


    return 0;
}