project('daytime', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

inc_dir = include_directories(['include'], [get_option('cli11_include_dir')], [get_option('spdlog_include_dir')])

srcClient = ['src/daytime_client/main.cpp']
srcServer = ['src/daytime_client/main.cpp']

executable('server',
            sources : srcServer,
            include_directories : inc_dir,
           )

executable('client',
            sources : srcClient,
            include_directories : inc_dir,
           )
