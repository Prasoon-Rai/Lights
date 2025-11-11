#include "raylib.h"
#include "raymath.h"
#include "LightPoint.h++"

const int ring = 50;
const int slices = 50;

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "basic lighting in raylib");

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

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, ring, slices));
    sphere.materials[0].shader = shader;

    // Bake lights
    auto orange = Lights_Point((Vector3){ -2.0f, 1.0f, -2.0f }, ORANGE, true, "orange");
    auto red = Lights_Point((Vector3){ 2.0f, 1.0f, 2.0f }, RED, true, "red");
    auto pink = Lights_Point((Vector3){ -2.0f, 1.0f, 2.0f }, PINK, true, "pink");
    auto blue = Lights_Point((Vector3){ 2.0f, 1.0f, -2.0f }, BLUE, true, "blue");

    SetTargetFPS(120);

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

        if (IsKeyPressed(KEY_P)) {
            pink.light.enabled = !pink.light.enabled;
        }
        UpdateLightValues(shader, pink.light);

        if (IsKeyPressed(KEY_B)) {
            blue.light.enabled = !blue.light.enabled;
        }
        UpdateLightValues(shader, blue.light);


        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

                DrawModel(plane, Vector3Zero(), 1.0f, WHITE);
                DrawModel(sphere, Vector3(0.0f, 2.0f, 0.0f), 1.0f, WHITE);

                // Draw sphere to show where the light is
                if (orange.light.enabled) DrawSphereEx(orange.light.position, 0.2f, ring, slices, orange.light.color);
                else DrawSphereWires(orange.light.position, 0.2f, ring, slices, ColorAlpha(orange.light.color, 0.3f));

                if (red.light.enabled) DrawSphereEx(red.light.position, 0.2f, ring, slices, red.light.color);
                else DrawSphereWires(red.light.position, 0.2f, ring, slices, ColorAlpha(red.light.color, 0.3f));

                if (pink.light.enabled) DrawSphereEx(pink.light.position, 0.2f, ring, slices, pink.light.color);
                else DrawSphereWires(pink.light.position, 0.2f, ring, slices, ColorAlpha(pink.light.color, 0.3f));

                if (blue.light.enabled) DrawSphereEx(blue.light.position, 0.2f, ring, slices, blue.light.color);
                else DrawSphereWires(blue.light.position, 0.2f, ring, slices, ColorAlpha(blue.light.color, 0.3f));

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
