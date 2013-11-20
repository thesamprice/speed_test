import os
env = Environment(CPPPATH=[],
                  CCFLAGS=[],
                  LIBS=[],
                  LIBPATH=[],
                  ENV = {'PATH' : os.environ['PATH']})

env['CCFLAGS'] += ['-g3','-O4','-fPIC' ]
env['CPPPATH'] += ['src' , '/opt/local/include']


src =  Glob('src/*.cpp')

env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))
#env["CC"] = "clang"  
#env["CXX"] = "/usr/bin/g++" 
#env["CXX"] = "/usr/local/bin/clang++"
env.Program(target='speed_test', source=src)

