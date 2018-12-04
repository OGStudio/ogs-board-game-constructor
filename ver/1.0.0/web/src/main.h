
/*
This file is part of OGS Board game constructor:
  https://github.com/OGStudio/ogs-board-game-constructor

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OGS_BOARD_GAME_CONSTRUCTOR_MAIN_H
#define OGS_BOARD_GAME_CONSTRUCTOR_MAIN_H

// Application+frame+Reporting Start
#include "core.h"

// Application+frame+Reporting End
// Application+handleEvent-web Start
#include <SDL2/SDL.h>

// Application+handleEvent-web End
// Application+setupWindow-web Start
#include <SDL2/SDL.h>

// Application+setupWindow-web End

// Application+HTTPClient Start
#include "network.h"

// Application+HTTPClient End
// Application+Logging Start
#include "log.h"

// Application+Logging End
// Application+Mouse Start
#include "input.h"

// Application+Mouse End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End
// Application+ResourcePool Start
#include "resource.h"

// Application+ResourcePool End

// Example+LoadEmbeddedAPIScript Start
#include "api.lua.h"
#include "resource.h"

// Example+LoadEmbeddedAPIScript End
// Example+LoadEmbeddedResources Start
#include "shaders/color.vert.h"
#include "shaders/color.frag.h"
#include "resource.h"

// Example+LoadEmbeddedResources End
// Example+LoadRemoteIndexScript Start
#include "network.h"

// Example+LoadRemoteIndexScript End
// Example+ScriptingEnvironment Start
#include "script.h"
#include <sol.hpp>

// Example+ScriptingEnvironment End

// MAIN_APPLICATION_LOG Start
#include "log.h"
#include "format.h"
#define MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// MAIN_APPLICATION_LOG End
// MAIN_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define MAIN_EXAMPLE_LOG_PREFIX "main::Example(%p) %s"
#define MAIN_EXAMPLE_LOG(...) \
    log::logprintf( \
        MAIN_EXAMPLE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// MAIN_EXAMPLE_LOG End


namespace bgc
{
namespace main
{

// Application Start
class Application
{
    public:
        Application(const std::string &name)
        {

// Application End
            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+Mouse Start
            this->setupMouse();
            
            // Application+Mouse End
            // Application+ResourcePool Start
            this->setupResourcePool();
            
            // Application+ResourcePool End
            // Application+HTTPClient Start
            this->setupHTTPClient();
            
            // Application+HTTPClient End
            // Application+HTTPClientProcessor Start
            this->setupHTTPClientProcessor();
            
            // Application+HTTPClientProcessor End
// Application Start
        }
        ~Application()
        {

// Application End
            // Application+HTTPClientProcessor Start
            this->tearHTTPClientProcessorDown();
            
            // Application+HTTPClientProcessor End
            // Application+HTTPClient Start
            this->tearHTTPClientDown();
            
            // Application+HTTPClient End
            // Application+ResourcePool Start
            this->tearResourcePoolDown();
            
            // Application+ResourcePool End
            // Application+Mouse Start
            this->tearMouseDown();
            
            // Application+Mouse End
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
// Application Start
        }

// Application End
    // Application+camera Start
    public:
        osg::Camera *camera()
        {
            return this->viewer->getCamera();
        }
    // Application+camera End
    // Application+frame+Reporting Start
    public:
        core::Reporter frameReporter;
        void frame()
        {
            this->viewer->frame();
            this->frameReporter.report();
        }
    // Application+frame+Reporting End
    // Application+handleEvent-web Start
    private:
        bool fingerEventsDetected = false;
    public:
        bool handleEvent(const SDL_Event &e)
        {
            // Get event queue.
            osgViewer::GraphicsWindow *gw =
                dynamic_cast<osgViewer::GraphicsWindow *>(
                    this->viewer->getCamera()->getGraphicsContext());
            if (!gw)
            {
                return false;
            }
            osgGA::EventQueue &queue = *(gw->getEventQueue());
    
            // Detect finger events.
            if (
                e.type == SDL_FINGERMOTION ||
                e.type == SDL_FINGERDOWN ||
                e.type == SDL_FINGERUP
            ) {
                this->fingerEventsDetected = true;
            }
            // Handle mouse events unless finger events are detected.
            if (!this->fingerEventsDetected)
            {
                return this->handleMouseEvent(e, queue);
            }
            // Handle finger events.
            return this->handleFingerEvent(e, queue);
        }
    
    private:
        bool handleFingerEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            int absX = this->windowWidth * e.tfinger.x;
            int absY = this->windowHeight * e.tfinger.y;
            auto correctedY = -(this->windowHeight - absY);
            switch (e.type)
            {
                case SDL_FINGERMOTION:
                    queue.mouseMotion(absX, correctedY);
                    return true;
                case SDL_FINGERDOWN: 
                    // NOTE We pass `1` to denote LMB.
                    queue.mouseButtonPress(absX, correctedY, 1);
                    return true;
                case SDL_FINGERUP:
                    // NOTE We pass `1` to denote LMB.
                    queue.mouseButtonRelease(absX, correctedY, 1);
                    return true;
                default:
                    break;
            }
            return false;
        }
    
        bool handleMouseEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            switch (e.type)
            {
                case SDL_MOUSEMOTION: {
                    auto correctedY = -(this->windowHeight - e.motion.y);
                    queue.mouseMotion(e.motion.x, correctedY);
                    return true;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonPress(e.button.x, correctedY, e.button.button);
                    return true;
                }
                case SDL_MOUSEBUTTONUP: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonRelease(e.button.x, correctedY, e.button.button);
                    return true;
                }
                default:
                    break;
            }
            return false;
        }
    // Application+handleEvent-web End
    // Application+setupWindow-embedded Start
    private:
        int windowWidth;
        int windowHeight;
    public:
        void setupWindow(int width, int height)
        {
            this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            this->windowWidth = width;
            this->windowHeight = height;
        }
    // Application+setupWindow-embedded End
    // Application+setupWindow-web Start
    private:
        SDL_Window *sdlWindow = 0;
    public:
        bool setupWindow(
            const std::string &title,
            int width,
            int height
        ) {
            this->configureSDLGLContext();
            this->sdlWindow =
                SDL_CreateWindow(
                    title.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    SDL_WINDOW_OPENGL
                );
            if (!this->sdlWindow)
            {
                MAIN_APPLICATION_LOG(
                    "ERROR Could not create SDL window: '%s'\n",
                    SDL_GetError()
                );
                return false;
            }
    
            SDL_GL_CreateContext(this->sdlWindow);
            this->setupWindow(width, height);
    
            return true;
        }
        void configureSDLGLContext()
        {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }
    // Application+setupWindow-web End

    // Application+HTTPClient Start
    public:
        network::HTTPClient *httpClient;
    private:
        void setupHTTPClient()
        {
            this->httpClient = new network::HTTPClient;
        }
        void tearHTTPClientDown()
        {
            delete this->httpClient;
        }
    // Application+HTTPClient End
    // Application+HTTPClientProcessor Start
    public:
        network::HTTPClientProcessor *httpClientProcessor;
    private:
        const std::string httpClientProcessorCallbackName = "HTTPClientProcessor";
    
        void setupHTTPClientProcessor()
        {
            this->httpClientProcessor = new network::HTTPClientProcessor(this->httpClient);
            // Subscribe processor to be processed each frame.
            this->frameReporter.addCallback(
                [&] {
                    this->httpClientProcessor->process();
                },
                this->httpClientProcessorCallbackName
            );
        }
        void tearHTTPClientProcessorDown()
        {
            this->frameReporter.removeCallback(this->httpClientProcessorCallbackName);
            delete this->httpClientProcessor;
        }
    // Application+HTTPClientProcessor End
    // Application+Logging Start
    private:
        log::Logger *logger;
        void setupLogging(const std::string &appName)
        {
            // Create custom logger.
            this->logger = new log::Logger(appName);
            // Provide the logger to OpenSceneGraph.
            osg::setNotifyHandler(this->logger);
            // Only accept notifications of Info level or higher
            // like warnings and errors.
            //osg::setNotifyLevel(osg::INFO);
            osg::setNotifyLevel(osg::WARN);
        }
        void tearLoggingDown()
        {
            // Remove the logger from OpenSceneGraph.
            // This also destroys the logger: no need to deallocate it manually.
            osg::setNotifyHandler(0);
        }
    // Application+Logging End
    // Application+Mouse Start
    public:
        osg::ref_ptr<input::Mouse> mouse;
    private:
        void setupMouse()
        {
            // Create mouse events' handler.
            this->mouse = new input::Mouse;
            // Register it.
            this->viewer->addEventHandler(this->mouse);
        }
        void tearMouseDown()
        {
            // This also removes Mouse instance.
            this->viewer->removeEventHandler(this->mouse);
        }
    // Application+Mouse End
    // Application+Rendering Start
    public:
        void setScene(osg::Node *scene)
        {
            // Make sure we reset the scene upon setting the same scene again.
            this->viewer->setSceneData(0);
            this->viewer->setSceneData(scene);
        }
    private:
        osgViewer::Viewer *viewer;
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            this->viewer = new osgViewer::Viewer;
            // Use single thread: CRITICAL for mobile and web.
            this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            // Create manipulator: CRITICAL for mobile and web.
            this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }
        void tearRenderingDown()
        {
            delete this->viewer;
        }
    // Application+Rendering End
    // Application+ResourcePool Start
    public:
        resource::Pool *resourcePool;
    private:
        void setupResourcePool()
        {
            this->resourcePool = new resource::Pool;
        }
        void tearResourcePoolDown()
        {
            delete this->resourcePool;
        }
    // Application+ResourcePool End
// Application Start
};
// Application End

// Example+1.0.0 Start
const auto EXAMPLE_TITLE = "ogstudio-1.0.0: Memory gameplay";
// Example+1.0.0 End

// Example Start
struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

// Example End
        // Example+Parameters Start
        this->setupParameters(parameters);
        
        // Example+Parameters End
        // Example+ScriptingEnvironment Start
        this->setupScriptingEnvironment();
        
        // Example+ScriptingEnvironment End

        // Example+KVC Start
        this->setupKVC();
        
        // Example+KVC End
        // Example+KVC+application.camera.clearColor Start
        this->kvc->registerKey(
            "application.camera.clearColor",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                auto camera = this->app->camera();
                // Set.
                if (!values.empty())
                {
                    // Report error if values' count is insufficient.
                    if (values.size() != 3)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 3"
                        );
                    }
                    // Apply color otherwise.
                    else
                    {
                        auto color = camera->getClearColor();
                        color.r() = atof(values[0].c_str());
                        color.g() = atof(values[1].c_str());
                        color.b() = atof(values[2].c_str());
                        camera->setClearColor(color);
                    }
                }
        
                // Return current color for Get and after Set.
                auto color = camera->getClearColor();
                return std::vector<std::string>({
                    format::printfString("%f", color.r()),
                    format::printfString("%f", color.g()),
                    format::printfString("%f", color.b()),
                });
            )
        );
        // Example+KVC+application.camera.clearColor End
        // Example+KVC+application.mouse Start
        this->setupApplicationMouse();
        
        // Example+KVC+application.mouse End

        // Example+LoadEmbeddedAPIScript Start
        this->loadEmbeddedAPIScript();
        
        // Example+LoadEmbeddedAPIScript End
        // Example+LoadEmbeddedResources Start
        this->loadEmbeddedResources();
        
        // Example+LoadEmbeddedResources End
        // Example+LoadRemoteIndexScript Start
        this->loadRemoteIndexScript();
        
        // Example+LoadRemoteIndexScript End

// Example Start
    }
    ~Example()
    {

// Example End
        // Example+ScriptingEnvironment Start
        this->tearScriptingEnvironmentDown();
        
        // Example+ScriptingEnvironment End
        // Example+KVC+application.mouse Start
        this->tearApplicationMouseDown();
        
        // Example+KVC+application.mouse End
        // Example+KVC Start
        this->tearKVCDown();
        
        // Example+KVC End
// Example Start
        delete this->app;
    }

// Example End
    // Example+KVC Start
    private:
        script::KVC *kvc;
        void setupKVC()
        {
            this->kvc = new script::KVC(this->environment);
        }
        void tearKVCDown()
        {
            delete this->kvc;
        }
    // Example+KVC End
    // Example+KVC+application.mouse Start
    private:
        const std::string applicationMousePressedButtonsKey =
            "application.mouse.pressedButtons";
        const std::string applicationMousePositionKey =
            "application.mouse.position";
        const std::string applicationMouseCallbackName =
            "ApplicationMouseTransmitter";
    
        void setupApplicationMouse()
        {
            // Transmit pressed buttons.
            this->app->mouse->pressedButtonsChanged.addCallback(
                [=] {
                    this->transmitApplicationMouseButtons();
                },
                this->applicationMouseCallbackName
            );
            // Transmit position.
            this->app->mouse->positionChanged.addCallback(
                [=] {
                    this->transmitApplicationMousePosition();
                },
                this->applicationMouseCallbackName
            );
            // NOTE We don't provide getters because Lua side
            // NOTE should keep the state itself.
            // NOTE Also, we don't provide setters because C++ side
            // NOTE has no such notion.
        }
        void tearApplicationMouseDown()
        {
            this->app->mouse->pressedButtonsChanged.removeCallback(
                this->applicationMouseCallbackName
            );
            this->app->mouse->positionChanged.removeCallback(
                this->applicationMouseCallbackName
            );
        }
        void transmitApplicationMouseButtons()
        {
            // Convert buttons to string representation.
            auto buttons = this->app->mouse->pressedButtons;
            std::vector<std::string> strbuttons;
            for (auto button : buttons)
            {
                strbuttons.push_back(mouseButtonToString(button));
            }
            // Transmit.
            this->environment->call(
                this->applicationMousePressedButtonsKey,
                strbuttons
            );
        }
        void transmitApplicationMousePosition()
        {
            // Convert position to string representation.
            auto position = this->app->mouse->position;
            std::vector<std::string> strposition = {
                format::printfString("%f", position.x()),
                format::printfString("%f", position.y()),
            };
            // Transmit.
            this->environment->call(
                this->applicationMousePositionKey,
                strposition
            );
        }
    // Example+KVC+application.mouse End
    // Example+Parameters Start
    private:
        Parameters parameters;
        void setupParameters(const Parameters &parameters)
        {
            this->parameters = parameters;
        }
    // Example+Parameters End
    // Example+ScriptingEnvironment Start
    private:
        script::Environment *environment;
        sol::state *lua;
    
        void setupScriptingEnvironment()
        {
            this->environment = new script::Environment;
    
            this->lua = new sol::state;
            this->lua->open_libraries();
            // Register Environment instance.
            (*this->lua)["ENV"] = this->environment;
            // Register Environment class.
            this->lua->new_usertype<script::Environment>(
                "Environment",
                // 'setVerbose' method.
                "setVerbose",
                [](script::Environment &env, bool state)
                {
                    env.setVerbose(state);
                },
                // 'addClient' method.
                "addClient",
                [](script::Environment &env, script::EnvironmentClient *client, sol::nested<std::vector<std::string> > keys)
                {
                    env.addClient(client, keys);
                },
                //&script::Environment::addClient,
                // 'call' method.
                "call",
                [](script::Environment &env, const std::string &key, sol::nested<std::vector<std::string> > values)
                {
                    return env.call(key, values);
                }
            );
            // Register EnvironmentClient class.
            this->lua->new_usertype<script::EnvironmentClient>(
                "EnvironmentClient",
                // 'call' method.
                "call",
                sol::property(
                    [](script::EnvironmentClient &ec, sol::function luaCallback)
                    {
                        ec.call =
                            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                                sol::nested<std::vector<std::string> > result =
                                    luaCallback(key, sol::as_table(values));
                                return std::move(result.source);
                            );
                    }
                )
            );
        }
        void tearScriptingEnvironmentDown()
        {
            delete this->lua;
            delete this->environment;
        }
        void executeScript(const std::string &contents)
        {
            // Try to execute the script.
            try {
                this->lua->script(contents);
                MAIN_EXAMPLE_LOG("Successfully executed script");
            }
            catch (const std::exception &e)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not execute script. %s",
                    e.what()
                );
            }
        }
    // Example+ScriptingEnvironment End
    // Example+LoadEmbeddedAPIScript Start
    private:
        void loadEmbeddedAPIScript()
        {
            MAIN_EXAMPLE_LOG("Loading embedded API script");
            resource::Resource apiRes(
                "scripts",
                "api.lua",
                api_lua,
                api_lua_len
            );
            // Execute the script.
            try {
                this->lua->script(apiRes.contents);
                MAIN_EXAMPLE_LOG("Successfully loaded embedded API script");
            }
            catch (const std::exception &e)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not load embedded API script. %s",
                    e.what()
                );
            }
        }
    // Example+LoadEmbeddedAPIScript End
    // Example+LoadEmbeddedResources Start
    private:
        void loadEmbeddedResources()
        {
            auto resourcePool = this->app->resourcePool;
            resourcePool->addResource(
                resource::Resource(
                    "shaders",
                    "color.vert",
                    color_vert,
                    color_vert_len
                )
            );
            resourcePool->addResource(
                resource::Resource(
                    "shaders",
                    "color.frag",
                    color_frag,
                    color_frag_len
                )
            );
        }
    // Example+LoadEmbeddedResources End
    // Example+LoadRemoteIndexScript Start
    private:
        void loadRemoteIndexScript()
        {
            // Make sure `base` parameter exists.
            auto it = this->parameters.find("base");
            if (it == this->parameters.end())
            {
                MAIN_EXAMPLE_LOG(
                    "WARNING Not loading `index.lua` "
                    "because `base` parameter is missing"
                );
                return;
            }
    
            auto base = it->second;
            auto path = base + "/index.lua";
            MAIN_EXAMPLE_LOG("Loading a script from '%s'", path.c_str());
    
            auto success = [&](std::string response) {
                MAIN_EXAMPLE_LOG("Successfully loaded the script");
                this->executeScript(response);
            };
            auto failure = [&](std::string reason) {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not load the script. '%s'",
                    reason.c_str()
                );
            };
            // GET.
            this->app->httpClient->get(path, success, failure);
        }
    // Example+LoadRemoteIndexScript End
// Example Start
};
// Example End

} // namespace main
} // namespace bgc

#endif // OGS_BOARD_GAME_CONSTRUCTOR_MAIN_H

