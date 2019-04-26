#define GLEW_STATIC //ʹ�þ�̬���ӿ�
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

//����Ķ�����������
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

//������ɫ������Դ��
const char* vertexShaderSource =
"#version 330 core                   \n"
"layout (location = 0) in vec3 aPos; \n"
"void main(){                        \n"
"        gl_Position=vec4(aPos.x , aPos.y , aPos.z, 1.0);} \n";

//Ƭ����ɫ������Դ��
const char* fragmentShaderSource =
"#version 330 core   \n"
"out vec4 FragColor; \n"
"void main() { \n"
"        FragColor = vec4 (1.0f, 0.5f, 0.2f, 1.0f);} \n";




//�ص�����
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//��סEscape��
		glfwSetWindowShouldClose(window, true);//�˳�����
	}
}
int main() {


	//�̶���ʽ
	glfwInit();//��ʼ��GLFW��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//������߰汾Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//������Ͱ汾Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);//����һ������800��600 ����������Ϊ������
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();//�ر���ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window); //ѡ��ǰ��window��Ϊ���߳�

									//Init GLEW
	glewExperimental = true; //����GLEW�ڹ���OpenGL�ĺ���ָ��ʱ�����ʹ���ִ����ļ���
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//ǰ���������Ǵ��ڵ����½ǵ�λ�ã��������������ÿ��


							   //�����������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //1����һ��id 
	glBindVertexArray(VAO);//��VAO
						   /*
						   unsigned int VAO[10];
						   glGenVertexArrays(10,VAO);//����ж��VAO ���������������׵�ַ
						   */

						   //���㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);//ͬ�� 1����һ��id ����һ��VBO����
						  //���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���㻺�����Ļ���������GL_ARRAY_BUFFER.
									   //����ʹ�õ��κ���GL_ARRAY_BUFFERĿ���ϵĻ�����ö����������õ�ǰ�󶨵Ļ��壨VBO��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���


																			  /*
																			  glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
																			  ���ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
																			  �ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�
																			  ����������������ϣ�����͵�ʵ�����ݡ�
																			  ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�
																			  ����������ʽ��
																			  GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
																			  GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
																			  GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
																			  �����ε�λ�����ݲ���ı䣬ÿ����Ⱦ����ʱ������ԭ������������ʹ�����������GL_STATIC_DRAW��
																			  ���������˵һ�������е����ݽ�Ƶ�����ı䣬��ôʹ�õ����;���GL_DYNAMIC_DRAW��GL_STREAM_DRAW��
																			  ��������ȷ���Կ������ݷ����ܹ�����д����ڴ沿�֡�
																			  */

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ����
	//�����������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
	glCompileShader(vertexShader);//���붥����ɫ��


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//����Ƭ����ɫ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);//����Ƭ����ɫ��

									//���Ҫʹ�øղű������ɫ�����Ǳ�����������ӳ�Ϊһ����ɫ���������,
									//Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
									//����һ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//��Ҫ��֮ǰ�������ɫ�����ӵ���������ϣ�Ȼ����glLinkProgram��������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);//attach Ӣ�ķ��� ���� 
	glLinkProgram(shaderProgram);

	// �����ж��Ƿ����ӳɹ�
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Program::LINK_FAILED\n" << infoLog << std::endl;
	}





	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Ϊ�˲������ǵĳ�����һ���򵥵�ͼ��������˳����߹رմ��ڣ�������Ҫ����һ����Ⱦѭ��(render loop)
	while (!glfwWindowShouldClose(window))
	{
		//����
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3, 1.0f);//������glClear()�����ɫ����֮��������ɫ����ᱻ���Ϊ���������ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ����

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);//�������� ���±�Ϊ0�Ķ��㿪ʼ ��3������


		glfwSwapBuffers(window);//��Ϊfront buffer��back buffer,front buffer��������������Ļ�ϵ�ͼƬ,
								//����Ⱦ��ʱ������back buffer�н���,һ����Ⱦָ������ˣ��ͽ���back buffer��front buffer���Ŀ��
		glfwPollEvents();//�����û��Ľ�������ָ��

	}

	glfwTerminate();//�ͷ�GLFW������ڴ�
	return 0;
}



