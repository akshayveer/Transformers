#include "gl_framework.hpp"
#include "body_parts.hpp"


float step=0;

void Transform();
GLFWwindow* window;
void init_structures(void){
    struct_cube();
    struct_pelvis();
    struct_leg();
    struct_body();
    struct_hand();
    struct_thigh();
    struct_wheel();
    struct_left_prism();
    struct_right_prism();
    struct_foot();
   	struct_front_left_window();
    struct_left_bonnet();
    struct_right_bonnet();
    struct_left_hood();
    struct_right_hood();
    struct_front_right_window();
    struct_head();
    struct_ground();

}




void renderGL(void){

    		glRotatef(cs475::car_angle,0,1,0);
    		glTranslatef(0,0,cs475::forward);
    		GLfloat matrix[16]; 
			glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

		 	float cam2_pos[]={	pelvis_dim[0]/2,pelvis_dim[1],torso_dim[2],
		 						pelvis_dim[0]/2,pelvis_dim[1],torso_dim[2]+1,
		 						0,1,0};

    		float cam3_pos[]={0.35/2,1,-2,0.35/2,1,0,0,1,0};
				
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
					cs475::cam3_pos[i+k*3]=temp1[i]/temp1[3];
					cs475::cam2_pos[i+k*3]=temp2[i]/temp2[3];
				}
			}
			
	
    
    glCallList(pelvis);
    glPushMatrix();    // left hip hierarchy
        if(cs475::left_hip_angle>=0) glRotatef(cs475::left_hip_angle,1,0,0);  // to rotate about front edge of pelvis
        // to rotate about rear edge of pelvis
        else {										
            glTranslatef(0,0,-thigh_dim[2]);
            glRotatef(cs475::left_hip_angle,1,0,0);
            glTranslatef(0,0,thigh_dim[2]);
        }
        
        glCallList(thigh);

        glPushMatrix();  // left knee hierarchy

        	// to rotate left leg about front edge of left thigh
            glTranslatef(0,-thigh_dim[1],0);        
            glRotatef(cs475::left_knee_angle,1,0,0);    
            glTranslatef(0,thigh_dim[1],0);     

            glTranslatef(cs475::close_leg,0,0);

            glCallList(leg);
       
            glPushMatrix();   // placing left wheel on left leg botton left side from origin
              glTranslatef(0,-thigh_dim[1]-leg_dim[1],0);
              glRotatef(-90,0,1,0);
              glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
              glColor3f(0,0,0);
              glCallList(wheel);
              glColor3f(1,1,0);
            glPopMatrix();

            glPushMatrix();  // to align left foot with left leg
              glTranslatef(-thigh_leg_space,0,0);
              glCallList(foot);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // right hip hierarchy

        if(cs475::right_hip_angle>=0) glRotatef(cs475::right_hip_angle,1,0,0); // to rotate about front edge of pelvis
        // to rotate about rear edge of pelvis
        else {
            glTranslatef(0,0,-thigh_dim[2]);
            glRotatef(cs475::right_hip_angle,1,0,0);
            glTranslatef(0,0,thigh_dim[2]);
        }
        glPushMatrix();   // to position right thigh in correct position from left thigh position
            glTranslatef(pelvis_dim[0]-thigh_dim[0],0,0);
            glCallList(thigh);
        glPopMatrix();

        glPushMatrix();  // right leg hierarchy
        	// to rotate right leg about front edge of right thigh
            glTranslatef(0,-thigh_dim[1],0);       
            glRotatef(cs475::right_knee_angle,1,0,0);   
            glTranslatef(0,thigh_dim[1],0);         

            glPushMatrix();  // to position right leg from left thigh
                glTranslatef(2*thigh_leg_space+leg_dim[0],0,0);  
                glCallList(leg);
            glPopMatrix();

            glPushMatrix();  // to position right wheel  from orgin
              glTranslatef(pelvis_dim[0],-thigh_dim[1]-leg_dim[1],0);
              glRotatef(90,0,1,0);
              glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
              glColor3f(0,0,0);
              glCallList(wheel);
              glColor3f(1,1,0);
            glPopMatrix();

            glPushMatrix();  // to position right foot from position below left leg
              glTranslatef(leg_dim[0]+thigh_leg_space,0,0);
              glCallList(foot);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // torso hierarchy
    	// to lower down torso in transformation
        glTranslatef(0,-cs475::torso_shift_down,0);

        // to rotate torso about upper edge of pelvise
        glTranslatef(0,pelvis_dim[1],0);
        glRotatef(cs475::torso_angle,1,0,0);
        glTranslatef(0,-pelvis_dim[1],0);

        glCallList(torso);

        glPushMatrix();  // head
            glCallList(head);
        glPopMatrix();

        glPushMatrix();   // left back panel
        	// to rotate left back panel about axis passing through one of its edge
            glTranslatef(0,0,-torso_dim[2]);
            glRotatef(-cs475::panel_angle,0,1,0);
            glTranslatef(0,0,torso_dim[2]);

            glTranslatef(-cs475::panel_shift,0,0);  // to undo shift

            glPushMatrix();
                glTranslatef(panel_gap,0,-torso_dim[2]);  // to shift left panel right
                glRotatef(90,0,1,0);
                glTranslatef(0.0,pelvis_dim[1],0);
                glScalef(pelvis_dim[0]/2,torso_dim[1],prism_height); 
                // glColor3f(0.1,0.2,0.8);

                glCallList(front_left_window);
                glColor3f(0,34.0/255,102.0/255);
                glCallList(left_prism);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix(); // right back panel
        	// to rotate right back panel about axis passing through one of its edge
            glTranslatef(pelvis_dim[0],0,-torso_dim[2]);   
            glRotatef(cs475::panel_angle,0,1,0);
            glTranslatef(-pelvis_dim[0],0,torso_dim[2]);

            glTranslatef(cs475::panel_shift,0,0);  // to undo shift
            glPushMatrix();
                glTranslatef(-panel_gap,0,-torso_dim[2]);     // to move right panel to left
                glTranslatef(pelvis_dim[0],0,-pelvis_dim[0]/2);
                glRotatef(-90,0,1,0);
                glTranslatef(0.0,pelvis_dim[1],0);  // to lift up the pelvis
                glScalef(pelvis_dim[0]/2,torso_dim[1],prism_height);
                glCallList(front_right_window);
                glColor3f(0,34.0/255,102.0/255);
                glCallList(right_prism);
            glPopMatrix();
        glPopMatrix();


        // left hand shouler
        glPushMatrix();      

            glTranslatef(cs475::value,cs475::up,0);
            glTranslatef(0,-torso_dim[2],0);
            glRotatef(-cs475::hand_angle,0,1,0);
            glTranslatef(0,torso_dim[2],0);

            glTranslatef(0,torso_dim[1]+pelvis_dim[1],0);
            glRotatef(-cs475::left_shoulder_z,0,0,1);
            glRotatef(-cs475::left_shoulder_x,1,0,0);
            glRotatef(cs475::left_shoulder_z,0,0,1);
            glTranslatef(0,-torso_dim[1]-pelvis_dim[1],0);

            glTranslatef(0,torso_dim[1]+pelvis_dim[1],0);
            glRotatef(-cs475::left_shoulder_z,0,0,1);
            glTranslatef(0,-torso_dim[1]-pelvis_dim[1],0);

            glPushMatrix();  // to draw left upper arm
               
                glRotatef(90,0,1,0);
                glTranslatef(0.0,pelvis_dim[1],0);
                glScalef(torso_dim[2],torso_dim[1],hand_length);
                glCallList(left_hood);
                glCallList(left_bonnet);
         /*       glColor3f(0.75294117647,0.75294117647,0.75294117647);
                glTranslatef(1/tan(prism_angle*M_PI/180),1,-1);


                glScalef(0.09,0.09,0.09);
                glRotatef(-90,1,0,0);
                gluDisk(quadratic,0,1,32,32);*/
                glCallList(left_prism);

            glPopMatrix();

            glPushMatrix();
                 glTranslatef(0,0.17,-0.1);
                glRotatef(-cs475::left_elbow_angle,1,0,0);
                glTranslatef(0,-0.17,0.1);
                glTranslatef(-0.1,pelvis_dim[1]-0.17,0);
                glScalef(0.1,0.17,0.1);
                glCallList(cube);
            glPopMatrix();
            glTranslatef(0*pelvis_dim[0],pelvis_dim[1]+torso_dim[1],0);
            glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
            glColor3f(0,0,0);
            glTranslatef(0,0,0.1/2);
            if(cs475::tyre_angle< 5 && cs475::tyre_angle> -5) glRotatef(-cs475::tyre_angle/2,1,0,0);
            else{
            	if(cs475::tyre_angle>0) glRotatef(-2.5,1,0,0);
            	else if(cs475::tyre_angle<0) glRotatef(2.5,1,0,0);
            }
            glTranslatef(0,0,-0.1/2);
            glCallList(wheel);
            glColor3f(1,1,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-cs475::value,cs475::up,0);
            glTranslatef(pelvis_dim[0],-torso_dim[2],0);
            glRotatef(cs475::hand_angle,0,1,0);
            glTranslatef(-pelvis_dim[0],torso_dim[2],0);

            glTranslatef(pelvis_dim[0],torso_dim[1]+pelvis_dim[1],0);
            glRotatef(cs475::right_shoulder_z,0,0,1);
            glRotatef(-cs475::right_shoulder_x,1,0,0);
            glTranslatef(-pelvis_dim[0],-torso_dim[1]-pelvis_dim[1],0);
            glPushMatrix();
                glTranslatef(pelvis_dim[0],0,-torso_dim[2]);
                glRotatef(-90,0,1,0);
                glTranslatef(0.0,pelvis_dim[1],0);
                glScalef(torso_dim[2],torso_dim[1],hand_length);
                glCallList(right_hood);
                glCallList(right_bonnet);
               /* glColor3f(0.75294117647,0.75294117647,0.75294117647);
                glTranslatef(1-1/tan(prism_angle*M_PI/180),1,-1);

                glScalef(0.09,0.09,0.09);
                glRotatef(-90,1,0,0);
                gluDisk(quadratic,0,1,32,32);*/
                
                glCallList(right_prism);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0,0.17,-0.1);
               glRotatef(-cs475::right_elbow_angle,1,0,0);
               glTranslatef(0,-0.17,0.1);
                glTranslatef(pelvis_dim[0],pelvis_dim[1]-0.17,0);
                glScalef(0.1,0.17,0.1);
                glCallList(cube);
            glPopMatrix();
            glTranslatef(pelvis_dim[0],pelvis_dim[1]+torso_dim[1],0);
            glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
            glColor3f(0,0,0);

            glTranslatef(0,0,0.1/2);
            if(cs475::tyre_angle< 5 && cs475::tyre_angle> -5) glRotatef(cs475::tyre_angle/2,1,0,0);
            else{
            	if(cs475::tyre_angle>0) glRotatef(2.5,1,0,0);
            	else if(cs475::tyre_angle<0) glRotatef(-2.5,1,0,0);
            }
            glTranslatef(0,0,-0.1/2);
            glCallList(wheel);
            glColor3f(1,1,0);
        glPopMatrix();

    glPopMatrix();
}





void renderRoom(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    cs475::load_default_cam();
    glLoadIdentity();
    gluLookAt(cs475::current_cam_pos[0],cs475::current_cam_pos[1],cs475::current_cam_pos[2],
    	cs475::current_cam_pos[3],cs475::current_cam_pos[4],cs475::current_cam_pos[5],
    	cs475::current_cam_pos[6],cs475::current_cam_pos[7],cs475::current_cam_pos[8]);


    glCallList(ground);
    glTranslatef(0,10*(leg_dim[1]+thigh_dim[1]+foot_height),-6);
    glScalef(10,10,10);
    renderGL();
}


void Transform(){
	step=0.01;
	int m;
	int n;
	if(cs475::toCar){
		m=1;
		n=1;	
	} 
	else{
		m=-1;
		n=0;	
	} 
  for(int i=0;i<torso_dim[1]/step;i++){
    cs475::up+=(m*step);
    renderRoom();
    glfwSwapBuffers(window);
  	glfwPollEvents();
  }
  for(int i=0;i<90/cs475::step;i++){
    cs475::hand_angle+=(m*cs475::step);
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for(int i=0;i<0.03/step;i++){
    cs475::value+=m*step;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  float current_angle=cs475::left_knee_angle;
  for(int i=0;i<(n*90-m*current_angle)/cs475::step;i++){
    cs475::left_knee_angle+=(m*cs475::step);
    cs475::right_knee_angle+=(m*cs475::step);
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for(int i=0;i<panel_gap/step;i++){
    cs475::panel_shift+=m*step;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for(int i=0;i<90/cs475::step;i++){
    cs475::panel_angle+=(m*cs475::step);
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  for(int i=0;i<90/cs475::step;i++){
    cs475::torso_angle+=(m*cs475::step);
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  step=10*step;
  for(int i=0;i<(pelvis_dim[1]+thigh_dim[1])/step;i++){
    cs475::torso_shift_down+=m*step;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  cs475::toCar=false;
  cs475::toTransformer=false;
  cs475::step=5;

}


int main ()
{

    glfwSetErrorCallback(cs475::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
      return -1;



  int win_width=512;
  int win_height=512;

    //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(win_width, win_height, "Transformer", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      return -1;
  }

    //! Make the window's context current
  glfwMakeContextCurrent(window);

    //Keyboard Callback
  glfwSetKeyCallback(window, cs475::key_callback);
    //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, cs475::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwGetFramebufferSize(window, &win_width, &win_height);
  cs475::framebuffer_size_callback(window, win_width, win_height);
    //Initialize GL state
  cs475::initGL();
  init_structures();

    // Loop until the user closes the window

  while (glfwWindowShouldClose(window) == 0)
  {

      if(!cs475::toCar && !cs475::toTransformer)
        renderRoom();
      else Transform();
        // renderRoom();
        
        // Swap front and back buffers
      glfwSwapBuffers(window);

        // Poll for and process events
      glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
