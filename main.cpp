#include "gl_framework.hpp"
#include "body_parts.hpp"
#include <fstream>

using namespace cs475;
float istep=0;
bool rotate_body=false;
bool rotate_cam=false;
float angle_step=20;
float rotate=0;
float fps=30;
void Transform();
GLFWwindow* window;
unsigned int framenum=0;
unsigned char *pRGB;

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
    struct_objects();
    struct_hand_texture();
}

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (win_width+1) * (win_height + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, win_width, win_height, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"frames/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<win_width<<" "<<win_height<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (win_width+1) * (win_height + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}


void renderGL(void){

    glScalef(10,10,10);
    glCallList(pelvis);
    glPushMatrix();    // left hip hierarchy
        // if(cs475::left_hip_angle>=0) 
          glRotatef(cs475::left_hip_angle,1,0,0);  // to rotate about front edge of pelvis
        // to rotate about rear edge of pelvis
        /*else {                    
            glTranslatef(0,0,-thigh_dim[2]);
            glRotatef(cs475::left_hip_angle,1,0,0);
            glTranslatef(0,0,thigh_dim[2]);
        }*/
        
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
              glTranslatef(0,0,-move_foot);
              glTranslatef(-thigh_leg_space,0,0);
              glCallList(foot);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // right hip hierarchy

        // if(cs475::right_hip_angle>=0) 
          glRotatef(cs475::right_hip_angle,1,0,0); // to rotate about front edge of pelvis
        // to rotate about rear edge of pelvis
        /*else {
            glTranslatef(0,0,-thigh_dim[2]);
            glRotatef(cs475::right_hip_angle,1,0,0);
            glTranslatef(0,0,thigh_dim[2]);
        }*/
        glPushMatrix();   // to position right thigh in correct position from left thigh position
            glTranslatef(pelvis_dim[0]-thigh_dim[0],0,0);
            glCallList(thigh);
        glPopMatrix();

        glPushMatrix();  // right leg hierarchy
          // to rotate right leg about front edge of right thigh
            glTranslatef(0,-thigh_dim[1],0);       
            glRotatef(cs475::right_knee_angle,1,0,0);   
            glTranslatef(0,thigh_dim[1],0);         

            glTranslatef(-cs475::close_leg,0,0);
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
              glTranslatef(0,0,-move_foot);
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
        
          glTranslatef((0.15/2)+(torso_dim[0]-0.15)/2,(torso_dim[1]+pelvis_dim[1]),-torso_dim[2]/2);
          glRotatef(head_angle,0,1,0);
          glTranslatef((-0.15/2)-(torso_dim[0]-0.15)/2,-(torso_dim[1]+pelvis_dim[1]),torso_dim[2]/2);
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
                  glCallList(left_prism);

              glPopMatrix();

              glPushMatrix();
                   glTranslatef(0,0.17,-0.1);
                  glRotatef(-cs475::left_elbow_angle,1,0,0);
                  glTranslatef(0,-0.17,0.1);
                  glTranslatef(-0.1,pelvis_dim[1]-0.17,0);
                  glScalef(0.1,0.17,0.1);
                  glCallList(hand_texture);
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
                glCallList(right_prism);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0,0.17,-0.1);
               glRotatef(-cs475::right_elbow_angle,1,0,0);
               glTranslatef(0,-0.17,0.1);
                glTranslatef(pelvis_dim[0],pelvis_dim[1]-0.17,0);
                glScalef(0.1,0.17,0.1);
                glCallList(hand_texture);
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
  if(record){
    capture_frame(framenum++);
  }
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  if(rotate_body && transform){
    car_angle+=1;
  }

  if(vehicle_mode){
    transformer_position[0]+=forward*sin(car_angle*M_PI/180);
    transformer_position[2]+=forward*cos(car_angle*M_PI/180);
  }


  if(record){
    myfile << transformer_position[0] << " " << transformer_position[1] << " " << transformer_position[2] << " " ;
    myfile << up << " " << hand_angle << " " << value << " " << left_knee_angle << " " << right_knee_angle << " " << panel_shift << " ";
    myfile << panel_angle << " " << torso_angle << " " << torso_shift_down << " " << cs475::toCar << " " << transform << endl;
  }

  if(rotate_cam){
    cam1_pos[3]=transformer_position[0];
  cam1_pos[1]=transformer_position[1];
  cam1_pos[4]=transformer_position[4];
  cam1_pos[5]=transformer_position[2];
  cam1_pos[0]=cam1_pos[3]+30*sin((cam_angle+angle_step)*M_PI/180);
  cam1_pos[2]=cam1_pos[5]+30*cos((cam_angle+angle_step)*M_PI/180);
  
  if(angle_step<130) angle_step+=0.5;
  }
    cs475::loadCurrentCamera();
    glLoadIdentity();
    gluLookAt(cs475::current_cam_pos[0],cs475::current_cam_pos[1],cs475::current_cam_pos[2],
      cs475::current_cam_pos[3],cs475::current_cam_pos[4],cs475::current_cam_pos[5],
      cs475::current_cam_pos[6],cs475::current_cam_pos[7],cs475::current_cam_pos[8]);

    glPushMatrix();
      glTranslatef(0,-10*(leg_dim[1]+thigh_dim[1]+foot_height),0);
      glCallList(ground);
      glTranslatef(764.716,0,-422.059);
      glScalef(50,50,1);
      glCallList(objects);
    glPopMatrix();

    glTranslatef(cs475::transformer_position[0],cs475::transformer_position[1],cs475::transformer_position[2]);
    glRotatef(rotate,1,0,1);
    glRotatef(cs475::car_angle,0,1,0);
    renderGL();
}


void Transform(){
  

  istep=0.01;
  // step=1;
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
  for(int i=0;i<torso_dim[1]/istep;i++){
    cs475::up+=(m*istep);
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


  for(int i=0;i<0.03/istep;i++){
    cs475::value+=m*istep;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for(int i=0;i<thigh_leg_space/istep;i++){
    cs475::close_leg+=m*istep;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for(int i=0;i<(foot_length-leg_dim[2])/istep;i++){
    cs475::move_foot+=m*istep;
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

  for(int i=0;i<panel_gap/istep;i++){
    cs475::panel_shift+=m*istep;
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
  istep=1*istep;
  for(int i=0;i<(pelvis_dim[1]+thigh_dim[1])/istep;i++){
    cs475::torso_shift_down+=m*istep;
    renderRoom();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  cs475::transform=false;
  cs475::step=5;

}

void playBack(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  cam1_pos[4]=0;
  transformer_position[1]=100;
  for(int i=0;i<100;i++){
    cam1_pos[4]+=1; 
    renderRoom();
    glfwSwapBuffers(window);

  }

  float velocity=0.1;
 
  while(transformer_position[1]>=10*velocity){
    transformer_position[1]-=velocity;
    cam1_pos[4]=transformer_position[1];
    
   
      renderRoom();
      glfwSwapBuffers(window);

    velocity+=0.1;
  }
  
  angle_step=10;
  
  for(int i=0;i<90/angle_step;i++){
    cs475::left_knee_angle+=angle_step;
    cs475::right_knee_angle+=angle_step;
    right_hip_angle-=angle_step;  
    transformer_position[1]-=velocity;
    cam1_pos[4]=transformer_position[1];
   
     
      renderRoom();
      glfwSwapBuffers(window);
    
  }
 
  car_angle=20;
  torso_angle=20;
  
  glfwSetTime(0.00);
  while (glfwGetTime()<1){
    renderRoom();
    glfwSwapBuffers(window);
  }
  angle_step=3;
  for(int i=0;i<90/angle_step;i++){
    cs475::left_knee_angle-=angle_step;
    cs475::right_knee_angle-=angle_step;
    right_hip_angle+=angle_step;  
  torso_angle-=(2.0/3.0);
    renderRoom();
    glfwSwapBuffers(window);
  }
  glfwSetTime(0.00);
  while (glfwGetTime()<1){
    renderRoom();
    glfwSwapBuffers(window);
  }
  angle_step=1;
  float l=cam1_pos[2]-cam1_pos[5];
  float cx=(cam1_pos[0]+cam1_pos[3])/2,cz=(cam1_pos[2]+cam1_pos[5])/2;
  for(int i=0;i<30;i++){
    head_angle+=angle_step;
    cam1_pos[3]=cx+(2*l/3)*sin(1*head_angle*M_PI/180);
    cam1_pos[5]=cz-(l/2)*cos(1*head_angle*M_PI/180);

    cam1_pos[0]=cx-(l/3)*sin(1*head_angle*M_PI/180);
    cam1_pos[2]=cz+(l/3)*cos(1*head_angle*M_PI/180);
    cx-=1;
    renderRoom();
    glfwSwapBuffers(window);
  }

  glfwSetTime(0.00);
   while (glfwGetTime()<2){
    renderRoom();
    glfwSwapBuffers(window);
  }
   
  angle_step=1;
  l=cam1_pos[2]-cam1_pos[5];
  cx=(cam1_pos[0]+cam1_pos[3])/2,cz=(cam1_pos[2]+cam1_pos[5])/2;
  for(int i=0;i<30;i++){
    head_angle-=angle_step;
    cam1_pos[3]=cx+(2*l/3)*sin(1*head_angle*M_PI/180);
    cam1_pos[5]=cz-(l/2)*cos(1*head_angle*M_PI/180);

    cam1_pos[0]=cx-(l/3)*sin(1*head_angle*M_PI/180);
    cam1_pos[2]=cz+(l/3)*cos(1*head_angle*M_PI/180);
    cx+=1;
    renderRoom();
    glfwSwapBuffers(window);
  }
    step=1;
    rotate_body=true;
    transform=true;
  toCar=true;
  toTransformer=false;
  Transform();
  vehicle_mode=true;
  forward=0.1;
  glfwSetTime(0.00);
  while (glfwGetTime()<0.5){
    renderRoom();
      glfwSwapBuffers(window);
  }

  copy(cam2_pos,cam1_pos);
  forward=5;
  angle_step=25;
  l=10;
  glfwSetTime(0.00);
  rotate_cam=true;
  while (glfwGetTime()<1){
    car_angle+=0.5;
    renderRoom();
      glfwSwapBuffers(window);
  }
  
  step=5;
  rotate_body=false;
  transform=true;
  toCar=false;
  toTransformer=true;
  Transform();
  vehicle_mode=true;
  forward=1;
  step=2;
    
     left_shoulder_x=30;
      right_shoulder_x=30;
      left_elbow_angle=50;
      right_elbow_angle=50;
  glfwSetTime(0.00);
  while(glfwGetTime()<7){
    for(int i=0;i<30/step;i++){
    
     /* left_shoulder_x+=step;
      right_shoulder_x-=step;*/
      left_hip_angle-=(step/2);
      left_knee_angle+=(step/1);
      torso_angle+=(step/20);
      renderRoom();
        glfwSwapBuffers(window);
    }
    for(int i=0;i<30/step;i++){
      
    /*  left_shoulder_x-=step;
      right_shoulder_x+=step;*/
      left_hip_angle+=(step/2);
      left_knee_angle-=(step/1);
      torso_angle-=(step/20);
      renderRoom();
        glfwSwapBuffers(window);
    }
    for(int i=0;i<30/step;i++){
      
      /*left_shoulder_x-=step;
      right_shoulder_x+=step;*/
      right_hip_angle-=(step/2);
      right_knee_angle+=(step/1);
      torso_angle+=(step/20);
      renderRoom();
        glfwSwapBuffers(window);
    }
    for(int i=0;i<30/step;i++){
      /*left_shoulder_x+=step;
      right_shoulder_x-=step;*/
      right_hip_angle+=(step/2);
      right_knee_angle-=(step/1);
      torso_angle-=(step/20);
      renderRoom();
        glfwSwapBuffers(window);
    }
  }
  forward=0;
  playback=false;
  // cout << transformer_position[0] << transformer_position[2] << endl;
 /* string line;
  ifstream myfile ("keyframes.txt");

  if (myfile.is_open()){
    glfwSetTime(0.00);
    while (!myfile.eof()){
      if(glfwGetTime()>1/30.0){

        myfile >> transformer_position[0] >> transformer_position[1] >> transformer_position[2];
        myfile >> up >> hand_angle >> value >> left_knee_angle >> right_knee_angle >> panel_shift;
        myfile >> panel_angle >> torso_angle >>  torso_shift_down >> cs475::toCar >> transform;

        renderRoom();
        glfwSwapBuffers(window);
        glfwSetTime(0.00); 
      } 
        glfwPollEvents();
    }
    myfile.close();
  }

  else cout << "Unable to open file"; */
  rotate_cam=false;
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


      if(cs475::transform) Transform();
      else if(cs475::playback) playBack();
      else  renderRoom();
      
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
