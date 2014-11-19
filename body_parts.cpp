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
float panel_gap=0.08;
float hand_length=0.2;
float hand_dim[3]={0.01,0.09,0.01};
float foot_height=0.1;
float foot_length=0.2;
float texture_shift=0.01;
float window_shift=0.05;

GLuint LoadTexture(const char * pic)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3

	unsigned char * data;
	FILE * file = fopen(pic,"rb");
	fread(header, 1, 54, file);
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	data = new unsigned char [imageSize];
	fread(data,1,imageSize,file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(data);
	return textureID;
}

void struct_front_left_window(void){
	glNewList(front_left_window,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLuint myTex  = LoadTexture("./images/BG.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
			glPushMatrix();
				glTranslatef(window_shift,0,0);
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 0);	glVertex3f(0+window_shift,1+texture_shift,0-window_shift);
					glTexCoord2f(1,0); glVertex3f(1-window_shift,1+texture_shift,0-window_shift);
					glTexCoord2f(1,1);	glVertex3f(1-window_shift,1+texture_shift,-1+window_shift);
					glTexCoord2f(0,1);glVertex3f(1/tan(prism_angle*M_PI/180)+window_shift,1+texture_shift,-1+window_shift);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void struct_front_right_window(void){
	glNewList(front_right_window,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLuint myTex  = LoadTexture("./images/BG.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
			glPushMatrix();
				glTranslatef(-window_shift,0,0);
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 0);	glVertex3f(0+window_shift,1+texture_shift,0-window_shift);
					glTexCoord2f(1,0); glVertex3f(1-window_shift,1+texture_shift,0-window_shift);
					glTexCoord2f(1,1);	glVertex3f(1-1/tan(prism_angle*M_PI/180)-window_shift,1+texture_shift,-1+window_shift);
					glTexCoord2f(0,1);glVertex3f(0+window_shift,1+texture_shift,-1+window_shift);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void struct_left_bonnet(void){
	glNewList(left_bonnet,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLuint myTex  = LoadTexture("./images/front.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
			glPushMatrix();
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 0);	glVertex3f(0,1+0.01,0);
					glTexCoord2f(1,0); glVertex3f(1,1+0.01,0);
					glTexCoord2f(1,1);	glVertex3f(1,1+0.01,-1);
					glTexCoord2f(0,1);glVertex3f(1/tan(prism_angle*M_PI/180),1+0.01,-1);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}
void struct_right_bonnet(void){
	glNewList(right_bonnet,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			GLuint myTex  = LoadTexture("./images/front.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
			glPushMatrix();
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 0);	glVertex3f(0,1+0.01,0);
					glTexCoord2f(1,0); glVertex3f(1,1+0.01,0);
					glTexCoord2f(1,1);	glVertex3f(1-1/tan(prism_angle*M_PI/180),1+0.01,-1);
					glTexCoord2f(0,1);glVertex3f(0,1+0.01,-1);
				glEnd();

			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void struct_left_hood(void){
	GLuint myTex;
	glNewList(left_hood,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			myTex  = LoadTexture("./images/left.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
		        glBegin(GL_QUADS);
			        glTexCoord2f(1,1);	glVertex3f(1,0,-1-texture_shift);
					glTexCoord2f(0,1); 	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1-texture_shift);
					glTexCoord2f(0,0);	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1-texture_shift);
					glTexCoord2f(1,0);  glVertex3f(1,1,-1-texture_shift);
				glEnd();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			myTex  = LoadTexture("./images/test.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
				glBegin(GL_QUADS);
					glTexCoord2f(1,1); glVertex3f(1/tan(prism_angle*M_PI/180)-texture_shift,0,-1-texture_shift);
					glTexCoord2f(0,1); glVertex3f(-texture_shift,0,-texture_shift);
					glTexCoord2f(0,0); glVertex3f(-texture_shift,1,-texture_shift);
					glTexCoord2f(1,0); glVertex3f(1/tan(prism_angle*M_PI/180)-texture_shift,1,-1-texture_shift);
				glEnd();
		glDisable(GL_TEXTURE_2D);	
		
	glEndList();
}

void struct_right_hood(void){
	glNewList(right_hood,GL_COMPILE);
		GLuint myTex;
		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			myTex  = LoadTexture("./images/right.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
		        glBegin(GL_QUADS);
			        glTexCoord2f(1,1);	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1-texture_shift);
					glTexCoord2f(0,1); 	glVertex3f(0,0,-1-texture_shift);
					glTexCoord2f(0,0);	glVertex3f(0,1,-1-texture_shift);
					glTexCoord2f(1,0);  glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1-texture_shift);
				glEnd();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			myTex  = LoadTexture("./images/test.bmp");
			glBindTexture(GL_TEXTURE_2D, myTex);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex3f(1+texture_shift,0,0-texture_shift);
					glTexCoord2f(1,1); glVertex3f(1-1/tan(prism_angle*M_PI/180)+texture_shift,0,-1-texture_shift);
					glTexCoord2f(1,0); glVertex3f(1-1/tan(prism_angle*M_PI/180)+texture_shift,1,-1-texture_shift);
					glTexCoord2f(0,0); glVertex3f(1+texture_shift,1,0-texture_shift);
				glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}


void struct_cube(void)
{
	glNewList(cube,GL_COMPILE); 
	

	// front face
	// glColor3f( 1.0, 0.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	// right face
	// glColor3f(0.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(1,0,0);
	glVertex3f(1,0,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,0);
	glEnd();

	// back face
	// glColor3f( 0.0, 0.0, 1.0); 
	glBegin(GL_POLYGON);
	glVertex3f(1,0,-1);
	glVertex3f(0,0,-1);
	glVertex3f(0,1,-1);
	glVertex3f(1,1,-1);
	
	glEnd();

	// left face
	// glColor3f( 1.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1,-1);
	glEnd();

	// top cube
	// glColor3f( 1.0, 0.0, 1.0); 
	glBegin(GL_POLYGON);
	glVertex3f(0,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1,1,-1);
	glVertex3f(0,1,-1);
	glEnd();

	// bottom cube
	// glColor3f( 0.0, 1.0, 0.0); 
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

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		GLuint myTex  = LoadTexture("./images/4.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glBegin(GL_QUADS);
	        glTexCoord2f(0,0);	glVertex3f(0,0,0+texture_shift);
			glTexCoord2f(1,0); 	glVertex3f(1,0,0+texture_shift);
			glTexCoord2f(1,1);	glVertex3f(1,1,0+texture_shift);
			glTexCoord2f(0,1);  glVertex3f(0,1,0+texture_shift);
		glEnd();
	glDisable(GL_TEXTURE_2D);

	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_thigh(void){
	glNewList(thigh,GL_COMPILE);
	glPushMatrix();
	// glColor3f(1,0,0);
	glTranslatef(0,-thigh_dim[1],0);
	glScalef(thigh_dim[0],thigh_dim[1],thigh_dim[2]);
	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		GLuint myTex  = LoadTexture("./images/leg.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glBegin(GL_QUADS);
	        glTexCoord2f(0,0);	glVertex3f(0,0,0+texture_shift);
			glTexCoord2f(1,0); 	glVertex3f(1,0,0+texture_shift);
			glTexCoord2f(1,1);	glVertex3f(1,1,0+texture_shift);
			glTexCoord2f(0,1);  glVertex3f(0,1,0+texture_shift);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(1+texture_shift,0,0);
			glTexCoord2f(1,0); glVertex3f(1+texture_shift,0,-1);
			glTexCoord2f(1,1); glVertex3f(1+texture_shift,1,-1);
			glTexCoord2f(0,1); glVertex3f(1+texture_shift,1,0);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(1,0,-1-texture_shift);
			glTexCoord2f(1,0); glVertex3f(0,0,-1-texture_shift);
			glTexCoord2f(1,1); glVertex3f(0,1,-1-texture_shift);
			glTexCoord2f(0,1); glVertex3f(1,1,-1-texture_shift);	
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(0-texture_shift,0,-1);
			glTexCoord2f(1,0); glVertex3f(0-texture_shift,0,0);
			glTexCoord2f(1,1); glVertex3f(0-texture_shift,1,0);
			glTexCoord2f(0,1); glVertex3f(0-texture_shift,1,-1);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_leg(void){
	glNewList(leg,GL_COMPILE);
	glPushMatrix();
	glTranslatef(-thigh_leg_space,-thigh_dim[1]-leg_dim[1],0);
	glScalef(leg_dim[0],leg_dim[1],leg_dim[2]);

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		GLuint myTex  = LoadTexture("./images/hood2.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);

		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(1+texture_shift,0,0);
			glTexCoord2f(1,0); glVertex3f(1+texture_shift,0,-1);
			glTexCoord2f(1,1); glVertex3f(1+texture_shift,1,-1);
			glTexCoord2f(0,1); glVertex3f(1+texture_shift,1,0);
		glEnd();

		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(0-texture_shift,0,-1);
			glTexCoord2f(1,0); glVertex3f(0-texture_shift,0,0);
			glTexCoord2f(1,1); glVertex3f(0-texture_shift,1,0);
			glTexCoord2f(0,1); glVertex3f(0-texture_shift,1,-1);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0,0,1);
	glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_body(void){
	GLuint myTex;
	glNewList(torso,GL_COMPILE);  // displacement=0.05
	glPushMatrix();
	// glColor3f(0,0.5,0.1);
	glTranslatef(torso_gap/2,pelvis_dim[1],0);
	glScalef(torso_dim[0],torso_dim[1],torso_dim[2]);
	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		myTex  = LoadTexture("./images/hood2.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glPushMatrix();
	        glBegin(GL_QUADS);
		        glTexCoord2f(0,0);	glVertex3f(0-texture_shift,0,-1);
				glTexCoord2f(1,0); 	glVertex3f(0-texture_shift,0,0);
				glTexCoord2f(1,1);	glVertex3f(0-texture_shift,1,0);
				glTexCoord2f(0,1);  glVertex3f(0-texture_shift,1,-1);
			glEnd();
			glBegin(GL_QUADS);
		        glTexCoord2f(0,0);	glVertex3f(1+texture_shift,0,0);
				glTexCoord2f(1,0); 	glVertex3f(1+texture_shift,0,-1);
				glTexCoord2f(1,1);	glVertex3f(1+texture_shift,1,-1);
				glTexCoord2f(0,1);  glVertex3f(1+texture_shift,1,0);
			glEnd();
			glBegin(GL_QUADS);
		        glTexCoord2f(0,0);	glVertex3f(0,1+texture_shift,0);
				glTexCoord2f(1,0); 	glVertex3f(1,1+texture_shift,0);
				glTexCoord2f(1,1);	glVertex3f(1,1+texture_shift,-1);
				glTexCoord2f(0,1);  glVertex3f(0,1+texture_shift,-1);
			glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		myTex  = LoadTexture("./images/1.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glBegin(GL_QUADS);
	        glTexCoord2f(0,0);	glVertex3f(0,0,0+texture_shift);
			glTexCoord2f(1,0); 	glVertex3f(1,0,0+texture_shift);
			glTexCoord2f(1,1);	glVertex3f(1,1,0+texture_shift);
			glTexCoord2f(0,1);  glVertex3f(0,1,0+texture_shift);
		glEnd();
	glDisable(GL_TEXTURE_2D);

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

    gluCylinder(quadratic,1,1,0.1f,32,32);
    glPushMatrix();
    	glRotatef(180,0,1,0);
    	gluDisk(quadratic,0,1,32,32);
    glPopMatrix();
    glTranslatef(0,0,0.1);
    gluDisk(quadratic,0,1,32,32);

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		GLuint myTex  = LoadTexture("./images/wheel.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glPushMatrix();
			glTranslatef(0,0,texture_shift);
	        glBegin(GL_QUADS);
		        glTexCoord2f(0, 0);	glVertex3f(-1/sqrt(2),-1/sqrt(2),0);
				glTexCoord2f(1,0); glVertex3f(1/sqrt(2),-1/sqrt(2),0);
				glTexCoord2f(1,1);	glVertex3f(1/sqrt(2),1/sqrt(2),0);
				glTexCoord2f(0,1);glVertex3f(-1/sqrt(2),1/sqrt(2),0);
			glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    // glColor3f(1,0,0);
	glEndList();
}



void struct_left_prism(void){
	glNewList(left_prism,GL_COMPILE);
	glPushMatrix();
	glBegin(GL_POLYGON);
	// glColor3f(0,0,1);
	

	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1,0,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,0);
	glEnd();
	
	glBegin(GL_POLYGON);
	// glColor3f(0,0,1);
	glVertex3f(1,0,-1);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(1,1,-1);
	glEnd();
	
	glBegin(GL_POLYGON);
	// glColor3f(1,1,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(0,1,1);
	glVertex3f(0,0,0);
	glVertex3f(1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1,0,-1);
	glVertex3f(1,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(1,0,1);
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
	glBegin(GL_POLYGON);
	// glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(1,1,0);
	glEnd();
	
	glBegin(GL_POLYGON);
	// glColor3f(0,0,1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(0,0,-1);
	glVertex3f(0,1,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glEnd();
	
	glBegin(GL_POLYGON);
	// glColor3f(1,1,0);
	glVertex3f(0,0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(0,1,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,-1);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),0,-1);
	glVertex3f(1,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	// glColor3f(1,0,1);
	glVertex3f(0,1,0);
	glVertex3f(1,1,0);
	glVertex3f(1-1/tan(prism_angle*M_PI/180),1,-1);
	glVertex3f(0,1,-1);
	glEnd();
	
	glPopMatrix();
	glEndList();
}

void struct_foot(void){
	glNewList(foot,GL_COMPILE);
	glPushMatrix();
		// glColor3f(0.1,0.1,0.1);
		glTranslatef(0,-(leg_dim[1]+thigh_dim[1]+foot_height),foot_length-leg_dim[2]);
		glScalef(leg_dim[0],foot_height,foot_length);
		glCallList(cube);
	glPopMatrix();
	glEndList();
}

void struct_head(void){
	glNewList(head,GL_COMPILE);
	glPushMatrix();
		glTranslatef((torso_dim[0]-0.15)/2,torso_dim[1]+pelvis_dim[1],0);
        glScalef(0.15,0.15,torso_dim[2]);

    glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		GLuint myTex  = LoadTexture("./images/3.bmp");
		glBindTexture(GL_TEXTURE_2D, myTex);
		glPushMatrix();
	        glBegin(GL_QUADS);
		        glTexCoord2f(0,0);	glVertex3f(0,0,0+texture_shift);
				glTexCoord2f(1,0); glVertex3f(1,0,0+texture_shift);
				glTexCoord2f(1,1);	glVertex3f(1,1,0+texture_shift);
				glTexCoord2f(0,1);glVertex3f(0,1,0+texture_shift);
			glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
		// glColor3f(0,0,0);
        glCallList(cube);
        // glColor3f(1,1,0);
	glPopMatrix();
	glEndList();
}

void struct_ground(void){
	GLuint myTex;
	glNewList(ground,GL_COMPILE);
		glPushMatrix();
		// glScalef(1000,1000,1000);
		float w=1000,h=1000;
			// glColor3f(0,1,0);	
		glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				myTex  = LoadTexture("./images/road.bmp");
				glBindTexture(GL_TEXTURE_2D, myTex);
		   	glBegin(GL_QUADS);
		    	glTexCoord2f(0, 0); glVertex3f(w,0,-w);
				glTexCoord2f(1, 0); glVertex3f(-w,0,-w);
				glTexCoord2f(1, 1); glVertex3f(-w,0,w);
				glTexCoord2f(0, 1); glVertex3f(w,0,w);
			glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
			// glScalef(1000,1000,1000);	
			glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				myTex  = LoadTexture("./images/image.bmp");
				glBindTexture(GL_TEXTURE_2D, myTex);

				
				glBegin(GL_QUADS);
					glTexCoord2f(1, 0); glVertex3f(w,0,-w);
					glTexCoord2f(1, 1); glVertex3f(w,h,-h);
					glTexCoord2f(0, 1); glVertex3f(-w,h,-w);
					glTexCoord2f(0, 0); glVertex3f(-w,0,-w);
				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex3f(w,0,-w);
					glTexCoord2f(0, 1); glVertex3f(w,0,w);
					glTexCoord2f(1, 1); glVertex3f(w,h,w);
					glTexCoord2f(1, 0); glVertex3f(w,h,-w);
				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex3f(w,0,w);
					glTexCoord2f(1, 0); glVertex3f(-w,0,w);
					glTexCoord2f(1, 1); glVertex3f(-w,h,w);
					glTexCoord2f(0, 1); glVertex3f(w,h,w);
				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex3f(-w,0,-w);
					glTexCoord2f(0, 1); glVertex3f(-w,h,-w);
					glTexCoord2f(1, 1); glVertex3f(-w,h,w);
					glTexCoord2f(1, 0); glVertex3f(-w,0,w);
				glEnd();

				// glColor3f(1,1,0);
				glBegin(GL_QUADS);
					 glTexCoord2f(1, 0); glVertex3f(w,w,-w);
					 glTexCoord2f(1, 1); glVertex3f(w,w,w);
					 glTexCoord2f(0, 1); glVertex3f(-w,w,w);
					 glTexCoord2f(0, 0); glVertex3f(-w,w,-w);
					 
				glEnd();

			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glEndList();
}
