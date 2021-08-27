#include "Signatures.h"

bool initGL(){

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	gluOrtho2D(-640.0,640.0,-480.0,480.0);

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glColor3f(0.0f, 0.0f, 0.0f);

    glPointSize(POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update(){

}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
    drawPolygon();
    glFlush();

    while(true){
    	glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);

    	cout<<"Choose transformation: "<<endl;
		cout<<"1 for Translation"<<endl<<"2 for Rotation"<<endl;
		cout<<"3 for Scaling"<<endl<<"4 for Reflection"<<endl;
		cout<<"5 for shearing"<<endl<<"0 to Exit"<<endl;
		cout<<"Enter your choice: ";cin>>transformation;

        cout<<"transformation: "<<transformation<<endl;
        if(!transformation){
            return;
        }

		if(transformation == 1){
			cout<<"Enter the translation factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            drawTranslatedPolygon(factor_x,factor_y);
		}
		else if(transformation == 2){
			double angle;
			cout<<"Enter the rotation angle: ";
            cin>>angle;
            double x,y;
            cout<<"Enter point about which to be rotated: ";
            cin>>x>>y;
            angle_radians = angle * 3.1416 / 180;
            drawPolygon();
            drawRotatedPolygon(angle_radians, x, y);
		}
		else if(transformation == 3){
			cout<<"Enter the scaling factor for X and Y: ";
            cin>>factor_x >> factor_y;
            double x,y;
            cout<<"Enter point about which to be scaled: ";
            cin>>x>>y;
            drawPolygon();
            drawScaledPolygon(factor_x,factor_y, x, y);
		}
        else if(transformation == 4){
            double angle;
            cout<<"Enter the angle with X-axis and Y-intercept of the mirror: ";
            cin>>angle >> factor_y;
            angle_radians = angle * 3.1416/180;
            drawPolygon();
            drawReflectedPolygon(angle_radians,factor_y);
        }
        else if(transformation == 5){
            cout<<"Enter the shearing factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            drawShearedPolygon(factor_x, factor_y);
        }
		else if(transformation){
			cout<<"Invalid option"<<endl;
		}
        else;
    }
   
    glFlush(); 
}

void y_axis(){
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
		glVertex2d(0, -480.0);
		glVertex2d(0, 480.0);
	glEnd();
	// glFlush();
}

void x_axis(){
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
		glVertex2d(-640.0, 0);
		glVertex2d(640.0, 0);
	glEnd();
	// glFlush();
}

void setEdgeCount(int option){
	if(option == 0){
		cout<<"Invalid"<<endl;
	}
	else if(option == 1 || option == 2){
		edge_count = 2;
	}
	else{
		edge_count = option;
	}
}

vector<vector<double>> matrix_multiplication(double points[][3], double matrix[][3], int r1, int c1, int r2, int c2){
    
    vector<vector<double>> ans(3);

    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            ans[i].push_back(0);
        }
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            for(int k=0;k<r2;k++){
                ans[i][j] += (points[i][k] * matrix[k][j]); 
            }
        }
    }
    return ans;
}

double round(double d){
    return floor(d + 0.5);
}

void drawPolygon(){
    y_axis();
    x_axis();
    glColor3f(1.0,1.0,1.0);
    if(edge_count==2)
    	glBegin(GL_LINES);
    else
    	glBegin(GL_POLYGON);
    
    for (int i = 0; i < edge_count; i++){
        glVertex2d(X_points[i], Y_points[i]);
    }
    glEnd();
    glFlush();
}

void drawTranslatedPolygon(double x, double y){
    double translate_matrix[2][1] = {{x}, {y}};
    for(int i=0;i<edge_count;i++){
        double new_x = X_points[i] + translate_matrix[0][0];
        double new_y = Y_points[i] + translate_matrix[1][0];
        transforms.push_back(pair<double, double>(new_x, new_y));
    }
    glFlush();
    glColor3f(0.0, 1.0, 0.0);
    if (edge_count == 2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for(pair<double, double> p: transforms){
        glVertex2d(p.first, p.second);
    }
    glEnd();
    glFlush();
    transforms.clear();
}

void drawRotatedPolygon(double angle_radians, double x, double y){
    double rotate_matrix[2][3] = {{cos(angle_radians), sin(angle_radians)}, {-sin(angle_radians), cos(angle_radians)}};
    double adjust_matrix[1][2] = {-x, -y};
    double reset_matrix[1][2] = {x, y};
    for(int i=0;i<edge_count;i++){
        double points[1][3] = {{X_points[i]+adjust_matrix[0][0], Y_points[i]+adjust_matrix[0][1]}};
        vector<vector<double>> ans = matrix_multiplication(points, rotate_matrix, 1, 2, 2, 2);
        transforms.push_back(pair<double, double>(ans[0][0]+reset_matrix[0][0], ans[0][1]+reset_matrix[0][1]));
    }

    glFlush();
    glColor3f(0.0, 1.0, 0.0);
    if (edge_count == 2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for(pair<double, double> p: transforms){
        glVertex2d(round(p.first), round(p.second));
    }
    glEnd();
    glFlush();
    transforms.clear();
}

void drawScaledPolygon(double x, double y, double xf, double yf){
    double scale_matrix[2][3] = {{x, 0}, {0, y}};
    for(int i=0;i<edge_count;i++){
        double points[1][3] = {{X_points[i], Y_points[i]}};
        vector<vector<double>> ans = matrix_multiplication(points, scale_matrix, 1, 2, 2, 2);
        double x_impact = xf*(1-x);
        double y_impact = yf*(1-y);
        transforms.push_back(pair<double, double>(ans[0][0]+x_impact, ans[0][1]+y_impact));
    }

    glFlush();
    glColor3f(0.0, 1.0, 0.0);
    if (edge_count == 2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for(pair<double, double> p: transforms){
        glVertex2d(round(p.first), round(p.second));
    }
    glEnd();
    glFlush();
    transforms.clear();
}

void drawReflectedPolygon(double angle_radians, double intercept){
    double reflect_matrix[3][3] = {{cos(2*angle_radians), sin(2*angle_radians), intercept*sin(2*angle_radians)},  
                                     {sin(2*angle_radians), -cos(2*angle_radians), -intercept*cos(2*angle_radians)+1}, 
                                     {0, 0, 1}};
    for(int i=0;i<edge_count;i++){
        double points[1][3] = {{X_points[i], Y_points[i], 0}};
        vector<vector<double>> ans = matrix_multiplication(points, reflect_matrix, 1, 3, 3, 3);
        transforms.push_back(pair<double, double>(ans[0][0], ans[0][1]));
    }

    glFlush();
    glColor3f(0.0, 1.0, 0.0);
    if (edge_count == 2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for(pair<double, double> p: transforms){
        glVertex2d(round(p.first), round(p.second));
    }
    glEnd();
    glFlush();
    transforms.clear();
}

void drawShearedPolygon(double shx, double shy){
    double reflect_matrix[3][3] = {{1, shy, 0},  
                                   {shx, 1, 0}, 
                                     {0, 0, 1}};
    for(int i=0;i<edge_count;i++){
        double points[1][3] = {{X_points[i], Y_points[i], 0}};
        vector<vector<double>> ans = matrix_multiplication(points, reflect_matrix, 1, 3, 3, 3);
        transforms.push_back(pair<double, double>(ans[0][0], ans[0][1]));
    }

    glFlush();
    glColor3f(0.0, 1.0, 0.0);
    if (edge_count == 2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for(pair<double, double> p: transforms){
        glVertex2d(round(p.first), round(p.second));
    }
    glEnd();
    glFlush();
    transforms.clear();
}