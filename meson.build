project('vertigal', 'c')

glfw_dep = dependency('glfw3')
cglm_dep = dependency('cglm')

src = [
    'src/main.c',
    'src/gl/gl.c',
    'src/gl/glad.c',
    'src/gl/callback.c',
    'src/gl/shaders.c',
    'src/gl/renderer.c',
    'src/io/filemapping.c',
    'src/io/formatedprint.c',


]

include = include_directories('include')

executable(
    'vertigal', 
    src, 
    dependencies: [glfw_dep, cglm_dep], 
    include_directories:[include],
    c_args: ['-DDEBUG'])