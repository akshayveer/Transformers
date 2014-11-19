#include "gl_framework.hpp"

namespace cs475{
	int win_width;
	int win_height;
	float hand_angle=0;
	bool space_press=false;
	float right_knee_angle=0;
	float left_knee_angle=0;
	bool toCar=false;
	bool toTransformer=false;
	float leg_shift=0;
	float step=5;  // 0.09
	float left_hip_angle=0;
	float right_hip_angle=0;
	float torso_angle=0;
	float panel_angle=0;
	float right_shoulder_z=0;
	float panel_shift=0;
	float shoulder_shift_z=0;
	float torso_shift_down=0;
	float left_shoulder_z=0;
	bool first=false;
	bool second=false;
	float left_shoulder_x=0;
	float right_shoulder_x=0;
	float up=0;
	float value=0;
	float left_elbow_angle=0;
	float right_elbow_angle=0;
	float close_leg=0;

	float x=0.0f,y=0,z=0.0f;
	float lx=0.0f,ly=0.0f,lz=0.0f;

	float cam_angle;
	float cam1_pos[9]={0,10,20,0,10,19,0,1,0};
	float cam2_pos[9]={0,2,1,0,2,0,0,1,0};
	float cam3_pos[9]={0.35/2,2,-2,0.35/2,2,0,0,1,0};
	float current_cam_pos[9];
	int cam_num=1;

	float forward=0;
	float tyre_angle=0;
	float direction=1;

	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat lightDiff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};

	GLfloat lightPos1[] = {1.0f, 10.0f, 10.0f, 0.0f};
	GLfloat lightPos2[] = {1.0f, 10.0f, -10.0f, 0.0f};

	GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat mat_shininess[] = {128.0};

	GLfloat spot_light_diffuse[]={0.4, 0.4, 0.4, 1.0};
	GLfloat spot_light_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat spot_light_direction[]={0.0, -1.0, 0.0};

	GLfloat spot_light_position2[]={1-0.732051,1+0.1,-1};
	GLfloat spot_light_position1[]={0.732051,1+0.1,-1};

	float car_angle=0;
	bool light1=true;
	bool light2=true;
	bool spot_light1=true;
	bool spot_light2=true;

void initGL(void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthRange(-100,100);
	copy(cam1_pos,current_cam_pos);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glLightfv(GL_LIGHT2, GL_SPECULAR, spot_light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, spot_light_position1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_light_direction);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 5.0);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	

	glLightfv(GL_LIGHT3, GL_SPECULAR, spot_light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, spot_light_position2);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_light_direction);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 5.0);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0);
	


}

void mulMatrix(GLfloat* matrix){

	for(int k=0;k<2;k++){
		float temp1[4]={0,0,0,0},temp2[4]={0,0,0,0};
		for(int j=0;j<4;j++){
			for(int i=0;i<4;i++){
				if(i!=3){
					temp1[j]+=cam3_pos[i+k*3]*matrix[4*i+j];
					temp2[j]+=cam2_pos[i+k*3]*matrix[4*i+j];
				}
				else{
					temp1[j]+=matrix[4*i+j];
					temp2[j]+=matrix[4*i+j];
				}
			}
		}
		for(int i=0;i<3;i++){
			cam3_pos[i+k*3]=temp1[i]/temp1[3];
			cam2_pos[i+k*3]=temp2[i]/temp2[3];
		}
	}

}

bool gluInvertMatrix(GLfloat* m, GLfloat* invOut){
	double inv[16], det;
	int i;

	inv[0] = m[5]  * m[10] * m[15] - 
	m[5]  * m[11] * m[14] - 
	m[9]  * m[6]  * m[15] + 
	m[9]  * m[7]  * m[14] +
	m[13] * m[6]  * m[11] - 
	m[13] * m[7]  * m[10];

	inv[4] = -m[4]  * m[10] * m[15] + 
	m[4]  * m[11] * m[14] + 
	m[8]  * m[6]  * m[15] - 
	m[8]  * m[7]  * m[14] - 
	m[12] * m[6]  * m[11] + 
	m[12] * m[7]  * m[10];

	inv[8] = m[4]  * m[9] * m[15] - 
	m[4]  * m[11] * m[13] - 
	m[8]  * m[5] * m[15] + 
	m[8]  * m[7] * m[13] + 
	m[12] * m[5] * m[11] - 
	m[12] * m[7] * m[9];

	inv[12] = -m[4]  * m[9] * m[14] + 
	m[4]  * m[10] * m[13] +
	m[8]  * m[5] * m[14] - 
	m[8]  * m[6] * m[13] - 
	m[12] * m[5] * m[10] + 
	m[12] * m[6] * m[9];

	inv[1] = -m[1]  * m[10] * m[15] + 
	m[1]  * m[11] * m[14] + 
	m[9]  * m[2] * m[15] - 
	m[9]  * m[3] * m[14] - 
	m[13] * m[2] * m[11] + 
	m[13] * m[3] * m[10];

	inv[5] = m[0]  * m[10] * m[15] - 
	m[0]  * m[11] * m[14] - 
	m[8]  * m[2] * m[15] + 
	m[8]  * m[3] * m[14] + 
	m[12] * m[2] * m[11] - 
	m[12] * m[3] * m[10];

	inv[9] = -m[0]  * m[9] * m[15] + 
	m[0]  * m[11] * m[13] + 
	m[8]  * m[1] * m[15] - 
	m[8]  * m[3] * m[13] - 
	m[12] * m[1] * m[11] + 
	m[12] * m[3] * m[9];

	inv[13] = m[0]  * m[9] * m[14] - 
	m[0]  * m[10] * m[13] - 
	m[8]  * m[1] * m[14] + 
	m[8]  * m[2] * m[13] + 
	m[12] * m[1] * m[10] - 
	m[12] * m[2] * m[9];

	inv[2] = m[1]  * m[6] * m[15] - 
	m[1]  * m[7] * m[14] - 
	m[5]  * m[2] * m[15] + 
	m[5]  * m[3] * m[14] + 
	m[13] * m[2] * m[7] - 
	m[13] * m[3] * m[6];

	inv[6] = -m[0]  * m[6] * m[15] + 
	m[0]  * m[7] * m[14] + 
	m[4]  * m[2] * m[15] - 
	m[4]  * m[3] * m[14] - 
	m[12] * m[2] * m[7] + 
	m[12] * m[3] * m[6];

	inv[10] = m[0]  * m[5] * m[15] - 
	m[0]  * m[7] * m[13] - 
	m[4]  * m[1] * m[15] + 
	m[4]  * m[3] * m[13] + 
	m[12] * m[1] * m[7] - 
	m[12] * m[3] * m[5];

	inv[14] = -m[0]  * m[5] * m[14] + 
	m[0]  * m[6] * m[13] + 
	m[4]  * m[1] * m[14] - 
	m[4]  * m[2] * m[13] - 
	m[12] * m[1] * m[6] + 
	m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] + 
	m[1] * m[7] * m[10] + 
	m[5] * m[2] * m[11] - 
	m[5] * m[3] * m[10] - 
	m[9] * m[2] * m[7] + 
	m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - 
	m[0] * m[7] * m[10] - 
	m[4] * m[2] * m[11] + 
	m[4] * m[3] * m[10] + 
	m[8] * m[2] * m[7] - 
	m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] + 
	m[0] * m[7] * m[9] + 
	m[4] * m[1] * m[11] - 
	m[4] * m[3] * m[9] - 
	m[8] * m[1] * m[7] + 
	m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] - 
	m[0] * m[6] * m[9] - 
	m[4] * m[1] * m[10] + 
	m[4] * m[2] * m[9] + 
	m[8] * m[1] * m[6] - 
	m[8] * m[2] * m[5];
	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}

void load_default_cam(){
	if(cam_num!=1){
		glLoadIdentity();
		gluLookAt(cs475::current_cam_pos[0],cs475::current_cam_pos[1],cs475::current_cam_pos[2],
			cs475::current_cam_pos[3],cs475::current_cam_pos[4],cs475::current_cam_pos[5],
			cs475::current_cam_pos[6],cs475::current_cam_pos[7],cs475::current_cam_pos[8]);

		GLfloat matrix[16]; 
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		GLfloat out[16];

		gluInvertMatrix(matrix,out);

		mulMatrix(out);

	}

	switch(cam_num){
		case 1: std::copy(cam1_pos,cam1_pos+9,current_cam_pos); break;
		case 2: std::copy(cam2_pos,cam2_pos+9,current_cam_pos); break;
		case 3: std::copy(cam3_pos,cam3_pos+9,current_cam_pos); break;
	}

}

void copy(float* src,float*dst){
	for(int i=0;i<9;i++) dst[i]=src[i];
}



void error_callback(int error, const char* description)
{
	std::cerr<<description<<std::endl;
}

//!GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	if  ( height == 0 ) height = 1;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glViewport( 0, 0, width, height);

	double aspect;
	if (width > height){
		aspect = (double)width/(double)height;
		gluPerspective(50, aspect, 1, 5000);
	}

	else{
		aspect = (double)height/(double)width;
		gluPerspective(50, aspect, 1, 5000);
	}

	win_width = width;
	win_height = height;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0,0,-1, 0.0f, 1.0f, 0.0f);
}



//!GLFW keyboard callback

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
// press=false;
//!Close the window if the ESC key was pressed
	if (key == GLFW_KEY_ESCAPE )
		glfwSetWindowShouldClose(window, GL_TRUE);

//  Right arrow , left arrow rotates transformer along y-axis 5 degrees anti-clockwise and 
// clockwise respectively
	if(key== GLFW_KEY_RIGHT && action==GLFW_RELEASE){
		tyre_angle=0;
	}

	if(key == GLFW_KEY_LEFT && action==GLFW_RELEASE ){
		tyre_angle=0;

	}
	if(key== GLFW_KEY_RIGHT ){
		forward+=direction*0.01;
		car_angle-=0.5;
		if(tyre_angle>-3) tyre_angle-=0.5/2;

	} 
	if(key == GLFW_KEY_LEFT ){
		forward+=direction*0.01;
		car_angle+=0.5;
		if(tyre_angle<3)tyre_angle+=0.5/2;

	}

//  up arrow , down arrow rotates transformer along x-axis 5 degrees clockwise and 
// anti-clockwise respectively

	if(key==GLFW_KEY_UP ){
		direction=1;
		forward+=0.1;
	} 
	else if(key==GLFW_KEY_DOWN ){
		direction=-1;
		forward-=0.1;
	} 

// toggle the direction of rotation
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) space_press=!space_press;

// rotate left hip anti-clockwise when pressed h and space is not pressed and 
// rotate left hip clockwise when pressed h and space is pressed constraining to degree of 
// rotation to 180
	if(key==GLFW_KEY_H  && mods!=GLFW_MOD_SHIFT){
		if(!space_press && left_hip_angle<=90-step) left_hip_angle+=step;
		else if(space_press && left_hip_angle>=step-90) left_hip_angle-=step;
	}

// rotate left leg anti-clockwise when pressed k and space is not pressed and 
// rotate left leg clockwise when pressed k and space is pressed constraining to degree of 
// rotation to 90
	if(key==GLFW_KEY_K  && mods!=GLFW_MOD_SHIFT){
		if(!space_press && left_knee_angle<=90-step) left_knee_angle+=step;
		else if(space_press && left_knee_angle>=step) left_knee_angle-=step;
	}

// rotate right hip anti-clockwise when pressed shift+h and space is not pressed and 
// rotate right hip clockwise when pressed shift+h and space is pressed constraining to degree of 
// rotation to 180
	if(key==GLFW_KEY_H && mods == GLFW_MOD_SHIFT ){
		if(!space_press && right_hip_angle<=90-step) right_hip_angle+=step;
		else if(space_press && right_hip_angle>=step-90) right_hip_angle-=step;
	}

// rotate right leg anti-clockwise when pressed shift+k and space is not pressed and 
// rotate right leg clockwise when pressed shift+k and space is pressed constraining to degree of 
// rotation to 90
	if(key==GLFW_KEY_K && mods == GLFW_MOD_SHIFT ){
		if(!space_press && right_knee_angle<=90-step) right_knee_angle+=step;
		else if(space_press && right_knee_angle>=step) right_knee_angle-=step;
	}

// rotate torso anti-clockwise when pressed c and space is not pressed and
// rotate torso clockwise when pressed c and space is pressed constraining to degree of 
// rotation to 180
	if(key==GLFW_KEY_Z ){
		if(!space_press && torso_angle<=90-step) torso_angle+=step;
		else if(space_press && torso_angle>=step-90) torso_angle-=step;
	}

	if(key==GLFW_KEY_C &&  action == GLFW_PRESS){

		glLoadIdentity();
		gluLookAt(cs475::current_cam_pos[0],cs475::current_cam_pos[1],cs475::current_cam_pos[2],
			cs475::current_cam_pos[3],cs475::current_cam_pos[4],cs475::current_cam_pos[5],
			cs475::current_cam_pos[6],cs475::current_cam_pos[7],cs475::current_cam_pos[8]);

		GLfloat matrix[16]; 
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		GLfloat out[16];

		gluInvertMatrix(matrix,out);

		mulMatrix(out);
		switch(cam_num){
			case 1: copy(cam2_pos,current_cam_pos); cam_num+=1;break;
			case 2: copy(cam3_pos,current_cam_pos); cam_num+=1;break;
			case 3: copy(cam1_pos,current_cam_pos); cam_num=1;break;
		}
	}

	if(key==GLFW_KEY_9 &&  action == GLFW_PRESS){

			if(light1){
				glDisable(GL_LIGHT0);
				light1=false;
			}
			else {
				glEnable(GL_LIGHT0);
				light1=true;
			}
	}

	if(key==GLFW_KEY_0 &&  action == GLFW_PRESS){
		
			if(light2){
				glDisable(GL_LIGHT1);
				light2=false;
			}
			else{
				glEnable(GL_LIGHT1);
				light2=true;
			}
	}

	if(key==GLFW_KEY_8 &&  action == GLFW_PRESS){
		
			if(spot_light1){
				glDisable(GL_LIGHT2);
				spot_light1=false;
			}
			else {
				std::cout << "entered" << std::endl;
				glEnable(GL_LIGHT2);
				spot_light1=true;
			}
	}

	if(key==GLFW_KEY_7 &&  action == GLFW_PRESS){
		
			if(spot_light2){
				glDisable(GL_LIGHT3);
				spot_light1=false;
			}
			else{
				glEnable(GL_LIGHT3);
				spot_light1=true;
			}
	}
	

	if(key==GLFW_KEY_1) first=!first;
	if(key==GLFW_KEY_2) second=!second;



	if(key== GLFW_KEY_M ){
		if(!space_press && hand_angle<=90-step) hand_angle+=5;
		else if(space_press && hand_angle>=step)  hand_angle-=5;
	}


	if(key==GLFW_KEY_R ){
		reset();
	}



	if(key==GLFW_KEY_S  && mods==GLFW_MOD_SHIFT){
		if(first){
			if(!space_press && left_shoulder_x<=90-step) left_shoulder_x+=step;
			else if(space_press && left_shoulder_x>=step) left_shoulder_x-=step;
		}
		if(second){
			if(!space_press && right_shoulder_x<=90-step) right_shoulder_x+=step;
			else if(space_press && right_shoulder_x>=step) right_shoulder_x-=step;
		}
	}

	else if(key==GLFW_KEY_S  && mods!=GLFW_MOD_SHIFT){
		if(first){
			if(!space_press && left_shoulder_z<=90-step) left_shoulder_z+=step;
			else if(space_press && left_shoulder_z>=step) left_shoulder_z-=step;
		}
		if(second){
			if(!space_press&& right_shoulder_z<=90-step) right_shoulder_z+=step;
			else if(space_press && right_shoulder_z>=step) right_shoulder_z-=step;
		}
	}
	if(key==GLFW_KEY_E ){
		if(first){
			if(!space_press && left_elbow_angle<=90-step) left_elbow_angle+=step;
			else if(space_press && left_elbow_angle>=step) left_elbow_angle-=step;
		}
		if(second){
			if(!space_press && right_elbow_angle<=90-step) right_elbow_angle+=step;
			else if(space_press && right_elbow_angle>=step) right_elbow_angle-=step;
		}
	}





	if(key==GLFW_KEY_T ){
		step=0.09;
		if(!space_press && !toCar){
			toCar=true;
		}

		else if(space_press && !toTransformer) toTransformer=true;
	}



	if(key==GLFW_KEY_Q ){
		if(!space_press ) leg_shift+=1;
		else if(space_press) leg_shift-=1;
	}



	if(key==GLFW_KEY_U ){
		if(!space_press ) up+=0.01;
		else if(space_press) up-=0.01;
	}

}

void reset(){

	hand_angle=0;
	space_press=false;
	right_knee_angle=0;
	left_knee_angle=0;
	toCar=false;
	toTransformer=false;
	leg_shift=0;
	step=5;  // 0.09
	left_hip_angle=0;
	right_hip_angle=0;
	torso_angle=0;
	panel_angle=0;
	right_shoulder_z=0;
	panel_shift=0;
	shoulder_shift_z=0;
	torso_shift_down=0;
	left_shoulder_z=0;
	first=false;
	second=false;
	left_shoulder_x=0;
	right_shoulder_x=0;
	up=0;
	value=0;
	left_elbow_angle=0;
	right_elbow_angle=0;
	close_leg=0;
}


};
