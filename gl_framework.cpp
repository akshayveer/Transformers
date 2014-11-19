#include "gl_framework.hpp"

namespace cs475
{
  int win_width;
  int win_height;

 float angle=0;
 float next_angle=0;
 float hand_angle=0;
 float bust_angle=0;
 float tyre_angle=0;
 bool shift=false;
 float rear_tyre=0;
 float rear_tyre_angle=0;
 float lower_part=0;
 float lower_down=0;
 float hand_angle2=0;
 float leg_angle=0;
 float right_knee_angle=0;
 float left_knee_angle=0;
 bool toCar=false;
 bool toTransformer=false;
 float low_shift=0;
 float leg_shift=0;
 float step=5;  // 0.09
 float left_hip_angle=0;
 float right_hip_angle=0;
 float torso_angle=0;
 float down_shift=0;
 float left_shoulder_y=0;
 float right_shoulder_z=0;
 float shoulder_shift_x=0;
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
   
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    // glFrontFace(GL_CCW);
  // glPolygonMode(GL_FRONT,GL_FILL);
  glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  
  // glShadeModel (GL_FLAT);
  glDepthRange(-2,2);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
  // glMatrixMode(GL_MODELVIEW);             // Select The Modelview Matrix
  // glLoadIdentity();
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    if  ( height == 0 ) height = 1;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Draw to the whole window
    glViewport( 0, 0, width, height );

    //Keep the aspect ratio fixed
    double aspect;
    if (width > height)
      {
	aspect = (double)width/(double)height;
	glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
      }
    else
      {
	aspect = (double)height/(double)width;
	glOrtho(-1.0, 1.0, -aspect, aspect, -1.0, 1.0);
      }
    win_width = width;
    win_height = height;
    glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	// gluLookAt(0, 0, 0, 0, 0,-1, 0, 1, 0);
  }
  
  //!GLFW keyboard callback

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
      shift=!shift;
    }

    if(key==GLFW_KEY_1 && action == GLFW_PRESS) first=!first;
    if(key==GLFW_KEY_2 && action == GLFW_PRESS) second=!second;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    //  Right arrow - increase rotation by 5 degree
    if(key== GLFW_KEY_RIGHT && action == GLFW_PRESS){
      angle+=5;
    }
    else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS) angle-=5;
    if(key==GLFW_KEY_UP && action == GLFW_PRESS) next_angle+=5;
    else if(key==GLFW_KEY_DOWN && action == GLFW_PRESS) next_angle-=5;

    if(key== GLFW_KEY_M && action == GLFW_PRESS){
      if(!shift ) hand_angle+=5;
      else if(shift )  hand_angle-=5;
    }
    if(key==GLFW_KEY_B && action == GLFW_PRESS){
      if(!shift )     left_shoulder_y+=step;
      else if(shift ) shoulder_shift_x-=step;
    }
   
    if(key==GLFW_KEY_R && action == GLFW_PRESS){
     reset();
    }

    if(key==GLFW_KEY_W && action == GLFW_PRESS) lower_part=0.05;
    

    if(key==GLFW_KEY_L && action == GLFW_PRESS){       
      if(!shift && leg_angle<=180) leg_angle+=5;
      else if(shift && leg_angle>=0) leg_angle-=5;
    }

    if(key==GLFW_KEY_K && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT){

      if(!shift && left_knee_angle<=90-step) left_knee_angle+=step;
      else if(shift && left_knee_angle>=step) left_knee_angle-=step;
    }
    if(key==GLFW_KEY_K && mods == GLFW_MOD_SHIFT && action == GLFW_PRESS){
       if(!shift && right_knee_angle<=90-step) right_knee_angle+=step;
      else if(shift && right_knee_angle>=step) right_knee_angle-=step;
    }

    if(key==GLFW_KEY_H && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT){

      if(!shift && left_hip_angle<=90-step) left_hip_angle+=step;
      else if(shift && left_hip_angle>=step-90) left_hip_angle-=step;
    }
    if(key==GLFW_KEY_H && mods == GLFW_MOD_SHIFT && action == GLFW_PRESS){
       if(!shift && right_hip_angle<=90-step) right_hip_angle+=step;
      else if(shift && right_hip_angle>=step-90) right_hip_angle-=step;
    }

    if(key==GLFW_KEY_S && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT){
      if(first){
         if(!shift && left_shoulder_x<=90-step) left_shoulder_x+=step;
         else if(shift && left_shoulder_x>=step) left_shoulder_x-=step;
      }
      if(second){
        if(!shift && right_shoulder_x<=90-step) right_shoulder_x+=step;
         else if(shift && right_shoulder_x>=step) right_shoulder_x-=step;
      }
    }

    else if(key==GLFW_KEY_S && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT){
      if(first){
         if(!shift && left_shoulder_z<=90-step) left_shoulder_z+=step;
         else if(shift && left_shoulder_z>=step) left_shoulder_z-=step;
      }
       if(second){
        if(!shift && right_shoulder_z<=90-step) right_shoulder_z+=step;
         else if(shift && right_shoulder_z>=step) right_shoulder_z-=step;
      }
    }
    if(key==GLFW_KEY_E && action == GLFW_PRESS){
      if(first){
         if(!shift && left_elbow_angle<=90-step) left_elbow_angle+=step;
         else if(shift && left_elbow_angle>=step) left_elbow_angle-=step;
      }
      if(second){
        if(!shift && right_elbow_angle<=90-step) right_elbow_angle+=step;
         else if(shift && right_elbow_angle>=step) right_elbow_angle-=step;
      }
    }


     
      

    if(key==GLFW_KEY_T && action == GLFW_PRESS){
        step=0.09;
      if(!shift && !toCar){
        toCar=true;
      }

      else if(shift && !toTransformer) toTransformer=true;
    }

    if(key==GLFW_KEY_P && action == GLFW_PRESS){       
      if(!shift ) low_shift=1;
      else if(shift) low_shift-=1;
    }

    if(key==GLFW_KEY_Q && action == GLFW_PRESS){       
      if(!shift ) leg_shift+=1;
      else if(shift) leg_shift-=1;
    }

    if(key==GLFW_KEY_C && action == GLFW_PRESS){       
      if(!shift && torso_angle<=90-step) torso_angle+=step;
      else if(shift && torso_angle>=step-90) torso_angle-=step;
    }

    if(key==GLFW_KEY_D && action == GLFW_PRESS){       
      if(!shift ) down_shift+=0.01;
      else if(shift) down_shift-=0.01;
    }

    if(key==GLFW_KEY_U && action == GLFW_PRESS){       
      if(!shift ) up+=0.01;
      else if(shift) up-=0.01;
    }

  }

  void reset(){
    angle=0;
  next_angle=0;
  hand_angle=0;
 bust_angle=0;
  tyre_angle=0;
  shift=false;
  rear_tyre=0;
  rear_tyre_angle=0;
  lower_part=0;
  lower_down=0;
  hand_angle2=0;
  leg_angle=0;
  right_knee_angle=0;
  left_knee_angle=0;
  toCar=false;
  toTransformer=false;
  low_shift=0;
  leg_shift=0;
  step=5;  // 0.09
  left_hip_angle=0;
  right_hip_angle=0;
  torso_angle=0;
  down_shift=0;
  left_shoulder_y=0;
  right_shoulder_z=0;
  shoulder_shift_x=0;
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
  }

  
};  
  


