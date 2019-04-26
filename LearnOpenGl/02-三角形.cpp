#define GLEW_STATIC //使用静态链接库
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

//定义的顶点坐标数据
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

//顶点着色器设置源码
const char* vertexShaderSource =
"#version 330 core                   \n"
"layout (location = 0) in vec3 aPos; \n"
"void main(){                        \n"
"        gl_Position=vec4(aPos.x , aPos.y , aPos.z, 1.0);} \n";

//片段着色器设置源码
const char* fragmentShaderSource =
"#version 330 core   \n"
"out vec4 FragColor; \n"
"void main() { \n"
"        FragColor = vec4 (1.0f, 0.5f, 0.2f, 1.0f);} \n";




//回调函数
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//按住Escape键
		glfwSetWindowShouldClose(window, true);//退出窗口
	}
}
int main() {


	//固定格式
	glfwInit();//初始化GLFW库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//定义最高版本为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//定义最低版本为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);//创建一个窗口800×600 第三个参数为标题名
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();//关闭中止窗口
		return -1;
	}
	glfwMakeContextCurrent(window); //选择当前的window作为主线程

									//Init GLEW
	glewExperimental = true; //能让GLEW在管理OpenGL的函数指针时更多地使用现代化的技术
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//前两个参数是窗口的左下角的位置，后两个参数设置宽高


							   //顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //1代表一个id 
	glBindVertexArray(VAO);//绑定VAO
						   /*
						   unsigned int VAO[10];
						   glGenVertexArrays(10,VAO);//如果有多个VAO 传入数组名当作首地址
						   */

						   //顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);//同理 1代表一个id 生成一个VBO对象
						  //把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER.
									   //我们使用的任何在GL_ARRAY_BUFFER目标上的缓冲调用都会用来配置当前绑定的缓冲（VBO）
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将之前定义的顶点数据复制到缓冲的内存中


																			  /*
																			  glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
																			  它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
																			  第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
																			  第三个参数是我们希望发送的实际数据。
																			  第四个参数指定了我们希望显卡如何管理给定的数据。
																			  它有三种形式：
																			  GL_STATIC_DRAW ：数据不会或几乎不会改变。
																			  GL_DYNAMIC_DRAW：数据会被改变很多。
																			  GL_STREAM_DRAW ：数据每次绘制时都会改变。
																			  三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW。
																			  如果，比如说一个缓冲中的数据将频繁被改变，那么使用的类型就是GL_DYNAMIC_DRAW或GL_STREAM_DRAW，
																			  这样就能确保显卡把数据放在能够高速写入的内存部分。
																			  */

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。
	//第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
	glCompileShader(vertexShader);//编译顶点着色器


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建片段着色器
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);//编译片段着色器

									//如果要使用刚才编译的着色器我们必须把它们链接称为一个着色器程序对象,
									//然后在渲染对象的时候激活这个着色器程序。
									//创建一个程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//需要把之前编译的着色器附加到程序对象上，然后用glLinkProgram链接它们
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);//attach 英文翻译 依附 
	glLinkProgram(shaderProgram);

	// 用来判断是否连接成功
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


	//为了不让我们的程序花了一个简单的图像就立即退出或者关闭窗口，我们需要创建一个渲染循环(render loop)
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3, 1.0f);//当调用glClear()清除颜色缓冲之后，整个颜色缓冲会被填充为设置里的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);//画三角形 从下标为0的顶点开始 画3个顶点


		glfwSwapBuffers(window);//分为front buffer和back buffer,front buffer解决最终输出在屏幕上的图片,
								//在渲染的时候都是在back buffer中进行,一旦渲染指令完成了，就交换back buffer和front buffer完成目标
		glfwPollEvents();//接受用户的交互操作指令

	}

	glfwTerminate();//释放GLFW分配的内存
	return 0;
}



