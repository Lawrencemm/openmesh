from conans import ConanFile, CMake, tools


class OpenmeshConan(ConanFile):
    name = "OpenMesh"
    version = "7.1"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "https://github.com/lawrencem99/openmesh.git"
    description = "<Description of Openmesh here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False}
    generators = "cmake"
    scm = {
        "type": "git",
        "url": "https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh.git",
        "revision": "OpenMesh-"+version,
        "subfolder": "OpenMesh",
    }

    def configure(self):
        if self.settings.compiler == "Visual Studio":
            del self.options.fPIC

    def source(self):
        # disable documentation build
        tools.replace_in_file("OpenMesh/CMakeLists.txt", "add_subdirectory (Doc)", "")

        # disable "d" suffix for Debug build
        tools.replace_in_file("OpenMesh/CMakeLists.txt", 'set (CMAKE_DEBUG_POSTFIX "d")', '')

        # do not build both shared and static library for non-Windows builds
        tools.replace_in_file("OpenMesh/src/OpenMesh/Tools/CMakeLists.txt", "target_link_libraries (OpenMeshToolsStatic OpenMeshCoreStatic)", "")
        tools.replace_in_file("OpenMesh/src/OpenMesh/Tools/CMakeLists.txt", "add_dependencies (fixbundle OpenMeshToolsStatic)", "")

    def build(self):
        # choose shared/static for Windows builds
        tools.replace_in_file("OpenMesh/CMakeLists.txt", "set( OPENMESH_BUILD_SHARED false", "set( OPENMESH_BUILD_SHARED " + ("true" if self.options.shared else "false"))

        # do not build both shared and static library for non-Windows builds
        tools.replace_in_file("OpenMesh/src/OpenMesh/Core/CMakeLists.txt", "SHAREDANDSTATIC", "SHARED" if self.options.shared else "STATIC")
        tools.replace_in_file("OpenMesh/src/OpenMesh/Tools/CMakeLists.txt", "SHAREDANDSTATIC", "SHARED" if self.options.shared else "STATIC")

        cmake = CMake(self)

        if self.settings.compiler != "Visual Studio":
            cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = self.options.fPIC

        cmake.configure(defs={"BUILD_APPS": "OFF"}, source_folder="OpenMesh")
        cmake.build()
        cmake.install()

    def package(self):
        pass
        # self.copy("*", dst="include/OpenMesh", src="openmesh/src/OpenMesh")
        # self.copy("*.lib", dst="lib", keep_path=False)
        # self.copy("*.dll", dst="bin", keep_path=False)
        # self.copy("*.so", dst="lib", keep_path=False)
        # self.copy("*.dylib", dst="lib", keep_path=False)
        # self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["OpenMeshCore", "OpenMeshTools"]
