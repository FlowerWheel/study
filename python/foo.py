
class Foo:
    """hello world"""
    # static member declarations
    version = 0.1

    # instance member declarations
    def __init__(self, nm="default"):
        """ constructor """
        self.name = nm

    def show_name(self):
        print(self.name)
        print(self.__class__.__name__)

    def show_version(self):
        print(self.version)
