#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "LOpenGL.h"
#include<stdio.h>

class LTexture
{
    public:
    	//Constructor
        LTexture();

        //Destructor
        ~LTexture();

        //Creates texture from pixels
        bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );

        //Delete Texture
        void freeTexture();

        void render( GLfloat x, GLfloat y );

        GLuint getTextureID();

        GLuint textureWidth();

        GLuint textureHeight();

    private:
        //Texture name
        GLuint mTextureID;

        //Texture dimensions
        GLuint mTextureWidth;
        GLuint mTextureHeight;
};

#endif