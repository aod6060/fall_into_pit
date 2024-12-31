env = None

env = Environment(
    TARGET_ARCH='x86',
    CPPPATH=[
        "include"
    ],
    LIBPATH=[
        "lib"
    ],
    LIBS=[
        'SDL2main.lib',
        'SDL2.lib',
        'SDL2_image.lib',
        'SDL2_ttf.lib',
        'SDL2_mixer.lib',
        'opengl32.lib',
        'glew32.lib',
        'kernel32.lib',
        'user32.lib',
        'gdi32.lib',
        'winspool.lib',
        'comdlg32.lib',
        'advapi32.lib' ,
        'shell32.lib',
        'ole32.lib',
        'oleaut32.lib',
        'uuid.lib',
        'odbc32.lib',
        'odbccp32.lib'
    ],
    CPPFLAGS=[
        '/std:c++17',
        '/Gd',
        '/EHsc',
        '/fp:precise',
        '/MD',
        '/sdl'
    ],
    LINKFLAGS=[
        '/SUBSYSTEM:CONSOLE',
        '/MACHINE:X86',
        '/NODEFAULTLIB:library'])


if not (env is None):
    env["source_files"] = []

    target="#/bin/run"

    # Add in SConscripts
    SConscript("#/src/SConscript", exports="env")

    env.Program(target=target, source=env["source_files"])