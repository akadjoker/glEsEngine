/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_5.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:07 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/02/15 18:08:34 by lrosa-do         ###   ########.fr       */
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
const float GRASS_WIDTH =1;
const float GRASS_HEIGHT=1;

struct iVertex
{
	   float x, y, z;
      float r,g,b,a;
      float u, v;
       iVertex()
       {

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
  int AddVertex( float x, float y, float z, float tu,float tv)
  {
    return AddVertex(iVertex(x,y,z,tu,tv));
  }
  int AddVertex( Vec3 pos,Vec2 uv)
  {
    return AddVertex(iVertex(pos.x,pos.y,pos.z,uv.x,uv.y));
  }
    void VertexNormal(int index, float x, float y ,float z)
    {
        if (index < 0 || index > vertices.size())
            return;
        //vertices[index].normal.set(x,y,z);
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
  void CreateCube()
  {
    VertexDeclaration *decl = vertexData->getVertexDeclation();
    decl->addElement(0, VF_POSITION  , VET_FLOAT3);
    decl->addElement(1, VF_COLOR     , VET_FLOAT4);
    decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);

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
  build();
  }
  void CreatePlane(float w,float d)
  {
        VertexDeclaration *decl = vertexData->getVertexDeclation();
          decl->addElement(0, VF_POSITION  , VET_FLOAT3);
          decl->addElement(1, VF_COLOR     , VET_FLOAT4);
          decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);


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

      AddTriangle(0,1,2); // front
      AddTriangle(0,2,3);
      build();
    
    }
void CreateSphere( float radius, int rings, int sectors)
{
   VertexDeclaration *decl = vertexData->getVertexDeclation();
          decl->addElement(0, VF_POSITION  , VET_FLOAT3);
          decl->addElement(1, VF_COLOR     , VET_FLOAT4);
          decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);

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
    build();
}
void AddPlane( const Vec3& center, const Vec3& right, const Vec3& up)
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
    AddVertex(v0.x, v0.y, v0.z);
    AddVertex(v1.x, v1.y, v1.z);
    AddVertex(v2.x, v2.y, v2.z);
    AddVertex(v3.x, v3.y, v3.z);

    AddTriangle(0, 1, 2);
    AddTriangle(1, 3, 2);
}

void createCylinderMesh(float radius, float length,	int tesselation, bool closeTop=true, float oblique=0.0f) 
{	
    VertexDeclaration *decl = vertexData->getVertexDeclation();
          decl->addElement(0, VF_POSITION  , VET_FLOAT3);
          decl->addElement(1, VF_COLOR     , VET_FLOAT4);
          decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);

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
Shader shader=Shader::createSolidColorTexture();

Camera camera; 
camera.SetPosition(0, 1, 10); 

IMesh grass;

VertexDeclaration *decl = grass.vertexData->getVertexDeclation();
decl->addElement(0, VF_POSITION  , VET_FLOAT3);
decl->addElement(1, VF_COLOR     , VET_FLOAT4);
decl->addElement(2, VF_TEXCOORD1 , VET_FLOAT2);

IMesh cube;
cube.CreateCube();



IMesh sphere;
sphere.CreateSphere(1,32,32);

IMesh cilinder;
cilinder.CreateCylinder(1,1,16);//createCylinderMesh(1,1,10);

IMesh plane;
plane.CreatePlane(80,80);


// int num_vertex=( (3 + 4) * (6 * 6) );
// int stride =( (3 + 4) * (6 * 6) )  * sizeof(float);
 
//  vertices.reserve(12);
//  indices.reserve(18);


for (unsigned int i = 0; i < 3; i++)  // each grass mesh consists of 3 planes
		{
			// planes intersect along the Y axis with 60 degrees between them
			float x = cos(radToDeg(i * 60)) * GRASS_WIDTH / 2;
			float z = sin(radToDeg(i * 60)) * GRASS_WIDTH / 2;

			for (unsigned int j = 0; j < 4; j++)  // each plane has 4 vertices
			{
				//iVertex& vert = vertices[i * 4 + j];
        Vec3 pos;
        Vec2 uv;
        Vec3 normal;
				pos.x = j < 2 ? -x : x;
				pos.y = j % 2 ? 0 : GRASS_HEIGHT;
				pos.z = j < 2 ? -z : z;

		
				uv.x = j < 2 ? 0 : 1;
				uv.y = 1*-j % 2;
        grass.AddVertex(pos, uv);
			}
		}

   // unsigned* faces = indices.data();

		for (unsigned int i = 0; i < 3; i++)  // each grass mesh consists of 3 planes
		{
			unsigned int off = i * 4;  // each plane consists of 2 triangles

        grass.addFace(0 +off, 3 +off, 1 +off);
        
        grass.addFace(0 +off, 2 +off, 3 +off);

    
			// *faces++ = 0 + off;
			// *faces++ = 3 + off;
			// *faces++ = 1 + off;

			// *faces++ = 0 + off;
			// *faces++ = 2 + off;
			// *faces++ = 3 + off;
		}

grass.build();

 

      
       



Texture2D texture_grass;
texture_grass.Load("assets/gras_02.png");


Texture2D texture_floor;
texture_floor.Load("assets/grass_1024.jpg");


 
   Mat4 projection = Mat4::ProjectionMatrix(45.0f,  static_cast<float>(screenWidth) / screenHeight, 0.1f, 1000.0f);
    

   glClearColor(0.1,0.1,0.3f,1.0);
   glEnable(GL_DEPTH_TEST);  
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  


  std::vector<Vec3> positions;
     for (int x = -280; x < 280; x += 10)
		{
			for (int z = -280; z < 280; z += 10)
			{
				Vec3 pos( (x/5.0f) + (GetRandomValue(-5,5)/4.0f) , 0, (z/5.0f) + (GetRandomValue(-5,5) /4.0f));
        positions.push_back(pos);
          
			}
		}

  

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

        Mat4 model= Mat4::Identity();
        shader.setMatrix4("model", model);
        texture_floor.Bind(0);

        plane.render();
		

        model=     Mat4::Translate(-1,1,0);
        shader.setMatrix4("model", model);
        texture_floor.Bind(0);
        sphere.render();
        
        model=     Mat4::Translate(1,1,0);
        shader.setMatrix4("model", model);
        texture_floor.Bind(0);
        cilinder.render();
    
		
    
       
      texture_grass.Bind(0);
   
      for (auto pos : positions)
      {

            model= Mat4::Identity();
           model = Mat4::Translate(pos.x,pos.y,pos.z);// * Mat4::Rotate(Vec3(0,1,0),radToDeg(-90));
           shader.setMatrix4("model", model);
           grass.render();
		
		}
     app.Swap();
  }
 

  
  return 0;
}