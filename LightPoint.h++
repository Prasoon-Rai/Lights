//
// Created by Prasoon Rai on 11/11/25.
//

#ifndef LEARNRAYLIB_LIGHTPOINT_H
#define LEARNRAYLIB_LIGHTPOINT_H
#define RLIGHTS_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "raylights.h++"
#include <string>
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

class Lights_Point {
public:
    Light light;
    std::string name;
    Shader shader = LoadShader(TextFormat("/Users/prasoonrai/Desktop/LearnRaylib/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                           TextFormat("/Users/prasoonrai/Desktop/LearnRaylib/shaders/glsl%i/lighting.fs", GLSL_VERSION));

    Lights_Point(Vector3 position, Color color, bool enabled, std::string name) {
        light = CreateLight(LIGHT_POINT, position, Vector3Zero(), color, shader);
        light.enabled = enabled;
        this->name = name;
    };
    ~Lights_Point() {
        UnloadShader(shader);
    };
};

#endif //LEARNRAYLIB_LIGHTPOINT_H