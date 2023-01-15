import os
import sys

print("ENGINE : Starting Python Engine...")

currentDir :str = os.path.dirname(__file__)
userDir = currentDir + "\\Resources\\Scripts"
engineDir = currentDir + "\\Resources\\Scripts\\EnginePy"

print("LOG : Adding following directory to sys.path :")
print(f"    User scripts dir: {userDir}")
print(f"    Engine .pyd dir : {engineDir}")

sys.path.insert(1, userDir) #Allow you to import modules from script folder
sys.path.insert(1, engineDir) #Allow to import Built-in modules