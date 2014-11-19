#include "gl_framework.hpp"
#include <stdio.h>
#include <stdlib.h>

#define cube 1
#define pelvis 2
#define leg 3
#define torso 4
#define hand 5
#define thigh 6
#define wheel 7
#define foot 8
#define left_prism 9
#define right_prism 10
#define front_left_window 11
#define left_bonnet 12
#define right_bonnet 13
#define left_hood 14
#define right_hood 15
#define front_right_window 16
#define head 17
#define ground 18
#define objects 19
#define hand_texture 20

void struct_cube(void);
void struct_pelvis(void);
void struct_leg(void);
void struct_body(void);
void struct_hand(void);
void struct_thigh(void);
void struct_wheel(void);
void struct_foot(void);
void struct_left_prism(void);
void struct_right_prism(void);
GLuint LoadTexture(const char * pic);
void struct_front_left_window(void);
void struct_front_right_window(void);
void struct_left_bonnet(void);
void struct_right_bonnet(void);
void struct_left_hood(void);
void struct_right_hood(void);
void struct_head(void);
void struct_ground(void);
void struct_objects(void);
void struct_hand_texture(void);

 static GLUquadricObj *quadratic=gluNewQuadric();
 // dimestion x,y,z
 extern float pelvis_dim[3];
 extern float thigh_space;
 extern float thigh_dim[3];  // z<pevis_z  // y can be any thing
 extern float thigh_leg_space;  // full gap
 extern float leg_dim[3];
 extern float torso_gap;     // full gap
 extern float prism_height;
 extern float torso_dim[3];
 extern float prism_angle;
 extern float panel_gap;       
 extern float hand_length;
 extern float hand_dim[3];
 extern float foot_length;
 extern float foot_height;
 extern float texture_shift;
 extern float window_shift;
 extern float x,y,z;
 
