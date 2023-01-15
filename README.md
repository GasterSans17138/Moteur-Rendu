# **PlatformerGL - ZALLIO Liam and Eliot Nerrand**
---
<img src="https://gitlabstudents.isartintra.com/projets/2021_gp_2026modernopengl_gp_2026modernopengl-gp1_zallio_l/-/raw/master/OpenGL/Resources/ScreenShots/UserInterface.PNG?inline=false" alt="User Interface">

# Description 

- The PlatformerGL project is a rendering engine made on OpenGL 4.0. It features resource loading, 3D rendering, lighting, a scene hierarchy and a user interface.
- The code is written in C++, with the GLAD and the GLFW libraries used for the rendering, and the ImGui librairy used for the user interface.
- The project is made on Microsoft Visual Studio 2019.
---
---

# Navigation 


## Scene Graph 
- The Scene Graph window display the hierarchy informations of the scene. The hierarchy is the list of all the **GameObjects** in your scene.
- Click on an object in the hierarchy to display its information in the **Inspector**.
- You can right-click on existing object to delete them or add a child beneath it.

## Resource Manager
- This window display every resources loaded.
- You can acces the texture and material information.

## Material
- You can add a new material, then drag and drop textures into it.
- **Materials** are composed by a diffuse color, a texture, a specular color, and a shiniess parameter which influence the specular lighting.
- **Materials** can be dragged and dropped into meshes.

## Inspector 
- The inspector display all informations of the selected **GameObject** in the Hierarchy.
- Every **GameObjects** has a **Transform** component attached to it. It contains the local position, rotation and scale of the object.
- The inspector display every **Component** of the selected object.

---
---
# Component
- You can add **Components** to **GameObjects** in the inspector.
- You can not remove Components from a gameObject.

## Mouvements
- You can move with WASD but you can rebind it  with your preferences in the options menu.

## Light

<img src="https://gitlabstudents.isartintra.com/projets/2021_gp_2026modernopengl_gp_2026modernopengl-gp1_zallio_l/-/raw/master/OpenGL/Resources/ScreenShots/Light.PNG?inline=false" alt="Lighting demo">

### There are three types of light :
    - Directional lights cast a general light for every object in the scene, regardless of their positions.
    - Point light cast a light limited in space. You can tweak its attenuation.
    - Spot light cast a light similar to a torch.

- For all types of lihgt, you can change its color, itensity, and the general ambient light which is common to all light.
- You can add up to 7 light in the scene.

## Mesh
- Meshes are defined by a Material and a model. You can drag and drop both from the Resources window.
- The default model of a mesh is a cube. You can not remove the model reference of mesh.
- The default material of a mesh is a white, with white specular. You can remove the material reference from a mesh.
