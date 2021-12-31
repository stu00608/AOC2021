
class BinaryDiagnostic :

    def __init__(self):
        self.dec_gamma_rate = 0
        self.dec_epsilon_rate = 0
        self.bin_gamma_rate = []
        self.bin_epsilon_rate = []
        self.data_mat = []

        file = open("../input/day3.txt", "r")
        for line in file :
            self.data_mat.append(line.strip("\n"))

    def run(self):

        for i in range(len(self.data_mat[0])):
            bit_indicator = 0
            for j in range(len(self.data_mat)):
                bit = self.data_mat[j][i]
                if bit == '0':
                    bit_indicator -= 1
                elif bit == '1':
                    bit_indicator += 1
                else:
                    print("Error")

            print(bit_indicator) 
            if bit_indicator > 0 :
                # Most common is 1
                self.bin_gamma_rate.append("1")
                self.bin_epsilon_rate.append("0")
            elif bit_indicator < 0 :

                self.bin_gamma_rate.append("0")
                self.bin_epsilon_rate.append("1")
                # Most common is 0
                pass
            else:
                print("bit number is same")
        
        print(self.bin_gamma_rate)
        self.dec_gamma_rate = int( ''.join(self.bin_gamma_rate), 2 )
        self.dec_epsilon_rate = int( ''.join(self.bin_epsilon_rate), 2 )
        # print(''.join(self.bin_gamma_rate))
        print(self.dec_gamma_rate * self.dec_epsilon_rate)

if __name__ == '__main__':
    app = BinaryDiagnostic()
    app.run()