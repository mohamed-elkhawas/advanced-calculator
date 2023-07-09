class Calculator:
    eqns = {}
    eqn_n = 0
    def __init__(self, path="eqns.txt"):
        self.get_eqns(path)

    def try_to_add(self, key, val, l):
        try:
            self.eqns[key][l] += val
        except:
            try:
                self.eqns[key][l] = val
            except:
                self.eqns[key] = {l: val}

    def assign_num(self, part, k, l, d=0):

        key = part[k:] if d == 0 else 'd'

        if part[:k] in ['', '+']:
            self.try_to_add(key, 1, l)
        elif part[:k] == '-':
            self.try_to_add(key, -1, l)
        else:
            self.try_to_add(key, float(part[:k]), l)

    def add_param(self, part, l):
        d = 1
        for k in range(len(part)):
            if part[k] not in ['.', '+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']:
                self.assign_num(part, k, l)
                d = 0
                break
        if d == 1:
            self.assign_num(part=part, k=len(part), l=l, d=1)

    def cut_parts(self, line_half, eqn_n):
        j = 0
        for i in range(len(line_half)):
            if line_half[i] in ["+", "-"]:
                if i != 0:
                    part = line_half[j:i]
                    self.add_param(part, eqn_n)
                j = i
        part = line_half[j:]
        self.add_param(part, eqn_n)

    def get_eqns(self, path):
        with open(path, "r") as f:
            lines = f.readlines()

        for eqn_n in range(len(lines)):
            lines[eqn_n] = lines[eqn_n].replace(" ", "")
            left, right = lines[eqn_n].strip().split("=")
            self.cut_parts(left, eqn_n)

            if right[0] not in ["+", "-"]:
                right = '+' + right

            right = right.replace('+', '@')
            right = right.replace('-', '+')
            right = right.replace('@', '-')

            self.cut_parts(right, eqn_n)
        self.eqn_n = eqn_n

    def add_eqn(self, num1, num2, sub=0):
        eqn = {}
        for param in self.eqns:
            try:
                if sub == 0:
                    eqn[param] = self.eqns[param][num1] + self.eqns[param][num2]
                else:
                    eqn[param] = self.eqns[param][num1] - self.eqns[param][num2]
            except:
                try:
                    eqn[param] = self.eqns[param][num1]
                except:
                    try:
                        if sub == 0:
                            eqn[param] = self.eqns[param][num2]
                        else:
                            eqn[param] = - self.eqns[param][num2]
                    except:
                        pass
        try:
            eqn['d']
        except:
            eqn['d'] = 0

        return eqn

    def print_eqn(self, eqn):
        out = ""
        first = True
        for param in eqn:
            if param != "d":
                if eqn[param] != 0:
                    if first:
                        out += f"{eqn[param]}{param} "
                        first = False
                    else:
                        if eqn[param] > 0:
                            out += "+"
                        if eqn[param] == 1:
                            out += f"{param} "
                        else:
                            out += f"{eqn[param]}{param} "
        print(out + f"= {eqn['d']}")

    def get_unique_arr(self):
        unique = []
        for i in range(self.eqn_n + 1):
            unique.append([])

        skip = []
        for param in self.eqns:
            if param == 'd':
                continue
            for eqn_number in self.eqns[param]:
                if eqn_number in skip:
                    continue
                if len(self.eqns[param]) == 1:
                    unique[eqn_number] = [param]
                    skip.append(eqn_number)
                else:
                    unique[eqn_number].append(param)

        while True:
            is_unique = True
            params = []
            for i in range(len(unique)):
                if len(unique[i]) > 1:
                    if is_unique:
                        is_unique = False
                        unique[i] = [unique[i][0]]
                        params.append(unique[i][0])
                    else:
                        for param in params:
                            if param in unique[i]:
                                unique[i].remove(param)
                                if len(unique[i]) == 1:
                                    params.append(unique[i][0])
                                    break

            if is_unique:
                break

        return unique

    def iterate(self, old_val, unique_list, solved):
        new_val = {}
        for i in range(len(unique_list)):
            param = unique_list[i][0]
            if not solved[param]:
                factor = self.eqns[param][i]
                try:
                    sum = self.eqns['d'][i]
                except:
                    sum = 0
                for j in self.eqns:
                    if self.eqns[j] != 'd' and j != param:
                        try:
                            try:
                                sum += self.eqns[j][i] * new_val[j]
                            except:
                                sum += self.eqns[j][i] * old_val[j]
                        except:
                            pass
                new_val[param] = - sum / factor
            else:
                new_val[param] = old_val[param]

        return new_val

    def solve(self):  # solve by iterations
        unique = self.get_unique_arr()
        for item in unique: # check if it is solvable
            if item == []:
                print("error wrong equations")
                return 1
        diff, solved, old_val = {}, {}, {}
        for param in self.eqns:  # start estimated value
            if param != 'd':
                old_val[param] = 0
                diff[param] = []
                solved[param] = False
        it = 0
        while True:
            finished = True
            new_val = self.iterate(old_val, unique, solved)
            for param in new_val:
                diff[param].append(abs(new_val[param] - old_val[param]))
                if abs(new_val[param] - old_val[param]) > 0.001:
                    finished = False
            if finished:
                break
            old_val = new_val

            if it == 0:
                saved_val = new_val
            if it == 1:
                saved_val2 = new_val
            it += 1

            if it == 3:
                for param in diff:
                    if (diff[param][2] == diff[param][1]) and diff[param][2] != 0:
                        old_val[param] = ((saved_val[param] - saved_val2[param]) / 2) + saved_val2[param]
                        it = 0
                        diff[param] = []
                    else:
                        if not (diff[param][2] < diff[param][1] and diff[param][1] < diff[param][0]):
                            if diff[param][2] != 0:
                                old_val[param] = saved_val[param] / 3
                                it = 0
                                diff[param] = []
                            else:
                                solved[param] = True
                                diff[param] = []
                        else:
                            diff[param] = []

        for result in new_val:
            print(f"{result} = {round(new_val[result], 5)}")

c = Calculator()
c.print_eqn(c.add_eqn(0,1,sub=0))
c.solve()