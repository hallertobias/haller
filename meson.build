project('aba', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

inc_dir = include_directories(['include'])

src = ['src/aba.cpp', 'src/charout.cpp']

executable('aba',
            sources : src,
            include_directories : inc_dir,
          )

executable('charout',
           sources: src,
           include_directories: inc_dir)