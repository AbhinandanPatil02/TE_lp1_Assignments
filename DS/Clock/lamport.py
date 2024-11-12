class LogicalClock:
    def __init__(self, process_id):
        self.clock = 0
        self.process_id = process_id  # Unique ID for each process

    # Get current logical clock value
    def get_curr_time(self):
        return self.clock

    # Increment clock on an internal event (tick)
    def tick(self):
        self.clock += 1
        print(f"Process {self.process_id} internal tick. Clock: {self.clock}")

    # Update clock when receiving a message from another process
    def update_on_receive(self, received_time):
        self.clock = max(self.clock, received_time) + 1
        print(f"Process {self.process_id} received message. Updated Clock: {self.clock}")

    # Simulate sending a message with the current clock value
    def send_message(self):
        print(f"Process {self.process_id} sending message with time: {self.clock}")
        return self.clock

def main():
    # Initialize two logical clock instances (representing processes)
    c1 = LogicalClock(process_id=1)
    c2 = LogicalClock(process_id=2)

    print("\n=== Initial Time ===")
    print(f"Time initial c1 : {c1.get_curr_time()}")
    print(f"Time initial c2 : {c2.get_curr_time()}")

    # Simulate internal events (ticks)
    c1.tick()  # Event at process c1
    c2.tick()  # Event at process c2

    print("\n=== After Internal Ticks ===")
    print(f"Time after tick c1 : {c1.get_curr_time()}")
    print(f"Time after tick c2 : {c2.get_curr_time()}")

    # Simulate message exchange: c1 sends a message to c2
    print("\n=== Message Exchange: c1 -> c2 ===")
    message_time_c1 = c1.send_message()
    c2.update_on_receive(message_time_c1)

    # Simulate message exchange: c2 sends a message to c1
    print("\n=== Message Exchange: c2 -> c1 ===")
    message_time_c2 = c2.send_message()
    c1.update_on_receive(message_time_c2)

    print("\n=== Final Clock Times ===")
    print(f"Final Time c1: {c1.get_curr_time()}")
    print(f"Final Time c2: {c2.get_curr_time()}")

    # Check synchronization status
    if c1.get_curr_time() == c2.get_curr_time():
        print("Both clocks are synchronized.")
    elif c1.get_curr_time() > c2.get_curr_time():
        print("c2 is running behind.")
    else:
        print("c1 is running behind.")

if __name__ == "__main__":
    main()
