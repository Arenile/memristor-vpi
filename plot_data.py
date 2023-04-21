from matplotlib import pyplot as plt
import numpy as np
import csv

with open("./verilog_with_memrist.csv") as csvFile:
    data = csvFile.read()

    splitData = data.splitlines()

    x_vals = []
    y_vals = []

    for val in splitData:
        x_vals.append(val.split(",")[0])
        y_vals.append(val.split(",")[2])

    x_val_arr = np.array(x_vals[1:],dtype=float)
    y_val_arr = np.array(y_vals[1:],dtype=float)

    print(x_vals)
    print(y_vals)

    plt.plot(x_val_arr, y_val_arr, "k", label="Digital Memristor State")

with open("./verilog_with_memrist.csv") as csvFile:
    data = csvFile.read()

    splitData = data.splitlines()

    x_vals = []
    y_vals = []

    for val in splitData:
        x_vals.append(val.split(",")[0])
        y_vals.append(val.split(",")[1])

    x_val_arr = np.array(x_vals[1:],dtype=float)
    y_val_arr = np.array(y_vals[1:],dtype=float)

    print(x_vals)
    print(y_vals)

    plt.plot(x_val_arr, y_val_arr, "k--", label="Analog Memristor State")

plt.legend()
plt.xlabel("Simulation Time Step")
plt.ylabel("Memristor State")
plt.title("Memristor State Plot Against Ditigal Value")
plt.axvline(500, color = 'k', linestyle = "-.")

plt.show()

