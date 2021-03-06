#define GLEW_STATIC //使用静态链接库
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

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

							   //为了不让我们的程序花了一个简单的图像就立即退出或者关闭窗口，我们需要创建一个渲染循环(render loop)
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		glClearColor(1.0f, 1.0f, 0, 1.0f);//当调用glClear()清除颜色缓冲之后，整个颜色缓冲会被填充为设置里的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲


		glfwSwapBuffers(window);//分为front buffer和back buffer,front buffer解决最终输出在屏幕上的图片,
								//在渲染的时候都是在back buffer中进行,一旦渲染指令完成了，就交换back buffer和front buffer完成目标
		glfwPollEvents();//接受用户的交互操作指令

	}

	glfwTerminate();//释放GLFW分配的内存
	return 0;
}