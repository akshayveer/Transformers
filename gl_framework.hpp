
#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>



namespace cs475
{
  //! Initialize GL State
	
	 

  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  void reset(void);

extern float angle;
extern float next_angle;
extern float hand_angle;
extern float bust_angle;
extern float tyre_angle;
extern bool shift;
extern float rear_tyre;
extern float rear_tyre_angle;
extern float lower_part;
extern float lower_down;
extern float hand_angle2;
extern float leg_angle;
extern float right_knee_angle;
extern float left_knee_angle;
extern bool toCar;
extern bool toTransformer;
extern float low_shift;
extern float leg_shift;
extern float step;
extern float right_hip_angle;
extern float left_hip_angle;
extern float torso_angle;
extern float down_shift;
extern float left_shoulder_y;
extern float left_shoulder_z;
extern float right_shoulder_z;
extern float shoulder_shift_x;
extern float shoulder_shift_z;
extern float torso_shift_down;
extern bool first;
extern bool second;
extern float right_shoulder_x;
extern float left_shoulder_x;
extern float up;
extern float value;
extern float left_elbow_angle;
extern float right_elbow_angle;
};


#endif
