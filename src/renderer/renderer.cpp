#include "renderer.h"


Renderer::Renderer()
{
    
}


int Renderer::runRenderer()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(renderWidth, renderHeight, "Tracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    gladLoadGL();

    ImGui_ImplGlfwGL3_Init(window, true);

    lumenGUI.setRenderResolution(renderWidth, renderHeight);

    renderCamera.setCamera(glm::vec2(renderWidth, renderHeight));

    quadRenderShader.setShader("res/shaders/quadRender.vert", "res/shaders/quadRender.frag");
    initQuadRender();

    initScene();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //--------------
        // GUI setting & callbacks
        //--------------
        lumenGUI.setupGUI();

        ImGuiIO& io = ImGui::GetIO();
        ImVec2 currentMousePos = ImGui::GetMousePos();

        keyboardCallback(&io);

        if (lastPosX !=  currentMousePos.x || lastPosY != currentMousePos.y)
            mouseCallback(&io, currentMousePos.x, currentMousePos.y);

        //--------------
        // CPU Rendering
        //--------------
        if (renderReset) // If anything in camera or scene data has changed, we flush the CUDA data and reinit them again
            resetRender();

        frameCounter++;

        // RENDER CODE

        quadRenderShader.useShader();
        displayGLBuffer();

        //----------------
        // GUI rendering
        //----------------
        lumenGUI.renderGUI();

        glfwSwapBuffers(window);
    }

    //---------
    // Cleaning
    //---------
    lumenGUI.stopGUI();
    cleanScene();

    glfwTerminate();

    return 0;
}


void Renderer::initQuadRender()
{
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
}


void Renderer::cleanQuadRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glDeleteBuffers(1, &quadVBO);

    quadVBO = 0;
}


void Renderer::initScene()
{
    Scene testScene;
    testScene.loadScene("res/scenes/testScene.txt");

    sphereCount = testScene.getSphereCount();
    spheresList = testScene.getSceneSpheresList();

//    std::cout << "SPHERECOUNT : " << sphereCount << std::endl;
//    for(int i = 0; i < sphereCount; i++)
//    {
//        std::cout << "RADIUS : " << spheresList[i].radius << std::endl;
//        std::cout << "POS X : " << spheresList[i].position.x << " POS Y : " << spheresList[i].position.y << " POS Z : " << spheresList[i].position.z << std::endl;
//        std::cout << "COL R : " << spheresList[i].color.x << " COL G : " << spheresList[i].color.y << " COL B: " << spheresList[i].color.z << std::endl;
//        std::cout << "EMI R : " << spheresList[i].emissiveColor.x << " EMI G : " << spheresList[i].emissiveColor.y << " EMI B : " << spheresList[i].emissiveColor.z << std::endl;
//        std::cout << "///////////////" << std::endl;
//    }
}


void Renderer::cleanScene()
{
    sphereCount = 0;
    delete[] spheresList;
}


void Renderer::resetRender()
{
    frameCounter = 0;
    // RESET CODE

    renderReset = false;
}


void Renderer::displayGLBuffer()
{
    glBindVertexArray(this->quadVAO);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}


void Renderer::keyboardCallback(ImGuiIO* guiIO)
{
    if (guiIO->KeysDown[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (guiIO->KeysDown[GLFW_KEY_W])
    {
        renderCamera.keyboardCall(FORWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_S])
    {
        renderCamera.keyboardCall(BACKWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_A])
    {
        renderCamera.keyboardCall(LEFT, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_D])
    {
        renderCamera.keyboardCall(RIGHT, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_KP_ADD])
    {
        if (guiIO->KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() + 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() + 0.005f);

        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (guiIO->KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() - 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() - 0.005f);

        renderReset = true;
    }
}


void Renderer::mouseCallback(ImGuiIO* guiIO, float mousePosX, float mousePosY)
{
    if (firstMouse)
    {
        lastPosX = mousePosX;
        lastPosY = mousePosY;
        firstMouse = false;
    }

    float offsetX = mousePosX - lastPosX;
    float offsetY = mousePosY - lastPosY;

    lastPosX = mousePosX;
    lastPosY = mousePosY;

    if (guiIO->MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (offsetX != 0 || offsetY != 0)
        {
            renderCamera.mouseCall(offsetX, offsetY, true);
            renderReset = true;
        }
    }
}
