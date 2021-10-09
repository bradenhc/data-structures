from conans import ConanFile, CMake, tools


class HcDatastructsConan(ConanFile):
    name = "hc_datastructs"
    version = "0.1.0"
    license = "MIT"
    author = "Braden Hitchcock <developer.hitchcock@gmail.com>"
    url = "https://github.com/bradenhc/data-structures"
    description = "<Description of HcDatastructs here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    settings = "os", "compiler", "build_type", "arch"

    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    generators = "cmake_find_package"
    export_sources = "CMakeLists.txt, LICENSE, README.md, vector/*"

    def build_requirements(self):
        self.build_requires("gtest/1.10.0")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collectlibs(self)
