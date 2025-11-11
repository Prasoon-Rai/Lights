#include "raylib.h"
#include "raymath.h"
#include "LightPoint.h++"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");

    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load lighting shader
    Shader shader = LoadShader(TextFormat("shaders/glsl%i/lighting.vs", GLSL_VERSION),
                           TextFormat("shaders/glsl%i/lighting.fs", GLSL_VERSION));

    // Create models and assign shader
    Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 4.0f, 2.0f));
    cube.materials[0].shader = shader;

    Model plane = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 1, 1));
    plane.materials[0].shader = shader;

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 100, 100));
    sphere.materials[0].shader = shader;

    // Bake lights
    auto orange = Lights_Point((Vector3){ -2.0f, 1.0f, -2.0f }, ORANGE, true, "orange");
    auto red = Lights_Point((Vector3){ 2.0f, 1.0f, 2.0f }, RED, true, "red");
    auto pink = Lights_Point((Vector3){ -2.0f, 1.0f, 2.0f }, BLUE, true, "pink");

    SetTargetFPS(1000);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_O)) {
            orange.light.enabled = !orange.light.enabled;
        }
        UpdateLightValues(shader, orange.light);

        if (IsKeyPressed(KEY_R)) {
            red.light.enabled = !red.light.enabled;
        }
        UpdateLightValues(shader, red.light);

        if (IsKeyPressed(KEY_B)) {
            pink.light.enabled = !pink.light.enabled;
        }
        UpdateLightValues(shader, pink.light);


        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(plane, Vector3Zero(), 1.0f, WHITE);
                DrawModel(sphere, Vector3(0.0f, 2.0f, 0.0f), 1.0f, WHITE);

                // Draw sphere to show where the light is
                if (orange.light.enabled) DrawSphereEx(orange.light.position, 0.2f, 8, 8, orange.light.color);
                else DrawSphereWires(orange.light.position, 0.2f, 8, 8, ColorAlpha(orange.light.color, 0.3f));

                if (red.light.enabled) DrawSphereEx(red.light.position, 0.2f, 8, 8, red.light.color);
                else DrawSphereWires(red.light.position, 0.2f, 8, 8, ColorAlpha(red.light.color, 0.3f));

                if (pink.light.enabled) DrawSphereEx(pink.light.position, 0.2f, 8, 8, pink.light.color);
                else DrawSphereWires(pink.light.position, 0.2f, 8, 8, ColorAlpha(pink.light.color, 0.3f));

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadModel(cube);
    UnloadModel(plane);
    UnloadShader(shader);

    CloseWindow();

    return 0;
}
