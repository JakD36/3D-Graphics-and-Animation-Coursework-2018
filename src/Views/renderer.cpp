#include "Renderer.hpp"

using namespace std;

void Renderer::SetViewport(float x, float y, float width, float height){
    m_viewportX = x;
    m_viewportY = y;
    m_viewportWidth = width;
    m_viewportHeight = height;
}

void Renderer::SetWindowDimensions(int windowWidth, int windowHeight){
    this->m_windowWidth = windowWidth;
    this->m_windowHeight = windowHeight;
    
    // Update viewport so its size is appropriate for the new window!
    int width, height;
    glfwGetFramebufferSize(p_window, &width, &height);
}

// Initialise the Renderer for this viewport
Renderer::Renderer(GLFWwindow* window) {
    int profiler = ProfilerService::GetInstance()->StartTimer("Renderer Initialisation");

    p_window = window;

    // Grab the window dimensions for the current window, saves passing too many arguments to the constructor
    glfwGetWindowSize(p_window, &m_windowWidth, &m_windowHeight);

    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

    // TwoPassFramebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

//    m_framebuffer = new TwoPassFramebuffer(frameWidth, frameHeight);
    m_framebuffer = new SinglePassFramebuffer();

    ProfilerService::GetInstance()->StopTimer(profiler);
}

Renderer::~Renderer()
{
    delete m_framebuffer;
    m_framebuffer = NULL;
}

void Renderer::Render(SceneGraph* scene){
    int profiler = ProfilerService::GetInstance()->StartTimer("Render");

    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

    m_framebuffer->RenderTo();
    RenderScene(scene,0, 0, frameWidth, frameHeight);
    m_framebuffer->PostRender(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);

    ProfilerService::GetInstance()->StopTimer(profiler);
}

void Renderer::RenderScene(SceneGraph *scene, int viewportX, int viewportY, int viewportWidth, int viewportHeight)
{
    // Convert all our projected coordinates to screen coordinates for the texture
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewportX, viewportY, viewportWidth, viewportHeight);

    glClearBufferfv(GL_COLOR, 0, &m_clearColour[0]);
    static const GLfloat one = 1.0f;

    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    Camera* camera = scene->GetCamera();
    glm::mat4 viewMatrix = camera->BuildViewMat();

    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<GameObject*> Objs = scene->GetObjs();
    LightStruct* p_lights = scene->GetLights();
    LightStruct lights[LIGHTSN];

    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(p_lights + n);
    }

    printf("Pre Block Binding = %d\n\n",(int)glGetError());
    vector<ProgramInfo>* programs = ShaderManager::GetInstance()->GetShaderPrograms();
    int programCount = programs->size();
    for(int i = 0; i < programCount; ++i)
    {
        GLuint index = glGetUniformBlockIndex((*programs)[i].program,"lightBlock");
        printf("%s %d\n\n",(*programs)[i].path.c_str(),index);
        printf("Mid Block Binding = %s\n\n",(char*)glewGetErrorString(glGetError()));
        glUniformBlockBinding((*programs)[i].program, index, 0);
    }
    GLenum error = glGetError();
    printf("Post Block Binding = %d %s\n\n",error,(char*)glewGetErrorString(error));

    lights[2].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[2].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    lights[3].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[3].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    printf("Pre light buffer = %d\n\n",(int)glGetError());

    m_lightUbo.UpdateData(lights);

    printf("Post light buffer = %d\n\n",(int)glGetError());

    glm::vec3 camPos = camera->GetPosition();
    glm::mat4 projMatrix = camera->GetCachedProjMat();

    printf("Pre Object Render = %d\n\n",(int)glGetError());
    for(int n = 0;n<Objs.size();n++)
    {
        Objs[n]->Render(*camera);
    }
    printf("Post Object Render = %d\n\n",(int)glGetError());
}