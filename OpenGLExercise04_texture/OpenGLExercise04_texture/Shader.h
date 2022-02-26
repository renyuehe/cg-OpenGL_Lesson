#pragma once
#include <string>

class Shader
{
public:
	Shader(const char *, const char *);
	~Shader();

	const char* vertexSource;
	const char* fragmentSource;

	std::string vertexString;
	std::string fragmentString;

	unsigned int ID; //Shader Program ID

	void use();
private:

	void checkCompileErrors(unsigned int ID, std::string type);
};

