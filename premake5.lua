-- premake5.lua
workspace "CS2010"
   configurations { "Debug", "Release" }

function setupProject(name, mainFile)
   project(name)
      kind "ConsoleApp"
      language "C++"
      cppdialect "C++17"
      targetdir ("bin/%{cfg.buildcfg}" .. name)

      files { "src/**.h", "include/**.h", mainFile }
      includedirs { "include" }

      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"

      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"
end

setupProject("pgm1", "src/SlackT_pgm1.cpp")
setupProject("pgm2", "src/SlackT_pgm2.cpp")
setupProject("pgm3", "src/SlackT_pgm3.cpp")
setupProject("pgm4", "src/SlackT_pgm4.cpp")
