class Dive:

    def __init__(self):
        self.depth = 0
        self.horizontal = 0
        self.aim = 0

        file = open("../input/day2.txt", "r")
        self.data_list = file.readlines()

    def execute_command(self, command):
        # Command [type, val]
        type = command[0]
        val = int(command[1])
        if type == "forward" :
            self.horizontal += val
            self.depth += self.aim * val
        elif type == "down" :
            self.aim += val
        elif type == "up" :
            self.aim -= val

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
