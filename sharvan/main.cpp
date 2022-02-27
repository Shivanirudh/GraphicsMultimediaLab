//
//  main.cpp
//  3dtransform
//
//  Created by Sharvan Kumaran on 2/27/22.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/GLUT.h>
#include <vector>
#include <math.h>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef struct Point{
    double x;
    double y;
    double z;
    double h;
};

Point Multiply(vector<vector<double>> M, Point P);
double side = 2;
class Cube{
    map<char,Point> vertices;
    string quads[6] = {"ABCD","ADEF","CDEH","BCHG","BAFG","EFGH"};
    vector<vector<double>> side_colors = {{1.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}};
public: Cube(){
    vector<Point> points= {{-side/2,-side/2,-side/2},{-side/2,side/2,-side/2},{side/2,side/2,-side/2},{side/2,-side/2,-side/2},{side/2,-side/2,side/2},{-side/2,-side/2,side/2},{-side/2,side/2,side/2},{side/2,side/2,side/2}};
    for(int i=0;i<8;i++){
        vertices.insert(pair<char,Point>('A'+i,points[i]));
    }
}
    void draw(){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3d(-250, 0, 0);
        glVertex3d(250, 0, 0);
        glVertex3d(0, -250, 0);
        glVertex3d(0, 250, 0);
        glVertex3d(0, 0, -250);
        glVertex3d(0, 0, 250);
        glEnd();
        for(int i=0;i<6;i++){
            string quad = quads[i];
            glColor3f(side_colors[i][0], side_colors[i][1], side_colors[i][2]);
            glBegin(GL_QUADS);
            for(int j=0;j<4;j++){
                glVertex3d(vertices[quad[j]].x, vertices[quad[j]].y, vertices[quad[j]].z);
            }
            glEnd();
        }
        glFlush();
    }
    
    void rotateX(double theta){
        vector<vector<double>> R(4,vector<double>(4,0));
        double rad = (theta*3.14)/180;
        R[0][0]=1;
        R[1][1]=cos(rad);
        R[1][2]=sin(rad);
        R[2][1]=-sin(rad);
        R[2][2]=cos(rad);
        R[3][3]=1;
        for(int i = 0;i<8;i++){
            vertices['A'+i] = Multiply(R, vertices['A'+i]);
        }
    }
};

Point Multiply(vector<vector<double>> M, Point P){
    vector<double> product(4,0);
    vector<double> point = {P.x,P.y,P.z,P.h};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            product[i]+=M[i][j]*point[j];
        }
    }
    return Point({product[0],product[1],product[2],product[3]});
}

void init(){
    char choice;
    glClearColor(1, 1, 1, 0);
    glPointSize(3);
    glLoadIdentity();
    printf("I/O");
    scanf("%c", &choice);
    if(choice=='o'){
        gluPerspective(43.6, 1, 4, 15);
    }else{
        gluPerspective(43.6, 1, 5.2, 15);
    }
    gluLookAt(0, 0, 6, 0, 0, 5, 0, 1, 0);
    glEnable(GL_DEPTH_TEST);
}

void demo(){
    double theta;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    printf("Enter theta: ");
    scanf("%lf",&theta);
    Cube cube;
    cube.draw();
    cube.rotateX(theta);
    cube.draw();
    glFlush();
    
}
int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3d transform");
    glutDisplayFunc(demo);
    init();
    glutMainLoop();
}
