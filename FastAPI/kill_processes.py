import psutil # library for interacting with system processes and resources (CPU, memory, network, etc.).


def find_processes_by_port(port):
    matching_pids = set()

    for conn in psutil.net_connections(kind="inet"):
        # Extract local port safely
        try:
            local_port = conn.laddr.port
        except AttributeError:
            local_port = conn.laddr[1] if conn.laddr else None

        # Match the port and listening state
        if local_port == port and conn.status == psutil.CONN_LISTEN:
            pid = conn.pid
            if pid and pid != 0 and psutil.pid_exists(pid):
                try:
                    proc = psutil.Process(pid)
                    print(f"🔍 Found PID {pid} ({proc.name()}) on port {port}")
                    matching_pids.add(pid)
                except (psutil.NoSuchProcess, psutil.AccessDenied):
                    # Skip invalid or inaccessible processes
                    continue

    return list(matching_pids)




def kill_processes(pids):
    for pid in pids:
        try:
            proc = psutil.Process(pid)
            print(f"🔧 Terminating PID {pid} ({proc.name()})...")
            proc.terminate()          # Ask process to terminate

            try:
                proc.wait(timeout=3)  # Wait up to 3s
                print(f"✅ Killed PID {pid}")
            except psutil.TimeoutExpired:
                print(f"⚠️ PID {pid} did not exit in time. Forcing kill...")
                proc.kill()  # Force kill if terminate didn’t work
                proc.wait(timeout=3)
                print(f"✅ Force killed PID {pid}")
        except psutil.NoSuchProcess:
            print(f"ℹ️ PID {pid} already exited.")
        except psutil.AccessDenied:
            print(f"❌ Permission denied to kill PID {pid}.")
        except Exception as e:
            print(f"❌ Unexpected error with PID {pid}: {e}")


def main():
    ports = [8000, 9999]   # Ports to scan
    all_pids = set()       # Collect unique PIDs here

    for port in ports:
        pids = find_processes_by_port(port)
        if pids:
            print(f"🔍 Found listening PIDs on port {port}: {', '.join(map(str, pids))}")
            all_pids.update(pids)
        else:
            print(f"✅ No listening processes found on port {port}")

    if all_pids:
        kill_processes(all_pids)
        return list(all_pids)
    else:
        print("✅ No processes to kill.")
        return []


if __name__ == "__main__":
    main()