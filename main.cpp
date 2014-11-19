  #include "gl_framework.hpp"
  #include "body_parts.hpp"

float step=0;

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

}


void renderGL( void ){
    //  Clear screen and Z-buffer

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(cs475::next_angle,1,0,0);
    glRotatef(cs475::angle,0,1,0);

    glPushMatrix();
        glCallList(pelvis);
        glPushMatrix();
            
            if(cs475::left_hip_angle>=0) glRotatef(cs475::left_hip_angle,1,0,0);
            else {
                glTranslatef(0,0,-thigh_dim[2]);
                glRotatef(cs475::left_hip_angle,1,0,0);
                glTranslatef(0,0,thigh_dim[2]);
            }
            glCallList(thigh);

            glPushMatrix();
                glTranslatef(0,-thigh_dim[1],0);        // to rotate legs
                glRotatef(cs475::left_knee_angle,1,0,0);    // to rotate legs
                glTranslatef(0,thigh_dim[1],0);         // to rotate legs 
                glPushMatrix();
                    glTranslatef(cs475::leg_shift*thigh_leg_space,0,0);    // to move left leg right
                    glCallList(leg);
                glPopMatrix();
                glTranslatef(0,-thigh_dim[1]-leg_dim[1],0);
                glRotatef(-90,0,1,0);
                glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
                glCallList(wheel);
            glPopMatrix();


        glPopMatrix();

        glPushMatrix();

            if(cs475::right_hip_angle>=0) glRotatef(cs475::right_hip_angle,1,0,0);
            else {
                glTranslatef(0,0,-thigh_dim[2]);
                glRotatef(cs475::right_hip_angle,1,0,0);
                glTranslatef(0,0,thigh_dim[2]);
            }
            glPushMatrix();
                glTranslatef(pelvis_dim[0]-thigh_dim[0],0,0);
                glCallList(thigh);
            glPopMatrix();

            // to rotate legs
            
            glPushMatrix();
                glTranslatef(0,-thigh_dim[1],0);        // to rotate legs
                glRotatef(cs475::right_knee_angle,1,0,0);    // to rotate legs
                glTranslatef(0,thigh_dim[1],0);         // to rotate legs 
                glPushMatrix();
                    glTranslatef(-cs475::leg_shift*thigh_leg_space,0,0);    // to move right leg to left
                    glTranslatef(2*thigh_leg_space+leg_dim[0],0,0);   // to align right leg in correct position
                    glCallList(leg);
                glPopMatrix();
                glTranslatef(pelvis_dim[0],-thigh_dim[1]-leg_dim[1],0);
                glRotatef(90,0,1,0);
                glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
                glCallList(wheel);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            if(cs475::torso_shift_down >=0 && cs475:: torso_shift_down<=pelvis_dim[1]+thigh_dim[1])
                glTranslatef(0,-cs475::torso_shift_down,0);
            else if(cs475::torso_shift_down>=pelvis_dim[1]+thigh_dim[1])
                glTranslatef(0,-(pelvis_dim[1]+thigh_dim[1]),0);
            glTranslatef(0,pelvis_dim[1],0);
            glRotatef(cs475::torso_angle,1,0,0);
            glTranslatef(0,-pelvis_dim[1],0);
            glCallList(torso);
            
            glPushMatrix();
                glTranslatef(pelvis_dim[0]/2,pelvis_dim[1]+torso_dim[1],-torso_dim[2]/2);
                glRotatef(-90,1,0,0);
                glScalef(torso_dim[2]/2,torso_dim[2]/2,0.5);
                glCallList(wheel);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,0,-torso_dim[2]);
                glRotatef(-cs475::left_shoulder_y,0,1,0);
                glTranslatef(0,0,torso_dim[2]);
                glTranslatef(-cs475::shoulder_shift_x,0,0);
            
                glPushMatrix();
                    glTranslatef(hand_gap,0,-torso_dim[2]);
                    glRotatef(90,0,1,0);
                    glTranslatef(0.0,pelvis_dim[1],0);
                    glScalef(pelvis_dim[0]/2,torso_dim[1],prism_height);
                    glCallList(left_prism);
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(pelvis_dim[0],0,-torso_dim[2]);   // changed 
                glRotatef(cs475::left_shoulder_y,0,1,0);
                glTranslatef(-pelvis_dim[0],0,torso_dim[2]);
                glTranslatef(cs475::shoulder_shift_x,0,0);
                glPushMatrix();
                    glTranslatef(-hand_gap,0,-torso_dim[2]);     // to move hand into body
                    glTranslatef(pelvis_dim[0],0,-pelvis_dim[0]/2);
                    glRotatef(-90,0,1,0);
                    glTranslatef(0.0,pelvis_dim[1],0);
                    glScalef(pelvis_dim[0]/2,torso_dim[1],prism_height);
                    glCallList(right_prism);
                glPopMatrix();
            glPopMatrix();


            // left hand shouler
            glPushMatrix();      // torso_dim[1]/step*x=(torso_dim[2]-torso_dim[0])/2
                glTranslatef(cs475::value,cs475::up,0);
                glTranslatef(0,-torso_dim[2],0);
                glRotatef(-cs475::hand_angle,0,1,0);
                glTranslatef(0,torso_dim[2],0);

                glTranslatef(0,torso_dim[1]+pelvis_dim[1],0);
                glRotatef(-cs475::left_shoulder_z,0,0,1);
                glRotatef(-cs475::left_shoulder_x,1,0,0);
                glTranslatef(0,-torso_dim[1]-pelvis_dim[1],0);
                glPushMatrix();
                    glRotatef(90,0,1,0);
                    glTranslatef(0.0,pelvis_dim[1],0);
                    glScalef(torso_dim[2],torso_dim[1],hand_length);
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
                glTranslatef(0*pelvis_dim[0],pelvis_dim[1],0);
                glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
                glCallList(wheel);
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
                glTranslatef(pelvis_dim[0],pelvis_dim[1],0);
                glScalef(leg_dim[2]/2,leg_dim[2]/2,1);
                glCallList(wheel);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
            
          
    

  

}


void Transform(){
step=0.0001;
int m;
if(cs475::toCar) m=1;
else m=-1;
  for(int i=0;i<90/cs475::step;i++){
    cs475::hand_angle+=(m*cs475::step);
    // cs475::right_shoulder_z+=(m*cs475::step);
    renderGL();
    glfwSwapBuffers(window);
  }
  for(int i=0;i<torso_dim[1]/step;i++){
    cs475::up+=(m*step);
    renderGL();
    glfwSwapBuffers(window);
  }
  // std::cout << (torso_dim[0]-torso_dim[2])/2 << std::endl;

  for(int i=0;i<0.03/step;i++){
    cs475::value+=m*step;
    renderGL();
    glfwSwapBuffers(window);
  }
  
  for(int i=0;i<90/cs475::step;i++){
    cs475::left_knee_angle+=(m*cs475::step);
    cs475::right_knee_angle+=(m*cs475::step);
    renderGL();
    glfwSwapBuffers(window);
  }
  for(int i=0;i<hand_gap/step;i++){
    cs475::shoulder_shift_x+=m*step;
    renderGL();
    glfwSwapBuffers(window);
  }
 
  for(int i=0;i<90/cs475::step;i++){
    cs475::left_shoulder_y+=(m*cs475::step);
    renderGL();
    glfwSwapBuffers(window);
  }

 
  for(int i=0;i<90/cs475::step;i++){
    cs475::torso_angle+=(m*cs475::step);
    renderGL();
    glfwSwapBuffers(window);
  }
  step=10*step;
  for(int i=0;i<(pelvis_dim[1]+thigh_dim[1])/step;i++){
    cs475::torso_shift_down+=m*step;
    renderGL();
    glfwSwapBuffers(window);
  }
   cs475::toCar=false;
   cs475::toTransformer=false;
    
    
}


int main () 
{


    //! The pointer to the GLFW window
    

    //! Setting up the GLFW Error callback
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

        // Render here
      if(!cs475::toCar && !cs475::toTransformer) 
        renderGL();
    else Transform();
      // test_anlge+=0.005;
      // else Transform();

        // Swap front and back buffers
      glfwSwapBuffers(window);

        // Poll for and process events
      glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
