//
//  block.hpp
//  discForms
//
//  Created by sierra on 12/12/2019.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include "ofMain.h"
#include "block.hpp"
#include <vector>

class Block
{
public:
    Block(float x, float y, float z, float w, float h, float d);
    void draw();
    void setColor(ofColor _color);
    
    void update();
    
    
    private:
    float xPos;
    float yPos;
    float zPos;
    
    ofColor color;
    
    ofBoxPrimitive box;
};

#endif /* block_hpp */
