# Lights in Raylib 3D

## What is this project?

The project is a very basic demonstration of creating lights in Raylib in 3D.

## Adding your own light 

You must add the following lines to the ```main.cpp``` file in order to add your own light.

```
// Create a new point light
auto myLight = Lights_Point(
    (Vector3){ x, y, z },     // Position in 3D space
    COLOR,                     // Color (e.g., GREEN, PURPLE, YELLOW)
    true,                      // Enabled state
    "myLightName"             // Identifier string
);

// In the game loop, update the light
UpdateLightValues(shader, myLight.light);

// Optional: Add keyboard toggle
if (IsKeyPressed(KEY_YOUR_KEY)) {
    myLight.light.enabled = !myLight.light.enabled;
}

// Visualize the light position
if (myLight.light.enabled) 
    DrawSphereEx(myLight.light.position, 0.2f, 8, 8, myLight.light.color);
else 
    DrawSphereWires(myLight.light.position, 0.2f, 8, 8, 
                    ColorAlpha(myLight.light.color, 0.3f));
```

## Note
This is a very simple demonstration of lights in Raylib, the project will futher be modified in future to help develope complex lighting tasks in other 3D related projects.
