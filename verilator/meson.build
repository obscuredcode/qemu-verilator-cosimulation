project('verilator_cosim', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

# Add your source files here
sources = files('main.cpp')


# Define the executable
executable('verilator_cosim', sources, dependencies : [dependency('verilator', required : true)])