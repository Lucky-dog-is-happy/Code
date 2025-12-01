import rclpy
from rclpy.node import Node

class PersonNode(Node):
    def __init__(self, node_name:str, name:str, age:int) -> None:
        super().__init__(node_name)
        print('PersonNode __init__')
        self.age = age
        self.name = name

    def eat(self, food_name:str):
        self.get_logger().info(f"my name is {self.name}, {self.age} old, I am eating {food_name}")

def main():
    rclpy.init()
    node = PersonNode('person_node', 'lucky', 18)
    node.eat('rice')
    rclpy.spin(node)
    rclpy.shutdown()
