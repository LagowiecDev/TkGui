# TkGui
TkGui is a cross-platform GUI framework designed for integrating with various rendering APIs and event systems. It provides a straightforward way to build and render graphical user interfaces, supporting multiple event systems and rendering backends.

## Features
- **Cross-Platform**: Works seamlessly across multiple platforms.
- **Flexible Panel Creation**: Create and manage panels with custom sizes, positions, and content.
- **Image Rendering**: Supports rendering images either from raw data or loaded from files.
- **Rendering Integration**: Easily integrates with Vulkan, OpenGL, DirectX, and Metal for rendering.

## Basic Usage Example

Here's a simple example of how to set up and render a basic UI with TkGui:

```cpp
TkGui::Begin();
    
// Background Panel
TkGui::Panel({ 0.0f, 0.0f, 0.0f, 2, 2 }, { { 1, 0, 1 }, TkGui::Image{ 1, 1, 4, { { 1, 1, 1, 1 } } } });

// Title Panel with Image
TkGui::Panel({ 0.0f, 0.5f, 0.0f, 1, 0.5f }, { { 1, 1, 1 }, TkGui::LoadImage("Title.png") });

// Red Panel with Image
TkGui::Panel({ 0.0f, 0.0f, 0.0f, 0.5f, 0.25 }, { { 1, 0, 0 }, TkGui::Image{ 1, 1, 4, { { 1, 1, 1, 1 } } } });

// Green Panel with Image
TkGui::Panel({ 0.0f, -0.375f, 0.0f, 0.5f, 0.25 }, { { 0, 1, 0 }, TkGui::Image{ 1, 1, 4, { { 1, 1, 1, 1 } } } });

// Blue Panel with Image
TkGui::Panel({ 0.0f, -0.75f, 0.0f, 0.5f, 0.25 }, { { 0, 0, 1 }, TkGui::Image{ 1, 1, 4, { { 1, 1, 1, 1 } } } });

TkGui::End();

// Draw the UI
TkGui::Draw(TkGui::GetDrawData());

// Handle Events
TkGui::GetEvents(window);
```

### Key Functions

- **TkGui::Begin()**: Starts the rendering process. Call at the beginning of each frame.
- **TkGui::End()**: Ends the rendering process. Call at the end of the frame.
- **TkGui::Panel(position, content)**: Defines a panel with a given position and content. The position is specified as a 5-element array `{ x, y, z, width, height }`.
- **TkGui::Image(width, height, textureID, color)**: Renders an image inside the panel. The textureID refers to the image texture, and the color can be used to modify the image.
- **TkGui::LoadImage(filepath)**: Loads an image from the specified file (e.g., `"Title.png"`).
- **TkGui::Draw(drawData)**: Renders the UI using the chosen rendering backend (Vulkan, OpenGL, etc.).
- **TkGui::GetEvents(window)**: Processes input events from the event system.

### Rendering Backends

TkGui supports the following rendering APIs:
- **OpenGL**
- ~~**Vulkan**~~
- ~~**DirectX9**~~
- ~~**DirectX11**~~
- ~~**DirectX12**~~
- ~~**Metal**~~

### Event Systems

TkGui supports various event systems:
- **GLFW**
- ~~**SDL**~~
- ~~**Windows API**~~
- ~~**X11** ~~
- ~~**Wayland**~~

## Cross-Platform Considerations

- For **rendering**, select the appropriate backend based on your system's capabilities (e.g., OpenGL, Vulkan, DirectX, or Metal).
- For **event handling**, choose the event system suitable for your target platform (e.g., GLFW, SDL, Win32, or Linux).

## Dependencies

To use TkGui, make sure the necessary libraries are linked for the chosen rendering backend and event system:
- OpenGL, Vulkan, DirectX, or Metal for rendering.
- GLFW, SDL, or Win32 for event handling..