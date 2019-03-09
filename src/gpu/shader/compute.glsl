#version 430

layout (local_size_x = 1, local_size_y = 1) in;

layout (r32i, binding = 0) uniform iimage2D img_output;

void main() {
  // Aucun tableau de donnée n'étant passé au moment de la création de la texture,
  // c'est le compute shader qui va dessiner à l'intérieur de l'image associé
  // à la texture.
  
  // gl_LocalInvocationID.xy * gl_WorkGroupID.xy == gl_GlobalInvocationID
	ivec2 size = imageSize(img_output);
	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++) {
			if (((i & 1) ^ (j & 1)) != 0)
				imageStore(img_output, ivec2(j, i), ivec4(0xFF0000FF, 0, 0, 0));
			else
				imageStore(img_output, ivec2(j, i), ivec4(0xFFFF00FF, 0, 0, 0));
			}
}
