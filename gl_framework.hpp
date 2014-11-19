
#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>




namespace cs475
{
  void initGL(void);

  void error_callback(int error, const char* description);

  void framebuffer_size_callback(GLFWwindow* window, int width, int height);

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  void reset(void);

  void load_default_cam(void);

  void copy(float* src,float*dst);

  void mulMatrix(GLfloat* matrix);

  bool gluInvertMatrix(GLfloat* m, GLfloat* invOut);


	extern float hand_angle;
	extern bool space_press;
	extern float right_knee_angle;
	extern float left_knee_angle;
	extern bool toCar;
	extern bool toTransformer;
	extern float leg_shift;
	extern float step;
	extern float right_hip_angle;
	extern float left_hip_angle;
	extern float torso_angle;
	extern float panel_angle;
	extern float left_shoulder_z;
	extern float right_shoulder_z;
	extern float panel_shift;
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
	extern float close_leg;
	extern int win_width;
	extern int win_height;
	extern float cam_angle;
	extern float cam1_pos[9];
	extern float cam2_pos[9];
	extern float cam3_pos[9];
	extern float current_cam_pos[9];
	extern int cam_num;
	extern float forward;
	extern float car_angle;
	extern float tyre_angle;
};


#endif
