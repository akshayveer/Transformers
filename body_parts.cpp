#include "body_parts.hpp"

float pelvis_dim[3]={0.35,0.15,0.15};
float thigh_space=0.1;
float thigh_dim[3]={(pelvis_dim[0]-thigh_space)/2,0.2,0.1};
float leg_dim[3]={pelvis_dim[0]/2,0*thigh_dim[2]+thigh_dim[1]+pelvis_dim[1],pelvis_dim[2]};
float thigh_leg_space=(leg_dim[0]-thigh_dim[0])/2;
float torso_gap=0.01;
float torso_dim[3]={pelvis_dim[0]-torso_gap,0.3,pelvis_dim[2]};
float prism_height=0.2;
float prism_angle=75;
float hand_gap=0.08;
float hand_length=0.2;
float hand_dim[3]={0.01,0.09,0.01};


void struct_cube(void)
{
	glNewList(cube,GL_COMPILE); 
	

	// front face
	glColor3f( 1.0, 0.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	// right face
	glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(1,0,0);
	glVertex3f(1,0,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,0);
	glEnd();

	// back face
	glColor3f( 0.0, 0.0, 1.0); 
	glBegin(GL_POLYGON);
	glVertex3f(1,0,-1);
	glVertex3f(0,0,-1);
	glVertex3f(0,1,-1);
	glVertex3f(1,1,-1);
	
	glEnd();

	// left face
	glColor3f( 1.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1,-1);
	glEnd();

	// top cube
	glColor3f( 1.0, 0.0, 1.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1,1,-1);
	glVertex3f(0,1,-1);
	glEnd();

	// bottom cube
	glColor3f( 0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(0,0,-1);
	glVertex3f(1,0,-1);
	glVertex3f(1,0,0);
	glEnd();

	glEndList();
}


void struct_pelvis(void){
	glNewList(pelvis,GL_COMPILE);
	glPushMatrix();
	glScalef(pelvis_dim[0],pelvis_dim[1],pelvis_dim[2]);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_thigh(void){
	glNewList(thigh,GL_COMPILE);
	glPushMatrix();
	glTranslatef(0,-thigh_dim[1],0);
	glScalef(thigh_dim[0],thigh_dim[1],thigh_dim[2]);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_leg(void){
	glNewList(leg,GL_COMPILE);
	glPushMatrix();
	glTranslatef(-thigh_leg_space,-thigh_dim[1]-leg_dim[1],0);
	glScalef(leg_dim[0],leg_dim[1],leg_dim[2]);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_body(void){
	glNewList(torso,GL_COMPILE);  // displacement=0.05
	glPushMatrix();
	glTranslatef(torso_gap/2,pelvis_dim[1],0);
	glScalef(torso_dim[0],torso_dim[1],torso_dim[2]);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_hand(void){
	glNewList(hand,GL_COMPILE);
	glPushMatrix();
	glTranslatef(-0.15,0.15,0);
	glScalef(0.15,0.35,0.05);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}


void struct_wheel(void){
	glNewList(wheel,GL_COMPILE);
	glPushMatrix();
	glColor3f(0.1,0.1,0.1);
    gluCylinder(quadratic,1,1,0.1f,32,32);
    glTranslatef(0,0,0.1);
    gluDisk(quadratic,0,1,32,32);
    glPopMatrix();
    glColor3f(1,0,0);
	glEndList();
}



void struct_left_prism(void){
	glNewList(left_prism,GL_COMPILE);
	glPushMatrix();

	
	

	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1,0,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex3f(1,0,-1);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(1,1,-1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1,1);
	glVertex3f(0,0,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1,0,-1);
	glVertex3f(1,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1,0,1);
	glVertex3f(0,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1,1,-1);
	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1);
	glEnd();
	
	glPopMatrix();
	glEndList();
}
void struct_right_prism(void){
	glNewList(right_prism,GL_COMPILE);
	glPushMatrix();

	
	// glScalef(pelvis_dim[0]/2,torso_dim[1],0.2);

	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(1,1,0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(0,0,-1);
	glVertex3f(0,1,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
	glVertex3f(0,0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1,0,1);
	glVertex3f(0,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(0,1,-1);
	glEnd();
	
	glPopMatrix();
	glEndList();
}
