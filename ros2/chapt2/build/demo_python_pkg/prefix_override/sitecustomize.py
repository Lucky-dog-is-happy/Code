import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/lucky/Code/ros2/chapt2/install/demo_python_pkg'
