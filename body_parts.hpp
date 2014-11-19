#include "gl_framework.hpp"
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
 extern float hand_gap;       // hand into body
 extern float hand_length;
 extern float hand_dim[3];
 
