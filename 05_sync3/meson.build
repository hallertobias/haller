project('loadsim', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

inc_dir = include_directories(['include'], [get_option('cli11_include_dir')])

src = ['src/dining.cpp']

executable('dining',
            sources : src,
            include_directories : inc_dir,
           )
