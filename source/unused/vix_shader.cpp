#include <vix_shader.h>

namespace Vixen {

	//////////////////////////////////////////////////////////////////////////
	Shader::Shader(void)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	Shader::~Shader(void)
	{
		//delete program
		glDeleteProgram(m_program);
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::initFromFile(const std::string& vShaderPath, const std::string& fShaderPath)
	{
		//if program doesn't exit, create one
		if (!glIsProgram(m_program))
		{
			m_program = glCreateProgram();
		}
		//grab source from files
		const GLchar* vShaderSrc = readShader(vShaderPath);
		const GLchar* fShaderSrc = readShader(fShaderPath);
		//load shader files
		loadShader(GL_VERTEX_SHADER, vShaderSrc);
		loadShader(GL_FRAGMENT_SHADER, fShaderSrc);
#ifdef _DEBUG
		printf("Shader initialized.\n");
#endif
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::initFromString(const std::string& vShaderStr, const std::string& fShaderStr)
	{
		//if program doesn't exit, create one
		if (!glIsProgram(m_program))
		{
			m_program = glCreateProgram();
		}
		//load shader files
		loadShaderStr(GL_VERTEX_SHADER, vShaderStr.c_str());
		loadShaderStr(GL_FRAGMENT_SHADER, fShaderStr.c_str());
#ifdef _DEBUG
		printf("Shader initialized.\n");
#endif // _DEBUG
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::bind()
	{
		//bind shader to opengl pipeline
		glUseProgram(m_program);
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::unbind()
	{
		//unbind program from shader pipeline
		glUseProgram(NULL);
	}
	//////////////////////////////////////////////////////////////////////////
	const GLuint Shader::getProgramID() const
	{
		return m_program;
	}
	//////////////////////////////////////////////////////////////////////////
	const GLuint Shader::getUniformLoc(const GLchar* name) const
	{
		GLuint location = glGetUniformLocation(m_program, name);
		if (location < 0) {
			printf("Uniform Location Error: %s\n", glGetError());
		}
		return location;
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::loadShader(GLenum shaderType, const GLchar* source)
	{
		//check if source is valid
		if (source == nullptr)
			return;
		//create shader object
		GLuint shader = glCreateShader(shaderType);
		//put shader source into memory
		glShaderSource(shader, 1, &source, nullptr);
		delete[] source;
		//compile shader
		glCompileShader(shader);
		if (!checkCompiled(shader)) return;
		//attach shader object to program
		glAttachShader(m_program, shader);
		//link program
		glLinkProgram(m_program);
		if (!checkLinked(m_program))
		{
			glDeleteShader(shader);
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	bool Shader::checkLinked(GLuint program)
	{
		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked); //check linked
		if (!linked)
		{
#ifdef _DEBUG
			GLsizei length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			GLchar* log = new GLchar[length + 1];
			glGetProgramInfoLog(program, length, &length, log);
			printf("Shader Program Linking Failed: %s\n", log);
			delete[] log;
#endif
			return false; //program link failed
		}
		return true; //program link success
	}
	//////////////////////////////////////////////////////////////////////////
	bool Shader::checkCompiled(GLuint shader)
	{
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); //get compile status
		if (!compiled) //if compilation failed
		{
#ifdef _DEBUG
			GLsizei length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			//output shader error info
			GLchar* log = new GLchar[length + 1];
			glGetShaderInfoLog(shader, length, &length, log);
			printf("Shader compilation failed: %s\n", log);
			delete[] log;
#endif
			return false; //shader compilation failure
		}
		return true; //shader compilation success
	}
	//////////////////////////////////////////////////////////////////////////
	const GLchar* Shader::readShader(const std::string& fileName)
	{
		//file object
		FILE* infile;
#ifdef _WIN32
		fopen_s(&infile, fileName.c_str(), "rb");
#else
		infile = fopen(fileName.c_str(), "rb");
#endif
		if (!infile)
		{
#ifdef _DEBUG
			printf("Unable to open file: %s\n", fileName.c_str());
#endif
			return nullptr;
		}
		//seek end of file
		fseek(infile, 0, SEEK_END);
		//cache length in bytes
		int len = ftell(infile);
		//seek beginning of file
		fseek(infile, 0, SEEK_SET);
		//source buffer
		GLchar* source = new GLchar[len + 1];
		//read file into buffer
		fread(source, 1, len, infile);
		//close file after reading
		fclose(infile);
		//null terminate
		source[len] = 0;
		//return shader string
		return const_cast<const GLchar*>(source);
	}
	//////////////////////////////////////////////////////////////////////////
	void Shader::loadShaderStr(GLenum shaderType, const char* source)
	{
		if (source == nullptr)
			return;
		GLuint shader = glCreateShader(shaderType);
		//put our shader source into memory
		glShaderSource(shader, 1, &source, nullptr);
		//try to compile our shader
		glCompileShader(shader);
		if (!checkCompiled(shader))
		{
			//return from function
			return;
		}
		//we attach our shader object to our program
		glAttachShader(m_program, shader);
		//link program
		glLinkProgram(m_program);
		if (!checkLinked(m_program))
		{
			glDeleteShader(shader);
			return;
		}
	}
}