#include <string.h>
#include "rclcpp/rclcpp.hpp"

class PersonNode:public rclcpp::Node
{
  private:
    std::string name_;
    int age_;

  public:
    PersonNode(const std::string &node_name,
        const std::string &name,
        const int &age) : Node(node_name)
  {
    this->name_ = name;
    this->age_ = age;
  };

    void eat(const std::string &food_name)
    {
      RCLCPP_INFO(this->get_logger(), "I am %s, %d years old, eating %s", name_.c_str(), age_, food_name.c_str());  
    };
};

int main(int agrc, char **agrv)
{
  rclcpp::init(agrc, agrv);
  auto node = std::make_shared<PersonNode>("cpp_node", "lucky", 18);
  node->eat("fishros");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}
