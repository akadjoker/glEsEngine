#include "glad.h"

#include "../pch.hpp"
#include "../utils.hpp"
#include "../render.hpp"
#include "../math.hpp"
#include "../camera.hpp"
#include "../core.hpp"
  
const int screenWidth = 1280;
const int screenHeight = 720;



int run_sample() 
{
App app;
app.CreateWindow(screenWidth, screenHeight, "Vertex Light");

Shader shader=Shader::createSolidColor();

 

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};         

   unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

Camera camera; 
camera.SetPosition(0, 1, 10); 
  
VertexData * grass = new VertexData();
VertexDeclaration *decl = grass->getVertexDeclation();
decl->addElement(0, VF_POSITION , VET_FLOAT3);
decl->addElement(1, VF_COLOR , VET_FLOAT3);

VertexBuffer * vertex =grass->createVertexBuffer( sizeof(float), sizeof(vertices)/6, true);


 
vertex->createBuffer(&vertices);
 



 
   Mat4 projection = Mat4::ProjectionMatrix(45.0f,  static_cast<float>(screenWidth) / screenHeight, 0.1f, 1000.0f);
    

  glClearColor(0.1,0.1,0.3f,1.0);
  glEnable(GL_DEPTH_TEST);  
  

  while (!app.ShouldClose()) 
  {
        
       float deltaTime = app.GetFrameTime();
        


        const Uint8 *keys = SDL_GetKeyboardState(NULL);

         if(keys[SDL_SCANCODE_W])
          camera.ProcessKeyboard(FORWARD, deltaTime);
        else if(keys[SDL_SCANCODE_S])
           camera.ProcessKeyboard(BACKWARD, deltaTime);
  
        if(keys[SDL_SCANCODE_A])
             camera.ProcessKeyboard(LEFT, deltaTime);
        else if(keys[SDL_SCANCODE_D])
             camera.ProcessKeyboard(RIGHT, deltaTime);
           
         
        int MouseX,MouseY;
        
        Uint32 button = SDL_GetRelativeMouseState(&MouseX, &MouseY);
        if (button & SDL_BUTTON(SDL_BUTTON_LEFT)) 
        {
          camera.ProcessMouseMovement(MouseX, -MouseY);
        } 

 
             
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        Mat4 view =camera.GetViewMatrix();
  
 
        Mat4 model= Mat4::Identity();
   
        shader.Bind();
        shader.setMatrix4("view", view);
        shader.setMatrix4("projection" ,projection);
        shader.setMatrix4("model", model);
       
        grass->Render(GL_TRIANGLES,  3);

        app.Swap();



  }

delete grass;
  
  return 0;
}