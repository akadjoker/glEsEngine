#include "glad.h"

#include "../pch.hpp"
#include "../utils.hpp"
#include "../render.hpp"
#include "../math.hpp"
#include "../camera.hpp"
#include "../core.hpp"
  
const int screenWidth = 1280;
const int screenHeight = 720;


struct iVertex
{
	  Vec3   pos;
    Color  color;
 	  Vec2   coord;
    Vec3 normal;
	iVertex() {}
	iVertex(float x, float y, float z, float nx, float ny, float nz, Color c, float tu, float tv)
		 {
      this->pos.x=x;
      this->pos.y=y;
      this->pos.z=z;
      this->color.r=c.r;
      this->color.g=c.g;
      this->color.b=c.b;
      this->color.a=c.a;
     }

	iVertex(const Vec3& pos, const Vec3& normal,  Color c, const Vec2& tcoords)
			 {
      this->pos=pos;
      this->color.r=c.r;
      this->color.g=c.g;
      this->color.b=c.b;
      this->color.a=c.a;
     }
};



 std::vector<iVertex> vertices;
 std::vector<unsigned int>    indices;

int addVertex( const iVertex &v)
{
    vertices.push_back(v);
    return (int)vertices.size()-1;
}
int AddVertex(float x, float y, float z)
  {
      Color c(1,1,1,1);
      addVertex(iVertex(x,y,z,0,0,0,c,0.0,0.0));
      return (int)vertices.size() -1;
  }
  int AddVertex(float x, float y, float z,float r, float g, float b, float a)
  {
      Color c(r,g,b,a);
      addVertex(iVertex(x,y,z,0,0,0,c,0.0,0.0));
      return (int)vertices.size() -1;
  }
  
int addFace(int a,int b,int c)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
    return (int)indices.size()-1;
}
void VertexTexCoords(int index, float x, float y)
{
  vertices[index].coord.x=x;
  vertices[index].coord.y=y;
  
}

void createCube(float w, float h, float d)
{

  

  float x = w / 2.0f;
  float y = h / 2.0f;
  float z = d / 2.0f;


AddVertex(-x,-y,-z );
AddVertex(-x, y,-z );
AddVertex( x, y,-z );
AddVertex( x,-y,-z );

AddVertex(-x,-y, z );
AddVertex(-x, y, z );
AddVertex( x, y, z );
AddVertex( x,-y, z );

AddVertex(-x,-y, z );
AddVertex(-x, y, z );
AddVertex( x, y, z );
AddVertex( x,-y, z );

AddVertex(-x,-y,-z );
AddVertex(-x, y,-z );
AddVertex( x, y,-z );
AddVertex( x,-y,-z );

AddVertex(-x,-y, z );
AddVertex(-x, y, z );
AddVertex( x, y, z );
AddVertex( x,-y, z );

AddVertex(-x,-y,-z );
AddVertex(-x, y,-z );
AddVertex( x, y,-z );
AddVertex( x,-y,-z );

VertexTexCoords(0,0.0,1.0);
VertexTexCoords(1,0.0,0.0);
VertexTexCoords(2,1.0,0.0);
VertexTexCoords(3,1.0,1.0);

VertexTexCoords(4,1.0,1.0);
VertexTexCoords(5,1.0,0.0);
VertexTexCoords(6,0.0,0.0);
VertexTexCoords(7,0.0,1.0);

VertexTexCoords(8,0.0,1.0);
VertexTexCoords(9,0.0,0.0);
VertexTexCoords(10,1.0,0.0);
VertexTexCoords(11,1.0,1.0);

VertexTexCoords(12,0.0,0.0);
VertexTexCoords(13,0.0,1.0);
VertexTexCoords(14,1.0,1.0);
VertexTexCoords(15,1.0,0.0);

VertexTexCoords(16,0.0,1.0);
VertexTexCoords(17,0.0,0.0);
VertexTexCoords(18,1.0,0.0);
VertexTexCoords(19,1.0,1.0);

VertexTexCoords(20,1.0,1.0);
VertexTexCoords(21,1.0,0.0);
VertexTexCoords(22,0.0,0.0);
VertexTexCoords(23,0.0,1.0);

addFace(0,1,2); // front
addFace(0,2,3);
addFace(6,5,4); // back
addFace(7,6,4);
addFace(6+8,5+8,1+8); // top
addFace(2+8,6+8,1+8);
addFace(0+8,4+8,7+8); // bottom
addFace(0+8,7+8,3+8);
addFace(6+16,2+16,3+16); // right
addFace(7+16,6+16,3+16);
addFace(0+16,1+16,5+16); // left
addFace(0+16,5+16,4+16);
}
 
 

int run_sample() 
{
App app;
app.CreateWindow(screenWidth, screenHeight, "Vertex Texture Colored");

//Shader shader=Shader::createSolidColor();
Shader shader=Shader::createSolidColorTexture();


createCube(1,1,1);  
 
Camera camera; 
camera.SetPosition(0, 1, 10); 
     
VertexData * grass = new VertexData();
VertexDeclaration *decl = grass->getVertexDeclation();
decl->addElement(0, VF_POSITION  , VET_FLOAT3);
decl->addElement(1, VF_COLOR     , VET_FLOAT4);
decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);
decl->addElement(3, VF_NORMAL    , VET_FLOAT3);

// int num_vertex=( (3 + 4) * (6 * 6) );
// int stride =( (3 + 4) * (6 * 6) )  * sizeof(float);
 

VertexBuffer * vertex =grass->createVertexBuffer(  decl->getSize(), vertices.size(), true);
IndexBuffer * indexes = grass->createIndexBuffer(I32BIT, indices.size() );


vertex->createBuffer(vertices.data());
indexes->createBuffer(indices.data()); 


 

      
       



Texture2D texture;
texture.Load("assets/container2.png");

 
   Mat4 projection = Mat4::ProjectionMatrix(45.0f,  static_cast<float>(screenWidth) / screenHeight, 0.1f, 1000.0f);
    

   glClearColor(0.1,0.1,0.3f,1.0);
   glEnable(GL_DEPTH_TEST);  
  

  while (!app.ShouldClose()) 
  {
       
       float deltaTime =  app.GetFrameTime();
        
 

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
        texture.Bind(0);
   
       shader.Bind();
       shader.setMatrix4("view", view);
       shader.setMatrix4("projection" ,projection);
       shader.setMatrix4("model", model);

      grass->Render(GL_TRIANGLES,  indices.size());

  

      model= Mat4::Identity();
      model = Mat4::Translate(-2.5,0,0);  
      shader.setMatrix4("model", model);
      grass->Render(GL_TRIANGLES,  indices.size());
    
     
         app.Swap();



  }
 
    
delete grass;
  
  return 0;
}