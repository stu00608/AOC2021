class Dive:

    def __init__(self):
        self.depth = 0
        self.horizontal = 0

        file = open("../input/day2.txt", "r")
        self.data_list = file.readlines()

    def execute_command(self, command):
        # Command [type, val]
        if command[0] == "forward" :
            self.horizontal += int(command[1])
        elif command[0] == "down" :
            self.depth += int(command[1])
        elif command[0] == "up" :
            self.depth -= int(command[1])

    def run(self):
        # Run the main program.
        for data in self.data_list :
            command = data.split()
            self.execute_command(command)

    def show_data(self):
        print(f"Horizontal : {self.horizontal}, Depth : {self.depth}")

if __name__ == '__main__':

    app = Dive()
    app.run()
    app.show_data()
