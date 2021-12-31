
class BinaryDiagnostic :

    def __init__(self):
        self.bin_oxygen_rate = []
        self.bin_co2_rate = []
        self.dec_oxygen_rate = 0
        self.dec_co2_rate = 0
        self.data_mat = []


        file = open("../input/day3.txt", "r")
        for line in file :
            self.data_mat.append(line.strip("\n"))

    def run(self):


        self.bin_oxygen_rate = self.data_mat
        for i in range(len(self.bin_oxygen_rate[0])):
            # i also be the position

            if len(self.bin_oxygen_rate) == 1:
                break

            zero_data = []
            one_data = []
            for j in range(len(self.bin_oxygen_rate)):
                bit = self.bin_oxygen_rate[j][i]
                if bit == '0':
                    zero_data.append(self.bin_oxygen_rate[j])
                elif bit == '1':
                    one_data.append(self.bin_oxygen_rate[j])
                else:
                    print("Error")

            if len(one_data) > len(zero_data) :
                self.bin_oxygen_rate = one_data
            elif len(zero_data) > len(one_data) :
                self.bin_oxygen_rate = zero_data
            else:
                self.bin_oxygen_rate = one_data

        print(self.bin_oxygen_rate)


        self.bin_co2_rate = self.data_mat
        for i in range(len(self.bin_co2_rate[0])):
            # i also be the position

            if len(self.bin_co2_rate) == 1:
                break

            zero_data = []
            one_data = []
            for j in range(len(self.bin_co2_rate)):
                bit = self.bin_co2_rate[j][i]
                if bit == '0':
                    zero_data.append(self.bin_co2_rate[j])
                elif bit == '1':
                    one_data.append(self.bin_co2_rate[j])
                else:
                    print("Error")

            if len(one_data) > len(zero_data) :
                self.bin_co2_rate = zero_data
            elif len(zero_data) > len(one_data) :
                self.bin_co2_rate = one_data
            else:
                self.bin_co2_rate = zero_data

        print(self.bin_co2_rate)

        print( int(self.bin_oxygen_rate[0], 2) * int(self.bin_co2_rate[0], 2) )

if __name__ == '__main__':
    app = BinaryDiagnostic()
    app.run()