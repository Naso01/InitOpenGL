# InitOpenGL

Visual Studio C++ solution that hosts an OpenGL 3.3–style graphics course project. The repository is organized as **many Git branches**, each capturing a lab milestone, assignment, or experimental lighting variant. The **`master` branch** currently contains only the stock “Hello World” console template (`OpenGL/OpenGL.cpp`); the interactive renderer, assets, and third-party libraries live on the **named remote branches** under `origin/` (for example `origin/Final-Exam`, `origin/Lab8-2_KernelEffect_FramebuffersPostProsessing`).

**Remote:** [https://github.com/Naso01/InitOpenGL](https://github.com/Naso01/InitOpenGL)

Each **topic branch** (everything except `master`) includes a **minimal root `README.md`** at its latest commit: short intro, a link back to this file on **master**, the same **Attribution** block, and a **This branch** section with only that branch's description.

---

## Attribution

- **Overall architecture, engine layout, and the progressive lab sequence** follow the structure and teaching materials provided by the **course professor** (window/bootstrap, core classes, shader workflow, tool window integration, and lab stepping order).
- **Exercises, midterm, and final exam** implementations are **my own work**, built on top of that course foundation.
- **Some code on individual lab branches** is also **my own** (iterations, fixes, or extensions beyond the baseline handout), while other parts remain aligned with the supplied lab framework.

When reusing or citing this repository, treat **branch names and commit history** as the source of truth for what was authored when.

---

## What the full project contains (typical branch)

Branches that include the full engine (for example `Final-Exam`, `Lab8-2_KernelEffect_FramebuffersPostProsessing`) generally include:

| Area | Purpose |
|------|---------|
| `InitOpenGL.sln` | Visual Studio solution |
| `OpenGL/` | Application code: `main.cpp`, `GameController`, `Mesh`, `Shader`, `Camera`, `Texture`, UI (`ToolWindow`), fonts, skybox, post-processing, etc. |
| `Assets/Models`, `Assets/Textures`, `Assets/Fonts` | OBJ/MTL models, textures (diffuse, normal, specular), fonts (e.g. FreeType) |
| `External/` | **GLFW** (window + input), **GLEW** (OpenGL entry points), **FreeType** (text rasterization), **GLM** (math; typically via vcpkg or bundled includes as configured in the `.vcxproj`) |

Typical pipeline:

1. **GLFW** creates the OpenGL context; **GLEW** loads extension functions.
2. **Meshes** load geometry and materials from OBJ, upload VBOs/IBOs, and bind textures.
3. **Shaders** implement the lighting model (Blinn-Phong–style diffuse + specular in `Diffuse.*shader`), optional normal mapping / instancing, skybox sampling, and post-processing passes.
4. A **WinForms tool window** drives uniforms and scene options at runtime.

Open the `.sln`, set the startup project to **OpenGL**, choose **x64**, and build **Debug** or **Release** (paths to libs/DLLs are wired in the project file on full branches).

---

## Lab sequence (incremental topics)

The labs build the renderer in order. Below, “adds” describes what **changes relative to the previous step** in the `OpenGL/` tree (from `git diff` summaries between consecutive lab tips).

### `Lab1_ToolWindow&Shaders` → `Lab1-2_ToolWindow&Shaders` → `Lab1-3_ToolWindow&Shaders`

- **Lab1**: Introduces the base loop, mesh + shader plumbing, and a minimal pipeline.
- **Lab1-2**: Expands the **tool window** (`ToolWindow.h` / `.resx`) so runtime UI can influence the app.
- **Lab1-3**: Connects UI to **shader uniforms** (`SimpleFragmentShader.fragmentshader`, `GameController.cpp`).

### `Lab2_OpenGLProjections`

Adds **`Camera`**, **`Resolution`**, and projection/view matrix wiring; updates the vertex shader path so geometry is transformed with **perspective projection** and a movable camera (`Camera.cpp` / `.h`, `WindowController`, `Shader`).

### `Lab3-1` → `Lab3-2` → `Lab3-3` (`ColorTriangle_ShadersGLSLIndexBuffers`)

- **3-1**: Indexed drawing and richer vertex attributes for a **colored triangle** mesh path.
- **3-2**: Tweaks camera and mesh buffer layout.
- **3-3**: Further **mesh** work (larger `Mesh.cpp` changes): multiple attributes / draw path refinements.

### `Lab4-1` → `Lab4-2` → `Lab4-3` (`TexturesFilteringMipMaps`)

Introduces **`Texture`** loading and binding; fragment shader samples **2D textures**; later iterations adjust **filtering / mipmapping** behavior in `Texture.cpp` and hook parameters through `Mesh` / `Shader`.

### `Lab5-1` → `Lab5-2` (`ModelsAndText` / `ModelAndText`)

- **5-1**: Adds **Phong-style textured lighting** (`Diffuse.vertexshader` / `Diffuse.fragmentshader`, `Color.*`) and substantially extends **`Mesh`** for OBJ materials.
- **5-2**: Adds **FreeType text** (`Fonts.cpp` / `.h`, `Font.*shader`) rendered in screen space.

### `Lab6-1` → … → `Lab6-5` (`DepthBlendCubeMaps`)

- **6-1**: **Depth testing** and **blending** setup in the game loop; texture path updates for transparent surfaces.
- **6-2**: Tweaks **fragment lighting** (alpha / diffuse interaction).
- **6-3**: Scene and shader adjustments for blending correctness.
- **6-4**: Cleanup / simplification of draw paths.
- **6-5**: Adds a **cubemap skybox** (`Skybox.cpp` / `.h`, `Skybox.*shader`) and camera-related integration so the environment renders behind geometry.

### `Lab7-1` → `Lab7-2` → `Lab7-3` (`NormalMapsInstancing`)

- **7-1**: **Normal mapping** inputs in the diffuse shader; instancing hooks in `Mesh`.
- **7-2**: Builds the **TBN (Tangent–Bitangent–Normal) matrix** in `Mesh.cpp` / vertex shader so normal maps align to surface UV space.
- **7-3**: Combines **instanced draws** with TBN-correct lighting (expanded `Mesh` / vertex shader).

### `Lab8-1` → `Lab8-2` (`FramebuffersPostProsessing` / `KernelEffect`)

- **8-1**: **Framebuffer object (FBO)** off-screen rendering and a **post-processing** pass (`PostProcessor.cpp`, `PostProcessor.*shader`)—full-screen triangle sampling a **scene color texture**.
- **8-2**: Adds **`KernelEffect.*shader`**: a **3×3 neighbor convolution** on the resolved texture (implemented offsets + weights for **blur**; comments show **sharpen** and **edge detect** kernels). This is a standard second pass for image filters in screen space.

---

## Lighting experiment branches (forked from the “full” lab stack)

The branch **`Lighting`** is a **pared-down snapshot** relative to `Lab8-2`: it removes skybox, fonts, post-processing stack, and several advanced mesh features, and keeps a **single directional-style Phong light** with simple uniforms in `Diffuse.fragmentshader` (good for isolating lighting math).

From that baseline, the following branches **extend the lighting model** in the fragment shader and C++ uniform setup:

### `Spotlight`

Implements a **spot light**: in addition to Phong diffuse/specular and **distance attenuation** (constant / linear / quadratic terms), the shader tests whether the fragment lies inside a **cone** around `light.direction`.

- **Cone test:** `a = cos(coneAngle)` compared to `d = dot(normalize(light.direction), -lightDir)` where `lightDir` is from the light toward the fragment. If `a < d`, the fragment is inside the bright cone.
- **Inside the cone:** attenuation is multiplied by a **falloff** term using `a/d` (with clamping in this branch) so intensity softens toward the cone edge.
- **Outside the cone:** only **ambient** (texture × ambient color) contributes, so the rest of the scene falls back to dim base lighting.

### `pointlight`

Replaces the simplified light with a **positional point light**: same Phong terms, but **no cone**; intensity scales by **inverse-square-style attenuation** using tunable polynomial coefficients in the denominator.

### `Multiple-Lights`

Generalizes to **`NR_LIGHTS` (4)** lights in one shader using `uniform Light light[NR_LIGHTS]`. Each entry can carry cone parameters, so you can mix **spot** behaviors. The shader **loops** per fragment, summing contributions (with a split path for in-cone vs out-of-cone ambient).

### `AdvancedLighting`

Small iteration on **`Multiple-Lights`**: renames the uniform array to `lights`, applies **clamped** `a/d` for smoother spotlight edges (matches the numeric stability idea used on `Spotlight`), and adjusts C++ upload (`GameController` / `Mesh`). Useful as a staging branch for tuning multi-light + spotlight falloff.

---

## Assignments and custom work

### `Midterm`

Strips back much of the late-lab stack and focuses on a **YUV color manipulation** exercise in `YUVFragmentShader.fragmentshader`: RGB → **YUV** via a fixed `mat3`, per-channel **gain** (`YChannel`, `UChannel`, `VChannel` as percentages), optional **color inversion**, blending two textures, then **YUV → RGB** for display. Tool window controls drive those uniforms.

### `Final-Exam`

The capstone branch: restores **diffuse/normal/specular** materials, **skybox**, **fonts**, **post-processing** (including **kernel effects**), adds **`InputController`** for richer interaction, and significantly extends **`ToolWindow`** (specular controls, light movement, scene modes, water-related commits per history, etc.). This is the most complete “single scene” experience in the repo.

### `Exercise1_PlayerTriangles`

A gameplay-flavored exercise on an **earlier** stack: **one player triangle** (WASD) and **ten NPC triangles** with randomized positions, simple **AI / steering** toward the player, and facing behavior—implemented with the **simple** shader path (`SimpleVertexShader` / `SimpleFragmentShader`) rather than the full PBR-style stack.

### `Exercise2_Lighting&Textures`

Adds a dedicated **`Light.fragmentshader`** with a **`Material` / `Light` struct** and a loop over **`NR_LIGHTS`** (set to 1 here), plus expanded **`GameController`** and **`ToolWindow`** wiring for lighting and textures—an intermediate “mini engine” exercise between Lab 5 and later lighting branches.

### `Exercise-2.0`

Built on the **Lab 7.3** instancing + normal-map stack: extends **`ToolWindow`** and **`GameController`** with interaction such as **mouse-drag mesh movement** (`m_leftMouseHeld`, cursor position) while keeping the advanced mesh/lighting path.

### `CustomModelImport`

Forks from **`Lab5-2`** but pulls forward major systems: **post-processing**, **kernel effect shaders**, **skybox**, extended **`Mesh` / `Camera` / `Texture`**, etc.—a **custom integration** path for importing and rendering user models with the fuller rendering feature set.

---

## `master`

`master` is intentionally minimal (template **Hello World**). Clone the repo and **`git checkout <branch-name>`** to inspect or build a specific milestone.

---

## Checking out a branch locally

```bash
git fetch origin
git checkout Final-Exam
# or: git checkout Spotlight
```

Use **Visual Studio 2022** (project toolset **v143** where present) and match **x64** to the bundled GLFW/GLEW/FreeType library folders on Windows.

---

## License / course materials

Course-provided headers, project scaffolding, and lab materials remain subject to the **original course terms**. My assignment and extension work is shared here for portfolio purposes; please respect academic integrity policies if you are taking the same or a related course.
