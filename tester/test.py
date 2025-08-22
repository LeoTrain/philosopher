from collections import deque
import subprocess
import time
import os

def parse_line(line: str):
    parts = line.strip().split(" ", 2)
    if len(parts) < 3:
        return None
    return parts[0], parts[1], parts[2]

def update_state(states: dict, philo_id: str, timestamp: str, action: str):
    if philo_id not in states:
        states[philo_id] = deque(maxlen=3)
    padded_action = action.ljust(12)
    states[philo_id].append(f"[{timestamp} {padded_action}]")

def display_states(states: dict, current_time: str, nb_philos: int):
    os.system("clear")
    print(f"Time: {current_time} ms\n")
    for pid in range(1, nb_philos + 1):
        pid_str = str(pid)
        history = "".join(states[pid_str]) if pid_str in states else "[waiting]"
        print(f"{pid}: {history}")

def run_philosophers(nb_philos: int = 5):
    process = subprocess.Popen(
        ["../philo", str(nb_philos), "800", "200", "200", "15"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1
    )
    states = {}
    try:
        for line in process.stdout:
            parsed = parse_line(line)
            if not parsed:
                continue
            timestamp, philo_id, action = parsed
            update_state(states, philo_id, timestamp, action)
            display_states(states, timestamp, nb_philos)
            time.sleep(0.05)
    except KeyboardInterrupt:
        process.terminate()
    process.wait()

if __name__ == "__main__":
    run_philosophers()
