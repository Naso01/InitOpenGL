# InitOpenGL - `Spotlight`

This repository is a **Visual Studio C++ OpenGL** course project. Work is organized across **many Git branches**; you are viewing **`Spotlight`**. For the **complete branch index**, lab sequence, build notes, and lighting overview, see the canonical README on **`master`**.

**Repository:** [https://github.com/Naso01/InitOpenGL](https://github.com/Naso01/InitOpenGL)

**Full documentation (`master`):** [README.md on master](https://github.com/Naso01/InitOpenGL/blob/master/README.md)

## Attribution

- **Overall architecture, engine layout, and the progressive lab sequence** follow the structure and teaching materials provided by the **course professor** (window/bootstrap, core classes, shader workflow, tool window integration, and lab stepping order).
- **Exercises, midterm, and final exam** implementations are **my own work**, built on top of that course foundation.
- **Some code on individual lab branches** is also **my own** (iterations, fixes, or extensions beyond the baseline handout), while other parts remain aligned with the supplied lab framework.

When reusing or citing this repository, treat **branch names and commit history** as the source of truth for what was authored when.

---

## This branch

Implements a **spot light**: in addition to Phong diffuse/specular and **distance attenuation** (constant / linear / quadratic terms), the shader tests whether the fragment lies inside a **cone** around `light.direction`.

- **Cone test:** `a = cos(coneAngle)` compared to `d = dot(normalize(light.direction), -lightDir)` where `lightDir` is from the light toward the fragment. If `a < d`, the fragment is inside the bright cone.
- **Inside the cone:** attenuation is multiplied by a **falloff** term using `a/d` (with clamping in this branch) so intensity softens toward the cone edge.
- **Outside the cone:** only **ambient** (texture x ambient color) contributes, so the rest of the scene falls back to dim base lighting.

---

## License / course materials

Course-provided headers, project scaffolding, and lab materials remain subject to the **original course terms**. Assignment and extension work is shared here for portfolio purposes; please respect academic integrity policies if you are taking the same or a related course.

