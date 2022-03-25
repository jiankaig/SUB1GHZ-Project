import subprocess
import sys

pid1 = subprocess.Popen([sys.executable, "server.py"])
pid1.stdin.write(b'192.168.18.16')
pid2 = subprocess.Popen([sys.executable, "web_esd_opcua.py"])