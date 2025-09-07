import subprocess # allows to run other programs or scripts from Python
import sys

# Kill all processes
subprocess.run([sys.executable, "kill_processes.py"]) # blocking

# Start FastAPI
print("Starting FastAPI...")
subprocess.Popen([sys.executable, "-m", "uvicorn", "app_fastapi:app"]) # non-blocking
