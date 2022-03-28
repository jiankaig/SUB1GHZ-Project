#! /bin/sh
#export PYTHONPATH="C:\\Users\User\AppData\Local\Microsoft\WindowsApps\python"
export PYTHONPATH="C:\Users\User\AppData\Local\Programs\Python\Python39\python"
echo $PYTHONPATH
# where python
echo "running web_esd_opcua.py"
python3 web_esd_opcua.py

echo "running server.py"
python3 server.py

