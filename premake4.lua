solution "opengltext"
    configurations { "Debug", "Release" }
    platforms { "x32", "x64" }
    location "build"
    
	configuration { "x32", "Debug" }
		targetdir "bin/x86/debug/"
        debugdir "bin/x86/debug/"
        libdirs "external/lib/x86/"
		flags { "Symbols" }
	configuration { "x32", "Release" }
		targetdir "bin/x86/release/"
        debugdir "bin/x86/release/"
        libdirs "external/lib/x86/"
		flags { "Optimize" }
	configuration { "x64", "Debug" }
		targetdir "bin/x64/debug/"
        debugdir "bin/x64/debug/"
        libdirs "external/lib/x64/"
		flags { "Symbols" }
	configuration { "x64", "Release" }
		targetdir "bin/x64/release/"
        debugdir "bin/x64/release/"
        libdirs "external/lib/x64/"
		flags { "Optimize" }
	configuration {}
    
    includedirs { "external/include/" }
        
    project "opengltext"
        kind "StaticLib"
        language "C++"
        files { "code/opengltext/**.hpp", "code/opengltext/**.cpp" }
        objdir "build/opengltext/obj/"
        links { "opengl32", "gl3w" }
        
    project "opengltext_demo"
        kind "ConsoleApp"
        language "C++"
        files { "code/opengltext_demo/**.hpp", "code/opengltext_demo/**.cpp" }
        objdir "build/opengltext_demo/obj/"
        links { "opengl32", "gl3w", "SDL2", "SDL2main" }