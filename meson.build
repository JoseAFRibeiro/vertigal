project('vertigal', 'c', default_options: ['c_std=c17'])

compiler = meson.get_compiler('c')
sys = build_machine.system()

if sys == 'linux'
    args = [
        '-DDEBUG'
    ]
    linker_args = [
        '-lm'
    ]
    include = include_directories('include')
    glfw_dep = dependency('glfw3')
    cglm_dep = dependency('cglm')
endif

if sys == 'windows'
    if compiler.get_id() == 'gcc'
        args = [
            '-DDEBUG',
            '-D_win32',
            '-fstack-protector-all'
        ]      
        linker_args = []
    elif compiler.get_id() == 'msvc'
        args = [
            '/DDEBUG',
            '/D_win32',
            '/VERBOSE:LIB',
        ]     
        linker_args = ['/MACHINE:x64']
    endif
endif
    cglm_path = get_option('cglm_path')
    glfw_path = get_option('glfw_path')
    glfw_lib = get_option('glfw_lib_option')

    include = [ 'include' ]
    include += glfw_path / 'include'
    include += cglm_path / 'include'

    glfw_dep = compiler.find_library('glfw3', dirs: glfw_path / glfw_lib, static: true)
    cglm_dep = compiler.find_library('cglm', dirs: cglm_path / 'build')

src = [
    'src/main.c',
    'src/gl/gl.c',
    'src/gl/glad.c',
    'src/gl/callback.c',
    'src/gl/shaders.c',
    'src/gl/renderer.c',
    'src/gl/gui/gui.c',
    'src/gl/gui/glfw_gl4_nuklear.c',
    'src/gl/transformations/camera.c',
    'src/io/filemapping.c',
    'src/io/formatedprint.c',
    'src/io/fileutils.c',
    'src/io/imageloader.c',
    'src/models/objmodel.c',
    'src/models/objutils.c',
]


executable(
    'vertigal', 
    src, 
    dependencies: [glfw_dep, cglm_dep], 
    include_directories:[include],
    c_args: args,
    link_args: linker_args )