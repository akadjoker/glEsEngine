/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:25:56 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/02/16 20:22:22 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "glad.h"
#include "utils.hpp"
#include "math.hpp"
#include "stb_image.h" 


#define FVF_XYZ              1<<0
#define FVF_NORMAL           1<<1
#define FVF_COLOR            1<<2
#define FVF_FCOLOR           1<<3
#define FVF_BINORMAL         1<<4
#define FVF_TANGENT          1<<5

#define FVF_TEX1             1<<6
#define FVF_TEX2             1<<7
#define FVF_TEX3             1<<8
#define FVF_TEX4             1<<9
#define FVF_TEX5             1<<10



enum E_INDEX_TYPE
{
    I16BIT = 0,
    I32BIT = 1
};

enum E_PRIMITIVE_TYPE
{
    //! All vertices are non-connected points.
    EPT_POINTS=0,

    //! All vertices form a single connected line.
    EPT_LINE_STRIP,

    //! Just as LINE_STRIP, but the last and the first vertex is also connected.
    EPT_LINE_LOOP,

    //! Every two vertices are connected creating n/2 lines.
    EPT_LINES,

    //! After the first two vertices each vertex defines a new triangle.
    //! Always the two last and the new one form a new triangle.
    EPT_TRIANGLE_STRIP,

    //! After the first two vertices each vertex defines a new triangle.
    //! All around the common first vertex.
    EPT_TRIANGLE_FAN,

    //! Explicitly set all vertices for each triangle.
    EPT_TRIANGLES
};

enum VertexAttributeType
{
    VET_FLOAT1,
    VET_FLOAT2,
    VET_FLOAT3,
    VET_FLOAT4,
    VET_SHORT1,
    VET_SHORT2,
    VET_SHORT3,
    VET_SHORT4,
    VET_BYTE3,
    VET_BYTE4,
};

enum VertexAttribute
{
    VF_POSITION      = 1<<0, // vertex position 3 floats x,y,z
    VF_COLOR         = 1<<1, // vertex color 4 bytes r,g,b,a
    VF_NORMAL        = 1<<2, // normal 3 floats x,y,z
    VF_TANGENT       = 1<<3, // normal 3 floats x,y,z
    VF_BINORMAL      = 1<<4, // normal 3 floats x,y,z
    VF_TEXCOORD1     = 1<<5, // texcoord 1 2 floats u,v
    VF_TEXCOORD2     = 1<<6, // texcoord 1 2 floats u,v
    VF_TEXCOORD3     = 1<<7, // texcoord 1 2 floats u,v
    VF_TEXCOORD4     = 1<<8, // texcoord 1 2 floats u,v
    VF_TEXCOORD5     = 1<<9, // texcoord 1 2 floats u,v
    VF_TEXCOORD6     = 1<<10, //texcoord 1 2 floats u,v

};





inline int FVFDecodeLength(unsigned int fvf)
{
	int nSize = 0;
	if (fvf & FVF_XYZ)		nSize+=3 * sizeof(FLOAT);
	if (fvf & FVF_NORMAL)	nSize+=3 * sizeof(FLOAT);

	if (fvf & FVF_COLOR)	nSize+=4 * sizeof(BYTE);

    if (fvf & FVF_FCOLOR)	nSize+=4 * sizeof(FLOAT);

	if (fvf & FVF_BINORMAL)	nSize+=3 * sizeof(FLOAT);
    if (fvf & FVF_TANGENT)	nSize+=3 * sizeof(FLOAT);


	if (fvf & FVF_TEX1)		nSize+=2 * sizeof(FLOAT);
	if (fvf & FVF_TEX2)		nSize+=2 * sizeof(FLOAT);
	if (fvf & FVF_TEX3)		nSize+=2 * sizeof(FLOAT);
	if (fvf & FVF_TEX4)		nSize+=2 * sizeof(FLOAT);
	if (fvf & FVF_TEX5)		nSize+=2 * sizeof(FLOAT);

	return nSize;
}



inline UINT getTypeFormat(VertexAttributeType etype)
	{
		switch(etype)
		{
		case VET_FLOAT1:
			return GL_FLOAT;
		case VET_FLOAT2:
			return GL_FLOAT;
		case VET_FLOAT3:
			return GL_FLOAT;
		case VET_FLOAT4:
			return GL_FLOAT;
		case VET_SHORT1:
			return GL_SHORT;
		case VET_SHORT2:
			return GL_SHORT;
		case VET_SHORT3:
			return GL_SHORT;
		case VET_SHORT4:
			return GL_SHORT;
        case VET_BYTE3:
            return GL_UNSIGNED_BYTE;
        case VET_BYTE4:
            return GL_UNSIGNED_BYTE;
		}
		return 0;
	}
	inline UINT getTypeSize(VertexAttributeType etype)
	{
		switch(etype)
		{
		case VET_FLOAT1:
			return sizeof(float);
		case VET_FLOAT2:
			return sizeof(float)*2;
		case VET_FLOAT3:
			return sizeof(float)*3;
		case VET_FLOAT4:
			return sizeof(float)*4;
		case VET_SHORT1:
			return sizeof(short);
		case VET_SHORT2:
			return sizeof(short)*2;
		case VET_SHORT3:
			return sizeof(short)*3;
		case VET_SHORT4:
			return sizeof(short)*4;
        case VET_BYTE3:
            return sizeof(unsigned char)*3+1;
        case VET_BYTE4:
            return sizeof(unsigned char)*4+1;
		}
		return 0;
	}


	inline unsigned short getTypeCount(VertexAttributeType etype)
	{
		switch (etype)
		{
		case VET_FLOAT1:
			return 1;
		case VET_FLOAT2:
			return 2;
		case VET_FLOAT3:
			return 3;
		case VET_FLOAT4:
			return 4;
		case VET_SHORT1:
			return 1;
		case VET_SHORT2:
			return 2;
		case VET_SHORT3:
			return 3;
		case VET_SHORT4:
			return 4;
        case VET_BYTE3:
            return 3;
        case VET_BYTE4:
            return 4;
		}
      return 0;
	}



struct Color
{
    float r,g,b,a;

	Color() : r( 1.0f ), g( 1.0f ), b( 1.0f ), a( 1.0f )
	{
	}
	
	Color( const float r, const float g, const float b, const float a=1.0f) :
		r( r ), g( g ), b( b ), a( a )
	{
	}

	Color(const Color &v ) : r( v.r ), g( v.g ), b( v.b ), a( v.a )
	{
	}
    void set(const Color &c)
    {
        this->r=c.r;
        this->g=c.g;
        this->b=c.b;
        this->a=c.a;
    }
    void set(const float r, const float g, const float b, const float a=1.0f)
    {
        this->r=r;
        this->g=g;
        this->b=b;
        this->a=a;
    }
    
    bool operator==( const Color &v ) const
	{
		return (r == v.r  && 
				g == v.g  && 
                b == v.b  && 
                a == v.a  );
	}
};

class Texture2D
{
    public:
    Texture2D()
    {

    }
    ~Texture2D()
    {
         if (id != 0) 
         {
           glDeleteTextures(1, &id);
           Log(0, "TEXTURE2D: [ID %i] Unload Opengl Texture2D", id);
        }
    }
     Texture2D(int w, int h)
    {
       width =w;
       height=h;
       components=4;

       unsigned char *data =( unsigned char *)malloc(width * height * components);
       if (data == nullptr) 
      {
         Log(2,"Failed to cretae image ");
         return ;
      }
      memset(data, 0xFF, width * height * components);
     
         GLenum  format = GL_RGBA;

        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
 
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //glBindTexture(GL_TEXTURE_2D, 0);
        Log(0, "TEXTURE2D: [ID %i] Create Opengl Texture2D", id);
 
        free(data);
        
    }
    bool Load(const std::string &file_name,bool flip_y=false)
    {
        unsigned int bytesRead;
       unsigned char *fileData =  LoadFileData(file_name.c_str(),&bytesRead);
       if(!fileData)
            return false;

    if (flip_y)
      stbi_set_flip_vertically_on_load(1);
     unsigned char *data =  stbi_load_from_memory(fileData,bytesRead,&width, &height, &components, STBI_default);
    //  width =256;
    //  height=256;
    //  components=4;

//       unsigned char *data =( unsigned char *)malloc(width * height * components);
      //unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &components, STBI_default);
      if (data == nullptr) 
      {
         Log(2,"Failed to load image: %s",file_name.c_str());
         return false;
      }

      GLenum format;
      switch (components) 
      {
         case STBI_grey:
            format = GL_RED;
            break;
         case STBI_grey_alpha:
            format = GL_RG;
            break;
         case STBI_rgb:
            format = GL_RGB;
            break;
         case STBI_rgb_alpha:
            format = GL_RGBA;
            break;
         default:
            free(data);
            return false;
      }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
       // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
       // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //glBindTexture(GL_TEXTURE_2D, 0);
        Log(0, "TEXTURE2D: [ID %i] Create Opengl Texture2D", id);
        free(fileData);
        free(data);
        return true;
    }

    void Bind(UINT unit) 
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, id);
    }
   void unBind(UINT unit) 
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    private:
        UINT id;   
        int width;          
        int height;         
        int components;         
};


class Shader
{
    public:
    Shader()
    {
        m_program = 0;
    }
    ~Shader()
    {
        glDeleteProgram(m_program);
        Log(0, "SHADER: [ID %i] Unloaded shader program", m_program);
    }
    
    bool operator ==(const Shader&      other) const { return m_program == other.m_program; }
    bool operator !=(const Shader&      other) const { return m_program != other.m_program; }

    static Shader createSolid()
    {
        const char *vertexShaderSource = R"(
        #version 320 es
        precision mediump float;
        layout (location = 0) in vec3 position;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
        gl_Position = projection * view * model * vec4(position, 1.0);
        })";

        const char *fragmentShaderSource = R"(
        #version 320 es
        precision mediump float;
        out vec4 FragColor;

        void main()
        {
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        })";
        Shader shader;
        shader.create(vertexShaderSource,fragmentShaderSource);
        shader.LoadDefaults();
        return shader;

    }
    static Shader createSolidColor()
    {
        const char *vertexShaderSource = R"(
            #version 320 es
            precision mediump float;
            layout (location = 0) in vec3 position;
            layout (location = 1) in vec4 color;
            out vec4 ourColor;
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            void main()
            {
            ourColor = color;
            gl_Position = projection * view * model * vec4(position, 1.0);
            })";

            const char *fragmentShaderSource = R"(
            #version 320 es
            precision mediump float;
            in vec4 ourColor;
            out vec4 FragColor;
            void main()
            {
            FragColor = ourColor;
            })";

        Shader shader;
        shader.create(vertexShaderSource,fragmentShaderSource);
        shader.LoadDefaults();
        return shader;
    }
    static Shader createSolidColorTexture()
    {

        const char *vertexShaderSource = R"(
        #version 320 es
        precision mediump float;
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec2 aTexCoord;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        out vec4 ourColor;
        out vec2 TexCoord;

        void main()
        {
            gl_Position =projection * view * model* vec4(aPos, 1.0);
            ourColor = aColor;
            TexCoord = aTexCoord;
        }
        )";

        const char *fragmentShaderSource = R"(
        #version 320 es
        precision mediump float;
        out vec4 FragColor;
        
        in vec4 ourColor;
        in vec2 TexCoord;

        uniform sampler2D tex;

        void main()
        {
             vec4 texColor = texture(tex, TexCoord) * ourColor;
            if(texColor.a < 0.1)
                discard;
            FragColor = texColor;
        }
        )";
        Shader shader;
        shader.create(vertexShaderSource,fragmentShaderSource);
        shader.LoadDefaults();
        shader.setInt("tex",0);
        return shader;
    }
    static Shader createSolidAmbient()
    {
        const char *vertexShaderSource = R"(
        #version 320 es
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 3) in vec2 aTexCoord;
        layout (location = 4) in vec3 aNormal;
        
        out vec3 FragPos;
        out vec3 Normal;
        out vec4 ourColor;
        out vec2 TexCoord;
   
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
            FragPos = vec3(model * vec4(aPos, 1.0));
            Normal = mat3(transpose(inverse(model))) * aNormal;
            ourColor = aColor;  
             TexCoord = aTexCoord;

        gl_Position = projection * view  * vec4(FragPos, 1.0);
        }

)";

        const char *fragmentShaderSource = R"(
        #version 320 es
        precision mediump float;
        
     
        uniform vec3 viewPos; 

        in vec3 Normal;
        in vec3 FragPos; 
        in vec4 ourColor;
         in vec2 TexCoord;

        uniform sampler2D tex;
        out vec4 FragColor;
          
        void main()
        {
            vec3 lightPos   = vec3 (0.0,50.0,0.0);
            vec3 lightColor = vec3 (1.0,0.0,0.01);

             vec4 texColor = texture(tex, TexCoord) + ourColor;

            // ambient
                float ambientStrength = 0.6;
                vec3 ambient = ambientStrength * lightColor;
            
          // diffuse 
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;
            
            // specular
            float specularStrength = 0.5;
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);  
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
            vec3 specular = specularStrength * spec * lightColor;  
                
            vec3 result = (ambient + diffuse + specular) +  vec3(texColor.x,texColor.y,texColor.z);

            FragColor = vec4(result, 1.0);
        })";

        Shader shader;
        shader.create(vertexShaderSource,fragmentShaderSource);
        shader.LoadDefaults();
         shader.setInt("tex",0);
        return shader;
    }
static Shader createSolidAmbient2()
    {
         const char *vertexShaderSource = R"(
        #version 320 es
        precision mediump float;
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec2 aTexCoord;
        layout (location = 3) in vec3 aNormal;
             
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        out vec4 Color;
        out vec2 TexCoord;
        out vec3 Normal;

        void main()
        {
            gl_Position =projection * view * model* vec4(aPos, 1.0);
            Color = aColor;
            TexCoord = aTexCoord;
            Normal  = aNormal;
        }
        )";

        const char *fragmentShaderSource = R"(
        #version 320 es
        precision mediump float;
        out vec4 FragColor;
        
        in vec4 Color;
        in vec2 TexCoord;
        in vec3 Normal;
          

        uniform sampler2D tex;

        void main()
        {

            vec3 lightDirection= vec3(1.0, 1.0, 0.0);
            vec3 ambientLight  = vec3(0.2,0.2,0.2);
           
            

            vec4 texColor = texture(tex, TexCoord);
            vec3 normal = normalize(Normal);
            vec3 lightDir = normalize(lightDirection);
            
            float diffuse = max(dot(normal, lightDir), 0.0);
            vec4 diffuseColor = Color * texColor * diffuse;
            vec4 ambientColor = vec4(ambientLight, 1.0) * Color * texColor;


        
            
            FragColor = ambientColor + diffuseColor ;
            

            // vec4 texColor = texture(tex, TexCoord) * Color;
           //  FragColor = texColor;
        }
        )";
        Shader shader;
        shader.create(vertexShaderSource,fragmentShaderSource);
        shader.LoadDefaults();
        shader.setInt("tex",0);
        return shader;
    }
    bool create(const char* vShaderCode, const char* fShaderCode)
    {
        // 2. compile shaders
        unsigned int vertex, fragment;
       
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
       
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
       
        // shader Program
        m_program = glCreateProgram();
        glAttachShader(m_program, vertex);
        glAttachShader(m_program, fragment);
        glLinkProgram(m_program);
        checkCompileErrors(m_program, "PROGRAM");

        if (m_program>0)
            Log(0, "SHADER: [ID %i] Create shader program.", m_program);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        Bind();
        return true;
    }
    
    void Bind() 
    { 
        glUseProgram(m_program); 
    }
    void unBind() 
    { 
        glUseProgram(0); 
    }
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(m_program, name.c_str()), value); 
    }
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(m_program, name.c_str()), value); 
    }
    void setFloat4(const std::string &name, float x,float y, float z,float w) const
    { 
        glUniform4f(glGetUniformLocation(m_program, name.c_str()), x,y,z,w); 
    }
    void setFloat3(const std::string &name, float x,float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(m_program, name.c_str()), x,y,z); 
    }
    void setVector3(const std::string &name, const Vec3 &v) const
    { 
        glUniform3f(glGetUniformLocation(m_program, name.c_str()), v.x,v.y,v.z); 
    }
    void setFloat2(const std::string &name, float x,float y) const
    { 
        glUniform2f(glGetUniformLocation(m_program, name.c_str()), x,y); 
    }
    
    void setMatrix(const std::string &name, const GLfloat *value, GLboolean transpose = GL_FALSE) const
    { 
        glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1 , transpose,value); 
    }
    void setMatrix4(const std::string &name, Mat4 mat, GLboolean transpose = GL_FALSE) const
    { 
       setMatrix(name, mat.x, transpose); 
    }
    
    bool findUniform(const std::string name)const
    {
        std::map<std::string, int>::const_iterator it = m_uniforms.begin();
        while(it != m_uniforms.end())
        {
            if (strcmp(it->first.c_str(),name.c_str())==0)
            {
            return true;
            }
            it++;
        }
        return false;
    }
    int  getUniform(const std::string name)const
    {
        std::map<std::string, int>::const_iterator it = m_uniforms.begin();
        while(it != m_uniforms.end())
        {
            if (strcmp(it->first.c_str(),name.c_str())==0)
            {
            return it->second;
            }

            it++;
        }
         return -1;
    }
    int getUniformLocation(const std::string &uniformName) const
    {
        int location = -1;
        location =getUniform(uniformName);//uniforms[uniformName];
        if (location == -1)
            Log(2, "SHADER: [ID %i] Failed to find shader uniform: %s", m_program, uniformName.c_str());

    //  else SDL_Log( "SHADER: [ID %i] IShader uniform (%s) set at location: %i", id, uniformName, location);
        return location;
    }

    int getAttribLocation( const std::string &attribName) const
    {
        int location = -1;
        location = glGetAttribLocation(m_program, attribName.c_str());
        if (location == -1)
            Log(2, "SHADER: [ID %i] Failed to find shader attribute: %s", m_program, attribName.c_str());
        //App::getInstance()->ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SHADER Error",TextFormat("SHADER Failed to find shader attribute: %s)",attribName));
    //  else SDL_Log( "SHADER: [ID %i] IShader attribute (%s) set at location: %i", id, attribName, location);
        return location;
    }
    bool addUniform(const std::string name)
    {
        int location = -1;
        location = glGetUniformLocation(m_program, name.c_str());
        if (location == -1)
        {
            Log(2, "SHADER: [ID %i] Failed to find shader uniform: %s", m_program, name.c_str());
            //ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SHADER Error",TextFormat("SHADER Failed to find shader uniform: %s)",name));
            return false;
        }

       // Log(0, "SHADER: [ID %i] shader uniform (%s) set at location: %i", m_program, name.c_str(), location);
        m_uniforms.insert(std::make_pair(name, location));

    return true;
    }

    bool addAttribute(const std::string name)
    {
    int location = -1;
        location = glGetAttribLocation(m_program, name.c_str());

        if (location == -1)
        {
            Log(2, "SHADER: [ID %i] Failed to find shader attribute: %s", m_program, name.c_str());
        //ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SHADER Error",TextFormat("SHADER Failed to find shader attribute: %s)",name));
        return false;
        }

      //  Log(2, "SHADER: [ID %i] shader attribute (%s) set at location: %i", m_program, name.c_str(), location);
        m_attributes.insert(std::make_pair(name, location));
      return true;
    }
    void printData()
    {

    Log(0,"[SHADER]  Id(%d) Num Attributes(%d)  Num Uniforms (%d)",m_program, m_numAttributes,m_numUniforms);
    {
            std::map<std::string, int>::iterator it = m_attributes.begin();
            while(it != m_attributes.end())
            {
                Log(0,"[SHADER]  Id(%d)  attribute  index(%d) name(%s)",m_program,it->second, it->first.c_str());
                it++;
            }
    }
    {
        std::map<std::string, int>::iterator it = m_uniforms.begin();
            while(it != m_uniforms.end())
            {
                Log(0,"[SHADER]  Id(%d) uniform index(%d) name(%s)",m_program,it->second, it->first.c_str());

                it++;
            }
        }
    }
    void LoadDefaults()
    {
        GLint numActiveAttribs = 0;
        GLint maxAttribNameLength = 0;
        glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
        glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribNameLength);
        m_numAttributes=numActiveAttribs;
        for(GLint attrib = 0; attrib < numActiveAttribs; ++attrib)
        {
            int namelen = -1;
            int num = -1;
            char name[256]; // Assume no variable names longer than 256
            GLenum type = GL_ZERO;
            glGetActiveAttrib(m_program, attrib,  sizeof(name) - 1, &namelen, &num, &type, name);
            name[namelen] = 0;
            addAttribute(std::string((char*)&name[0]));
            glBindAttribLocation(m_program, attrib, (char*)&name[0]);
            Log(0,"SHADER: [ID %i] Active attribute (%s) set at location: %i", m_program, name,attrib);
        }
        // Get available shader uniforms
        int uniformCount = -1;
        glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);
        m_numUniforms=uniformCount;

        for (int i = 0; i < uniformCount; i++)
        {
            int namelen = -1;
            int num = -1;
            char name[256]; // Assume no variable names longer than 256
            GLenum type = GL_ZERO;
            glGetActiveUniform(m_program, i, sizeof(name) - 1, &namelen, &num, &type, name);
            name[namelen] = 0;
            addUniform(std::string((char*)&name[0]));
            Log(0,"SHADER: [ID %i] Active uniform (%s) set at location: %i", m_program, name, glGetUniformLocation(m_program, name));
        }

    }
    private:
        UINT m_program;
        std::map<std::string, int> m_uniforms;
        std::map<std::string, int> m_attributes;
        int m_numAttributes;
        int m_numUniforms;

    private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                Log(2,"SHADER: Error Compile %s Msg: %s", type.c_str(), infoLog );
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                Log(2,"SHADER: Error Link %s Msg: %s", type.c_str(), infoLog );
            }
        }
    }
};

class VertexDeclaration
{
public:
     struct Element
    {
        UINT index;
        UINT size;
        VertexAttribute   attribute;
        VertexAttributeType type;
     };

    VertexDeclaration():m_iVertexOffSetSize(0)
    {}

    void addElement(UINT index, VertexAttribute attribute, VertexAttributeType  type)
    {
        Element element;
        element.index=index;
        element.attribute=attribute;
        element.type=type;
        element.size=getTypeSize(type);
        m_iVertexOffSetSize += getTypeSize(type);
        elements.push_back(element);
    }

    const std::vector<Element>& getElements() const
    {
        return elements;
    }
    const UINT getSize(){ return (UINT)m_iVertexOffSetSize;};

private:
    std::vector<Element> elements;
    UINT m_iVertexOffSetSize;

};



class VertexArray
{
    public:
        VertexArray()
        {
            glGenVertexArrays(1, &m_id);
            glBindVertexArray(0);
            Log(0, "VAO: [ID %i] Create vertex array", m_id);
        }

        ~VertexArray()
        {
            glDeleteVertexArrays(1, &m_id);
            Log(0, "VAO: [ID %i] Delete vertex array", m_id);
        }

        void Bind()
        {
            glBindVertexArray(m_id);
        }
        void unBind()
        {
            glBindVertexArray(0);
        }
    private:
            UINT m_id{0};
            
             
};

class VertexBuffer

{
    public:
    VertexBuffer(UINT vertexSize, UINT vertexCount, bool dynamic=false)
        : m_dynamic(dynamic),m_vertexSize(vertexSize), m_vertexCount(vertexCount)
        {
            m_dataSize = vertexSize * vertexCount;
            glGenBuffers(1, &m_id);
            Log(0, "VBO: [ID %i] Create vertex buffer", m_id);
        }

        ~VertexBuffer()
        {
            glDeleteBuffers(1, &m_id);
            Log(0, "VBO: [ID %i] Delete vertex buffer ", m_id);
        }

        UINT getVertexSize()   const { return m_vertexSize; }
        UINT  getVertexCount() const { return m_vertexCount; }


        void Bind()
        {
             glBindBuffer(GL_ARRAY_BUFFER, m_id); 
        }
        void UnBind()
        {
             glBindBuffer(GL_ARRAY_BUFFER, 0); 
        }
      
        // unsigned char* Lock(UINT offset)
        // {
        //     m_offset = offset;
        //     unsigned char* m_data;
        //     Bind();
        //     m_data = (unsigned char*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
             
        //     return m_data;
        // }
        // void Unlock()
        // {
            
        //    // glBindBuffer(GL_ARRAY_BUFFER, m_id);
        //    // glBufferSubData(GL_ARRAY_BUFFER, m_offset, m_dataSize, m_data);
        //    glUnmapBuffer(GL_ARRAY_BUFFER);
        //    UnBind();
            
        // }
        void createBuffer(void *data)
        {
              glBindBuffer(GL_ARRAY_BUFFER, m_id);
              glBufferData(GL_ARRAY_BUFFER, m_dataSize, data, m_dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
              glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        void updateBuffer(void *data, UINT offset)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            glBufferSubData(GL_ARRAY_BUFFER, offset, m_dataSize, data);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
     
        }


 
    private:
            UINT m_id{0};
            bool m_dynamic{false};
            UINT m_offset{0};
            UINT m_vertexSize;
            UINT m_vertexCount;
            UINT m_dataSize;
           // unsigned char* m_data;
             
};


class IndexBuffer

{
    public:
        IndexBuffer(E_INDEX_TYPE type, UINT indexCount, bool dynamic=false)
          : m_dynamic(dynamic),m_type(type), m_indexCount(indexCount)
      
        {

            if (type==I16BIT)
                 m_dataSize = indexCount * sizeof(unsigned short);
            else
                 m_dataSize = indexCount * sizeof(unsigned int);
                 
            //(type==I16BIT)?sizeof(unsigned short): sizeof(unsigned int);
            //* sizeof(unsigned int)
           //  m_dataSize = indexCount * sizeof(unsigned int);
            glGenBuffers(1, &m_id);
            Log(0, "EBO: [ID %i] Create index buffer", m_id);
        }

        ~IndexBuffer()
        {
            glDeleteBuffers(1, &m_id);
            Log(0, "EBO: [ID %i] Delete index buffer ", m_id);
        
        }

        void Bind()
        {
              glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  m_id); 
        }
        void UnBind()
        {
              glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0); 
        }
     
        void createBuffer(void *data)
        {
               glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
               glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_dataSize, data, m_dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
               glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0); 
        }
  
        E_INDEX_TYPE getType(){return m_type;}
        
    private:
            UINT m_id{0};
            bool m_dynamic{false};
            UINT m_indexCount;
            E_INDEX_TYPE m_type;
             UINT m_dataSize;
};


class VertexData
{
public:

    VertexData()
    {
      m_vertex_declaration = new VertexDeclaration();  
      m_vertex_array       = new VertexArray();
    }
    ~VertexData()
    {
        delete m_vertex_array;
        delete m_vertex_declaration;
        if (m_vertex_buffer)
            delete m_vertex_buffer;
        if(m_index_buffer)
            delete m_index_buffer;
    }
    
   IndexBuffer *createIndexBuffer( E_INDEX_TYPE type, UINT indexCount, bool dynamic=false)
    { 
        if (m_index_buffer)
        {
            delete m_index_buffer;
        }
        m_index_buffer = new IndexBuffer(type,indexCount,dynamic);
        m_isDirty=true;
        return m_index_buffer;
    }
    
   VertexBuffer *createVertexBuffer(UINT vertexSize, UINT vertexCount, bool dynamic=false)
   {
    if(m_vertex_buffer)
    {
        delete m_vertex_buffer;
    }
    m_vertex_buffer = new VertexBuffer(vertexSize,vertexCount,dynamic);
    m_isDirty=true;
    return m_vertex_buffer;
   }

   VertexBuffer *getVertexBuffer(){ return m_vertex_buffer;};
   IndexBuffer  *getIndexBuffer(){return m_index_buffer;};
   VertexArray  *getVertexArray(){return m_vertex_array;};
   
   VertexDeclaration *getVertexDeclation()
   {
     m_vertex_array->Bind();
     return m_vertex_declaration;
   } 

   void Render(UINT mode,UINT count)
   {
        m_vertex_array->Bind();
        if (m_isDirty)
        {
            Update();
        }
        if (m_index_buffer)
        {
            m_index_buffer->Bind();
            
            E_INDEX_TYPE type=m_index_buffer->getType();
            if (type==E_INDEX_TYPE::I16BIT)
            {
                glDrawElements(mode, count, GL_UNSIGNED_SHORT, 0);  
            } else
             if (type==E_INDEX_TYPE::I32BIT)
            {
                  glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
            
            }
                  
        } else
        {
            if(m_vertex_buffer)
            {
                glDrawArrays(mode, 0, count);
            }
        }
   }

   void Update()
   {
    if (!m_vertex_buffer || m_vertex_declaration->getSize()<=0)
        return ;
        
    m_vertex_buffer->Bind();
    const std::vector<VertexDeclaration::Element> elements=  m_vertex_declaration->getElements();

    UINT m_iVertexOffSetSize = m_vertex_declaration->getSize();
    UINT m_offSet=0;

  //  Log(0," size %d  count %d \n",m_iVertexOffSetSize,  (int)elements.size());

//     Log(0,"2 size %d  size %d \n",m_iVertexOffSetSize,  sizeof(Vec3));


     for (int i=0; i < (int)elements.size(); i++)
     {
         void* pointer = reinterpret_cast<void*>(m_offSet);
   
         VertexDeclaration::Element elemnt = elements[i];
     //    m_iVertexOffSetSize += getTypeSize(elemnt.type);

  //buffer->SetVertexAttribute(2, 
  //getTypeCount(m_VertexDeclaration[i].type),
  // getTypeFormat(m_VertexDeclaration[i].type), true, m_iVertexOffSetSize, pointer);
  
          //  glVertexAttribPointer(elemnt.index, 
              
         glEnableVertexAttribArray(elemnt.index); 
        //  getTypeCount(elemnt.type), 
        //  getTypeFormat(elemnt.type), 
         
        //  GL_FALSE,  
        //  m_iVertexOffSetSize, 
        //  pointer);
         
        glVertexAttribPointer(elemnt.index, 
         
         getTypeCount(elemnt.type), 
         getTypeFormat(elemnt.type), 
         
         GL_FALSE,  
         m_iVertexOffSetSize, 
         pointer);
    
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vec3), (void*)0);

         m_offSet += getTypeSize(elemnt.type);
         
     }

     
    //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vec3), (void*)0);
    //   glEnableVertexAttribArray(0); 
      
    //   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,  sizeof(Vec3), (void*)0);
    //   glEnableVertexAttribArray(0); 
      
    //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vec3), (void*)0);
    //   glEnableVertexAttribArray(0); 
    //  	glVertexPointer(2, GL_FLOAT, sizeof(S3DVertex), &(static_cast<const Vertex*>(vertices))[0].Pos);
        //   layout (location = 0) in vec3 aPos;
        // layout (location = 1) in vec4 aColor;
        // layout (location = 2) in vec2 aTexCoord;
		
        		// glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,pos)));
                // glEnableVertexAttribArray(0);
                // glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,color)));
                // glEnableVertexAttribArray(1);
                // glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,normal)));
                // glEnableVertexAttribArray(2);

// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0);
// glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
// glEnableVertexAttribArray(1);

     m_vertex_array->unBind();
     m_isDirty=false;
   }
   
private:
    VertexArray *m_vertex_array;
    IndexBuffer *m_index_buffer{nullptr};
    VertexBuffer *m_vertex_buffer{nullptr};
    VertexDeclaration *m_vertex_declaration;
    bool m_isDirty{true};

};



// class Mesh
// {

//     private:

//      struct Face
//     {
//         int a;
//         int b;
//         int c;
//         Vec3 na;
//         Vec3 nb;
//         Vec3 nc;
//         Vec2 a_uv;
//         Vec2 b_uv;
//         Vec2 c_uv;
//     } ;

//     std::vector<Surface*> surfaces;
//     public:
//         Mesh()
//         {

//         }
//         ~Mesh()
//         {
//             for (int i = 0; i <(int) surfaces.size(); i++) 
//             {
//                 delete surfaces[i];
//             }
//             surfaces.clear();
//          }
//         bool LoadObj(const std::string &file_name)
//         {
//             if (!FileExists(file_name.c_str()))
//             {
//                 Log(2," File %s don't exists",file_name.c_str());
//                 return false;
//             }
//                 std::vector<Vec3> vertices;   
//                 std::vector<Vec3> normals;   
//                 std::vector<Vec2> texcoords;      
//                 std::vector<Face>    faces;    

//             Surface *surf = new Surface();
//             FILE* file;
//             file = fopen(file_name.c_str(), "r");
//             if (!file)
//                 return false;
//             char line[1024];
//              while (fgets(line, 1024, file)) 
//             {
//                 // Vertex information
//                 if (strncmp(line, "v ", 2) == 0) 
//                 {
//                     Vec3 vertex ;
//                     sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
//                     vertices.push_back(vertex);
                    
//                 }
//                 if (strncmp(line, "vn ", 3) == 0) 
//                 {
//                     Vec3 vertex ;
//                     sscanf(line, "vn %f %f %f", &vertex.x, &vertex.y, &vertex.z);
//                     normals.push_back(vertex);
                    
//                 }
//                 // Texture coordinate information
//                 if (strncmp(line, "vt ", 3) == 0) 
//                 {
//                     Vec2 texcoord ;
//                     sscanf(line, "vt %f %f", &texcoord.x, &texcoord.y);
//                     texcoords.push_back(texcoord);
//                  }
//                 // Face information
//                 if (strncmp(line, "f ", 2) == 0)
//                 {
//                     int vertex_indices[3];
//                     int texture_indices[3];
//                     int normal_indices[3];
//                     sscanf(
//                         line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
//                         &vertex_indices[0], &texture_indices[0], &normal_indices[0],
//                         &vertex_indices[1], &texture_indices[1], &normal_indices[1],
//                         &vertex_indices[2], &texture_indices[2], &normal_indices[2]
//                     );
             
//                     Face face;
//                     face.a = vertex_indices[0];
//                     face.b = vertex_indices[1];
//                     face.c = vertex_indices[2];
//                     face.a_uv = texcoords[texture_indices[0] - 1];
//                     face.b_uv = texcoords[texture_indices[1] - 1];
//                     face.c_uv = texcoords[texture_indices[2] - 1];
//                     face.na = normals[normal_indices[0] - 1];
//                     face.nb = normals[normal_indices[1] - 1];
//                     face.nc = normals[normal_indices[2] - 1];
//                     faces.push_back(face);
//                 }
//             }

//             for (int i=0; i < (int)faces.size();i++)
//             {
                
//                 Vec3 v0 = vertices[faces[i].a - 1];
//                 Vec3 v1 = vertices[faces[i].b - 1];
//                 Vec3 v2 = vertices[faces[i].c - 1];


//                 Vec2 uv0 = faces[i].a_uv;
//                 Vec2 uv1 = faces[i].b_uv;
//                 Vec2 uv2 = faces[i].c_uv;

//                 Vec3 n0 = faces[i].na;
//                 Vec3 n1 = faces[i].nb;
//                 Vec3 n2 = faces[i].nc;

//                 //int f0 = surf->AddVertex(v0,n0,uv0);
//                 //int f1 = surf->AddVertex(v1,n1,uv1);
//                 //int f2 = surf->AddVertex(v2,n2,uv2);

//                 //surf->AddTriangle(f0,f1,f2);
//             }

//             fclose(file);

//             //surf->Build();
//             surfaces.push_back(surf);
//             return true;
//         }

//         void Render()
//         {
//              for (int i = 0; i <(int) surfaces.size(); i++) 
//             {
//                 Surface *surf = surfaces[i];
//                // surf->Render();
//             }
//         }
  
// };