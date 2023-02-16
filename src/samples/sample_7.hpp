/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_7.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:07 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/02/16 20:22:27 by lrosa-do         ###   ########.fr       */
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

struct Vertex
{
  //ordem IMPORTA = SHADER = Elements
      Vec3  pos;
      Color color;
      Vec2  uv;
      Vec3  normal;
    
    
      Vertex()
      {

      };
     Vertex(float x, float y, float z)
		 {
          pos.set(x,y,z);
     }
     Vertex(const Vec3 &v)
		 {
          pos.set(v.x, v.y, v.z);
     }
     Vertex(float x, float y, float z,const Color &c)
		 {
        pos.set(x,y,z);
        color.set(c);
     }
     Vertex(float x, float y, float z, float tu, float tv)
		 {
        pos.set(x,y,z);
        uv.set(tu,tv);
      
     }
      Vertex(float x, float y, float z, float tu, float tv,const Color &c)
		 {
        pos.set(x,y,z);
        uv.set(tu,tv);
        color.set(c);
     }
     Vertex(float x, float y, float z, float tu, float tv,float nx, float ny,float nz)
		 {
        pos.set(x,y,z);
        uv.set(tu,tv);
        normal.set(nx,ny,nz);
     }
     Vertex(float x, float y, float z, float tu, float tv,float nx, float ny,float nz,const Color c)
		 {   
        pos.set(x,y,z);
        uv.set(tu,tv);
        normal.set(nx,ny,nz);
        color.set(c);
     }
};

class Surface
{
  private:
  std::vector<Vertex>         vertices;
  std::vector<unsigned int>    indices;
  VertexData *vertexData;
  
  public:
  Surface()
  {
    vertexData = new VertexData();
  }
  ~Surface()
  {
    delete vertexData;
  }
  void addElement(UINT index, VertexAttribute attribute, VertexAttributeType  type)
  {
    VertexDeclaration *decl = vertexData->getVertexDeclation();
    decl->addElement(index, attribute  , type);
  }
  void setElements()
  {
    addElement(0, VF_POSITION  , VET_FLOAT3);
    addElement(1, VF_COLOR     , VET_FLOAT4);
    addElement(2, VF_TEXCOORD1 , VET_FLOAT2);
    addElement(3, VF_NORMAL    , VET_FLOAT3);


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
  int AddVertex( const Vertex &v)
  {
      vertices.push_back(v);
      return (int)vertices.size()-1;
  }
  int AddVertex( float x, float y, float z)
  {
    return AddVertex(Vertex(x,y,z));
  }
    int AddVertex( float x, float y, float z,Color c)
  {
    Vertex v(x,y,z,c);
    
    return AddVertex(v);
  }
  int AddVertex( float x, float y, float z, float tu,float tv)
  {
    return AddVertex(Vertex(x,y,z,tu,tv));
  }
    int AddVertex( float x, float y, float z, float tu,float tv,const Color &c)
  {
    return AddVertex(Vertex(x,y,z,tu,tv,c));
  }
    int AddVertex( float x, float y, float z, float tu,float tv,float nx, float ny, float nz)
  {
    return AddVertex(Vertex(x,y,z,tu,tv,nx,ny,nz));
  }
     int AddVertex( float x, float y, float z, float tu,float tv,float nx, float ny, float nz,const Color c)
  {
    return AddVertex(Vertex(x,y,z,tu,tv,nx,ny,nz,c));
  }
  int AddVertex( const Vec3 &pos, const Vec2 &uv)
  {
    return AddVertex(Vertex(pos.x,pos.y,pos.z,uv.x,uv.y));
  }
    int AddVertex( const Vec3 &pos, const Vec2 &uv, const Vec3 &n)
  {
    return AddVertex(Vertex(pos.x,pos.y,pos.z,uv.x,uv.y,n.x,n.y,n.z));
  }
    int AddVertex( const Vec3 &pos, const Vec2 &uv, const Vec3 &n, const Color &c)
  {
    return AddVertex(Vertex(pos.x,pos.y,pos.z,uv.x,uv.y,n.x,n.y,n.z,c));
  }
   void VertexColor(int index, float r, float g ,float b,float a=1.0f)
    {
        if (index < 0 || index > (int)vertices.size())
            return;
        vertices[index].color.set(r,g,b,a);
    }
   void VertexColor(int index, const Color &c)
    {
        vertices[index].color.set(c);
    }
  
    void VertexNormal(int index, float x, float y ,float z)
    {
        if (index < 0 || index > (int)vertices.size())
            return;
        vertices[index].normal.set(x,y,z);
    }
  
   void VertexTexCoords(int index , float x, float y)
   {
        if (index < 0 || index > (int)vertices.size())
            return;
        vertices[index].uv.set(x,y);;
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
  void UpdateNormals() 
  {
    // Limpar quaisquer normais existentes
    for (int i = 0; i < (int)vertices.size(); i++) 
    {
        vertices[i].normal.x = 0.0f;
        vertices[i].normal.y = 0.0f;
        vertices[i].normal.z = 0.0f;
    }
    
    // Calcular normais para cada face do objeto
    for (int i = 0; i <(int) indices.size(); i += 3) 
    {
        // Obter os índices dos três vértices que formam esta face
        int i1 = indices[i];
        int i2 = indices[i+1];
        int i3 = indices[i+2];
        
        // Obter as coordenadas dos vértices
        float x1 = vertices[i1].pos.x;
        float y1 = vertices[i1].pos.y;
        float z1 = vertices[i1].pos.z;
        float x2 = vertices[i2].pos.x;
        float y2 = vertices[i2].pos.y;
        float z2 = vertices[i2].pos.z;
        float x3 = vertices[i3].pos.x;
        float y3 = vertices[i3].pos.y;
        float z3 = vertices[i3].pos.z;
        
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
        vertices[i1].normal.x += nx;
        vertices[i1].normal.y += ny;
        vertices[i1].normal.z += nz;
        vertices[i2].normal.x += nx;
        vertices[i2].normal.y += ny;
        vertices[i2].normal.z += nz;
        vertices[i3].normal.x += nx;
        vertices[i3].normal.y += ny;
        vertices[i3].normal.z += nz;
    }
    
    // Normalizar os vetores normais dos vértices
    for (int i = 0; i < (int)vertices.size(); i++) 
    {
        float length = sqrt(
        vertices[i].normal.x * vertices[i].normal.x + 
        vertices[i].normal.y * vertices[i].normal.y +
        vertices[i].normal.z * vertices[i].normal.z);
        vertices[i].normal.x /= length;
        vertices[i].normal.y /= length;
        vertices[i].normal.z /= length;
      
    }
}
void SetVertexColor(const Color &c)
{
      for (int i = 0; i < (int)vertices.size(); i++) 
    {
        vertices[i].color.set(c);
    }
}
 
};

class Mesh
{
  public:
    Mesh()
    {
      
    }
    ~Mesh()
    { 
           Clear();
    }
    Surface *CreateSurface()
    {
      Surface *surf = new Surface();
      surfaces.push_back(surf);
      return surf;
    } 
    void Clear()
    {
       for (int i = 0; i <(int) surfaces.size(); i++) 
            {
                delete surfaces[i];
            }
            surfaces.clear();
    }
      void Build()
    {
          for (int i = 0; i <(int) surfaces.size(); i++) 
        {
            Surface *surf = surfaces[i];
            surf->build();
        }
    }
     void UpdateNormals()
    {
          for (int i = 0; i <(int) surfaces.size(); i++) 
        {
            Surface *surf = surfaces[i];
            surf->UpdateNormals();
        }
    }
    void Render()
      {
            for (int i = 0; i <(int) surfaces.size(); i++) 
          {
              Surface *surf = surfaces[i];
              surf->render();
          }
      }
    static Mesh *CreatePlane(float w, float d,const Color &c)
    {

      Mesh* mesh=new Mesh();

      Surface* surf=mesh->CreateSurface();
      surf->setElements();

      surf->AddVertex(-w/2.0f,0.0,-d/2.0f,c);
      surf->AddVertex(-w/2.0f,0.0, d/2.0f,c);
      surf->AddVertex( w/2.0f,0.0, d/2.0f,c);
      surf->AddVertex( w/2.0f,0.0,-d/2.0f,c);


      surf->VertexNormal(0,0.0,1.0,0.0);
      surf->VertexNormal(1,0.0,1.0,0.0);
      surf->VertexNormal(2,0.0,1.0,0.0);
      surf->VertexNormal(3,0.0,1.0,0.0);

      surf->VertexTexCoords(0,0.0,1.0);
      surf->VertexTexCoords(1,0.0,0.0);
      surf->VertexTexCoords(2,1.0,0.0);
      surf->VertexTexCoords(3,1.0,1.0);
      surf->AddTriangle(0,1,2); // front
      surf->AddTriangle(0,2,3);
      
      mesh->Build();

      return mesh;

    }

static Mesh* CreateCone(const Color &c,	float height=1.0f,int segments=8,bool solid=true)
{

	int top=0,br=0,bl=0; // side of cone
	int bs0=0,bs1=0,newbs=0; // bottom side vertices

	if(segments<3 || segments>100) return NULL;

  Mesh* mesh=new Mesh();
  Surface* thissurf=mesh->CreateSurface();
  thissurf->setElements();

  
	Surface* thissidesurf=NULL;
	if(solid)
  {
		thissidesurf=mesh->CreateSurface();
    thissidesurf->setElements();
	}
	float div=float(360.0f/segments);


	float upos=1.0f;
	float udiv=float(1.0f/(segments));
	float RotAngle=90.0f;

	// first side
	float XPos=-cosdeg(RotAngle);
	float ZPos=sindeg(RotAngle);

	top=thissurf->AddVertex(0.0f,height,0.0f,upos-(udiv/2.0f),0.0f,c);
	br=thissurf->AddVertex(XPos,-height,ZPos,upos,1.f,c);

	// 2nd tex coord set
	thissurf->VertexTexCoords(top,upos-(udiv/2.0f),0.0f);
	thissurf->VertexTexCoords(br,upos,1.0f);

	if(solid==true) bs0=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
	if(solid==true) thissidesurf->VertexTexCoords(bs0,XPos/2.0f+0.5f,ZPos/2.0f+0.5f); // 2nd tex coord set

	RotAngle=RotAngle+div;

	XPos=-cosdeg(RotAngle);
	ZPos=sindeg(RotAngle);

	bl=thissurf->AddVertex(XPos,-height,ZPos,upos-udiv,1.0f,c);
	thissurf->VertexTexCoords(bl,upos-udiv,1.0f); // 2nd tex coord set

	if(solid==true) bs1=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
	if(solid==true) thissidesurf->VertexTexCoords(bs1,XPos/2.0f+0.5f,ZPos/2.0f+0.5f); // 2nd tex coord set

	thissurf->AddTriangle(bl,top,br);

	// rest of sides
	for(int i=1;i<=(segments-1);i++)
  {
		br=bl;
		upos=upos-udiv;
		top=thissurf->AddVertex(0.0,height,0.0f,upos-(udiv/2.0f),0.0f,c);
		thissurf->VertexTexCoords(top,upos-(udiv/2.0f),0.0f); // 2nd tex coord set

		RotAngle=RotAngle+div;

		XPos=-cosdeg(RotAngle);
		ZPos=sindeg(RotAngle);

		bl=thissurf->AddVertex(XPos,-height,ZPos,upos-udiv,1.0f,c);
		thissurf->VertexTexCoords(bl,upos-udiv,1.0f); // 2nd tex coord set

		if(solid==true) newbs=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
		if(solid==true) thissidesurf->VertexTexCoords(newbs,XPos/2.0f+0.5f,ZPos/2.0f+0.5f); // 2nd tex coord set

		thissurf->AddTriangle(bl,top,br);

		if(solid)
    {
			thissidesurf->AddTriangle(newbs,bs1,bs0);
      thissidesurf->UpdateNormals();
      thissidesurf->build();
      

			if(i<(segments-1))
      {
				bs1=newbs;
			}
		}
	}

  mesh->UpdateNormals();
	mesh->Build();
	return mesh;

}

static Mesh* CreateCylinder(const Color &c,float height=1.0f, int verticalsegments=12,bool solid=true)
{

	int ringsegments=0; // default?

	int tr=0,tl=0,br=0,bl=0;// 		side of cylinder
	int ts0=0,ts1=0,newts=0;// 	top side vertexs
	int bs0=0,bs1=0,newbs=0;// 	bottom side vertexs
	if(verticalsegments<3 || verticalsegments>100) return NULL;
	if(ringsegments<0 || ringsegments>100) return NULL;

      Mesh* mesh=new Mesh();
      Surface* thissurf=mesh->CreateSurface();
      thissurf->setElements();
	    Surface* thissidesurf=NULL;
	if(solid==true)
  {
		thissidesurf=mesh->CreateSurface();
    thissidesurf->setElements();
	}
	float div=float(360.0f/(verticalsegments));


	float ringSegmentHeight=(height*2.0)/(ringsegments+1);
	float upos=1.0f;
	float udiv=float(1.0f/(verticalsegments));
	float vdiv=float(1.0f/(ringsegments+1));

	float SideRotAngle=90.0f;

	// re-diminsion arrays to hold needed memory.
	// this is used just for helping to build the ring segments...

	int* tRing=new int[verticalsegments+1];
	int* bRing=new int[verticalsegments+1];

	// render end caps if solid
	if(solid==true)
  {

		float XPos=-cosdeg(SideRotAngle);
		float ZPos=sindeg(SideRotAngle);

		ts0=thissidesurf->AddVertex(XPos,height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
		bs0=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);

		// 2nd tex coord set
		thissidesurf->VertexTexCoords(ts0,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);
		thissidesurf->VertexTexCoords(bs0,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);

		SideRotAngle=SideRotAngle+div;

		XPos=-cosdeg(SideRotAngle);
		ZPos=sindeg(SideRotAngle);

		ts1=thissidesurf->AddVertex(XPos,height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
		bs1=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);

		// 2nd tex coord set
		thissidesurf->VertexTexCoords(ts1,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);
		thissidesurf->VertexTexCoords(bs1,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);

		for(int i=1;i<=verticalsegments-2;i++)
    {
			SideRotAngle=SideRotAngle+div;

			XPos=-cosdeg(SideRotAngle);
			ZPos=sindeg(SideRotAngle);

			newts=thissidesurf->AddVertex(XPos,height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);
			newbs=thissidesurf->AddVertex(XPos,-height,ZPos,XPos/2.0f+0.5f,ZPos/2.0f+0.5f,c);

			// 2nd tex coord set
			thissidesurf->VertexTexCoords(newts,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);
			thissidesurf->VertexTexCoords(newbs,XPos/2.0f+0.5f,ZPos/2.0f+0.5f);

			thissidesurf->AddTriangle(ts0,ts1,newts);
			thissidesurf->AddTriangle(newbs,bs1,bs0);

			if(i<(verticalsegments-2))
      {
				ts1=newts;
				bs1=newbs;
			}

		}
	}

	// -----------------------
	// middle part of cylinder
	float thisHeight=height;

	// top ring first
	SideRotAngle=90.0f;
	float XPos=-cosdeg(SideRotAngle);
	float ZPos=sindeg(SideRotAngle);
	float thisUPos=upos;
	float thisVPos=0.0f;
	tRing[0]=thissurf->AddVertex(XPos,thisHeight,ZPos,thisUPos,thisVPos,c);
	thissurf->VertexTexCoords(tRing[0],thisUPos,thisVPos); // 2nd tex coord set
	for(int i=0;i<=verticalsegments-1;i++)
  {
		SideRotAngle=SideRotAngle+div;
		XPos=-cosdeg(SideRotAngle);
		ZPos=sindeg(SideRotAngle);
		thisUPos=thisUPos-udiv;
		tRing[i+1]=thissurf->AddVertex(XPos,thisHeight,ZPos,thisUPos,thisVPos,c);
		thissurf->VertexTexCoords(tRing[i+1],thisUPos,thisVPos); // 2nd tex coord set
	}

	for(int ring=0;ring<=ringsegments;ring++)
  {

		// decrement vertical segment
		thisHeight=thisHeight-ringSegmentHeight;

		// now bottom ring
		SideRotAngle=90;
		XPos=-cosdeg(SideRotAngle);
		ZPos=sindeg(SideRotAngle);
		thisUPos=upos;
		thisVPos=thisVPos+vdiv;
		bRing[0]=thissurf->AddVertex(XPos,thisHeight,ZPos,thisUPos,thisVPos,c);
		thissurf->VertexTexCoords(bRing[0],thisUPos,thisVPos); // 2nd tex coord set
		for(int i=0;i<=verticalsegments-1;i++)
    {
			SideRotAngle=SideRotAngle+div;
			XPos=-cosdeg(SideRotAngle);
			ZPos=sindeg(SideRotAngle);
			thisUPos=thisUPos-udiv;
			bRing[i+1]=thissurf->AddVertex(XPos,thisHeight,ZPos,thisUPos,thisVPos,c);
			thissurf->VertexTexCoords(bRing[i+1],thisUPos,thisVPos); // 2nd tex coord set
		}

		// Fill in ring segment sides with triangles
		for(int v=1;v<=verticalsegments;v++)
    {
			tl=tRing[v];
			tr=tRing[v-1];
			bl=bRing[v];
			br=bRing[v-1];

			thissurf->AddTriangle(tl,tr,br);
			thissurf->AddTriangle(bl,tl,br);
		}

		// make bottom ring segment the top ring segment for the next loop.
		for(int v=0;v<=verticalsegments;v++)
    {
			tRing[v]=bRing[v];
		}
	}

	delete [] tRing;
	delete [] bRing;

	
  mesh->UpdateNormals();
	mesh->Build();
	
  
	return mesh;

}
  static Mesh* CreateCube(float w, float h, float d,const Color &c)
  {

   Mesh* mesh=new Mesh();

    Surface* surf=mesh->CreateSurface();
    surf->setElements();

  
float x = (w / 2.0f) +0.5f;
float y = (h / 2.0f) +0.5f;
float z = (d / 2.0f) +0.5f;
surf->AddVertex(-x,-y,-z, c);
surf->AddVertex(-x, y,-z, c);
surf->AddVertex( x, y,-z, c);
surf->AddVertex( x,-y,-z, c);

surf->AddVertex(-x,-y, z, c);
surf->AddVertex(-x, y, z, c);
surf->AddVertex( x, y, z, c);
surf->AddVertex( x,-y, z, c);

surf->AddVertex(-x,-y, z, c);
surf->AddVertex(-x, y, z, c);
surf->AddVertex( x, y, z, c);
surf->AddVertex( x,-y, z, c);

surf->AddVertex(-x,-y,-z, c);
surf->AddVertex(-x, y,-z, c);
surf->AddVertex( x, y,-z, c);
surf->AddVertex( x,-y,-z, c);

surf->AddVertex(-x,-y, z, c);
surf->AddVertex(-x, y, z, c);
surf->AddVertex( x, y, z, c);
surf->AddVertex( x,-y, z, c);

surf->AddVertex(-x,-y,-z, c);
surf->AddVertex(-x, y,-z, c);
surf->AddVertex( x, y,-z, c);
surf->AddVertex( x,-y,-z, c);




	surf->VertexNormal(0,0.0,0.0,-1.0);
	surf->VertexNormal(1,0.0,0.0,-1.0);
	surf->VertexNormal(2,0.0,0.0,-1.0);
	surf->VertexNormal(3,0.0,0.0,-1.0);

	surf->VertexNormal(4,0.0,0.0,1.0);
	surf->VertexNormal(5,0.0,0.0,1.0);
	surf->VertexNormal(6,0.0,0.0,1.0);
	surf->VertexNormal(7,0.0,0.0,1.0);

	surf->VertexNormal(8,0.0,-1.0,0.0);
	surf->VertexNormal(9,0.0,1.0,0.0);
	surf->VertexNormal(10,0.0,1.0,0.0);
	surf->VertexNormal(11,0.0,-1.0,0.0);

	surf->VertexNormal(12,0.0,-1.0,0.0);
	surf->VertexNormal(13,0.0,1.0,0.0);
	surf->VertexNormal(14,0.0,1.0,0.0);
	surf->VertexNormal(15,0.0,-1.0,0.0);

	surf->VertexNormal(16,-1.0,0.0,0.0);
	surf->VertexNormal(17,-1.0,0.0,0.0);
	surf->VertexNormal(18,1.0,0.0,0.0);
	surf->VertexNormal(19,1.0,0.0,0.0);

	surf->VertexNormal(20,-1.0,0.0,0.0);
	surf->VertexNormal(21,-1.0,0.0,0.0);
	surf->VertexNormal(22,1.0,0.0,0.0);
	surf->VertexNormal(23,1.0,0.0,0.0);

	surf->VertexTexCoords(0,0.0,1.0);
	surf->VertexTexCoords(1,0.0,0.0);
	surf->VertexTexCoords(2,1.0,0.0);
	surf->VertexTexCoords(3,1.0,1.0);

	surf->VertexTexCoords(4,1.0,1.0);
	surf->VertexTexCoords(5,1.0,0.0);
	surf->VertexTexCoords(6,0.0,0.0);
	surf->VertexTexCoords(7,0.0,1.0);

	surf->VertexTexCoords(8,0.0,1.0);
	surf->VertexTexCoords(9,0.0,0.0);
	surf->VertexTexCoords(10,1.0,0.0);
	surf->VertexTexCoords(11,1.0,1.0);

	surf->VertexTexCoords(12,0.0,0.0);
	surf->VertexTexCoords(13,0.0,1.0);
	surf->VertexTexCoords(14,1.0,1.0);
	surf->VertexTexCoords(15,1.0,0.0);

	surf->VertexTexCoords(16,0.0,1.0);
	surf->VertexTexCoords(17,0.0,0.0);
	surf->VertexTexCoords(18,1.0,0.0);
	surf->VertexTexCoords(19,1.0,1.0);

	surf->VertexTexCoords(20,1.0,1.0);
	surf->VertexTexCoords(21,1.0,0.0);
	surf->VertexTexCoords(22,0.0,0.0);
	surf->VertexTexCoords(23,0.0,1.0);

	surf->VertexTexCoords(0,0.0,1.0);
	surf->VertexTexCoords(1,0.0,0.0);
	surf->VertexTexCoords(2,1.0,0.0);
	surf->VertexTexCoords(3,1.0,1.0);

	surf->VertexTexCoords(4,1.0,1.0);
	surf->VertexTexCoords(5,1.0,0.0);
	surf->VertexTexCoords(6,0.0,0.0);
	surf->VertexTexCoords(7,0.0,1.0);

	surf->VertexTexCoords(8,0.0,1.0);
	surf->VertexTexCoords(9,0.0,0.0);
	surf->VertexTexCoords(10,1.0,0.0);
	surf->VertexTexCoords(11,1.0,1.0);

	surf->VertexTexCoords(12,0.0,0.0);
	surf->VertexTexCoords(13,0.0,1.0);
	surf->VertexTexCoords(14,1.0,1.0);
	surf->VertexTexCoords(15,1.0,0.0);

	surf->VertexTexCoords(16,0.0,1.0);
	surf->VertexTexCoords(17,0.0,0.0);
	surf->VertexTexCoords(18,1.0,0.0);
	surf->VertexTexCoords(19,1.0,1.0);

	surf->VertexTexCoords(20,1.0,1.0);
	surf->VertexTexCoords(21,1.0,0.0);
	surf->VertexTexCoords(22,0.0,0.0);
	surf->VertexTexCoords(23,0.0,1.0);



	surf->AddTriangle(0,1,2); // front
	surf->AddTriangle(0,2,3);
	surf->AddTriangle(6,5,4); // back
	surf->AddTriangle(7,6,4);
	surf->AddTriangle(6+8,5+8,1+8); // top
	surf->AddTriangle(2+8,6+8,1+8);
	surf->AddTriangle(0+8,4+8,7+8); // bottom
	surf->AddTriangle(0+8,7+8,3+8);
	surf->AddTriangle(6+16,2+16,3+16); // right
	surf->AddTriangle(7+16,6+16,3+16);
	surf->AddTriangle(0+16,1+16,5+16); // left
	surf->AddTriangle(0+16,5+16,4+16);

  surf->build();

	return mesh;

}


static Mesh *CreateSphere(const Color &c,int segments=12)
{

	if(segments<3 || segments>100) return NULL;

    Mesh* mesh=new Mesh();
    
    Surface* thissurf=mesh->CreateSurface();
    thissurf->setElements();


	float div=360.0/(segments*2);
	float height=1.0;
	float upos=1.0;
	float udiv=1.0/(segments*2);
	float vdiv=1.0/segments;
	float RotAngle=90;

	if(segments<3)
  { // diamond shape - no center strips

		for(int i=1;i<=segments*2;i++)
    {
			int np=thissurf->AddVertex(0.0f,height,0.0f,upos-(udiv/2.0f), 0.0f,c);//northpole
			int sp=thissurf->AddVertex(0.0f,-height,0.0f,upos-(udiv/2.0f),1.0f,c);//southpole
			float XPos=-cosdeg(RotAngle);
			float ZPos=sindeg(RotAngle);
			int v0=thissurf->AddVertex(XPos,0.0f,ZPos,upos,0.5f,c);
			RotAngle=RotAngle+div;
			if(RotAngle>=360.0f) RotAngle=RotAngle-360.0f;
			XPos=-cosdeg(RotAngle);
			ZPos=sindeg(RotAngle);
			upos=upos-udiv;
			int v1=thissurf->AddVertex(XPos,0.0f,ZPos,upos,0.5f,c);
			thissurf->AddTriangle(np,v0,v1);
			thissurf->AddTriangle(v1,v0,sp);
		}

	}

	if(segments>2){

		// poles first
		for(int i=1;i<=segments*2;i++)
    {

			int np=thissurf->AddVertex(0.0f,height,0.0f,upos-(udiv/2.0f),0.0f, c);//northpole
			int sp=thissurf->AddVertex(0.0f,-height,0.0f,upos-(udiv/2.0f),1.0f,c);//southpole

			float YPos=cosdeg(div);

			float XPos=-cosdeg(RotAngle)*(sindeg(div));
			float ZPos=sindeg(RotAngle)*(sindeg(div));

			int v0t=thissurf->AddVertex(XPos,YPos,ZPos,upos,vdiv,c);
			int v0b=thissurf->AddVertex(XPos,-YPos,ZPos,upos,1.0f-vdiv,c);

			RotAngle=RotAngle+div;

			XPos=-cosdeg(RotAngle)*(sindeg(div));
			ZPos=sindeg(RotAngle)*(sindeg(div));

			upos=upos-udiv;

			int v1t=thissurf->AddVertex(XPos,YPos,ZPos,upos,vdiv,c);
			int v1b=thissurf->AddVertex(XPos,-YPos,ZPos,upos,1.0f-vdiv,c);

			thissurf->AddTriangle(np,v0t,v1t);
			thissurf->AddTriangle(v1b,v0b,sp);

		}

		// then center strips

		upos=1.0f;
		RotAngle=90;
		for(int i=1;i<=segments*2;i++)
    {

			float mult=1;
			float YPos=cosdeg(div*(mult));
			float YPos2=cosdeg(div*(mult+1.0f));
			float Thisvdiv=vdiv;

			for(int j=1;j<=segments-2;j++){

				float XPos=-cosdeg(RotAngle)*(sindeg(div*(mult)));
				float ZPos=sindeg(RotAngle)*(sindeg(div*(mult)));

				float XPos2=-cosdeg(RotAngle)*(sindeg(div*(mult+1.0f)));
				float ZPos2=sindeg(RotAngle)*(sindeg(div*(mult+1.0f)));

				int v0t=thissurf->AddVertex(XPos,YPos,ZPos,upos,Thisvdiv,c);
				int v0b=thissurf->AddVertex(XPos2,YPos2,ZPos2,upos,Thisvdiv+vdiv,c);

				// 2nd tex coord set
				thissurf->VertexTexCoords(v0t,upos,Thisvdiv);
				thissurf->VertexTexCoords(v0b,upos,Thisvdiv+vdiv);

				float tempRotAngle=RotAngle+div;

				XPos=-cosdeg(tempRotAngle)*(sindeg(div*(mult)));
				ZPos=sindeg(tempRotAngle)*(sindeg(div*(mult)));

				XPos2=-cosdeg(tempRotAngle)*(sindeg(div*(mult+1.0f)));
				ZPos2=sindeg(tempRotAngle)*(sindeg(div*(mult+1.0f)));

				float temp_upos=upos-udiv;

				int v1t=thissurf->AddVertex(XPos,YPos,ZPos,temp_upos,Thisvdiv,       c);
				int v1b=thissurf->AddVertex(XPos2,YPos2,ZPos2,temp_upos,Thisvdiv+vdiv,c);

				// 2nd tex coord set
				thissurf->VertexTexCoords(v1t,temp_upos,Thisvdiv);
				thissurf->VertexTexCoords(v1b,temp_upos,Thisvdiv+vdiv);

				thissurf->AddTriangle(v1t,v0t,v0b);
				thissurf->AddTriangle(v1b,v1t,v0b);

				Thisvdiv=Thisvdiv+vdiv;
				mult=mult+1;

				YPos=cosdeg(div*(mult));
				YPos2=cosdeg(div*(mult+1.0f));

			}

			upos=upos-udiv;
			RotAngle=RotAngle+div;

		}

	}
	thissurf->UpdateNormals();
  thissurf->build();
	return mesh;

}



static Mesh *CreateTorus(const Color &c,float min_rad,float max_rad)
{
      Mesh* mesh=new Mesh();
      Surface* surf=mesh->CreateSurface();
      surf->setElements();

      float major_radius = max_rad;
      float minor_radius = min_rad;
      int major_segments = 32;
      int minor_segments = 16;


// Cria os vértices do torus
for (int i = 0; i <= major_segments; i++) 
{
  float theta = i * (2.0f * PI / major_segments);
  float sin_theta = sinf(theta);
  float cos_theta = cosf(theta);

  for (int j = 0; j <= minor_segments; j++) 
  {
    float phi = j * (2.0f * PI / minor_segments);
    float sin_phi = sinf(phi);
    float cos_phi = cosf(phi);

    // Posição do vértice
    Vec3 position(
      (major_radius + minor_radius * cos_phi) * cos_theta,
      (major_radius + minor_radius * cos_phi) * sin_theta,
      minor_radius * sin_phi
    );

    // Normal do vértice
    Vec3 normal(
      cos_theta * cos_phi,
      sin_theta * cos_phi,
      sin_phi
    );

    // Coordenada de textura do vértice
    Vec2 texture_coord(
      i / (float) major_segments,
      j / (float) minor_segments
    );

    // Adiciona o vértice ao Mesh
    surf->AddVertex(position, texture_coord, normal,c);
  }
}

// Cria as faces do torus
for (int i = 0; i < major_segments; i++)
 {
  for (int j = 0; j < minor_segments; j++)
   {
    // Indices dos vértices da face
    int a = (minor_segments + 1) * i + j;
    int b = (minor_segments + 1) * i + j + 1;
    int c = (minor_segments + 1) * (i + 1) + j + 1;
    int d = (minor_segments + 1) * (i + 1) + j;

    // Adiciona as faces ao Mesh
    surf->addFace(a, b, c);
    surf->addFace(a, c, d);
  }
 }


      surf->build();
      return mesh;
}


static Mesh *CreateHills(const Color &c,const Vec2 &tileSize, int NumXTiles,int NumYTiles, float hillHeight,const Vec2 &textureRepeatCount, const Vec2 &countHills)
{
    Mesh* mesh=new Mesh();
    Surface* surf=mesh->CreateSurface();
    surf->setElements();

    	// center
	const Vec2 center((tileSize.x * NumXTiles) * 0.5f, (tileSize.y * NumYTiles) * 0.5f);

	// texture coord step
	const Vec2 tx(
			textureRepeatCount.x  / NumXTiles,
			textureRepeatCount.y  / NumYTiles);

      // add one more point in each direction for proper tile count
	++NumXTiles;
	++NumYTiles;


  // create vertices from left-front to right-back
	int x;

 	float sx=0.f, tsx=0.f;
	for (x=0; x<NumXTiles; ++x)
	{
		float sy=0.f, tsy=0.f;
		for (int y=0; y<NumYTiles; ++y)
		{
			float p_x =   sx - center.x;
      float p_z  =  sy - center.y;
			float uv_x=tsx;
      float uv_y=1.0f - tsy;
      float p_y=0.0f;
 

      if (isnotzero(hillHeight))
      {
        p_y =  (sinf(p_x * countHills.x * PI / center.x) * 	cosf(p_z * countHills.y * PI / center.y)) * 	hillHeight;
      }
	
		

			surf->AddVertex(p_x, p_y, p_z, uv_x,uv_y,c);
      
			sy += tileSize.y;
			tsy += tx.y;
		}
		sx += tileSize.x;
		tsx += tx.x;
	}

  for (x=0; x<NumXTiles-1; ++x)
	{
		for (int y=0; y<NumYTiles-1; ++y)
		{
			const int current = x * NumYTiles + y;

      surf->addFace(current,
                   current + 1, 
                   current + NumYTiles);

      surf->addFace(current + 1,
                   current + 1 + NumYTiles, 
                   current + NumYTiles);




		}
	}

  surf->UpdateNormals();
  surf->build();
      
    return mesh;
}

static Mesh* LoadMesh(const std::string &filename)
{

    if (!FileExists(filename.c_str()))
        return nullptr;

  Stream file(filename.c_str());
  

	std::string header = file.readString();
	int id             = file.readInt();
  int numMaterials   = file.readInt();
  Log(0," Load mesh %s id:%d   materials:%d \n",header.c_str() , id,numMaterials);
  Mesh * mesh = new Mesh();

  for (int i=0; i<numMaterials;i++)
  {
    	int flags                = file.readInt();
      int use_diffuse          = file.readInt();
      int use_lightmap            = file.readInt();
      std::string diffuse;
      std::string lightmap;

      if (use_diffuse>=1)
      {
         diffuse  = file.readString();
      }
      
      if (use_lightmap>=1)
      {
         lightmap  = file.readString();
      }
       Log(0," Material %d  %d %d \n",i, use_diffuse,use_lightmap);
  }
  
 int num_surfaces=file.readInt();//numero of meshs
 Log(0," Surfaces %d \n",num_surfaces);
 for (int i=0;i < num_surfaces;i++)
 {
    std::string mesh_name    = file.readString();
    int flags                = file.readInt();
    int materialIndex        = file.readInt();
    int numVertices          = file.readInt();
    int numFaces             = file.readInt();
    int numUVChannels        = file.readInt();

    Surface * surf=mesh->CreateSurface();
    surf->setElements();
    

 
    Log(0," Name (%s) MateriaIndex: %d numVertex:%d numFaces:%d numUvMaps:%d \n",mesh_name.c_str(),materialIndex,numVertices,numFaces,numUVChannels);

     for (int x=0; x< numVertices ;x++)
		 {
            Vec3 pos;
            Vec3 normal;
            Vec2 uv;
           pos.x=file.readFloat();//pos
           pos.y=file.readFloat();
           pos.z=file.readFloat();
           
           normal.x=file.readFloat();//normal
           normal.y=file.readFloat();
           normal.z=file.readFloat();

           uv.x=file.readFloat();//texture 0
           uv.y=file.readFloat();
            if(numUVChannels==2)
            {
                file.readFloat();//texture 1
                file.readFloat();
            }
        surf->AddVertex(pos,uv,normal);
		 }
		  for (int x=0;x < numFaces;x++)
		 {
		    int a=file.readInt();
        int b=file.readInt();
        int c=file.readInt();
        surf->addFace(c,b,a);

		 }
      
    
  }
  
  int useBones = file.readInt();
  
      
    
  
   mesh->Build();  
   return mesh;
}

  private:
      std::vector<Surface*> surfaces;
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
app.CreateWindow(screenWidth, screenHeight, "Vertex Texture Colored",false);

//Shader shader=Shader::createSolidColor();
Shader shader=Shader::createSolidAmbient2();
  
//Shader shader=Shader::createSolidColorTexture();

Camera camera; 
camera.SetPosition(0, 1, 10);  

Texture2D texture;//(64,64);
texture.Load("assets/cube.png");

Texture2D texture_floor;//(64,64);
texture_floor.Load("assets/grass_1024.jpg");

Texture2D text_mesh;//(64,64);
text_mesh.Load("assets/african_head_diffuse.tga",true);



Mesh *plane=Mesh::CreateHills(Color(1,1,1),Vec2(5,5),10,10,0.2,Vec2(5,5),Vec2(8,8));
//Mesh::CreatePlane(50,50,Color(0.5f,0.5f,0.5f));

Mesh *cube= Mesh::CreateCube(1,1.5,1,Color(1,0,1));

Mesh *sphere = Mesh::CreateSphere(Color(1,0,0));

Mesh *cilinder = Mesh::CreateCylinder(Color(1,1,1));

Mesh *cone = Mesh::CreateCone(Color(1,1,0));

Mesh *torus = Mesh::CreateTorus(Color(1,1,0),0.2f,1.0f);

Mesh *mesh = Mesh::LoadMesh("assets/african_head.h3d");

 
//sphere.CreateSphere(1,32,32,Color(1,1,0));


  
 
   Mat4 projection = Mat4::ProjectionMatrix(45.0f,  static_cast<float>(screenWidth) / screenHeight, 0.1f, 1000.0f);
    

   glClearColor(0.1,0.1,0.3f,1.0);
   glEnable(GL_DEPTH_TEST);  
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  



int frameCount = 0;
Uint32 startTime = SDL_GetTicks();


  

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
  
  
      texture_floor.Bind(0);
      
       
       shader.Bind();
       shader.setMatrix4("view", view);
       shader.setMatrix4("projection" ,projection);
       shader.setVector3("viewPos" ,camera.Position);
       

        Mat4 model= Mat4::Identity();
        shader.setMatrix4("model", model);
        plane->Render();

             texture.Bind(0);
		 
        model= Mat4::Translate(-1,1,0);
        shader.setMatrix4("model", model);
        cube->Render();
		 
 

        model= Mat4::Translate(1,1,0);
        shader.setMatrix4("model", model);
        sphere->Render();
		 
        model= Mat4::Translate(3,1,0);
        shader.setMatrix4("model", model);
        cilinder->Render();

        model= Mat4::Translate(-3,1,0);
        shader.setMatrix4("model", model);
        cone->Render();


        model= Mat4::Translate(-5,1,0);
        shader.setMatrix4("model", model);
        torus->Render();
        


        text_mesh.Bind(0);
        model= Mat4::Translate(0,1,5);
        shader.setMatrix4("model", model);
        mesh->Render();
        
        
        app.Swap();



         frameCount++;
        if (SDL_GetTicks() - startTime >= 1000)
        {
            char title[150];

                snprintf(title, sizeof( title), "  FPS: %d", frameCount);

            SDL_SetWindowTitle(app.getWindow(), title);
            frameCount = 0;
            startTime = SDL_GetTicks();
        }
  } 
 
 delete plane;
 delete cube;
 delete sphere;
 delete cilinder;
 delete cone;
 delete torus;
delete mesh;

  std::cout<<"Exit"<<std::endl;
  return 0;
}