#!/usr/bin/env python3
import sys
import subprocess
import re
import threading
from collections import defaultdict
import time

class PhiloMonitor:
    def __init__(self):
        self.philosophers = {}
        self.lock = threading.Lock()
        self.running = True

    def parse_line(self, line):
        # Parse format: "timestamp philosopher_id action"
        match = re.match(r'(\d+)\s+(\d+)\s+(.+)', line.strip())
        if match:
            timestamp = int(match.group(1))
            philo_id = int(match.group(2))
            action = match.group(3)
            return timestamp, philo_id, action
        return None

    def update_display(self):
        while self.running:
            with self.lock:
                if self.philosophers:
                    # Clear screen
                    print('\033[2J\033[H', end='')

                    # Header
                    max_id = max(self.philosophers.keys())
                    print("Philosopher Monitor")
                    print("=" * 60)

                    # Column headers
                    header = "Time".ljust(8)
                    for i in range(1, max_id + 1):
                        header += f"P{i}".ljust(15)
                    print(header)
                    print("-" * len(header))

                    # Get recent actions (last 20)
                    all_actions = []
                    for philo_id, actions in self.philosophers.items():
                        for timestamp, action in actions[-20:]:
                            all_actions.append((timestamp, philo_id, action))

                    # Sort by timestamp
                    all_actions.sort(key=lambda x: x[0])

                    # Display recent actions
                    for timestamp, philo_id, action in all_actions[-15:]:
                        row = str(timestamp).ljust(8)
                        for i in range(1, max_id + 1):
                            if i == philo_id:
                                # Color code actions
                                if "eating" in action:
                                    colored_action = f"\033[92m{action}\033[0m"  # Green
                                elif "sleeping" in action:
                                    colored_action = f"\033[94m{action}\033[0m"  # Blue
                                elif "thinking" in action:
                                    colored_action = f"\033[93m{action}\033[0m"  # Yellow
                                elif "died" in action:
                                    colored_action = f"\033[91m{action}\033[0m"  # Red
                                elif "fork" in action:
                                    colored_action = f"\033[96m{action}\033[0m"  # Cyan
                                else:
                                    colored_action = action
                                row += colored_action.ljust(24)  # Account for color codes
                            else:
                                row += "".ljust(15)
                        print(row)

                    # Current status
                    print("\nCurrent Status:")
                    status_row = "".ljust(8)
                    for i in range(1, max_id + 1):
                        if i in self.philosophers and self.philosophers[i]:
                            last_action = self.philosophers[i][-1][1]
                            if "eating" in last_action:
                                status = "\033[92m●\033[0m EAT"
                            elif "sleeping" in last_action:
                                status = "\033[94m●\033[0m SLP"
                            elif "thinking" in last_action:
                                status = "\033[93m●\033[0m THK"
                            elif "died" in last_action:
                                status = "\033[91m●\033[0m DIE"
                            else:
                                status = "●"
                        else:
                            status = "○"
                        status_row += status.ljust(20)
                    print(status_row)

            time.sleep(0.1)

    def monitor(self, args):
        # Start display thread
        display_thread = threading.Thread(target=self.update_display)
        display_thread.daemon = True
        display_thread.start()

        try:
            # Start philosopher process
            process = subprocess.Popen(['./philo'] + args,
                                     stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT,
                                     text=True)

            for line in process.stdout:
                parsed = self.parse_line(line)
                if parsed:
                    timestamp, philo_id, action = parsed
                    with self.lock:
                        if philo_id not in self.philosophers:
                            self.philosophers[philo_id] = []
                        self.philosophers[philo_id].append((timestamp, action))

                        # Keep only last 50 actions per philosopher
                        if len(self.philosophers[philo_id]) > 50:
                            self.philosophers[philo_id] = self.philosophers[philo_id][-50:]

        except KeyboardInterrupt:
            print("\nStopping monitor...")
        finally:
            self.running = False
            process.terminate()

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 monitor_philo.py <philo_args>")
        print("Example: python3 monitor_philo.py 5 800 200 200")
        sys.exit(1)

    monitor = PhiloMonitor()
    monitor.monitor(sys.argv[1:])

if __name__ == "__main__":
    main()