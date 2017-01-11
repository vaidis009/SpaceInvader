//Vaidas Siupienius
//30.11.16
//space invader game
#include <SFML/Graphics.hpp>
#include <iostream>
#include "InvadersCl.h"
#include "cmake_module/BulletCl.h"

int rightMoves=0;
bool rightSide=true, leftSide=false;
BulletCl bullet[10];
float bulletY;
bool createBullet=true;
InvadersCl invaders[55];
sf::Vector2f playerPosition;
int j=0;
int invaderShoot=0;
int bulletNum=0;
int invaderNum=-1;
int shootedInvaders[55];
int shootedListCounter=0;
int leftSideScreen=0;
int rightSideScreen=220;
bool touchPlayer =false;
sf::Vector2f mostRight;
int shooted=0, shootedCollumn=0;

int main()
{
    //create Window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Invader Game");
    // setup any shapes or variables.
    sf::RectangleShape player(sf::Vector2f(40, 20));
// my code*************************************************************************
    // Invaders positions
    float invaderX = 0;
    float invaderY = 0;
    float invaderSpeed = 1.0f;
    float bulletSpeed=0.1f;
// array of invaders

    for (int j=0;j<55;j++){
        //moving line when is 11 invaders
        if (j!=0 && j!=1 && j%11==0){
            invaderY+=25;
            invaderX=0;
        }
        //std:: cout<<j;
        invaders[j]=InvadersCl();
        invaders[j].invader.setPosition(sf::Vector2f(invaderX,invaderY));
        invaderX+=35;
        invaderNum++;
    }
    float playerX = 1;
    float playerY = 379;
    float playerSpeed = 1.0f;
    player.setFillColor(sf::Color::Red);
    player.setPosition(playerX, playerY);
// ***********************************************************************************************

    // set timepeFrame to 1 60th of a second. 60 frames per second
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // the clock object keeps the time.
    sf::Clock clock;
    clock.restart();
    invaderY = 0;
    while (window.isOpen()) {
        invaderNum = 0;
        invaderX = 0;
        // check if the close window button is clicked on.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
// for checking is it touch player
        for (int i = 0; i < 55; i++) {
            if (invaders[i].invader.getGlobalBounds().intersects(player.getGlobalBounds()) == true) {
                touchPlayer = true;
            }
        }
        // until shoot all invaders
        if (shootedListCounter != 55 && touchPlayer == false) {
            //get the time since last update and restart the clock
            timeSinceLastUpdate += clock.restart();
            //update every 60th of a second
            //only when the time since last update is greate than 1/60 update the world.
            if (timeSinceLastUpdate > timePerFrame) {
                // get keyboard input.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    playerX = playerX - playerSpeed;
                    playerPosition = player.getPosition();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    playerX = playerX + playerSpeed;
                    playerPosition = player.getPosition();
                }
//for bullets and enamies
                for (int i = 0; i < 55; i++) {
                    if (invaders[i].invader.getGlobalBounds().intersects(bullet[bulletNum].bullet.getGlobalBounds()) ==
                        true) {
                        shootedInvaders[shootedListCounter] = i;
                        invaders[i].invader.setPosition(sf::Vector2f(-350, -350));
                        shootedListCounter++;
                        bullet[bulletNum].bullet.setPosition(sf::Vector2f(playerPosition.x + 15, -5));
                        invaderShoot++;

                    }
                }
//my code for moving invaders************************************************
                if (rightSide) {
                    invaderX = invaderX + 1;
                    for (int i = 0; i < 55; i++) {
                        invaders[i].invader.move(invaderX, invaderY);

                    }
                    rightMoves++;
                    if (rightMoves == rightSideScreen) {
                        rightSide = false;
                        leftSide = true;

                        // invaderNum = 0;
                        for (int j = 0; j < 55; j++) {
                            sf::Vector2f position = invaders[j].invader.getPosition();
                            invaders[j].invader.setPosition(sf::Vector2f(position.x, position.y + 10));
                        }
                    }
                }
                if (leftSide) {
                    invaderX = invaderX - 1;
                    for (int i = 0; i < 55; i++) {
                        invaders[i].invader.move(invaderX, invaderY);

                    }
                    rightMoves--;
                    if (rightMoves == leftSideScreen) {
                        rightSide = true;
                        leftSide = false;
                        for (int i = 0; i < 55; i++) {
                            sf::Vector2f position = invaders[i].invader.getPosition();
                            invaders[i].invader.setPosition(sf::Vector2f(position.x, position.y + 10));
                        }
                    }
                }
//**********end of moving invaders ******************************************************
                // update any variables..
                player.setPosition(playerX, playerY);
                // clear the screen and draw all the shapes
                window.clear();
                window.draw(player);

// starts bullets**********************************************************************************
                //bullet[bulletNum].bullet.setPosition(sf::Vector2f(playerPosition.x + 15, 377));
                window.draw(bullet[bulletNum].bullet);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (createBullet) {
                        bullet[bulletNum].bullet.setPosition(sf::Vector2f(playerPosition.x + 15, 377));
                        window.draw(bullet[bulletNum].bullet);
                        createBullet = false;
                    }
                }
                bullet[bulletNum].bullet.move(sf::Vector2f(0, -20));
                sf::Vector2f bulletPosition = bullet[bulletNum].bullet.getPosition();
// getting bullet position and checking is it reach top op screen
                if (bulletPosition.y <= 0.0f) {
                    createBullet = true;
                }
                //Drawing invaders ******************************
                for (int k = 0; k < 55; k++) {
                    if (k != shootedInvaders[shootedListCounter]) {
                        window.draw(invaders[k].invader);
                    }
                }

//****Ends of bullets*************************************************************************

                window.display();
                // reset the timeSinceLastUpdate to 0
                timeSinceLastUpdate = sf::Time::Zero;
            }
            //my code
            if (playerX == 0) {
                playerX = 559;
            } else if (playerX == 560) {
                playerX = 1;
            }
        }
// if touch the player  red screen
        else if (touchPlayer) {
            window.clear(sf::Color::Red);
            window.display();
        }

// if all invaders shooted
        else {
            window.clear(sf::Color::Green);
            window.display();


        }

    }

    return 0;
}