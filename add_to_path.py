import os
import subprocess
directory = f'{os.getcwd()}{os.path.sep}touch'
print(directory)
subprocess.run(['setx', f'path;{directory}'], shell=True)