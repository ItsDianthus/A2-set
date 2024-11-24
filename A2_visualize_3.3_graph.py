import csv
import matplotlib.pyplot as plt

threshold_num = []
merge_insert_random = []
merge_insert_reversed = []
merge_insert_almost_sorted = []

with open('A2_data_threshold_finder_.txt', 'r', encoding='utf-8') as file:
    reader = csv.reader(file, delimiter=';')
    next(reader)
    for row in reader:
        threshold_num.append(int(row[1].strip()))
        merge_insert_random.append(int(row[2].strip()))
        merge_insert_reversed.append(int(row[3].strip()))
        merge_insert_almost_sorted.append(int(row[4].strip()))

plt.plot(threshold_num, merge_insert_random, marker='o', label='Merge+Insert Random', color='b')
plt.plot(threshold_num, merge_insert_reversed, marker='s', label='Merge+Insert Reversed', color='g')
plt.plot(threshold_num, merge_insert_almost_sorted, marker='^', label='Merge+Insert Almost Sorted', color='r')

plt.xlabel('Threshold Num')
plt.ylabel('Time (ms)')
plt.title('Performance Analysis of Merge+Insert')
plt.legend()
plt.grid(True)
plt.show()
