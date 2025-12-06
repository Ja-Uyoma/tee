from conan import ConanFile
from conan.tools.cmake import CMake

class TeeRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("hedley/15")

    def build_requirements(self):
        self.test_requires("cmocka/1.1.7")
