from conan import ConanFile
from conan.tools.cmake import cmake_layout

class TeeRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("cmocka/1.1.5")

    def layout(self):
        cmake_layout(self)