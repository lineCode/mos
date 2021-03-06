#version 430 core

uniform mat4 model_view_projection;
uniform mat4 model_view;
layout(location = 0) in vec3 position;
void main() {
    gl_Position = model_view_projection * vec4(position, 1.0);
}
