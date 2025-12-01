import rclpy
from demo_python_pkg.person_node import PersonNode

class WriterNode(PersonNode):
    def __init__(self,node_name:str, name:str, age:int, book:str) -> None:
        super().__init__(node_name, name, age)
        print('WriteNode __init__')
        self.book = book

def main():
    rclpy.init()
    node = WriterNode('person_node', 'lucky', 18, 'how to crime')
    node.eat('fish')
    rclpy.spin(node)
    rclpy.shutdown()
