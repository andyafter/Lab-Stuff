class DataToMatrix():
    marker_data = []

    def __init__(self):
        self.get_data("./data/data.txt")

    def get_data(self, fname):
        f = open(fname, 'r')
        n_loop = 0
        while n_loop < 200000:
            n_loop += 1          # for getting testing data
            line = f.readline()
            if not line:
                break
            if line[:2] == "3d":
                self.num_dframes += 1
                d = line.split()[1:]
                data = []
                # number of vectors
                num = int(d[0])
                for k in range(num):
                    # data stores all the points inside the marker
                    # every group is 4 elements, the second element would be something like 1.000][227.002
                    # very dirty code, just use it
                    i = k*4
                    self.marker_ids[int(d[i+1][1:])] = 1
                    vec_marker = [float(d[i+2].split('[')[-1]), float(d[i+3]), float(d[i+4].split(']')[0])]
                    data.append(vec_marker)
                self.marker_data.append(data)
        f.close()


