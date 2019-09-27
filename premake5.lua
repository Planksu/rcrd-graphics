workspace "rcrd-graphics"
	configurations {"Debug", "Release"}
	targetdir "./builds/%{cfg.buildcfg}/%{cfg.platform}"
	objdir "./builds/obj/%{cfg.buildcfg}/%{cfg.platform}"
	location "./project-files"
	architecture "x86_64"

	libdirs {
		"../builds/%{cfg.buildcfg}/%{cfg.platform}"
	}
	
	configuration "Debug"
		defines {
			"DEBUG"
		}
	
	configuration "Release"
		defines {
			"NDEBUG"
		}
	
	configuration "macosx"	
		platforms { "x64" }
	configuration "not macosx"
		platforms { "x86", "x64" }

	configuration "windows"
		characterset "MBCS"
		systemversion "10.0.17763.0"
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32_LEAN_AND_MEAN"
		}

project "rcrd-graphics"
	targetname "rcrd-graphics"
	kind "ConsoleApp"
	-- kind "WindowedApp"
	language "C++"
	links {"glfw3", "OpenGL32", "glew32"}
	files { "./rcrd-graphics/include/**.h", "./rcrd-graphics/src/**.cpp", "./rcrd-graphics/source/**.h" }
		
	configuration "not macosx"
		includedirs {"./rcrd-graphics/include", "./rcrd-graphics/lib/include", "./rcrd-graphics/lib/glfw/include", "./rcrd-graphics/lib/glfw/include"}
		libdirs{"./rcrd-graphics/lib/glfw/lib-vc2019/", "./rcrd-graphics/lib/glew/x64/"}
	configuration "macosx"
		sysincludedirs {"./rcrd-graphics/lib/include", "./rcrd-graphics/lib/glfw/include"}

	configuration "windows"
		defines {}
		links {}

	configuration "not windows"
		defines {}

	configuration "linux"
		defines {}

	configuration "macosx"
		defines {}

	configuration "android"
		defines {}

	configuration "Debug"
		defines {"DEBUG"}
		symbols "On"	

	configuration "Release"
		defines {"NDEBUG"}
		optimize "On"
