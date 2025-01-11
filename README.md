# miniRT

This ray tracing project, written in **C** and based on the norminette specification of 42 school, is the biggest one in 42 school. It renders realistic scene effects on the screen by calculating the intersection data between rays and objects. The program uses a virtual function table to simulate C++'s polymorphism, allowing different objects to call their corresponding intersection functions to compute the interaction between rays and various object types.

A general ray equation is used, so when processing cylinders and cones, it is necessary to calculate the value of the coefficient t in the ray equation. Since a ray typically intersects an object at two points, the closest intersection point to the light source must be determined. Information about this closest intersection point, such as the object's shape, type, and normal vector, is stored in a structure.

These data are subsequently used to process color rendering, combining base colors, shadows, light sources, and ambient light to calculate diffuse reflection, highlights, and their respective intensity. Finally, the image is rendered. The checkerboard and texture effects are achieved by perturbing the normal vector.


## Installation and Compilation

1. **Clone the repository**:
   ```bash
   git clone git@github.com:Hazeliny/miniRT.git
   cd MiniRT
   ```

2. **Compile the project**:
   ```bash
   make
   make bonus
   ```

3. **Execute**:
   ```bash
   ./miniRT scenes/gentleman.rt
   ```


![MULTILIGHTS](https://github.com/Hazeliny/miniRT-final/blob/main/assets/colored_multilights.png)
![GENTLEMAN](https://github.com/Hazeliny/miniRT-final/blob/main/assets/gentleman.png)
![CHECKERBOARDCONE](https://github.com/Hazeliny/miniRT-final/blob/main/assets/checkerboard_cone.png)
![ROOM](https://github.com/Hazeliny/miniRT-final/blob/main/assets/room.png)
![TEXTURE](https://github.com/Hazeliny/miniRT-final/blob/main/assets/texture.png)

