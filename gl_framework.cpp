#include "gl_framework.hpp"

namespace cs475{
	int win_width;
	int win_height;
	float hand_angle=0;
	bool space_press=false;
	float right_knee_angle=0;
	float left_knee_angle=0;
	bool toCar=false;
	bool toTransformer=true;
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

	float transformer_position[3]={-367.761,0,854.055};
	float cam_angle=0;
	float cam2_z=30;
	float cam3_z=3;
	float cam1_pos[9]={-367.761,10,50+854.055,-367.761,10,10+854.055,0,1,0};
	float cam2_pos[9]={10*0.35/2,10,-cam2_z,10*0.35/2,10,0,0,1,0};
	float cam3_pos[9]={10*0.35/2,0,3,10*0.35/2,0,4,0,1,0};
	float current_cam_pos[9];
	int cam_num=1;

	float forward=0.0;
	float tyre_angle=0;
	bool transform=false;

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
	GLfloat spot_light_direction[]={0.0, 1.0, 0.0};

	GLfloat spot_light_position2[]={1-0.732051,1+0.1,-1};
	GLfloat spot_light_position1[]={0.732051,1+0.1,-1};

	float car_angle=0;
	bool light1=true;
	bool light2=true;
	bool spot_light1=true;
	bool spot_light2=true;

	bool record=false;
	bool playback=false;

	ofstream myfile;
  	bool vehicle_mode=false;

  	float move_foot=0;
  	float head_angle=0;

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
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_SPECULAR, spot_light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, spot_light_position2);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_light_direction);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 5.0);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0);
	glEnable(GL_LIGHT3);

	myfile.open ("keyframes.txt");
}


void loadCurrentCamera(){
	
	cam2_pos[0]=transformer_position[0]+(0.35*5*cos(car_angle*M_PI/180))-cam2_z*sin(car_angle*M_PI/180);
	cam2_pos[2]=transformer_position[2]+(0.35*5*sin(car_angle*M_PI/180))-cam2_z*cos(car_angle*M_PI/180);
	cam2_pos[3]=transformer_position[0]+(0.35*5*cos(car_angle*M_PI/180));
	cam2_pos[5]=transformer_position[2]+(0.35*5*sin(car_angle*M_PI/180));

	cam3_pos[0]=transformer_position[0]+(0.35*5*cos(car_angle*M_PI/180))+cam3_z*sin(car_angle*M_PI/180);
	cam3_pos[2]=transformer_position[2]-(0.35*5*sin(car_angle*M_PI/180))+cam3_z*cos(car_angle*M_PI/180);
	cam3_pos[3]=transformer_position[0]+(0.35*5*cos(car_angle*M_PI/180))+(cam3_z+1)*sin(car_angle*M_PI/180);
	cam3_pos[5]=transformer_position[2]-(0.35*5*sin(car_angle*M_PI/180))+(cam3_z+1)*cos(car_angle*M_PI/180);

	switch(cam_num){
		case 1: copy(cam1_pos,current_cam_pos); break;
		case 2: copy(cam2_pos,current_cam_pos); break;
		case 3: copy(cam3_pos,current_cam_pos); break;
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
		gluPerspective(40, aspect, 1, 5000);
	}

	else{
		aspect = (double)height/(double)width;
		gluPerspective(40, aspect, 1, 5000);
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
	if (key == GLFW_KEY_ESCAPE ){
		glfwSetWindowShouldClose(window, GL_TRUE);
		myfile.close();
	}
	

//  Right arrow , left arrow rotates transformer along y-axis 5 degrees anti-clockwise and 
// clockwise respectively
	if(key==GLFW_KEY_F && action==GLFW_PRESS && record){
		cout << "writing to file" << endl;
		myfile << transformer_position[0] << " " << transformer_position[1] << " " << transformer_position[2] << std::endl;
	}
	if(key== GLFW_KEY_RIGHT && action==GLFW_RELEASE){
		tyre_angle=0;
	}

	if(key == GLFW_KEY_LEFT && action==GLFW_RELEASE ){
		tyre_angle=0;

	}
	if(key== GLFW_KEY_RIGHT ){
		car_angle-=0.5;

		if(tyre_angle>-3) tyre_angle-=0.5/2;

	} 
	if(key == GLFW_KEY_LEFT ){
		
		car_angle+=0.5;
		if(tyre_angle<3)tyre_angle+=0.5/2;

	}

//  up arrow , down arrow rotates transformer along x-axis 5 degrees clockwise and 
// anti-clockwise respectively

	if(key==GLFW_KEY_UP ){
		 if(toCar) vehicle_mode=true;
		if(toCar)forward+=0.1;
		if(vehicle_mode){
			transformer_position[0]+=forward*sin(car_angle*M_PI/180);
			transformer_position[2]+=forward*cos(car_angle*M_PI/180);
		}
	} 
	else if(key==GLFW_KEY_DOWN ){
		 if(toCar) vehicle_mode=true;
		if(toCar) forward-=0.1;
		if(vehicle_mode){
			transformer_position[0]-=forward*sin(car_angle*M_PI/180);
			transformer_position[2]-=forward*cos(car_angle*M_PI/180);
		}
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

		switch(cam_num){
			case 1:  cam_num+=1;break;
			case 2:  cam_num+=1;break;
			case 3:  cam_num=1;break;
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
	

	if(key==GLFW_KEY_1 && action==GLFW_PRESS){
		first=!first;
	}
	if(key==GLFW_KEY_2 && action==GLFW_PRESS) second=!second;



	if(key== GLFW_KEY_M ){
		if(!space_press && hand_angle<=90-step) hand_angle+=5;
		else if(space_press && hand_angle>=step)  hand_angle-=5;
	}


	if(key==GLFW_KEY_R && action==GLFW_PRESS){
		// reset();
		if(!record) cout << "recording to file\n";
		else cout << "not recording\n";
		record=!record;
		return;

	}

	if(key==GLFW_KEY_P && action==GLFW_PRESS){
		if(!playback) cout << "playback mode is on\n";
		else cout << "playback mode is off\n";
		playback=!playback;
		return;
	}

	if(key==GLFW_KEY_A && action==GLFW_PRESS){
		cam_angle-=0.5;

	}


	if(key==GLFW_KEY_S  && mods==GLFW_MOD_SHIFT){

		if(first){
			if(!space_press && left_shoulder_x<=90-step) left_shoulder_x+=step;
			else if(space_press && left_shoulder_x>=step-90) left_shoulder_x-=step;
		}
		if(second){
			if(!space_press && right_shoulder_x<=90-step) right_shoulder_x+=step;
			else if(space_press && right_shoulder_x>=step-90) right_shoulder_x-=step;
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

	if(key==GLFW_KEY_V ){
		if(space_press){
			head_angle+=5;
		}
		else{
			head_angle-=5;
		}
	}




	if(key==GLFW_KEY_T && action==GLFW_PRESS){
		transform=true;
		if(toCar){
			toTransformer=true;
			toCar=false;
			return;
		}
		if(toTransformer){
			toCar=true;
			toTransformer=false;
			return;
		}

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
	cout << "entered" << endl;
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

	
	transformer_position[0]=-367.761;
	transformer_position[2]=854.055;

	cam_angle=0;
	cam2_z=30;
	cam3_z=3;
	
	cam1_pos[0]=-367.761;cam1_pos[2]=50+854.055;cam1_pos[3]=-367.761;cam1_pos[5]=10+854.055;

	cam_num=1;

	forward=0.0;
	tyre_angle=0;
	transform=false;

	car_angle=0;
	light1=true;
	light2=true;
	spot_light1=true;
	spot_light2=true;

	record=false;
	playback=false;

	vehicle_mode=false;

  	move_foot=0;
  	head_angle=0;

}


};
