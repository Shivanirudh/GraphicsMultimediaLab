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

    	cout<<"Choose first transformation: "<<endl;
		cout<<"1 for Translation"<<endl<<"2 for Rotation"<<endl;
		cout<<"3 for Scaling"<<endl<<"4 for Reflection"<<endl;
		cout<<"5 for shearing"<<endl<<"0 to Exit"<<endl;
		cout<<"Enter your choice: ";cin>>transformation;

        if(!transformation){
            return;
        }

		if(transformation == 1){
			cout<<"Enter the translation factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            setTranslateMatrix(factor_x,factor_y, 1);
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
            setRotateMatrix(angle_radians, x, y, 1);
		}
		else if(transformation == 3){
			cout<<"Enter the scaling factor for X and Y: ";
            cin>>factor_x >> factor_y;
            double x,y;
            cout<<"Enter point about which to be scaled: ";
            cin>>x>>y;
            drawPolygon();
            setScaleMatrix(factor_x,factor_y, x, y, 1);
		}
        else if(transformation == 4){
            double angle;
            cout<<"Enter the angle with X-axis and Y-intercept of the mirror: ";
            cin>>angle >> factor_y;
            angle_radians = angle * 3.1416/180;
            drawPolygon();
            setReflectMatrix(angle_radians,factor_y, 1);
        }
        else if(transformation == 5){
            cout<<"Enter the shearing factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            setShearMatrix(factor_x, factor_y, 1);
        }
		else if(transformation){
			cout<<"Invalid option"<<endl;
		}
        else;

        cout<<"Choose second transformation: "<<endl;
        cout<<"1 for Translation"<<endl<<"2 for Rotation"<<endl;
        cout<<"3 for Scaling"<<endl<<"4 for Reflection"<<endl;
        cout<<"5 for shearing"<<endl<<"0 to Exit"<<endl;
        cout<<"Enter your choice: ";cin>>transformation;

        if(!transformation){
            return;
        }

        if(transformation == 1){
            cout<<"Enter the translation factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            setTranslateMatrix(factor_x,factor_y, 2);
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
            setRotateMatrix(angle_radians, x, y, 2);
        }
        else if(transformation == 3){
            cout<<"Enter the scaling factor for X and Y: ";
            cin>>factor_x >> factor_y;
            double x,y;
            cout<<"Enter point about which to be scaled: ";
            cin>>x>>y;
            drawPolygon();
            setScaleMatrix(factor_x,factor_y, x, y, 2);
        }
        else if(transformation == 4){
            double angle;
            cout<<"Enter the angle with X-axis and Y-intercept of the mirror: ";
            cin>>angle >> factor_y;
            angle_radians = angle * 3.1416/180;
            drawPolygon();
            setReflectMatrix(angle_radians,factor_y, 2);
        }
        else if(transformation == 5){
            cout<<"Enter the shearing factor for X and Y: ";
            cin>>factor_x >> factor_y;
            drawPolygon();
            setShearMatrix(factor_x, factor_y, 2);
        }
        else if(transformation){
            cout<<"Invalid option"<<endl;
        }
        else;

        applyTransforms();
        drawTransfomedPolygon();
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

vector<vector<double>> matrix_multiplication(double points[][3], int pr){
    
    vector<vector<double>> final_transform(3);
    vector<vector<double>> ans(3);

    for(int i=0;i<pr;i++){
        for(int j=0;j<3;j++){
            ans[i].push_back(0);
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            final_transform[i].push_back(0);        
        }
    }
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                final_transform[i][j] += (transform1[i][k] * transform2[k][j]); 
            }
        }
    }
    for(int i=0;i<pr;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                ans[i][j] += (points[i][k] * final_transform[k][j]); 
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

void applyTransforms(){
    for(int i=0;i<edge_count;i++){
        double points[1][3] = {X_points[i], Y_points[i], 1};
        vector<vector<double>> ans = matrix_multiplication(points, 1);
        transforms.push_back(pair<double, double>(ans[0][0],ans[0][1]));
    }
}

void drawTransfomedPolygon(){

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
void setTranslateMatrix(double x, double y, int transform_number){
    if(transform_number == 1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform1[i][j] = 1;
                }
                else{
                    transform1[i][j] = 0;
                }
            }
        }
        transform1[0][2] = x;
        transform1[1][2] = y;    
    }
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform2[i][j] = 1;
                }
                else{
                    transform2[i][j] = 0;
                }
            }
        }
        transform2[0][2] = x;
        transform2[1][2] = y;
    }
}

void setRotateMatrix(double angle_radians, double x, double y, int transform_number){

    double adjust_matrix[3][3] = {{1, 0, -x}, 
                                 {0, 1, -y}, 
                                 {0, 0, 1}}; 
    double reset_matrix[3][3] = {{1, 0, x}, 
                                {0, 1, y}, 
                                {0, 0, 1}}; 
    double dummy_matrix[3][3] = {{cos(angle_radians), sin(angle_radians), 0}, 
                                {-sin(angle_radians), cos(angle_radians), 0}, 
                                {0, 0, 1}};

    double final_transform[3][3];
    if(angle_radians<0){
        dummy_matrix[0][1] *= -1;
        dummy_matrix[1][0] *= -1;
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            final_transform[i][j] = 0;        
        }
    }
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                final_transform[i][j] += (reset_matrix[i][k] * dummy_matrix[k][j]); 
            }
        }
    }


    if(transform_number == 1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                transform1[i][j] = 0;        
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    transform1[i][j] += (final_transform[i][k] * adjust_matrix[k][j]); 
                }
            }
        }
    }
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                transform2[i][j] = 0;        
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    transform2[i][j] += (final_transform[i][k] * adjust_matrix[k][j]); 
                }
            }
        }
    }
}

void setScaleMatrix(double x, double y, double xf, double yf, int transform_number){
    if(transform_number == 1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform1[i][j] = 1;
                }
                else{
                    transform1[i][j] = 0;
                }
            }
        }
        transform1[0][0] = x;
        transform1[1][1] = y;  
    }
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform2[i][j] = 1;
                }
                else{
                    transform2[i][j] = 0;
                }
            }
        }
        transform2[0][0] = x;
        transform2[1][1] = y;  
    }
}

void setReflectMatrix(double angle_radians, double intercept, int transform_number){
    if(transform_number == 1){
        transform1[0][0] = cos(2*angle_radians);
        transform1[0][1] = sin(2*angle_radians);
        transform1[0][2] = intercept*sin(2*angle_radians);

        transform1[1][0] = sin(2*angle_radians);
        transform1[1][1] = -cos(2*angle_radians);
        transform1[1][2] = intercept*cos(2*angle_radians)+1;

        transform1[2][0] = 0;
        transform1[2][1] = 0;
        transform1[2][2] = 1;
    }
    else{
        transform2[0][0] = cos(2*angle_radians);
        transform2[0][1] = sin(2*angle_radians);
        transform2[0][2] = intercept*sin(2*angle_radians);

        transform2[1][0] = sin(2*angle_radians);
        transform2[1][1] = -cos(2*angle_radians);
        transform2[1][2] = intercept*cos(2*angle_radians)+1;

        transform2[2][0] = 0;
        transform2[2][1] = 0;
        transform2[2][2] = 1;  
    }
}

void setShearMatrix(double shx, double shy, int transform_number){
    if(transform_number == 1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform1[i][j] = 1;
                }
                else{
                    transform1[i][j] = 0;
                }
            }
        }
        transform1[0][1] = shy;
        transform1[1][0] = shx;
    }
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i == j){
                    transform2[i][j] = 1;
                }
                else{
                    transform2[i][j] = 0;
                }
            }
        }
        transform2[0][1] = shy;
        transform2[1][0] = shx;
    }
}