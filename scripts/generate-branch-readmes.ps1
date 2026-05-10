#Requires -Version 5.1
<#
.SYNOPSIS
  Writes minimal README.md on each topic branch (intro, link to master, attribution, "This branch" snippet) and commits + pushes.
  Run from repo root: powershell -File scripts/generate-branch-readmes.ps1
  Use -WhatIf to only print actions without git write/push.
#>
param(
    [switch] $WhatIf,
    [string] $OnlyBranch = ""
)

$ErrorActionPreference = "Stop"
$RepoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
Set-Location $RepoRoot

function Get-AttributionBlock {
    return @"
## Attribution

- **Overall architecture, engine layout, and the progressive lab sequence** follow the structure and teaching materials provided by the **course professor** (window/bootstrap, core classes, shader workflow, tool window integration, and lab stepping order).
- **Exercises, midterm, and final exam** implementations are **my own work**, built on top of that course foundation.
- **Some code on individual lab branches** is also **my own** (iterations, fixes, or extensions beyond the baseline handout), while other parts remain aligned with the supplied lab framework.

When reusing or citing this repository, treat **branch names and commit history** as the source of truth for what was authored when.
"@
}

function Build-Readme {
    param(
        [string] $BranchDisplayName,
        [string] $ThisBranchBody
    )
    $attr = Get-AttributionBlock
    $nl = [Environment]::NewLine
    $parts = @(
        "# InitOpenGL - ``$BranchDisplayName``$nl$nl"
        "This repository is a **Visual Studio C++ OpenGL** course project. Work is organized across **many Git branches**; you are viewing **``$BranchDisplayName``**. For the **complete branch index**, lab sequence, build notes, and lighting overview, see the canonical README on **``master``**.$nl$nl"
        "**Repository:** [https://github.com/Naso01/InitOpenGL](https://github.com/Naso01/InitOpenGL)$nl$nl"
        "**Full documentation (``master``):** [README.md on master](https://github.com/Naso01/InitOpenGL/blob/master/README.md)$nl$nl"
        "$attr$nl$nl---$nl$nl## This branch$nl$nl"
        "$ThisBranchBody$nl$nl---$nl$nl## License / course materials$nl$nl"
        "Course-provided headers, project scaffolding, and lab materials remain subject to the **original course terms**. Assignment and extension work is shared here for portfolio purposes; please respect academic integrity policies if you are taking the same or a related course.$nl"
    )
    return ($parts -join "")
}

$SnippetByBranch = @{
    "Lab1_ToolWindow&Shaders"                    = "- **Lab1**: Introduces the base loop, mesh + shader plumbing, and a minimal pipeline."
    "Lab1-2_ToolWindow&Shaders"                  = "- **Lab1-2**: Expands the **tool window** (``ToolWindow.h`` / ``.resx``) so runtime UI can influence the app."
    "Lab1-3_ToolWindow&Shaders"                  = "- **Lab1-3**: Connects UI to **shader uniforms** (``SimpleFragmentShader.fragmentshader``, ``GameController.cpp``)."
    "Lab2_OpenGLProjections"                     = "Adds **``Camera``**, **``Resolution``**, and projection/view matrix wiring; updates the vertex shader path so geometry is transformed with **perspective projection** and a movable camera (``Camera.cpp`` / ``.h``, ``WindowController``, ``Shader``)."
    "Lab3-1_ColorTriangle_ShadersGLSLIndexBuffers" = "- **3-1**: Indexed drawing and richer vertex attributes for a **colored triangle** mesh path."
    "Lab3-2_ColorTriangle_ShadersGLSLIndexBuffers" = "- **3-2**: Tweaks camera and mesh buffer layout."
    "Lab3-3_ColorTriangle_ShadersGLSLIndexBuffers" = "- **3-3**: Further **mesh** work (larger ``Mesh.cpp`` changes): multiple attributes / draw path refinements."
    "Lab4-1_TexturesFilteringMipMaps"            = "Introduces **``Texture``** loading and binding; fragment shader samples **2D textures**. (Later lab steps refine filtering, mipmapping, and shader/mesh integration.)"
    "Lab4-2_TexturesFilteringMipMaps"            = "Iteration on **Lab4-1**: adjusts **filtering / mipmapping** behavior in ``Texture.cpp`` and related sampling setup."
    "Lab4-3_TexturesFilteringMipMaps"            = "Iteration on **Lab4-2**: refines **``Mesh``**, **``Shader``**, **``Texture``**, and **``SimpleFragmentShader``** so texture parameters and draw paths stay consistent."
    "Lab5-1_ModelsAndText"                       = "- **5-1**: Adds **Phong-style textured lighting** (``Diffuse.vertexshader`` / ``Diffuse.fragmentshader``, ``Color.*``) and substantially extends **``Mesh``** for OBJ materials."
    "Lab5-2_ModelAndText"                        = "- **5-2**: Adds **FreeType text** (``Fonts.cpp`` / ``.h``, ``Font.*shader``) rendered in screen space."
    "Lab6-1_DepthBlendCubeMaps"                  = "- **6-1**: **Depth testing** and **blending** setup in the game loop; texture path updates for transparent surfaces."
    "Lab6-2_DepthBlendCubeMaps"                  = "- **6-2**: Tweaks **fragment lighting** (alpha / diffuse interaction)."
    "Lab6-3_DepthBlendCubeMaps"                  = "- **6-3**: Scene and shader adjustments for blending correctness."
    "Lab6-4_DepthBlendCubeMaps"                  = "- **6-4**: Cleanup / simplification of draw paths."
    "Lab6-5_DepthBlendCubeMaps"                  = "- **6-5**: Adds a **cubemap skybox** (``Skybox.cpp`` / ``.h``, ``Skybox.*shader``) and camera-related integration so the environment renders behind geometry."
    "Lab7-1_NormalMapsInstancing"                = "- **7-1**: **Normal mapping** inputs in the diffuse shader; instancing hooks in ``Mesh``."
    "Lab7-2_TBN-Matrix_NormalMapsInstancing"   = "- **7-2**: Builds the **TBN (Tangent-Bitangent-Normal) matrix** in ``Mesh.cpp`` / vertex shader so normal maps align to surface UV space."
    "Lab7-3_TBN-instancing_NormalMapsInstancing" = "- **7-3**: Combines **instanced draws** with TBN-correct lighting (expanded ``Mesh`` / vertex shader)."
    "Lab8-1_FramebuffersPostProsessing"          = "- **8-1**: **Framebuffer object (FBO)** off-screen rendering and a **post-processing** pass (``PostProcessor.cpp``, ``PostProcessor.*shader``) - full-screen triangle sampling a **scene color texture**."
    "Lab8-2_KernelEffect_FramebuffersPostProsessing" = "- **8-2**: Adds **``KernelEffect.*shader``**: a **3x3 neighbor convolution** on the resolved texture (implemented offsets + weights for **blur**; comments show **sharpen** and **edge detect** kernels). This is a standard second pass for image filters in screen space."
    "Lighting"                                   = "The branch **``Lighting``** is a **pared-down snapshot** relative to ``Lab8-2``: it removes skybox, fonts, post-processing stack, and several advanced mesh features, and keeps a **single directional-style Phong light** with simple uniforms in ``Diffuse.fragmentshader`` (good for isolating lighting math)."
    "Spotlight"                                  = "Implements a **spot light**: in addition to Phong diffuse/specular and **distance attenuation** (constant / linear / quadratic terms), the shader tests whether the fragment lies inside a **cone** around ``light.direction``.`n`n- **Cone test:** ``a = cos(coneAngle)`` compared to ``d = dot(normalize(light.direction), -lightDir)`` where ``lightDir`` is from the light toward the fragment. If ``a < d``, the fragment is inside the bright cone.`n- **Inside the cone:** attenuation is multiplied by a **falloff** term using ``a/d`` (with clamping in this branch) so intensity softens toward the cone edge.`n- **Outside the cone:** only **ambient** (texture x ambient color) contributes, so the rest of the scene falls back to dim base lighting."
    "pointlight"                                 = "Replaces the simplified light with a **positional point light**: same Phong terms, but **no cone**; intensity scales by **inverse-square-style attenuation** using tunable polynomial coefficients in the denominator."
    "Multiple-Lights"                            = "Generalizes to **``NR_LIGHTS`` (4)** lights in one shader using ``uniform Light light[NR_LIGHTS]``. Each entry can carry cone parameters, so you can mix **spot** behaviors. The shader **loops** per fragment, summing contributions (with a split path for in-cone vs out-of-cone ambient)."
    "AdvancedLighting"                           = "Small iteration on **``Multiple-Lights``**: renames the uniform array to ``lights``, applies **clamped** ``a/d`` for smoother spotlight edges (matches the numeric stability idea used on ``Spotlight``), and adjusts C++ upload (``GameController`` / ``Mesh``). Useful as a staging branch for tuning multi-light + spotlight falloff."
    "Midterm"                                    = "Strips back much of the late-lab stack and focuses on a **YUV color manipulation** exercise in ``YUVFragmentShader.fragmentshader``: RGB to **YUV** via a fixed ``mat3``, per-channel **gain** (``YChannel``, ``UChannel``, ``VChannel`` as percentages), optional **color inversion**, blending two textures, then **YUV to RGB** for display. Tool window controls drive those uniforms."
    "Final-Exam"                                 = "The capstone branch: restores **diffuse/normal/specular** materials, **skybox**, **fonts**, **post-processing** (including **kernel effects**), adds **``InputController``** for richer interaction, and significantly extends **``ToolWindow``** (specular controls, light movement, scene modes, water-related commits per history, etc.). This is the most complete single-scene experience in the repo."
    "Exercise1_PlayerTriangles"                  = "A gameplay-flavored exercise on an **earlier** stack: **one player triangle** (WASD) and **ten NPC triangles** with randomized positions, simple **AI / steering** toward the player, and facing behavior - implemented with the **simple** shader path (``SimpleVertexShader`` / ``SimpleFragmentShader``) rather than the full PBR-style stack."
    "Exercise2_Lighting&Textures"                = "Adds a dedicated **``Light.fragmentshader``** with a **``Material`` / ``Light`` struct** and a loop over **``NR_LIGHTS``** (set to 1 here), plus expanded **``GameController``** and **``ToolWindow``** wiring for lighting and textures - an intermediate mini-engine exercise between Lab 5 and later lighting branches."
    "Exercise-2.0"                               = "Built on the **Lab 7.3** instancing + normal-map stack: extends **``ToolWindow``** and **``GameController``** with interaction such as **mouse-drag mesh movement** (``m_leftMouseHeld``, cursor position) while keeping the advanced mesh/lighting path."
    "CustomModelImport"                          = "Forks from **``Lab5-2``** but pulls forward major systems: **post-processing**, **kernel effect shaders**, **skybox**, extended **``Mesh`` / ``Camera`` / ``Texture``**, etc. - a **custom integration** path for importing and rendering user models with the fuller rendering feature set."
}

$refs = git for-each-ref --format="%(refname:short)" "refs/remotes/origin/*" | Where-Object { $_ -and ($_ -ne "origin") -and ($_ -notmatch '^origin/HEAD$') }

git fetch origin --quiet

foreach ($ref in $refs) {
    if ($ref -notmatch '^origin/(.+)$') { continue }
    $branchName = $Matches[1]
    if ($branchName -eq "master") { continue }
    if ($OnlyBranch -and ($branchName -ne $OnlyBranch)) { continue }

    $snippet = $SnippetByBranch[$branchName]
    if (-not $snippet) {
        Write-Warning "No snippet mapped for branch '$branchName' - skipping."
        continue
    }

    $snippetExpanded = $snippet.Replace("`n", [Environment]::NewLine)
    $readme = Build-Readme -BranchDisplayName $branchName -ThisBranchBody $snippetExpanded
    $readmePath = Join-Path $RepoRoot "README.md"

    if ($WhatIf) {
        Write-Host "[WhatIf] Would checkout $branchName, write README.md, commit, push"
        continue
    }

    git checkout -B $branchName "origin/$branchName" --quiet
    Set-Content -Path $readmePath -Value $readme -Encoding utf8

    $status = git status --porcelain README.md
    if (-not $status) {
        Write-Host "No changes for $branchName (README already matches)."
        continue
    }

    git add README.md
    git commit -m "Add branch-specific README"
    git push origin $branchName
    Write-Host "Updated and pushed: $branchName"
    Start-Sleep -Milliseconds 150
}

if (-not $WhatIf) {
    git checkout master --quiet
    Write-Host "Done. Checked out master."
}
