# InitOpenGL - `Multiple-Lights`

This repository is a **Visual Studio C++ OpenGL** course project. Work is organized across **many Git branches**; you are viewing **`Multiple-Lights`**. For the **complete branch index**, lab sequence, build notes, and lighting overview, see the canonical README on **`master`**.

**Repository:** [https://github.com/Naso01/InitOpenGL](https://github.com/Naso01/InitOpenGL)

**Full documentation (`master`):** [README.md on master](https://github.com/Naso01/InitOpenGL/blob/master/README.md)

## Attribution

- **Overall architecture, engine layout, and the progressive lab sequence** follow the structure and teaching materials provided by the **course professor** (window/bootstrap, core classes, shader workflow, tool window integration, and lab stepping order).
- **Exercises, midterm, and final exam** implementations are **my own work**, built on top of that course foundation.
- **Some code on individual lab branches** is also **my own** (iterations, fixes, or extensions beyond the baseline handout), while other parts remain aligned with the supplied lab framework.

When reusing or citing this repository, treat **branch names and commit history** as the source of truth for what was authored when.

---

## This branch

Generalizes to **`NR_LIGHTS` (4)** lights in one shader using `uniform Light light[NR_LIGHTS]`. Each entry can carry cone parameters, so you can mix **spot** behaviors. The shader **loops** per fragment, summing contributions (with a split path for in-cone vs out-of-cone ambient).

---

## License / course materials

Course-provided headers, project scaffolding, and lab materials remain subject to the **original course terms**. Assignment and extension work is shared here for portfolio purposes; please respect academic integrity policies if you are taking the same or a related course.

