project('vertigal', 'c')

compiler = meson.get_compiler('c')
sys = build_machine.system()

if sys == 'linux'
    glfw_dep = dependency('glfw3')
    cglm_dep = dependency('cglm')
endif

if sys == 'windows'

    cglm_path = get_option('cglm_path')
    glfw_path = get_option('glfw_path')
    glfw_lib = get_option('glfw_lib_option')

    glfw_dep = compiler.find_library('glfw3', dirs: glfw_path / glfw_lib)
    cglm_dep = compiler.find_library('cglm', dirs: cglm_path / 'build')
endif

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