//
//  block.cpp
//  discForms
//
//  Created by sierra on 12/12/2019.
//

#include "block.hpp"

Block::Block(float x, float y, float z, float w, float h, float d)
{
    xPos = x;
    yPos = y;
    zPos = z;
    box.setWidth(w);
    box.setHeight(h);
    box.setDepth(d);
}

void Block::draw()
{
    ofPushMatrix();
    ofTranslate(xPos, yPos, zPos);
    
    ofSetColor(color);
    
    box.draw();
}

void Block::setColor(ofColor _color)
{
    color = _color;
    //std::cout<< _color << std::endl;
    
}

void Block::update()
{
    
}
