/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_6.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:07 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/02/16 11:41:32 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
      float x, y, z;
      float nx, ny, nz;
      float r,g,b,a;
      float u, v;
       iVertex()
       {

       this->x=0;
      this->y=0;
      this->z=0;

  
      this->u=0;
      this->v=0;
      this->r=1;
      this->g=1;
      this->b=1;
      this->a=1;
        
       };
    iVertex(float x, float y, float z, float tu, float tv)
		 {
      this->x=x;
      this->y=y;
      this->z=z;

  
      this->u=tu;
      this->v=tv;

      this->r=1;
      this->g=1;
      this->b=1;
      this->a=1;
     }
        iVertex(float x, float y, float z, float tu, float tv,float nx, float ny,float nz)
		 {
      this->x=x;
      this->y=y;
      this->z=z;

      this->nx=nx;
      this->ny=ny;
      this->nz=nz;
      
      this->u=tu;
      this->v=tv;

      this->r=1;
      this->g=1;
      this->b=1;
      this->a=1;
     }
        iVertex(float x, float y, float z, float tu, float tv,float nx, float ny,float nz,const Color c)
		 {
      this->x=x;
      this->y=y;
      this->z=z;

      this->nx=nx;
      this->ny=ny;
      this->nz=nz;
      
      this->u=tu;
      this->v=tv;

      this->r=c.r;
      this->g=c.g;
      this->b=c.b;
      this->a=c.a;
     }
};

struct IMesh
{
  std::vector<iVertex>         vertices;
  std::vector<unsigned int>    indices;
  VertexData *vertexData;
  
  IMesh()
  {
    vertexData = new VertexData();
  }
  ~IMesh()
  {
    delete vertexData;
  }
  void addElement(UINT index, VertexAttribute attribute, VertexAttributeType  type)
  {
    VertexDeclaration *decl = vertexData->getVertexDeclation();
    decl->addElement(index, attribute  , type);
  }
        
    
  void render()
  {
     vertexData->Render(GL_TRIANGLES,  indices.size());
  }
  void build()
  {
    VertexDeclaration *decl = vertexData->getVertexDeclation();
    VertexBuffer * vertex  =vertexData->createVertexBuffer(  decl->getSize(), vertices.size());
    IndexBuffer * indexes = vertexData->createIndexBuffer(I32BIT, indices.size() );
    vertex->createBuffer(vertices.data());
    indexes->createBuffer(indices.data()); 
   
  } 
  int AddVertex( const iVertex &v)
  {
      vertices.push_back(v);
      return (int)vertices.size()-1;
  }
  int AddVertex( float x, float y, float z)
  {
    return AddVertex(iVertex(x,y,z,0,0));
  }
    int AddVertex( float x, float y, float z,Color c)
  {
    iVertex v(x,y,z,0,0);
    
    return AddVertex(v);
  }
  int AddVertex( float x, float y, float z, float tu,float tv)
  {
    return AddVertex(iVertex(x,y,z,tu,tv));
  }
    int AddVertex( float x, float y, float z, float tu,float tv,float nx, float ny, float nz)
  {
    return AddVertex(iVertex(x,y,z,tu,tv,nx,ny,nz));
  }
     int AddVertex( float x, float y, float z, float tu,float tv,float nx, float ny, float nz,const Color c)
  {
    return AddVertex(iVertex(x,y,z,tu,tv,nx,ny,nz,c));
  }
  int AddVertex( Vec3 pos,Vec2 uv)
  {
    return AddVertex(iVertex(pos.x,pos.y,pos.z,uv.x,uv.y));
  }
    void VertexNormal(int index, float x, float y ,float z)
    {
        if (index < 0 || index > vertices.size())
            return;
        vertices[index].nx=x;
        vertices[index].ny=y;
        vertices[index].nz=z;
        
    }
    void VertexTexCoords(int index , float x, float y)
   {
        if (index < 0 || index >vertices.size())
            return;
        vertices[index].u=x;
        vertices[index].v=y;
        
    }
  int addFace(int a,int b,int c)
  {
      indices.push_back(a);
      indices.push_back(b);
      indices.push_back(c);
   
      return (int)indices.size()-1;
  }
    int AddTriangle(int a,int b,int c)
  {
      indices.push_back(a);
      indices.push_back(b);
      indices.push_back(c);
      return (int)indices.size()-1;
  }
  void CalculateNormals() 
  {
    // Limpar quaisquer normais existentes
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].nx = 0;
        vertices[i].ny = 0;
        vertices[i].nz = 0;
    }
    
    // Calcular normais para cada face do objeto
    for (int i = 0; i < indices.size(); i += 3) 
    {
        // Obter os índices dos três vértices que formam esta face
        int i1 = indices[i];
        int i2 = indices[i+1];
        int i3 = indices[i+2];
        
        // Obter as coordenadas dos vértices
        float x1 = vertices[i1].x;
        float y1 = vertices[i1].y;
        float z1 = vertices[i1].z;
        float x2 = vertices[i2].x;
        float y2 = vertices[i2].y;
        float z2 = vertices[i2].z;
        float x3 = vertices[i3].x;
        float y3 = vertices[i3].y;
        float z3 = vertices[i3].z;
        
        // Calcular dois vetores que apontam para fora do plano da face
        float v1x = x2 - x1;
        float v1y = y2 - y1;
        float v1z = z2 - z1;
        float v2x = x3 - x1;
        float v2y = y3 - y1;
        float v2z = z3 - z1;
        float nx = v1y * v2z - v1z * v2y;
        float ny = v1z * v2x - v1x * v2z;
        float nz = v1x * v2y - v1y * v2x;
        
        // Adicionar a normal calculada para os vértices que formam esta face
        vertices[i1].nx += nx;
        vertices[i1].ny += ny;
        vertices[i1].nz += nz;
        vertices[i2].nx += nx;
        vertices[i2].ny += ny;
        vertices[i2].nz += nz;
        vertices[i3].nx += nx;
        vertices[i3].ny += ny;
        vertices[i3].nz += nz;
    }
    
    // Normalizar os vetores normais dos vértices
    for (int i = 0; i < vertices.size(); i++) 
    {
        float length = sqrt(vertices[i].nx * vertices[i].nx + vertices[i].ny * vertices[i].ny + vertices[i].nz * vertices[i].nz);
        vertices[i].nx /= length;
        vertices[i].ny /= length;
        vertices[i].nz /= length;
    }
}
  void CreateCube(const Color &c)
  {


  AddVertex(-1.0,-1.0,-1.0);
  AddVertex(-1.0, 1.0,-1.0);
  AddVertex( 1.0, 1.0,-1.0);
  AddVertex( 1.0,-1.0,-1.0);

  AddVertex(-1.0,-1.0, 1.0);
  AddVertex(-1.0, 1.0, 1.0);
  AddVertex( 1.0, 1.0, 1.0);
  AddVertex( 1.0,-1.0, 1.0);

  AddVertex(-1.0,-1.0, 1.0);
  AddVertex(-1.0, 1.0, 1.0);
  AddVertex( 1.0, 1.0, 1.0);
  AddVertex( 1.0,-1.0, 1.0);

  AddVertex(-1.0,-1.0,-1.0);
  AddVertex(-1.0, 1.0,-1.0);
  AddVertex( 1.0, 1.0,-1.0);
  AddVertex( 1.0,-1.0,-1.0);

  AddVertex(-1.0,-1.0, 1.0);
  AddVertex(-1.0, 1.0, 1.0);
  AddVertex( 1.0, 1.0, 1.0);
  AddVertex( 1.0,-1.0, 1.0);

  AddVertex(-1.0,-1.0,-1.0);
  AddVertex(-1.0, 1.0,-1.0);
  AddVertex( 1.0, 1.0,-1.0);
  AddVertex( 1.0,-1.0,-1.0);

  VertexNormal(0,0.0,0.0,-1.0);
  VertexNormal(1,0.0,0.0,-1.0);
  VertexNormal(2,0.0,0.0,-1.0);
  VertexNormal(3,0.0,0.0,-1.0);

  VertexNormal(4,0.0,0.0,1.0);
  VertexNormal(5,0.0,0.0,1.0);
  VertexNormal(6,0.0,0.0,1.0);
  VertexNormal(7,0.0,0.0,1.0);

  VertexNormal(8,0.0,-1.0,0.0);
  VertexNormal(9,0.0,1.0,0.0);
  VertexNormal(10,0.0,1.0,0.0);
  VertexNormal(11,0.0,-1.0,0.0);

  VertexNormal(12,0.0,-1.0,0.0);
  VertexNormal(13,0.0,1.0,0.0);
  VertexNormal(14,0.0,1.0,0.0);
  VertexNormal(15,0.0,-1.0,0.0);

  VertexNormal(16,-1.0,0.0,0.0);
  VertexNormal(17,-1.0,0.0,0.0);
  VertexNormal(18,1.0,0.0,0.0);
  VertexNormal(19,1.0,0.0,0.0);

  VertexNormal(20,-1.0,0.0,0.0);
  VertexNormal(21,-1.0,0.0,0.0);
  VertexNormal(22,1.0,0.0,0.0);
  VertexNormal(23,1.0,0.0,0.0);

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

 
   for (int i=0;i<vertices.size();i++)
  {
   iVertex v = vertices[i];
   v.r=c.r;
   v.g=c.g;
   v.b=c.b;
   v.a=c.a;
   vertices[i]=v;
  }
  

  AddTriangle(0,1,2); // front
  AddTriangle(0,2,3);
  AddTriangle(6,5,4); // back
  AddTriangle(7,6,4);
  AddTriangle(6+8,5+8,1+8); // top
  AddTriangle(2+8,6+8,1+8);
  AddTriangle(0+8,4+8,7+8); // bottom
  AddTriangle(0+8,7+8,3+8);
  AddTriangle(6+16,2+16,3+16); // right
  AddTriangle(7+16,6+16,3+16);
  AddTriangle(0+16,1+16,5+16); // left
  AddTriangle(0+16,5+16,4+16);
  CalculateNormals();
  build();
  }
  void CreatePlane(float w,float d,const Color &c)
  {



      AddVertex(-w,0.0,-d);
      AddVertex(-w,0.0, d);
      AddVertex( w,0.0, d);
      AddVertex( w,0.0,-d);


      VertexNormal(0,0.0,1.0,0.0);
      VertexNormal(1,0.0,1.0,0.0);
      VertexNormal(2,0.0,1.0,0.0);
      VertexNormal(3,0.0,1.0,0.0);

      VertexTexCoords(0,0.0,1.0);
      VertexTexCoords(1,0.0,0.0);
      VertexTexCoords(2,1.0,0.0);
      VertexTexCoords(3,1.0,1.0);


   for (int i=0;i<vertices.size();i++)
  {
   iVertex v = vertices[i];
   v.r=c.r;
   v.g=c.g;
   v.b=c.b;
   v.a=c.a;
   vertices[i]=v;
  }
  
      AddTriangle(0,1,2); // front
      AddTriangle(0,2,3);
    
      build();
    
    }
void CreateSphere( float radius, int rings, int sectors, const Color &c)
{



    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);

    for (int r = 0; r < rings; r++) {
        for (int s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            float const u = s * S;
            float const v = r * R;

            AddVertex(radius * x, radius * y, radius * z, u, v);
        }
    }

    for (int r = 0; r < rings - 1; r++) {
        for (int s = 0; s < sectors - 1; s++) {
            int const a = r * sectors + s;
            int const b = r * sectors + (s + 1);
            int const c = (r + 1) * sectors + (s + 1);
            int const d = (r + 1) * sectors + s;

            AddTriangle(a, d, c);
            AddTriangle(a, c, b);
        }
    }

   for (int i=0;i<vertices.size();i++)
  {
   iVertex v = vertices[i];
   v.r=c.r;
   v.g=c.g;
   v.b=c.b;
   v.a=c.a;
   vertices[i]=v;
  }
    CalculateNormals();
    build();
}
void AddPlane( const Vec3& center, const Vec3& right, const Vec3& up,const Color &col,const Vec3& n)
{
    // Calcula os vértices do plano com base no centro, right e up
    Vec3 normal = Vec3::Cross(right, up);
    Vec3 halfRight = right * 0.5f;
    Vec3 halfUp = up * 0.5f;

    Vec3 v0 = center - halfRight - halfUp;
    Vec3 v1 = center + halfRight - halfUp;
    Vec3 v2 = center - halfRight + halfUp;
    Vec3 v3 = center + halfRight + halfUp;

    // Adiciona os vértices e triângulos do plano
  // n.normalize();
    
   int a= AddVertex(v0.x, v0.y, v0.z,0.0,1.0,n.x,n.y,n.z,col);
   int b= AddVertex(v1.x, v1.y, v1.z,0.0,0.0,n.x,n.y,n.z,col);
   int c= AddVertex(v2.x, v2.y, v2.z,1.0,0.0,n.x,n.y,n.z,col);
   int d= AddVertex(v3.x, v3.y, v3.z,1.0,1.0,n.x,n.y,n.z,col);


  

    AddTriangle(a, b, c);
    AddTriangle(b, d, c);
    
}

void createCylinderMesh(float radius, float length,	int tesselation,const Color &c, bool closeTop=true, float oblique=0.0f) 
{	
	const float recTesselation = reciprocal((float)tesselation);
	const float recTesselationHalf = recTesselation * 0.5f;
	const float angleStep = (PI * 2.f ) * recTesselation;
	const float angleStepHalf = angleStep*0.5f;

	int i;
	iVertex v;


	float tcx = 0.f;
	for ( i = 0; i <= tesselation; ++i )
	{
		const float angle = angleStep * i;
		v.x = radius * cosf(angle);
		v.y = 0.f;
		v.z = radius * sinf(angle);

		v.u=tcx;
		v.v=0.f;
		vertices.push_back(v);

		v.x += oblique;
		v.y = length;
	
		
		v.v=1.0f;
		vertices.push_back(v);

		v.x = radius * cosf(angle + angleStepHalf);
		v.y = 0.f;
		v.z = radius * sinf(angle + angleStepHalf);

	
		v.u=tcx+recTesselationHalf;
		v.v=0.f;
		vertices.push_back(v);

		v.x += oblique;
		v.y = length;

		v.v=1.f;
		vertices.push_back(v);
		tcx += recTesselation;
	}

	// indices for the main hull part
	const int nonWrappedSize = tesselation* 4;
	for (i=0; i != nonWrappedSize; i += 2)
	{
		indices.push_back(i + 2);
		indices.push_back(i + 0);
		indices.push_back(i + 1);

		indices.push_back(i + 2);
		indices.push_back(i + 1);
		indices.push_back(i + 3);
	}

	// two closing quads between end and start
	indices.push_back(0);
	indices.push_back(i + 0);
	indices.push_back(i + 1);

	indices.push_back(0);
	indices.push_back(i + 1);
	indices.push_back(1);

	// close down
	v.x = 0.f;
	v.y = 0.f;
	v.z = 0.f;

	v.u = 1.f;
	v.v = 1.f;
	vertices.push_back(v);

	int index = vertices.size() - 1;

	for ( i = 0; i != nonWrappedSize; i += 2 )
	{
		indices.push_back(index);
		indices.push_back(i + 0);
		indices.push_back(i + 2);
	}

	indices.push_back(index);
	indices.push_back(i + 0);
	indices.push_back(0);

	if (closeTop)
	{
		// close top
		v.x = oblique;
		v.y = length;
		v.z = 0.f;
		v.u = 0.f;
		v.v = 0.f;
	  vertices.push_back(v);

		index = vertices.size() - 1;

		for ( i = 0; i != nonWrappedSize; i += 2 )
		{
		  indices.push_back(i + 1);
			indices.push_back(index);
			indices.push_back(i + 3);
		}

		indices.push_back(i + 1);
		indices.push_back(index);
		indices.push_back(1);
	}

   for (int i=0;i<vertices.size();i++)
  {
   iVertex v = vertices[i];
   v.r=c.r;
   v.g=c.g;
   v.b=c.b;
   v.a=c.a;
   vertices[i]=v;
  }
  CalculateNormals();
  
	build();


}
};


int GetRandomValue(int min, int max)
{
    if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }  

    return (rand()%(abs(max - min) + 1) + min);
}
   
int run_sample()   
{ 
App app;
app.CreateWindow(screenWidth, screenHeight, "Vertex Texture Colored");

//Shader shader=Shader::createSolidColor();
Shader shader=Shader::createSolidAmbient();
  
//Shader shader=Shader::createSolidColorTexture();

Camera camera; 
camera.SetPosition(0, 1, 10);  

Texture2D texture_floor(64,64);
//texture_floor.Load("assets/grass_1024.jpg");





IMesh sphere;

sphere.addElement(0, VF_POSITION  , VET_FLOAT3);
sphere.addElement(1, VF_COLOR     , VET_FLOAT4);
sphere.addElement(3, VF_NORMAL    , VET_FLOAT3);
sphere.addElement(4, VF_TEXCOORD1 , VET_FLOAT2);
sphere.CreateSphere(1,32,32,Color(1,1,0));

IMesh sphere2;

sphere2.addElement(0, VF_POSITION  , VET_FLOAT3);
sphere2.addElement(1, VF_COLOR     , VET_FLOAT4);
sphere2.addElement(3, VF_NORMAL    , VET_FLOAT3);
sphere2.addElement(4, VF_TEXCOORD1 , VET_FLOAT2);
sphere2.CreateSphere(1,32,32,Color(1,0,1));


IMesh cilinder;
cilinder.addElement(0, VF_POSITION  , VET_FLOAT3);
cilinder.addElement(1, VF_COLOR     , VET_FLOAT4);
cilinder.addElement(3, VF_NORMAL    , VET_FLOAT3);
cilinder.addElement(4, VF_TEXCOORD1 , VET_FLOAT2);
cilinder.createCylinderMesh(1,1,10,Color(0,0.8,0));

IMesh plane;
plane.addElement(0, VF_POSITION  , VET_FLOAT3);
plane.addElement(1, VF_COLOR     , VET_FLOAT4);
plane.addElement(3, VF_NORMAL    , VET_FLOAT3);
plane.addElement(4, VF_TEXCOORD1 , VET_FLOAT2);
plane.CreatePlane(80,80,Color(0,0.6,0));



IMesh walls;
walls.addElement(0, VF_POSITION  , VET_FLOAT3);
walls.addElement(1, VF_COLOR     , VET_FLOAT4);
walls.addElement(3, VF_NORMAL    , VET_FLOAT3);
walls.addElement(4, VF_TEXCOORD1 , VET_FLOAT2);
//plane.CreatePlane(1,1,Color(0,0.4,0));
walls.AddPlane(Vec3(14, 0, 0),  Vec3(0, 0, 50), Vec3(0, 50, 0)  ,Color(0,0.4,0),Vec3(1,0,0));
walls.AddPlane(Vec3(-14, 0, 0), Vec3(0, 0, -50), Vec3(0, 50, 0) ,Color(0,0.4,0),Vec3(1,0,0));
walls.AddPlane(Vec3(0, 0, -20), Vec3(50, 0, 0), Vec3(0, 50, 0)  ,Color(0,0.4,0),Vec3(0,0,1));
walls.build();


  
 
   Mat4 projection = Mat4::ProjectionMatrix(45.0f,  static_cast<float>(screenWidth) / screenHeight, 0.1f, 1000.0f);
    

   glClearColor(0.1,0.1,0.3f,1.0);
   glEnable(GL_DEPTH_TEST);  
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  



  

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
  
  
      
       
       shader.Bind();
       shader.setMatrix4("view", view);
       shader.setMatrix4("projection" ,projection);
       shader.setVector3("viewPos" ,camera.Position);
       

        Mat4 model= Mat4::Identity();
        shader.setMatrix4("model", model);

        plane.render();
		   walls.render();
       


        model= Mat4::Identity();
        model=   Mat4::Translate(4.5,5,0) * Mat4::Rotate(Vec3(0,0,1),degToRad(90)) * Mat4::Scale(1,12,1);
        shader.setMatrix4("model", model);
        cilinder.render();
        
        
        model= Mat4::Identity();
        model=   Mat4::Translate(-8,0,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1,6,1);
        shader.setMatrix4("model", model);
        cilinder.render();
		
      
        model= Mat4::Identity();
        model=   Mat4::Translate(5,0,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1,6,1);
        shader.setMatrix4("model", model);
        cilinder.render();
		

        model= Mat4::Identity();
        model=   Mat4::Translate(5,4.9,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1.4,1.2,1.2);
        shader.setMatrix4("model", model);
        sphere.render();

        model= Mat4::Identity();
        model=   Mat4::Translate(-8,4.9,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1.4,1.2,1.2);
        shader.setMatrix4("model", model);
        sphere.render();


        model= Mat4::Identity();
        model=   Mat4::Translate(5,0.3,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1.4,1.2,1.2);
        shader.setMatrix4("model", model);
        sphere2.render();

        model= Mat4::Identity();
        model=   Mat4::Translate(-8,0.3,0) * Mat4::Rotate(Vec3(1,0,0),degToRad(0)) *Mat4::Scale(1.4,1.2,1.2);
        shader.setMatrix4("model", model);
        sphere2.render();
        
 
     app.Swap();
  } 
 

  std::cout<<"Exit"<<std::endl;
  return 0;
}