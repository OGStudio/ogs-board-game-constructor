
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

// FEATURE Application+frame+Reporting/Include
// FEATURE Application+handleEvent-web/Include
// FEATURE Application+setupWindow-web/Include

// FEATURE Application+CameraManipulator/Include
// FEATURE Application+HTTPClient/Include
// FEATURE Application+Logging/Include
// FEATURE Application+MaterialPool/Include
// FEATURE Application+Mouse/Include
// FEATURE Application+NodePool/Include
// FEATURE Application+Rendering/Include
// FEATURE Application+ResourcePool/Include
// FEATURE Application+WindowResizing-web/Include

// FEATURE Example+loadCLIScript/Include

// FEATURE Example+ScriptingEnvironment/Include
// FEATURE Example+VBO/Include

// FEATURE MAIN_APPLICATION_LOG/Impl
// FEATURE MAIN_EXAMPLE_ENVIRONMENT_FUNCTION/Impl
// FEATURE MAIN_EXAMPLE_LOG/Impl
// FEATURE MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT/Impl

// FEATURE Example+StaticPluginOSG/Impl
// FEATURE Example+StaticPluginPNG/Impl

namespace bgc
{
namespace main
{

// FEATURE Application/Setup
            // FEATURE Application+Logging/Setup
            // FEATURE Application+Rendering/Setup
            // FEATURE Application+CameraManipulator/Setup
            // FEATURE Application+Mouse/Setup
            // FEATURE Application+NodePool/Setup
            // FEATURE Application+MaterialPool/Setup
            // FEATURE Application+ResourcePool/Setup
            // FEATURE Application+HTTPClient/Setup
            // FEATURE Application+HTTPClientProcessor/Setup
            // FEATURE Application+WindowResizing-web/Setup
// FEATURE Application/TearDown
            // FEATURE Application+HTTPClientProcessor/TearDown
            // FEATURE Application+HTTPClient/TearDown
            // FEATURE Application+MaterialPool/TearDown
            // FEATURE Application+NodePool/TearDown
            // FEATURE Application+ResourcePool/TearDown
            // FEATURE Application+Mouse/TearDown
            // FEATURE Application+Rendering/TearDown
            // FEATURE Application+Logging/TearDown
// FEATURE Application/Impl
    // FEATURE Application+camera/Impl
    // FEATURE Application+frame+Reporting/Impl
    // FEATURE Application+handleEvent-web/Impl
    // FEATURE Application+handleMousePress-android/Impl
    // FEATURE Application+run/Impl
    // FEATURE Application+setupWindow-desktop/Impl
    // FEATURE Application+setupWindow-embedded/Impl
    // FEATURE Application+setupWindow-ios/Impl
    // FEATURE Application+setupWindow-web/Impl

    // FEATURE Application+CameraManipulator/Impl
    // FEATURE Application+HTTPClient/Impl
    // FEATURE Application+HTTPClientProcessor/Impl
    // FEATURE Application+Logging/Impl
    // FEATURE Application+MaterialPool/Impl
    // FEATURE Application+Mouse/Impl
    // FEATURE Application+NodePool/Impl
    // FEATURE Application+Rendering/Impl
    // FEATURE Application+ResourcePool/Impl
    // FEATURE Application+WindowResizing-web/Impl
// FEATURE Application/End

// FEATURE Example+1.0.0/Title
// FEATURE Example+02/Title
// FEATURE Example+03/Title
// FEATURE Example+04/Title
// FEATURE Example+05/Title

// FEATURE Example/Setup
        // FEATURE Example+Parameters/Setup
        // FEATURE Example+VBO/Setup
        // FEATURE Example+ScriptingEnvironment/Setup
        // FEATURE Example+application.camera.clearColor/Setup
        // FEATURE Example+application.camera.nodeAtPosition/Setup
        // FEATURE Example+application.camera.position/Setup
        // FEATURE Example+application.camera.rotation/Setup
        // FEATURE Example+application.materialPool.createMaterial/Setup
        // FEATURE Example+application.materialPool.createMaterialCopy/Setup
        // FEATURE Example+application.materialPool.material.exists/Setup
        // FEATURE Example+application.materialPool.material.setShaders/Setup
        // FEATURE Example+application.materialPool.material.setUniform/Setup
        // FEATURE Example+application.mouse/Setup
        // FEATURE Example+application.nodePool.createNode/Setup
        // FEATURE Example+application.nodePool.createSphere/Setup
        // FEATURE Example+application.nodePool.node.addChild/Setup
        // FEATURE Example+application.nodePool.node.exists/Setup
        // FEATURE Example+application.nodePool.node.removeChild/Setup
        // FEATURE Example+application.nodePool.node.removeFromParents/Setup
        // FEATURE Example+application.nodePool.node.setMask/Setup
        // FEATURE Example+application.nodePool.node.setMaterial/Setup
        // FEATURE Example+application.nodePool.node.position/Setup
        // FEATURE Example+application.nodePool.node.rotation/Setup
        // FEATURE Example+application.parameters/Setup
        // FEATURE Example+application.resourcePool.loadResource/Setup
        // FEATURE Example+application.resourcePool.locations/Setup
        // FEATURE Example+application.resourcePool.resource.exists/Setup
        // FEATURE Example+LoadScriptTest/Setup
// FEATURE Example/TearDown
        // FEATURE Example+ScriptingEnvironment/TearDown
        // FEATURE Example+EnvironmentClients/TearDown
        // FEATURE Example+application.mouse/TearDown
// FEATURE Example/Impl
    // FEATURE Example+loadCLIScript/Impl

    // FEATURE Example+EnvironmentClients/Impl
    // FEATURE Example+LoadScriptTest/Impl
    // FEATURE Example+Parameters/Impl
    // FEATURE Example+ScriptingEnvironment/Impl
    // FEATURE Example+VBO/Impl

    // FEATURE Example+application.camera.clearColor/Impl
    // FEATURE Example+application.camera.nodeAtPosition/Impl
    // FEATURE Example+application.camera.position/Impl
    // FEATURE Example+application.camera.rotation/Impl
    // FEATURE Example+application.materialPool.createMaterial/Impl
    // FEATURE Example+application.materialPool.createMaterialCopy/Impl
    // FEATURE Example+application.materialPool.material.exists/Impl
    // FEATURE Example+application.materialPool.material.setShaders/Impl
    // FEATURE Example+application.materialPool.material.setUniform/Impl
    // FEATURE Example+application.mouse/Impl
    // FEATURE Example+application.nodePool.createNode/Impl
    // FEATURE Example+application.nodePool.createSphere/Impl
    // FEATURE Example+application.nodePool.node.addChild/Impl
    // FEATURE Example+application.nodePool.node.exists/Impl
    // FEATURE Example+application.nodePool.node.removeChild/Impl
    // FEATURE Example+application.nodePool.node.removeFromParents/Impl
    // FEATURE Example+application.nodePool.node.setMask/Impl
    // FEATURE Example+application.nodePool.node.setMaterial/Impl
    // FEATURE Example+application.nodePool.node.position/Impl
    // FEATURE Example+application.nodePool.node.rotation/Impl
    // FEATURE Example+application.parameters/Impl
    // FEATURE Example+application.resourcePool.loadResource/Impl
    // FEATURE Example+application.resourcePool.locations/Impl
    // FEATURE Example+application.resourcePool.resource.exists/Impl
// FEATURE Example/End

} // namespace main
} // namespace bgc

#endif // OGS_BOARD_GAME_CONSTRUCTOR_MAIN_H

