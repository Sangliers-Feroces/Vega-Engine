#version 430

layout(local_size_x = 1, local_size_y = 1) in;

layout(r32i, binding = 0) uniform iimage2D mem;
layout(rgba32f, binding = 0) uniform image2D lightmap;

void main()
{
	ivec2 size = imageSize(lightmap);

	//for (int k = 0; k < 4096; k++)
	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++) {
			if (((i & 1) ^ (j & 1)) != 0)
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 0.0f, 0.0f));
			else
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 1.0f, 0.0f));
			}
}
