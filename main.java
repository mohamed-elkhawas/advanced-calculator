import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

class Calculator {
    HashMap<String, HashMap<Integer, Double>> eqns;
    int eqn_n;
   
    public Calculator() {
        eqns = new HashMap<>();
        eqn_n = 0;
        get_eqns("eqns.txt");
    }

    public Calculator(String path) {
        eqns = new HashMap<>();
        eqn_n = 0;
        get_eqns(path);
    }

    public void try_to_add(String key, double val, int l) {
        try {
            eqns.get(key).put(l, eqns.get(key).get(l) + val);
        } catch (NullPointerException e) {
            try {
                eqns.get(key).put(l, val);
            } catch (NullPointerException ex) {
                eqns.put(key, new HashMap<>());
                eqns.get(key).put(l, val);
            }
        }
    }

    public void assign_num(String part, int k, int l, int d) {
        String key = (d == 0) ? part.substring(k) : "d";
        if (part.substring(0, k).equals("") || part.substring(0, k).equals("+")) {
            try_to_add(key, 1, l);
        } else if (part.substring(0, k).equals("-")) {
            try_to_add(key, -1, l);
        } else {
            try_to_add(key, Double.parseDouble(part.substring(0, k)), l);
        }
    }

    public void add_param(String part, int l) {
        int d = 1;
        for (int k = 0; k < part.length(); k++) {
            if (!".+-0123456789".contains(Character.toString(part.charAt(k)))) {
                assign_num(part, k, l, 0);
                d = 0;
                break;
            }
        }
        if (d == 1) {
            assign_num(part, part.length(), l, 1);
        }
    }

    public void cut_parts(String line_half, int eqn_n) {
        int j = 0;
        for (int i = 0; i < line_half.length(); i++) {
            if (line_half.charAt(i) == '+' || line_half.charAt(i) == '-') {
                if (i != 0) {
                    String part = line_half.substring(j, i);
                    add_param(part, eqn_n);
                }
                j = i;
            }
        }
        String part = line_half.substring(j);
        add_param(part, eqn_n);
    }

    public void get_eqns(String path) {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            int eqn_n = 0;
            while ((line = br.readLine()) != null) {
                line = line.replace(" ", "");
                String[] parts = line.split("=");
                String left = parts[0].trim();
                String right = parts[1].trim();
                cut_parts(left, eqn_n);
                if (right.charAt(0) != '+' && right.charAt(0) != '-') {
                    right = '+' + right;
                }
                right = right.replace('+', '@');
                right = right.replace('-', '+');
                right = right.replace('@', '-');
                cut_parts(right, eqn_n);
                eqn_n++;
            }
            this.eqn_n = eqn_n;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public HashMap<String, Double> add_eqn(int num1, int num2, int sub) {
        HashMap<String, Double> eqn = new HashMap<>();
        for (String param : eqns.keySet()) {
            try {
                if (sub == 0) {
                    eqn.put(param, eqns.get(param).get(num1) + eqns.get(param).get(num2));
                } else {
                    eqn.put(param, eqns.get(param).get(num1) - eqns.get(param).get(num2));
                }
            } catch (Exception e) {
                try {
                    if (!((eqns.get(param).get(num1) == null) || (eqns.get(param).get(num1) == 0.0))){
                       eqn.put(param, eqns.get(param).get(num1));
                    }
                    else{
                        if (!((eqns.get(param).get(num2) == null) || (eqns.get(param).get(num2) == 0.0))){
                            if (sub == 0) {
                                eqn.put(param, eqns.get(param).get(num2));
                            } else {
                                eqn.put(param, -eqns.get(param).get(num2));
                            }
                        }
                    }
                } catch (Exception e1) {}
            }
        }
        if (!eqn.containsKey("d")) {
            eqn.put("d", 0.0);
        }

        return eqn;
    }

    public void print_eqn(HashMap<String, Double> eqn) {
        String out = "";
        boolean first = true;
        for (String param : eqn.keySet()) {
            try{
                if (!param.equals("d")) {
                    if (eqn.get(param) != 0) {
                        if (first) {
                            out += eqn.get(param) + param + " ";
                            first = false;
                        } else {
                            if (eqn.get(param) > 0) {
                                out += "+";
                            }
                            if (eqn.get(param) == 1) {
                                out += param + " ";
                            } else {
                                out += eqn.get(param) + param + " ";
                            }
                        }
                    }
                }
            } catch (Exception e) {}
        }
        System.out.println(out + "= " + eqn.get("d"));
    }

    public List<List<String>> getUniqueArr() {
        List<List<String>> unique = new ArrayList<>();
        for (int i = 0; i < eqn_n; i++) {
            unique.add(new ArrayList<>());
        }
        List<Integer> skip = new ArrayList<>();
        for (String param : eqns.keySet()) {
            if (param.equals("d")) {
                continue;
            }
                
            for (HashMap.Entry <Integer, Double> eqn : eqns.get(param).entrySet()) {
                int eqnNumbers = eqn.getKey();
                
                if (skip.contains(eqnNumbers)) {
                    continue;
                }
                if (eqns.get(param).size() == 1) {
                    unique.set(eqnNumbers, Collections.singletonList(param));
                    skip.add(eqnNumbers);
                } else {
                    unique.get(eqnNumbers).add(param);
                }
            }
        }
        while (true) {
            boolean isUnique = true;
            List<String> params = new ArrayList<>();
            for (int i = 0; i < unique.size(); i++) {
                if (unique.get(i).size() > 1) {
                    if (isUnique) {
                        isUnique = false;
                        unique.set(i, Collections.singletonList(unique.get(i).get(0)));
                        params.add(unique.get(i).get(0));
                    } else {
                        for (String param : params) {
                            if (unique.get(i).contains(param)) {
                                unique.get(i).remove(param);
                                if (unique.get(i).size() == 1) {
                                    params.add(unique.get(i).get(0));
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (isUnique) {
                break;
            }
        }
        return unique;
    }

    public HashMap<String, Double> iterate(HashMap<String, Double> old_val, List<List<String>> unique_list, HashMap<String, Boolean> solved) {
        HashMap<String, Double> new_val = new HashMap<>();
        for (int i = 0; i < unique_list.size(); i++) {
            String param = (String) unique_list.get(i).get(0);
            if (!solved.get(param)) {
                double factor = this.eqns.get(param).get(i);
                double sum;
                try {
                    sum = this.eqns.get("d").get(i);
                } catch (Exception e) {
                    sum = 0;
                }
                for (String j : this.eqns.keySet()) {
                    if (!j.equals("d") && !j.equals(param)) {
                        try {
                            try {
                                sum += this.eqns.get(j).get(i) * new_val.get(j);
                            } catch (Exception e) {
                                sum += this.eqns.get(j).get(i) * old_val.get(j);
                            }
                        } catch (Exception e) {
                            // do nothing
                        }
                    }
                }
                new_val.put(param, -sum / factor);
            } else {
                new_val.put(param, old_val.get(param));
            }
        }
        return new_val;
    }

    public int solve() {
        List<List<String>> unique = getUniqueArr();
        for (List<String> item : unique) {
            if (item.isEmpty()) {
                System.out.println("error wrong equations");
                return 1;
            }
        }
        HashMap<String, ArrayList<Double>> diff = new HashMap<>();
        HashMap<String, Boolean> solved = new HashMap<>();
        HashMap<String, Double> old_val = new HashMap<>();
        HashMap<String, Double> new_val = new HashMap<>();
        HashMap<String, Double> saved_val = new HashMap<>();
        HashMap<String, Double> saved_val2 = new HashMap<>();
        for (String param : eqns.keySet()) {
            if (!param.equals("d")) {
                old_val.put(param, 0.0);
                diff.put(param, new ArrayList<Double>());
                solved.put(param, false);
            }
        }
        int it = 0;
        while (true) {
            boolean finished = true;
            new_val = iterate(old_val, unique, solved);
            for (String param : new_val.keySet()) {
                diff.get(param).add(Math.abs(new_val.get(param) - old_val.get(param)));
                if (Math.abs(new_val.get(param) - old_val.get(param)) > 0.001) {
                    finished = false;
                }
            }
            if (finished) {
                break;
            }
            old_val = new_val;
            if (it == 0) {
                saved_val = new_val;
            }
            if (it == 1) {
                saved_val2 = new_val;
            }
            it++;

            if (it == 3) {
                for (String param : diff.keySet()) {
                    if (diff.get(param).get(2) == diff.get(param).get(1) && diff.get(param).get(2) != 0) {
                        old_val.put(param, ((saved_val.get(param) - saved_val2.get(param)) / 2) + saved_val2.get(param));
                        it = 0;
                        diff.put(param, new ArrayList<>());
                    } else {
                        if (!(diff.get(param).get(2) < diff.get(param).get(1) && diff.get(param).get(1) < diff.get(param).get(0))) {
                            if (diff.get(param).get(2) != 0) {
                                old_val.put(param, saved_val.get(param) / 3);
                                it = 0;
                                diff.put(param, new ArrayList<>());
                            } else {
                                solved.put(param, true);
                                diff.put(param, new ArrayList<>());
                            }
                        } else {
                            diff.put(param, new ArrayList<>());
                        }
                    }
                }
            }
        }
        for (String result : new_val.keySet()) {
            System.out.println(result + " = " + Math.round(new_val.get(result)*100000)/100000.0);
        }
    
    return 0;
    }
}



public class main{

    public static void main(String []args){
        Calculator c = new Calculator();
        c.print_eqn(c.add_eqn(0,1,0));
        c.solve();
    }
}